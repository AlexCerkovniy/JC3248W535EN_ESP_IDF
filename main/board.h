#ifndef BOARD_H
#define BOARD_H

/* Onboard led */
#define LED_BUILTIN  2

/* Buttons */
#define BTN_NEXT_PIN  26
#define BTN_PREV_PIN  25

/* CAN pins */
#define CAN_PIN_TX   16
#define CAN_PIN_RX   17

/* LCD pins */
#define LCD_HOST    SPI2_HOST
#define LCD_PIN_MOSI 23
#define LCD_PIN_CLK  19
#define LCD_PIN_CS   22
#define LCD_PIN_DC   21
#define LCD_PIN_RST  18
#define LCD_PIN_BCKL 5

/* LCD config */
#define LCD_WIDTH 		(320)
#define LCD_HEIGHT 		(170)
#define LCD_SWAP_XY   	(true)
#define LCD_MIRROR_X  	(true)
#define LCD_MIRROR_Y  	(false)

#endif
