#include "obd2_task.h"
#include "project.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "obd2.h"

#define TAG "OBD2 TASK"

uint8_t pids_list[] = {
    AIR_INTAKE_TEMPERATURE,
    FUEL_TANK_LEVEL_INPUT,
    TIMING_ADVANCE,
    ETHANOL_FUEL_PERCENTAGE,
    SHORT_TERM_FUEL_TRIM_BANK_1,
    LONG_TERM_FUEL_TRIM_BANK_1
};

obd2_pids_list_t obd2_list = {
    .pids_list = pids_list,
    .size = sizeof(pids_list)/sizeof(pids_list[0])
};

obd2_data_t obd2;

uint32_t pid_request_index = 0;

static void obd2_task(void* arg);

void obd2_task_start(void){
    xTaskCreate(obd2_task, "obd2 task", 4800, NULL, 3 /* Higher than UI task */, NULL);
}

static void obd2_task(void* arg){
    obd2_status_t status = OBD_OK;

	/* Wait for ready notification from CAN task */
	ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(10000));
	ESP_LOGI(TAG, "OBD2 task started!");

    while(1){
        status = obd2_request_pid(obd2_list.pids_list[pid_request_index]);

        if(status == OBD_OK){
            pid_request_index++;
            if(pid_request_index >= obd2_list.size){
                pid_request_index = 0;
            }

            vTaskDelay(pdMS_TO_TICKS(20));
        }

        if (status != OBD_OK) {
            ESP_LOGE("OBD2 TASK", "PID request failed, status=%d", status);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}
