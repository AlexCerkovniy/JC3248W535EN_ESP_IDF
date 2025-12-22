#include <string.h>

#include "ui.h"

static void draw(void);
static void data(void *data);
static void event(ui_event_t event);

ui_screen_t dash_screen = {
    .screen = NULL,
    .init = NULL,
    .draw = draw,
    .data = NULL,
    .data = data,
    .event = event,
    .tick = NULL
};

static sensors_t dash_sensors;

enum {
    DASH_ECT,
    DASH_IAT,
    DASH_OIL_T,
    DASH_OIL_P,
    DASH_BOOST,
    DASH_RPM,
    DASH_FUEL,
    DASH_SPEED,
    DASH_AMBIENT_T
} dash_container_id_t;

static struct dash_container_t {
    lv_style_t value_style;
    lv_obj_t *container;
    lv_obj_t *name_label;
    lv_obj_t *value_label;
    lv_obj_t *value_max;
    int32_t x, y, w, h;
    char *name;
} dash_containers[] = {
    {{0}, NULL, NULL, NULL, NULL, 5, 5, 100, 50, "ECT, C"},
    {{0}, NULL, NULL, NULL, NULL, 110, 5, 100, 50, "IAT, C"},
    {{0}, NULL, NULL, NULL, NULL, 215, 5, 100, 50, "OIL.T, C"},
    {{0}, NULL, NULL, NULL, NULL, 5, 60, 100, 50, "OIL.P, Bar"},
    {{0}, NULL, NULL, NULL, NULL, 110, 60, 100, 50, "BOOST, Bar"},
    {{0}, NULL, NULL, NULL, NULL, 215, 60, 100, 50, "RPM"},
    {{0}, NULL, NULL, NULL, NULL, 5, 115, 100, 50, "FUEL, %"},
    {{0}, NULL, NULL, NULL, NULL, 110, 115, 100, 50, "SPEED, Km/h"},
    {{0}, NULL, NULL, NULL, NULL, 215, 115, 100, 50, "AMBIENT, C"}
};

