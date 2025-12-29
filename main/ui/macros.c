#include "macros.h"

void uint8_constrain(uint8_t *value, uint8_t min, uint8_t max) {
	if (*value < min) {
		*value = min;
	}
	else if (*value > max) {
		*value = max;
	}
}

void uint16_constrain(uint16_t *value, uint16_t min, uint16_t max) {
	if (*value < min) {
		*value = min;
	}
	else if (*value > max) {
		*value = max;
	}
}

void int16_constrain(int16_t *value, int16_t min, int16_t max) {
	if (*value < min) {
		*value = min;
	}
	else if (*value > max) {
		*value = max;
	}
}

lv_color_t temp_zone_color(int16_t param, int16_t yellow_threshold, int16_t red_threshold) {
	if (param < yellow_threshold) {
		return lv_color_hex(0xff00ff00);
	}

	if (param < red_threshold) {
		return lv_color_hex(0xffffff00);
	}

	return lv_color_hex(0xffff0000);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	if(x < in_min){
		return out_min;
	}

	if(x > in_max){
		return out_max;
	}

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
