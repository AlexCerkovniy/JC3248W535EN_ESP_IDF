#ifndef CAN_H
#define CAN_H

#include "driver/twai.h"
#include "hal/twai_types.h"

void can_init(void);
esp_err_t can_send_message(twai_message_t *msg);
void can_rx_callback(twai_message_t *msg);

#endif //CAN_H
