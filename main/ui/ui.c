#include "ui.h"
#include "esp_log.h"
#include "lv_port.h"

#define LOG_TAG "UI"

/* Background screen, all other screens draw on the top of it */
lv_obj_t *background = NULL;

ui_screen_t *screen_list[UI_SCREENS_COUNT] = {NULL};
ui_screen_id_t current_screen_id = UI_STARTUP_SCREEN;

void ui_init(void) {
    lvgl_port_lock(0);
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_color_black(), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    /* Create background */
    background = lv_obj_create(NULL);

    lvgl_port_unlock();

    screen_list[UI_STARTUP_SCREEN] = &startup_screen;
    screen_list[UI_MAIN_SCREEN] = &main_screen;
    screen_list[UI_DASH_SCREEN] = &dash_screen;
	screen_list[UI_OBD2_STATS_PAGE_1_SCREEN] = &obd2_page1_stats_screen;

    /* Initialize screens */
    for (uint32_t i = 0; i < UI_SCREENS_COUNT; i++) {
        if (screen_list[i]->init) {
            screen_list[i]->init();
        }
    }

    /* Load startup screen */
    ui_load_screen(UI_STARTUP_SCREEN, LV_SCR_LOAD_ANIM_NONE, 0, 0);

    /* Go to dash screen after startup screen */
    ui_load_screen(UI_MAIN_SCREEN, LV_SCR_LOAD_ANIM_FADE_IN, 400, 2000);
}

void ui_screen_send_data(void *data) {
    if (screen_list[current_screen_id]->data) {
        lvgl_port_lock(0);
        screen_list[current_screen_id]->data(data);
        lvgl_port_unlock();
    }
}

ui_screen_id_t ui_get_current_screen_id(void) {
    return current_screen_id;
}

void ui_load_screen(ui_screen_id_t screen_id, lv_screen_load_anim_t anim, uint32_t time, uint32_t delay) {
    lvgl_port_lock(0);
    ESP_LOGI(LOG_TAG, "Load screen ID: %u", screen_id);

    if (screen_list[current_screen_id]->teardown) {
        screen_list[current_screen_id]->teardown();
    }

    if (screen_list[screen_id]->draw) {
        screen_list[screen_id]->draw();
    }

    current_screen_id = screen_id;
    lv_scr_load_anim(screen_list[screen_id]->screen, anim, time, delay, true);
    lvgl_port_unlock();
}

void ui_event(ui_event_t event) {
    if (screen_list[current_screen_id]->event != NULL) {
        ESP_LOGI(LOG_TAG, "Event: %u", event);
        screen_list[current_screen_id]->event(event);
    }
}
