#ifndef EX_VALUE_INDICATOR_H
#define EX_VALUE_INDICATOR_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

typedef struct {
    char *name;
    int32_t x, y, w, h;
    lv_obj_t *container;
    lv_obj_t *name_label;
    lv_font_t *name_font;
    lv_obj_t *value_label;
    lv_font_t *value_font;
    lv_obj_t *value_min_max_label;
    lv_font_t *value_min_max_font;
    lv_color_t min_max_label_color;
    int32_t value, value_min, value_max;
} ex_value_indicator_t;

void ex_value_indicator_create(lv_obj_t *screen, ex_value_indicator_t *indicator);
void ex_value_indicator_set_size(ex_value_indicator_t *indicator, int32_t x, int32_t y, int32_t w, int32_t h);
void ex_value_indicator_set_name(ex_value_indicator_t *indicator, char *name, const lv_font_t *font);
void ex_value_indicator_set_min_max_label_color(ex_value_indicator_t *indicator, lv_color_t color);
void ex_value_indicator_set_value_font(ex_value_indicator_t *indicator, const lv_font_t *font);
void ex_value_indicator_set_value_min_max_font(ex_value_indicator_t *indicator, const lv_font_t *font);
void ex_value_indicator_set_value(ex_value_indicator_t *indicator, int32_t value, lv_color_t color, int32_t scale, bool redraw);
void ex_value_indicator_reset_min_max(ex_value_indicator_t *indicator);

#endif
