#include <string.h>

#include "ui.h"
#include "ex_value_indicator.h"

static void init(void);
static void draw(void);
static void data(void *data);
static void event(ui_event_t event);
static void update_labels(sensors_t *sensors, bool force_update);

ui_screen_t main_screen = {
    .screen = NULL,
    .init = init,
    .draw = draw,
    .teardown = NULL,
    .data = data,
    .event = event,
    .tick = NULL
};

static sensors_t sensors_old;

static enum {
    UI_MAIN_SPEED,
    UI_MAIN_RPM,
    UI_MAIN_ECT,
    UI_MAIN_IAT,
    UI_MAIN_OIL_T,

    UI_MAIN_CONTAINER_COUNT
} ui_main_screen_indicator_id_t;

static ex_value_indicator_t ex_indicators[UI_MAIN_CONTAINER_COUNT] = {0};

static void init(void) {
    ex_value_indicator_t *indicator;

    indicator = &ex_indicators[UI_MAIN_SPEED];
    ex_value_indicator_set_size(indicator, 0, 35, 106, 65);
    ex_value_indicator_set_name(indicator, "KM/H", &lv_font_montserrat_14);
    ex_value_indicator_set_value_font(indicator, &orbitron_30);

    indicator = &ex_indicators[UI_MAIN_RPM];
    ex_value_indicator_set_size(indicator, 106, 35, 106, 65);
    ex_value_indicator_set_name(indicator, "RPM", &lv_font_montserrat_14);
    ex_value_indicator_set_value_font(indicator, &orbitron_30);

    indicator = &ex_indicators[UI_MAIN_ECT];
    ex_value_indicator_set_size(indicator, 0, 100, 106, 65);
    ex_value_indicator_set_name(indicator, "ECT, C", &lv_font_montserrat_14);
    ex_value_indicator_set_min_max_label_color(indicator, lv_color_white());
    ex_value_indicator_set_value_font(indicator, &orbitron_30);
    ex_value_indicator_set_value_min_max_font(indicator, &lv_font_montserrat_14);

    indicator = &ex_indicators[UI_MAIN_IAT];
    ex_value_indicator_set_size(indicator, 106, 100, 106, 65);
    ex_value_indicator_set_name(indicator, "IAT, C", &lv_font_montserrat_14);
    ex_value_indicator_set_min_max_label_color(indicator, lv_color_white());
    ex_value_indicator_set_value_font(indicator, &orbitron_30);
    ex_value_indicator_set_value_min_max_font(indicator, &lv_font_montserrat_14);

    indicator = &ex_indicators[UI_MAIN_OIL_T];
    ex_value_indicator_set_size(indicator, 212, 100, 106, 65);
    ex_value_indicator_set_name(indicator, "OIL, C", &lv_font_montserrat_14);
    ex_value_indicator_set_value_font(indicator, &orbitron_30);
    ex_value_indicator_set_min_max_label_color(indicator, lv_color_white());
    ex_value_indicator_set_value_min_max_font(indicator, &lv_font_montserrat_14);
}

static void draw(void){
    lv_obj_t *screen = lv_obj_create(NULL);
    main_screen.screen = screen;

    lv_obj_set_style_bg_color(screen, lv_color_black(),
        LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *top_bar = lv_obj_create(screen);
    // lv_obj_set_pos(top_bar, 0, 0);
    // lv_obj_set_size(top_bar, lv_display_get_horizontal_resolution(NULL), 30);
    // lv_obj_set_style_border_width(top_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(top_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(top_bar, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(top_bar, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    for (uint32_t i = 0; i < sizeof(ex_indicators) / sizeof(ex_indicators[0]); i++) {
        ex_value_indicator_create(screen, &ex_indicators[i]);
    }

    /* Draw last known sensors values */
    update_labels(&sensors_old, true);
}

static void event(ui_event_t event) {
    if (event == UI_EVENT_SCREEN_NEXT) {
        ui_load_screen(UI_DASH_SCREEN, LV_SCR_LOAD_ANIM_FADE_IN, 150, 0);
    }
}

static void data(void *data) {
    update_labels((sensors_t *)data, false);
}

static void update_labels(sensors_t *sensors, bool forced) {
    lv_color_t color;

    uint16_constrain(&sensors->speed, 0, 999);
    uint16_constrain(&sensors->rpm, 0, 9999);
    int16_constrain(&sensors->ect, -99, 199);
    int16_constrain(&sensors->iat, -99, 199);
    int16_constrain(&sensors->oil_temp, -99, 199);

    if (sensors->speed != sensors_old.speed) {
        ex_value_indicator_set_value(&ex_indicators[UI_MAIN_SPEED], sensors->speed, lv_color_white(), 0, forced);
    }

    if (sensors->rpm != sensors_old.rpm) {
        color = temp_zone_color((int16_t)sensors->rpm, 4000, 6000);
        ex_value_indicator_set_value(&ex_indicators[UI_MAIN_RPM], sensors->rpm, color, 0, forced);
    }

    if (sensors->ect != sensors_old.ect || forced) {
        color = temp_zone_color(sensors->ect, 105, 110);
        ex_value_indicator_set_value(&ex_indicators[UI_MAIN_ECT], sensors->ect, color, 0, forced);
    }

    if (sensors->iat != sensors_old.iat || forced) {
        color = temp_zone_color(sensors->iat, 50, 60);
        ex_value_indicator_set_value(&ex_indicators[UI_MAIN_IAT], sensors->iat, color, 0, forced);
    }

    if (sensors->oil_temp != sensors_old.oil_temp || forced) {
        color = temp_zone_color(sensors->oil_temp, 105, 115);
        ex_value_indicator_set_value(&ex_indicators[UI_MAIN_OIL_T], sensors->oil_temp, color, 0, forced);
    }

    memcpy(&sensors_old, sensors, sizeof(sensors_t));
}