#ifndef UI_MACROS_H
#define UI_MACROS_H

#include "ui.h"

void uint8_constrain(uint8_t *value, uint8_t min, uint8_t max);
void uint16_constrain(uint16_t *value, uint16_t min, uint16_t max);
void int16_constrain(int16_t *value, int16_t min, int16_t max);
lv_color_t temp_zone_color(int16_t param, int16_t yellow_threshold, int16_t red_threshold);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif //UI_MACROS_H
