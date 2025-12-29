#include "project.h"
#include "display.h"
#include "esp_lvgl_port.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "esp_log.h"

#include "ui.h"
#include "can.h"
#include "obd2_task.h"

static const char *TAG = "MAIN";

static sensors_t sensors = {0};

static TickType_t last_ui_update_ticks = 0;

void app_main(void)
{
    bsp_display_init();
    bsp_display_set_brightness(100);

    ui_init();
	can_init();
	obd2_task_start();

	while (1) {
		// if (xTaskGetTickCount() - last_ui_update_ticks >= pdMS_TO_TICKS(250)) {
		// 	last_ui_update_ticks = xTaskGetTickCount();
		//
		// 	if (ui_get_current_screen_id() == UI_MAIN_SCREEN) {
		// 		sensors.ect++;
		// 		sensors.iat++;
		// 		sensors.oil_temp++;
		// 		sensors.oil_pressure++;
		//
		// 		ui_screen_send_data(&sensors);
		// 	}
		// }

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void can_rx_callback(twai_message_t *msg) {
	static int16_t val;

	if (msg->extd || msg->dlc_non_comp) {
		return;
	}

	//ESP_LOGI(TAG, "RX ID=%.3X DLC=%u", msg->identifier, msg->data_length_code);

	// Check Engine Response ID
	if (msg->identifier == 0x7E8 || msg->identifier == 0x7E9) {
		val = obd2_parse_packet(msg->data, msg->data_length_code);

		switch (msg->data[2]) {
			case AIR_INTAKE_TEMPERATURE: obd2.intake_temp = val; break;
			case FUEL_TANK_LEVEL_INPUT: obd2.fuel_level = val; break;
			case TIMING_ADVANCE: obd2.timing_advance = val; break;
			case ETHANOL_FUEL_PERCENTAGE: obd2.ethanol_fuel_percentage = val; break;
			case SHORT_TERM_FUEL_TRIM_BANK_1: obd2.short_fuel_trim_bank_1 = val; break;
			case LONG_TERM_FUEL_TRIM_BANK_1: obd2.long_fuel_trim_bank_1 = val; break;
			case SHORT_TERM_FUEL_TRIM_BANK_2: obd2.short_fuel_trim_bank_2 = val; break;
			case LONG_TERM_FUEL_TRIM_BANK_2: obd2.long_fuel_trim_bank_2 = val; break;

			default:
				break;
		}

		ESP_LOGI("OBD2", "RX PID 0x%.2X", msg->data[2]);
	}
	else if(msg->identifier == 0x0F8){ //Focus ST/RS Only
		sensors.boost = map(msg->data[5], 0, 0xC0, 0, 200);
		sensors.oil_temp = (int16_t)msg->data[7] - 60; //[-60|195]
		//ecu.ptu_c = (int16_t)RxData[0] - 50; //[-50|205] //Focus RS only
	}
	else if(msg->identifier == 0x090){
		sensors.oil_pressure = map(msg->data[4], 0x60, 0x7F, 0, 500);
		sensors.rpm = ((msg->data[4] & 0x0F) * 256 + msg->data[5]) * 2;
	}
	else if(msg->identifier == 0x130){
		sensors.speed = ((uint16_t)msg->data[6] * 256 + msg->data[7]) / 100;
	}
	else if(msg->identifier == 0x2F0){
		sensors.ect = (int16_t)msg->data[5] - 60;
		//sensors.iat = (int16_t)msg->data[7] - 120;
		sensors.iat = obd2.intake_temp;
	}
	else if(msg->identifier == 0x340){
		sensors.ambient_temp = (int16_t)msg->data[7] - 60;
	}
	else if(msg->identifier == 0x380){
		//sensors.fuel = (uint8_t)((uint16_t)msg->data[0] * 100 / 255);
		sensors.fuel = obd2.fuel_level;
	}

	if (xTaskGetTickCount() - last_ui_update_ticks >= pdMS_TO_TICKS(250)) {
		last_ui_update_ticks = xTaskGetTickCount();
		if (ui_get_current_screen_id() == UI_DASH_SCREEN) {
			ui_screen_send_data(&sensors);
		}
		else if (ui_get_current_screen_id() == UI_OBD2_STATS_PAGE_1_SCREEN) {
			ui_screen_send_data(&obd2);
		}
	}
}