static void dash_container_create(lv_obj_t *screen, struct dash_container_t *container) {
    container->container = lv_obj_create(screen);
    lv_obj_set_pos(container->container, container->x, container->y);
    lv_obj_set_size(container->container, container->w, container->h);
    lv_obj_set_style_pad_left(container->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(container->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(container->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(container->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(container->container, lv_color_hex(0xffaaaaaa), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(container->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    container->name_label = lv_label_create(container->container);
    lv_obj_set_pos(container->name_label, 0, 0);
    lv_obj_set_align(container->name_label, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_color(container->name_label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(container->name_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text_static(container->name_label, container->name);

    container->value_label = lv_label_create(container->container);
    lv_style_init(&container->value_style);
    lv_style_set_text_font(&container->value_style, &orbitron_30);
    lv_obj_add_style(container->value_label, &container->value_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_align(container->value_label, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_style_text_color(container->value_label, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(container->value_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text_static(container->value_label, "0");
}

// void arc_indicator_create(lv_obj_t *arc, lv_obj_t *label,
//                           int32_t x, int32_t y,
//                           int32_t w, int32_t h,
//                           int32_t default_value)
// {
//     /* Create arc */
//     lv_obj_set_pos(arc, x, y);
//     lv_obj_set_size(arc, w, h);
//     lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
//     lv_obj_set_style_arc_width(arc, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_arc_color(arc, lv_color_hex(0xff757575), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_arc_rounded(arc, false, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(arc, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_arc_rounded(arc, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_arc_color(arc, lv_color_hex(0xff00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_arc_width(arc, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(arc, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_opa(arc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(arc, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(arc, LV_TEXT_ALIGN_CENTER, LV_PART_KNOB | LV_STATE_DEFAULT);
//     lv_arc_set_value(arc, default_value);
//
//     /* Create label */
//     lv_obj_set_pos(label, x + w/2, y + h/2);
//     lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_label_set_text_fmt(label, "%" LV_PRId32, default_value);
//     // lv_obj_set_width(label, lv_pct(50));
// }

static void draw(void){
    lv_obj_t *screen = lv_obj_create(NULL);
    dash_screen.screen = screen;

    /* Use lv_color_hex(0) or lv_color_black() for black instead of lv_palette_main(LV_PALETTE_NONE) */
    lv_obj_set_style_bg_color(screen,lv_color_black(),
        LV_PART_MAIN | LV_STATE_DEFAULT);

    // // ECT arc indicator init
    // lv_obj_t *arc_ect = lv_arc_create(screen);
    // lv_obj_t *label_ect = lv_label_create(screen);
    // arc_indicator_create(arc_ect, label_ect, 5, 5, 80, 80, 0);
    //
    // lv_obj_t *arc_oil_temp = lv_arc_create(screen);
    // lv_obj_t *label_oil_temp = lv_label_create(screen);
    // arc_indicator_create(arc_oil_temp, label_oil_temp, 5, 90, 80, 80, 50);

    for (uint32_t i = 0; i < sizeof(dash_containers) / sizeof(dash_containers[0]); i++) {
        dash_container_create(screen, &dash_containers[i]);
    }
}

static void event(ui_event_t event) {
    if (event == UI_EVENT_SCREEN_NEXT) {
        ui_load_screen(UI_OBD2_STATS_PAGE_1_SCREEN, LV_SCR_LOAD_ANIM_FADE_IN, 150, 0);
    }
    else if (event == UI_EVENT_SCREEN_PREV) {
        ui_load_screen(UI_MAIN_SCREEN, LV_SCR_LOAD_ANIM_FADE_IN, 150, 0);
    }
}

static void data(void *data) {
    sensors_t *sensors = (sensors_t *)data;
    lv_color_t color = lv_color_white();
    uint16_t tmp;

    int16_constrain(&sensors->ect, -99, 199);
    int16_constrain(&sensors->iat, -99, 199);
    int16_constrain(&sensors->oil_temp, -99, 199);
    int16_constrain(&sensors->oil_pressure, -500, 800);
    int16_constrain(&sensors->ambient_temp, -99, 100);
    int16_constrain(&sensors->boost, -500, 800);
    uint8_constrain(&sensors->fuel, 0, 100);
    uint16_constrain(&sensors->rpm, 0, 9999);
    uint16_constrain(&sensors->speed, 0, 999);

    if (sensors->ect != dash_sensors.ect) {
        color = temp_zone_color(sensors->ect, 105, 110);
        lv_obj_set_style_text_color(dash_containers[DASH_ECT].value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_fmt(dash_containers[DASH_ECT].value_label, "%i", sensors->ect);
    }

    if (sensors->iat != dash_sensors.iat) {
        color = temp_zone_color(sensors->iat, 50, 60);
        lv_obj_set_style_text_color(dash_containers[DASH_IAT].value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_fmt(dash_containers[DASH_IAT].value_label, "%i", sensors->iat);
    }

    if (sensors->oil_temp != dash_sensors.oil_temp) {
        color = temp_zone_color(sensors->oil_temp, 105, 115);
        lv_obj_set_style_text_color(dash_containers[DASH_OIL_T].value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_fmt(dash_containers[DASH_OIL_T].value_label, "%i", sensors->oil_temp);
    }

    if (sensors->oil_pressure != dash_sensors.oil_pressure) {
        tmp = (uint16_t)abs(sensors->oil_pressure);
        lv_label_set_text_fmt(dash_containers[DASH_OIL_P].value_label, "%s%u.%.2u",
            (sensors->oil_pressure < 0)?"-":"", tmp/100, tmp%100);
    }

    if (sensors->boost != dash_sensors.boost) {
        tmp = (uint16_t)abs(sensors->boost);
        lv_label_set_text_fmt(dash_containers[DASH_BOOST].value_label, "%s%u.%.2u",
            (sensors->boost < 0)?"-":"", tmp/100, tmp%100);
    }

    if (sensors->rpm != dash_sensors.rpm) {
        color = temp_zone_color((int16_t)sensors->rpm, 5000, 6000);
        lv_obj_set_style_text_color(dash_containers[DASH_RPM].value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_fmt(dash_containers[DASH_RPM].value_label, "%u", sensors->rpm);
    }

    if (sensors->fuel != dash_sensors.fuel) {
        if (sensors->fuel < 10) {
            color = lv_color_hex(0xffff0000);
        }
        else if (sensors->fuel < 20) {
            color = lv_color_hex(0xffffff00);
        }
        else {
            color = lv_color_hex(0xff00ff00);
        }

        lv_obj_set_style_text_color(dash_containers[DASH_FUEL].value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_fmt(dash_containers[DASH_FUEL].value_label, "%u", sensors->fuel);
    }

    if (sensors->speed != dash_sensors.speed) {
        lv_label_set_text_fmt(dash_containers[DASH_SPEED].value_label, "%u", sensors->speed);
    }

    if (sensors->ambient_temp != dash_sensors.ambient_temp) {
        lv_label_set_text_fmt(dash_containers[DASH_AMBIENT_T].value_label, "%i", sensors->ambient_temp);
    }

    memcpy(&dash_sensors, sensors, sizeof(sensors_t));
}