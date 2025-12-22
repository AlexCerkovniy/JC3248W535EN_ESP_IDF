#ifndef STRUCTS_H
#define STRUCTS_H

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

#include <stdint.h>
#include <stdbool.h>

#include "ui_events.h"

typedef struct {
  lv_obj_t *screen;
  void (*init)(void);
  void (*draw)(void);
  void (*teardown)(void);
  void (*data)(void *data);
  void (*event)(ui_event_t event);
  void (*tick)(void);
} ui_screen_t;

typedef struct {
  uint16_t speed;
  uint16_t rpm;
  int16_t ect;
  int16_t iat;
  int16_t boost;
  int16_t oil_pressure;
  int16_t oil_temp;
  uint8_t fuel;
  int16_t ambient_temp;
} sensors_t;

#endif //STRUCTS_H
