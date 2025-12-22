#include "ex_value_indicator.h"

void ex_value_indicator_create(lv_obj_t *screen, ex_value_indicator_t *indicator) {
    indicator->container = lv_obj_create(screen);
    lv_obj_set_pos(indicator->container, indicator->x, indicator->y);
    lv_obj_set_size(indicator->container, indicator->w, indicator->h);
    lv_obj_set_style_pad_left(indicator->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(indicator->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(indicator->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(indicator->container, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(indicator->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(indicator->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(indicator->container, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(indicator->container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (indicator->name != NULL) {
        indicator->name_label = lv_label_create(indicator->container);
        lv_obj_set_style_text_font(indicator->name_label, indicator->name_font, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_align(indicator->name_label, LV_ALIGN_TOP_MID);
        lv_obj_set_style_text_color(indicator->name_label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_align(indicator->name_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_static(indicator->name_label, indicator->name);
    }

    if (indicator->value_min_max_font != NULL) {
        indicator->value_min_max_label = lv_label_create(indicator->container);
        lv_obj_set_style_text_font(indicator->value_min_max_label, indicator->value_min_max_font, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_align(indicator->value_min_max_label, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_style_text_color(indicator->value_min_max_label, indicator->min_max_label_color, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_align(indicator->value_min_max_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text_static(indicator->value_min_max_label, "0/0");
    }

    indicator->value_label = lv_label_create(indicator->container);
    lv_obj_set_style_text_font(indicator->value_label, indicator->value_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (indicator->name == NULL && indicator->value_min_max_font == NULL) {
        lv_obj_set_align(indicator->value_label, LV_ALIGN_CENTER);
    }
    else if (indicator->name == NULL) {
        lv_obj_set_align(indicator->value_label, LV_ALIGN_TOP_MID);
    }
    else if (indicator->value_min_max_font == NULL) {
        lv_obj_set_align(indicator->value_label, LV_ALIGN_BOTTOM_MID);
    }
    else {
        lv_obj_set_align(indicator->value_label, LV_ALIGN_CENTER);
    }
    lv_obj_set_align(indicator->value_label, (indicator->name != NULL) ? LV_ALIGN_CENTER : LV_ALIGN_TOP_MID);
    lv_obj_set_style_text_color(indicator->value_label, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(indicator->value_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text_static(indicator->value_label, "0");
}

void ex_value_indicator_set_size(ex_value_indicator_t *indicator, int32_t x, int32_t y, int32_t w, int32_t h) {
    indicator->x = x;
    indicator->y = y;
    indicator->w = w;
    indicator->h = h;
}

void ex_value_indicator_set_name(ex_value_indicator_t *indicator, char *name, const lv_font_t *font) {
    indicator->name = name;
    indicator->name_font = (lv_font_t *)font;
}

void ex_value_indicator_set_min_max_label_color(ex_value_indicator_t *indicator, lv_color_t color) {
    indicator->min_max_label_color = color;
}

void ex_value_indicator_set_value_font(ex_value_indicator_t *indicator, const lv_font_t *font) {
    indicator->value_font = (lv_font_t *)font;
}

void ex_value_indicator_set_value_min_max_font(ex_value_indicator_t *indicator, const lv_font_t *font) {
    indicator->value_min_max_font = (lv_font_t *)font;
}

void ex_value_indicator_set_value(ex_value_indicator_t *indicator, int32_t value, lv_color_t color, int32_t scale, bool redraw) {
    bool redraw_min_max = false;
    int32_t tmp[2];

    /* Update min/max */
    if (value > indicator->value_max) {
        indicator->value_max = value;
        redraw_min_max = true;
    }
    else if (value < indicator->value_min) {
        indicator->value_min = value;
        redraw_min_max = true;
    }

    if (redraw_min_max || redraw) {
        lv_obj_set_style_text_color(indicator->value_label,
            indicator->min_max_label_color,
            LV_PART_MAIN | LV_STATE_DEFAULT);

        if (scale == 100) {
            tmp[0] = abs(indicator->value_min);
            tmp[1] = abs(indicator->value_max);

            lv_label_set_text_fmt(indicator->value_min_max_label, "%s%ld.%.2ld/%s%ld.%.2ld",
                (indicator->value_min < 0)?"-":"", tmp[0]/100, tmp[0]%100,
                (indicator->value_max < 0)?"-":"", tmp[1]/100, tmp[1]%100);
        }
        else {
            lv_label_set_text_fmt(indicator->value_min_max_label, "%ld/%ld",
                indicator->value_min, indicator->value_max);
        }
    }

    lv_obj_set_style_text_color(indicator->value_label, color, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (value == 0) {
        lv_label_set_text_static(indicator->value_label, "0");
        return;
    }

    if (scale == 100) {
        tmp[0] = abs(value);
        lv_label_set_text_fmt(indicator->value_label, "%s%ld.%.2ld", (value < 0)?"-":"", tmp[0]/100, tmp[0]%100);
    }
    else {
        lv_label_set_text_fmt(indicator->value_label, "%ld", value);
    }
}

void ex_value_indicator_reset_min_max(ex_value_indicator_t *indicator) {
    indicator->value_max = 0;
    indicator->value_min = 0;
    lv_label_set_text_static(indicator->value_min_max_label, "0/0");
}
