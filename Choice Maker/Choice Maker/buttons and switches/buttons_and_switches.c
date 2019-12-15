#include <stdbool.h>
#include "buttons_and_switches.h"

volatile uint8_t bounce[NUMBER_OF_BUTTONS];

void  buttons_and_switches_initialize(void){
	
	for(uint8_t button_array_index = 0; button_array_index < NUMBER_OF_BUTTONS; button_array_index++)bounce[button_array_index] = 0;
}

uint8_t buttons_and_switches_start_button_is_pushed(void){

	uint8_t button_state = false;

	if(!(READ_PIN(PINA, START_BUTTON_PIN))){
		
		if(bounce[START_BUTTON_ARRAY_INDEX] < NUMBER_OF_NO_BOUNCES)bounce[START_BUTTON_ARRAY_INDEX]++;
	}
	
	else bounce[START_BUTTON_ARRAY_INDEX] = 0;
	
	if(bounce[START_BUTTON_ARRAY_INDEX] == NUMBER_OF_NO_BOUNCES)button_state = true;
	if(bounce[START_BUTTON_ARRAY_INDEX] >= NUMBER_OF_NO_BOUNCES)bounce[START_BUTTON_ARRAY_INDEX] = NUMBER_OF_NO_BOUNCES;
	
	return button_state;
}
