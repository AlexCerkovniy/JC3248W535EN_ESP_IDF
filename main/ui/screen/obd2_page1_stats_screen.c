#include "ui.h"

static void draw(void);
static void data(void *data);
static void event(ui_event_t event);

ui_screen_t obd2_page1_stats_screen = {
    .screen = NULL,
    .init = NULL,
    .draw = draw,
    .teardown = NULL,
    .data = data,
    .event = event,
    .tick = NULL
};

enum {
    OBD2_PAGE1_SHRTFT1 = 0,
    OBD2_PAGE1_LONGFT1,
    OBD2_PAGE1_TIMING_ADVANCE,
    OBD2_PAGE1_SHRTFT2,
    OBD2_PAGE1_LONGFT2,
    OBD2_PAGE1_ETHANOL_FUEL_PERCENTAGE,
    OBD2_PAGE1_EMPTY_2,
    OBD2_PAGE1_EMPTY_3,
    OBD2_PAGE1_EMPTY_4
} container_id_t;

static struct container_t {
    lv_style_t value_style;
    lv_obj_t *container;
    lv_obj_t *name_label;
    lv_obj_t *value_label;
    lv_obj_t *value_max;
    int32_t x, y, w, h;
    char *name;
} containers[] = {
    {{0}, NULL, NULL, NULL, NULL, 5, 5, 100, 50, "SHRTFT1, %"},
    {{0}, NULL, NULL, NULL, NULL, 110, 5, 100, 50, "LONGFT1, %"},
    {{0}, NULL, NULL, NULL, NULL, 215, 5, 100, 50, "TIMADV, Deg"},
    {{0}, NULL, NULL, NULL, NULL, 5, 60, 100, 50, "-"},
    {{0}, NULL, NULL, NULL, NULL, 110, 60, 100, 50, "-"},
    {{0}, NULL, NULL, NULL, NULL, 215, 60, 100, 50, "ETHANOL, %"},
    {{0}, NULL, NULL, NULL, NULL, 5, 115, 100, 50, "-"},
    {{0}, NULL, NULL, NULL, NULL, 110, 115, 100, 50, "-"},
    {{0}, NULL, NULL, NULL, NULL, 215, 115, 100, 50, "-"}
};

static void container_create(lv_obj_t *screen, struct container_t *container) {
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

static void draw(void){
    lv_obj_t *screen = lv_obj_create(NULL);
	obd2_page1_stats_screen.screen = screen;

    /* Use lv_color_hex(0) or lv_color_black() for black instead of lv_palette_main(LV_PALETTE_NONE) */
    lv_obj_set_style_bg_color(screen, lv_color_black(),
        LV_PART_MAIN | LV_STATE_DEFAULT);

    for (uint32_t i = 0; i < sizeof(containers) / sizeof(containers[0]); i++) {
        container_create(screen, &containers[i]);
    }
}

static void event(ui_event_t event) {
    if (event == UI_EVENT_SCREEN_PREV) {
        ui_load_screen(UI_DASH_SCREEN, LV_SCR_LOAD_ANIM_FADE_IN, 150, 0);
    }
}

static void data(void *data) {
    // obd2_data_t *obd2 = (obd2_data_t *)data;
    //
    // if (obd2->short_fuel_trim_bank_1 != obd2_old.short_fuel_trim_bank_1) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_SHRTFT1].value_label, "%i", obd2->short_fuel_trim_bank_1);
    // }
    //
    // if (obd2->long_fuel_trim_bank_1 != obd2_old.long_fuel_trim_bank_1) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_LONGFT1].value_label, "%i", obd2->long_fuel_trim_bank_1);
    // }
    //
    // if (obd2->timing_advance != obd2_old.timing_advance) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_TIMING_ADVANCE].value_label, "%i", obd2->timing_advance);
    // }
    //
    // if (obd2->short_fuel_trim_bank_2 != obd2_old.short_fuel_trim_bank_2) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_SHRTFT2].value_label, "%i", obd2->short_fuel_trim_bank_2);
    // }
    //
    // if (obd2->long_fuel_trim_bank_2 != obd2_old.long_fuel_trim_bank_2) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_LONGFT2].value_label, "%i", obd2->long_fuel_trim_bank_2);
    // }
    //
    // if (obd2->ethanol_fuel_percentage != obd2_old.ethanol_fuel_percentage) {
    //     lv_label_set_text_fmt(containers[OBD2_PAGE1_ETHANOL_FUEL_PERCENTAGE].value_label, "%i", obd2->ethanol_fuel_percentage);
    // }
    //
    // memcpy(&obd2_old, obd2, sizeof(obd2_data_t));
}