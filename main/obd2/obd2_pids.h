#pragma once

enum {
  PIDS_SUPPORT_01_20                                = 0x00,
  MONITOR_STATUS_SINCE_DTCS_CLEARED                 = 0x01,
  FREEZE_DTC                                        = 0x02,
  FUEL_SYSTEM_STATUS                                = 0x03,
  CALCULATED_ENGINE_LOAD                            = 0x04,
  ENGINE_COOLANT_TEMPERATURE                        = 0x05,
  SHORT_TERM_FUEL_TRIM_BANK_1                       = 0x06,
  LONG_TERM_FUEL_TRIM_BANK_1                        = 0x07,
  SHORT_TERM_FUEL_TRIM_BANK_2                       = 0x08,
  LONG_TERM_FUEL_TRIM_BANK_2                        = 0x09,
  FUEL_PRESSURE                                     = 0x0a,
  INTAKE_MANIFOLD_ABSOLUTE_PRESSURE                 = 0x0b,
  ENGINE_RPM                                        = 0x0c,
  VEHICLE_SPEED                                     = 0x0d,
  TIMING_ADVANCE                                    = 0x0e,
  AIR_INTAKE_TEMPERATURE                            = 0x0f,
  MAF_AIR_FLOW_RATE                                 = 0x10,
  THROTTLE_POSITION                                 = 0x11,
  COMMANDED_SECONDARY_AIR_STATUS                    = 0x12,
  OXYGEN_SENSORS_PRESENT_IN_2_BANKS                 = 0x13,
  OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM              = 0x14,
  OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM              = 0x15,
  OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM              = 0x16,
  OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM              = 0x17,
  OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM              = 0x18,
  OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM              = 0x19,
  OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM              = 0x1a,
  OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM              = 0x1b,
  OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO            = 0x1c,
  OXYGEN_SENSORS_PRESENT_IN_4_BANKS                 = 0x1d,
  AUXILIARY_INPUT_STATUS                            = 0x1e,
  RUN_TIME_SINCE_ENGINE_START                       = 0x1f,

  PIDS_SUPPORT_21_40                                = 0x20,
  DISTANCE_TRAVELED_WITH_MIL_ON                     = 0x21,
  FUEL_RAIL_PRESSURE                                = 0x22,
  FUEL_RAIL_GAUGE_PRESSURE                          = 0x23,
  OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x24,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x25,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x26,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x27,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x28,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x29,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2b,
  COMMANDED_EGR                                     = 0x2c,
  EGR_ERROR                                         = 0x2d,
  COMMANDED_EVAPORATIVE_PURGE                       = 0x2e,
  FUEL_TANK_LEVEL_INPUT                             = 0x2f,
  WARM_UPS_SINCE_CODES_CLEARED                      = 0x30,
  DISTANCE_TRAVELED_SINCE_CODES_CLEARED             = 0x31,
  EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x32,
  ABSOLULTE_BAROMETRIC_PRESSURE                     = 0x33,
/*OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x34,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x35,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x36,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x37,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x38,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x39,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3b,*/
  CATALYST_TEMPERATURE_BANK_1_SENSOR_1              = 0x3c,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_1              = 0x3d,
  CATALYST_TEMPERATURE_BANK_1_SENSOR_2              = 0x3e,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_2              = 0x3f,

  PIDS_SUPPORT_41_60                                = 0x40,
  MONITOR_STATUS_THIS_DRIVE_CYCLE                   = 0x41,
  CONTROL_MODULE_VOLTAGE                            = 0x42,
  ABSOLUTE_LOAD_VALUE                               = 0x43,
  FUEL_AIR_COMMANDED_EQUIVALENCE_RATE               = 0x44,
  RELATIVE_THROTTLE_POSITION                        = 0x45,
  AMBIENT_AIR_TEMPERATURE                           = 0x46,
  ABSOLUTE_THROTTLE_POSITION_B                      = 0x47,
  ABSOLUTE_THROTTLE_POSITION_C                      = 0x48,
  ABSOLUTE_THROTTLE_POSITION_D                      = 0x49,
  ABSOLUTE_THROTTLE_POSITION_E                      = 0x4a,
  ABSOLUTE_THROTTLE_POSITION_F                      = 0x4b,
  COMMANDED_THROTTLE_ACTUATOR                       = 0x4c,
  TIME_RUN_WITH_MIL_ON                              = 0x4d,
  TIME_SINCE_TROUBLE_CODES_CLEARED                  = 0x4e,
/*                                                  = 0x4f,
                                                    = 0x50,*/
  FUEL_TYPE                                         = 0x51,
  ETHANOL_FUEL_PERCENTAGE                           = 0x52,
  ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE               = 0x53,
/*EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x54,*/
/*                                                  = 0x55,
                                                    = 0x56,
                                                    = 0x57,
                                                    = 0x58,*/
  FUEL_RAIL_ABSOLUTE_PRESSURE                       = 0x59,
  RELATIVE_ACCELERATOR_PEDAL_POSITTION              = 0x5a,
  HYBRID_BATTERY_PACK_REMAINING_LIFE                = 0x5b,
  ENGINE_OIL_TEMPERATURE                            = 0x5c,
  FUEL_INJECTION_TIMING                             = 0x5d,
  ENGINE_FUEL_RATE                                  = 0x5e,
  EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED = 0x5f,
  ENGINE_TORQUE_DEMANDED                            = 0x61,
  ENGINE_TORQUE_PERCENTAGE                          = 0x62,
  PID_ENGINE_REF_TORQUE                             = 0x63

