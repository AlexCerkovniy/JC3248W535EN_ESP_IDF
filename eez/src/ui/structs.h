#ifndef EEZ_LVGL_UI_STRUCTS_H
#define EEZ_LVGL_UI_STRUCTS_H

#if !defined(EEZ_FOR_LVGL)
#warning "EEZ_FOR_LVGL is not enabled"
#define EEZ_FOR_LVGL
#endif


#if defined(EEZ_FOR_LVGL)

#include <eez/flow/flow.h>
#include <stdint.h>
#include <stdbool.h>

#include "vars.h"

using namespace eez;

enum FlowStructures {
    FLOW_STRUCTURE_SENSORS = 16384
};

enum FlowArrayOfStructures {
    FLOW_ARRAY_OF_STRUCTURE_SENSORS = 81920
};

enum sensorsFlowStructureFields {
    FLOW_STRUCTURE_SENSORS_FIELD_ECT = 0,
    FLOW_STRUCTURE_SENSORS_NUM_FIELDS
};

struct sensorsValue {
    Value value;
    
    sensorsValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_SENSORS_NUM_FIELDS, FLOW_STRUCTURE_SENSORS, 0);
    }
    
    sensorsValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    int ect() {
        return value.getArray()->values[FLOW_STRUCTURE_SENSORS_FIELD_ECT].getInt();
    }
    void ect(int ect) {
        value.getArray()->values[FLOW_STRUCTURE_SENSORS_FIELD_ECT] = IntegerValue(ect);
    }
};

typedef ArrayOf<sensorsValue, FLOW_ARRAY_OF_STRUCTURE_SENSORS> ArrayOfsensorsValue;


#endif

#endif /*EEZ_LVGL_UI_STRUCTS_H*/
