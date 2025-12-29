#ifndef SCREEN_H
#define SCREEN_H

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

extern ui_screen_t startup_screen;
extern ui_screen_t main_screen;
extern ui_screen_t dash_screen;
extern ui_screen_t obd2_page1_stats_screen;

typedef enum {
    UI_STARTUP_SCREEN = 0,
    UI_MAIN_SCREEN,
    UI_DASH_SCREEN,
	UI_OBD2_STATS_PAGE_1_SCREEN,

    UI_SCREENS_COUNT
} ui_screen_id_t;

#endif //SCREEN_H