  // more PIDs can be added from: https://en.wikipedia.org/wiki/OBD-II_PIDs
};

// // Mode 1 PIDs
// #define PID_ENGINE_LOAD 0x04
// #define PID_COOLANT_TEMP 0x05
// #define PID_SHORT_TERM_FUEL_TRIM_1 0x06
// #define PID_LONG_TERM_FUEL_TRIM_1 0x07
// #define PID_SHORT_TERM_FUEL_TRIM_2 0x08
// #define PID_LONG_TERM_FUEL_TRIM_2 0x09
// #define PID_FUEL_PRESSURE 0x0A
// #define PID_INTAKE_MAP 0x0B
// #define PID_RPM 0x0C
// #define PID_SPEED 0x0D
// #define PID_TIMING_ADVANCE 0x0E
// #define PID_INTAKE_TEMP 0x0F
// #define PID_MAF_FLOW 0x10
// #define PID_THROTTLE 0x11
// #define PID_AUX_INPUT 0x1E
// #define PID_RUNTIME 0x1F
// #define PID_DISTANCE_WITH_MIL 0x21
// #define PID_COMMANDED_EGR 0x2C
// #define PID_EGR_ERROR 0x2D
// #define PID_COMMANDED_EVAPORATIVE_PURGE 0x2E
// #define PID_FUEL_LEVEL 0x2F
// #define PID_WARMS_UPS 0x30
// #define PID_DISTANCE 0x31
// #define PID_EVAP_SYS_VAPOR_PRESSURE 0x32
// #define PID_BAROMETRIC 0x33
// #define PID_CATALYST_TEMP_B1S1 0x3C
// #define PID_CATALYST_TEMP_B2S1 0x3D
// #define PID_CATALYST_TEMP_B1S2 0x3E
// #define PID_CATALYST_TEMP_B2S2 0x3F
// #define PID_CONTROL_MODULE_VOLTAGE 0x42
// #define PID_ABSOLUTE_ENGINE_LOAD 0x43
// #define PID_AIR_FUEL_EQUIV_RATIO 0x44
// #define PID_RELATIVE_THROTTLE_POS 0x45
// #define PID_AMBIENT_TEMP 0x46
// #define PID_ABSOLUTE_THROTTLE_POS_B 0x47
// #define PID_ABSOLUTE_THROTTLE_POS_C 0x48
// #define PID_ACC_PEDAL_POS_D 0x49
// #define PID_ACC_PEDAL_POS_E 0x4A
// #define PID_ACC_PEDAL_POS_F 0x4B
// #define PID_COMMANDED_THROTTLE_ACTUATOR 0x4C
// #define PID_TIME_WITH_MIL 0x4D
// #define PID_TIME_SINCE_CODES_CLEARED 0x4E
// #define PID_ETHANOL_FUEL 0x52
// #define PID_FUEL_RAIL_PRESSURE 0x59
// #define PID_HYBRID_BATTERY_PERCENTAGE 0x5B
// #define PID_ENGINE_OIL_TEMP 0x5C
// #define PID_FUEL_INJECTION_TIMING 0x5D
// #define PID_ENGINE_FUEL_RATE 0x5E
// #define PID_ENGINE_TORQUE_DEMANDED 0x61
// #define PID_ENGINE_TORQUE_PERCENTAGE 0x62
// #define PID_ENGINE_REF_TORQUE 0x63
