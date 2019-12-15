#ifndef RGB_LED_H_
#define RGB_LED_H_

#include "ports.h"

#define RGB_LED_PORT PORTA
#define RGB_LED_PIN 6

#define T0H 0.35
#define T0L 1.36

#define T1H 1.36
#define T1L 0.35

#define RESET_TIME 50

#define NUMBER_OF_ATTEMPTS 6

#define SHINE 255
#define DONT_SHINE 0

void					RGB_LED_initialize							(void);

void					RGB_LED_send_logic_zero						(void);

void					RGB_LED_send_logic_one						(void);

void					RGB_LED_send_byte							(uint8_t byte);

void					RGB_LED_send_reset							(void);

void					RGB_LED_set_color							(uint8_t red, uint8_t green, uint8_t blue);

void					RGB_LED_set_light_blue						(void);

void					RGB_LED_set_dark_blue						(void);

void					RGB_LED_set_green							(void);

void					RGB_LED_set_yellow							(void);

void					RGB_LED_set_pink							(void);

void					RGB_LED_set_red								(void);

void					RGB_LED_light_show							(void);

#endif /* RGB_LED_H_ */
