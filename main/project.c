/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <esp_check.h>
#include <esp_timer.h>
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "board.h"

#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "ui.h"

void app_main(void)
{
    gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);

	ui_init();

	gpio_set_level(LED_BUILTIN, 1);

	while (1) {
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
