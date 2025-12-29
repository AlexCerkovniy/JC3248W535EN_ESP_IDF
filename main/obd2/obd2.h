#pragma once

#include "stdint.h"
#include "stdbool.h"

#include "obd2_pids.h"

typedef struct {
	uint8_t *pids_list;
	uint8_t size;
} obd2_pids_list_t;

typedef enum {
	OBD_OK = 0,
	OBD_BUSY,
	OBD_ERROR
} obd2_status_t;

int16_t obd2_parse_packet(uint8_t *packet, uint8_t len);
obd2_status_t obd2_request_pid(uint8_t pid);
