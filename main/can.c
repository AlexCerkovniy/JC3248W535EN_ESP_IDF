#include "can.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "board.h"

static SemaphoreHandle_t can_mutex;
static twai_status_info_t can_status = {0};
static bool auto_recovery = false;
static bool is_error_passive = false;

static void can_task(void* arg);

static const char *TAG = "CAN";

void can_init(void) {
    twai_general_config_t g_config = {
        .controller_id = 0,
        .mode = TWAI_MODE_NORMAL,
        .tx_io = CAN_PIN_TX,
        .rx_io = CAN_PIN_RX,
        .clkout_io = TWAI_IO_UNUSED,
        .bus_off_io = TWAI_IO_UNUSED,
        .tx_queue_len = 3,
        .rx_queue_len = 10,
        .alerts_enabled = TWAI_ALERT_ERR_ACTIVE | TWAI_ALERT_BUS_RECOVERED |TWAI_ALERT_BUS_ERROR | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_OFF,
        .clkout_divider = 0,
        .intr_flags = ESP_INTR_FLAG_LEVEL1 /* | ESP_INTR_FLAG_IRAM */,
        .general_flags = {0}
    };

    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();

    esp_err_t res = twai_driver_install(&g_config, &t_config, &f_config);
    if (res == ESP_OK) {
        ESP_LOGI(TAG, "Driver initialized!");
        auto_recovery = true;
    }
    else if (res == ESP_ERR_INVALID_ARG) {
        ESP_LOGE(TAG, "Invalid arguments!");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
    }
    else if (res == ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "Driver is already installed!");
    }
    else if (res == ESP_ERR_NO_MEM) {
        ESP_LOGE(TAG, "Out of memory!");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
    }
    else {
        ESP_LOGE(TAG, "Couldn't install CAN driver! Rebooting...");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
    }

    ESP_ERROR_CHECK(twai_start());
    is_error_passive = false;

    /* Create task */
    can_mutex = xSemaphoreCreateMutex();
    xTaskCreate(can_task, "can task", 4800, NULL, 3 /* Higher than UI task */, NULL);
}

esp_err_t can_send_receive_message(twai_message_t *rx_msg, twai_message_t *tx_msg, uint32_t rx_timeout){
	xSemaphoreTake(can_mutex, portMAX_DELAY);
	esp_err_t res = twai_transmit(tx_msg, 0);
	switch(res) {
		case ESP_OK:
			ESP_LOGI(TAG, "TX ID=%.3X DLC=%u", tx_msg->identifier, tx_msg->data_length_code);
			break;

		case ESP_ERR_TIMEOUT:
			ESP_LOGE(TAG, "Send timeout!");
			break;

		case ESP_ERR_NOT_SUPPORTED:
			ESP_LOGE(TAG, "Can't sent in Listen-Only mode!");
			break;
	}

	if(res == ESP_OK){
		res = twai_receive(rx_msg, rx_timeout);
	}
	xSemaphoreGive(can_mutex);

	return res;
}

esp_err_t can_send_message(twai_message_t *msg){
    xSemaphoreTake(can_mutex, portMAX_DELAY);
    esp_err_t res = twai_transmit(msg, 0);
    xSemaphoreGive(can_mutex);

    switch(res) {
        case ESP_OK:
            ESP_LOGI(TAG, "TX ID=%.3X DLC=%u", msg->identifier, msg->data_length_code);
            break;

        case ESP_ERR_TIMEOUT:
            ESP_LOGE(TAG, "Send timeout!");
            break;

        case ESP_ERR_NOT_SUPPORTED:
            ESP_LOGE(TAG, "Can't sent in Listen-Only mode!");
            break;
    }

    return res;
}

static void can_task(void* arg) {
    uint32_t alerts = 0;
    esp_err_t ret = ESP_OK;
    twai_message_t rx_msg;

	vTaskDelay(pdMS_TO_TICKS(1500));
	xTaskNotifyGive(xTaskGetHandle("obd2 task"));
    ESP_LOGI(TAG, "Task started!");

    for (;;) {
        if (twai_read_alerts(&alerts, 0) == ESP_OK) {
            if (alerts & TWAI_ALERT_ERR_ACTIVE) {
                ESP_LOGE(TAG, "Error active alert!");
                is_error_passive = false;
            }
            if (alerts & TWAI_ALERT_ERR_PASS) {
                ESP_LOGE(TAG, "Error passive alert!");
                is_error_passive = true;
            }
            if (alerts & TWAI_ALERT_BUS_ERROR) {
                ESP_LOGE(TAG, "Bus error!");
            }
            if (alerts & TWAI_ALERT_BUS_OFF) {
                ESP_LOGW(TAG, "Bus-off...");
                if (auto_recovery) {
                    ESP_LOGW(TAG, "Auto-recovery...");
                    twai_initiate_recovery();
                }
            }
            if (alerts & TWAI_ALERT_BUS_RECOVERED) {
                ESP_LOGI(TAG, "Bus recovered!");
                if (auto_recovery) {
                    ESP_LOGI(TAG, "Restart can...");
                    ESP_ERROR_CHECK(twai_start());
                    is_error_passive = false;
                }
            }
        }

        ESP_ERROR_CHECK(twai_get_status_info(&can_status));

        if (xSemaphoreTake(can_mutex, 0) == pdTRUE) {
			ret = twai_receive(&rx_msg, 0);
			xSemaphoreGive(can_mutex);

            if (ret == ESP_OK) {
                can_rx_callback(&rx_msg);
				//vTaskDelay(pdMS_TO_TICKS(1));
                taskYIELD ();
            }
        }

		if(ret != ESP_OK){
			vTaskDelay(pdMS_TO_TICKS(10));
		}
    }
}

__attribute__((weak)) void can_rx_callback(twai_message_t *msg) {
    (void)msg;
}