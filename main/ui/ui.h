#ifndef UI_H
#define UI_H

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

#include "structs.h"
#include "fonts.h"
#include "screen/screen.h"
#include "macros.h"
#include "ui_events.h"

void ui_init(void);
ui_screen_id_t ui_get_current_screen_id(void);
void ui_load_screen(ui_screen_id_t screen_id, lv_screen_load_anim_t anim, uint32_t time, uint32_t delay);
void ui_screen_send_data(void *data);
void ui_event(ui_event_t event);

#endif //UI_H
