#ifndef OBD2_TASK_H
#define OBD2_TASK_H

#include "obd2.h"

typedef struct {
    int16_t intake_temp;
    int16_t fuel_level;
    int16_t timing_advance;
    int16_t ethanol_fuel_percentage;
    int16_t short_fuel_trim_bank_1;
    int16_t long_fuel_trim_bank_1;
    int16_t short_fuel_trim_bank_2;
    int16_t long_fuel_trim_bank_2;
} obd2_data_t;

extern obd2_data_t obd2;

void obd2_task_start(void);

#endif //OBD2_TASK_H
