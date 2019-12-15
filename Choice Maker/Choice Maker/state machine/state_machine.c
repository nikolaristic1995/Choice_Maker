#include <avr/interrupt.h>
#include <avr/io.h>
#include "common.h"
#include "ports.h"
#include "timer_0.h"
#include "USART.h"
#include "I2C.h"
#include "LCD.h"
#include "RGB_LED.h"
#include "PWM_2.h"
#include "buzzer.h"
#include "state_machine.h"
#include <util/delay.h>
#include "state_machine.h"
#include <string.h>

volatile uint8_t event = NOTHING_IS_HAPPENING;
volatile uint8_t state = WAITING;
volatile uint8_t choice_counter = 0;
char* choice[MAXIMUM_NUMBER_OF_CHOICES];
//choice[redni broj izbora][choice string]
void state_machine_initialize(void){

	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" Pa caaao maco! ");
	_delay_ms(3100);
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" Unesi svoj 1.  ");
	LCD_set_column_and_row(0, 1);
	LCD_print("     izbor:     ");
	RGB_LED_set_green();
	
	event = NOTHING_IS_HAPPENING;
	state = WAITING;
}

uint8_t state_machine_get_event(void){
	
	if(USART_character_is_received())return CHOICE_IS_BEING_RECEIVED;
	
	/*else if(buttons_and_switches_pause_button_is_pushed())return PAUSE;
	
	else if(buttons_and_switches_save_parameters_button_is_pushed())return SAVE;
	
	else if(buttons_and_switches_cursor_up_button_is_pushed())return CURSOR_UP;
	
	else if(buttons_and_switches_cursor_down_button_is_pushed())return CURSOR_DOWN;
	
	else if(buttons_and_switches_increment_by_1_button_is_pushed())return INCREMENT_BY_1;
	
	else if(buttons_and_switches_increment_by_10_button_is_pushed())return INCREMENT_BY_10;
	
	else if(buttons_and_switches_increment_by_100_button_is_pushed())return INCREMENT_BY_100;
	
	else if(buttons_and_switches_increment_by_1000_button_is_pushed())return INCREMENT_BY_1000;
	
	else if(buttons_and_switches_increment_by_10000_button_is_pushed())return INCREMENT_BY_10000;
	
	else if(buttons_and_switches_start_button_is_pushed())return START;
	
	else if(buttons_and_switches_restart_button_is_pushed())return RESTART;*/
	
	else return NOTHING_IS_HAPPENING;
}

void state_machine_update_choice_matrix(void){

    choice[choice_counter] = USART_get_string();
	choice_counter++;
	
	LCD_clear_screen();
	LCD_set_column_and_row(0,0);
	LCD_print(choice[choice_counter - 1]);
	
	UDR; //to empty the UDR buffer. character 10 seems to make problem
	
}

void state_machine_routine(void){

	event = state_machine_get_event();

	switch(state){
		
		case WAITING: {
			
			switch(event){
				
				case CHOICE_IS_BEING_RECEIVED: state_machine_update_choice_matrix();break;
			}
			
			break;
		}
	}
}
