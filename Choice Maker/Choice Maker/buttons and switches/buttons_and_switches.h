#ifndef BUTTONS_AND_SWITCHES_H_
#define BUTTONS_AND_SWITCHES_H_

#include "ports.h"

#define START_PARAMETERS_BUTTON_PORT PORTA

#define START_BUTTON_PIN 7


#define NUMBER_OF_BUTTONS 12
#define NUMBER_OF_NO_BOUNCES 25

#define START_BUTTON_ARRAY_INDEX 0

extern volatile uint8_t bounce[NUMBER_OF_BUTTONS];

void					buttons_and_switches_initialize										(void);

uint8_t					buttons_and_switches_start_button_is_pushed							(void);

#endif /* BUTTONS_AND_SWITCHES_H_ */
