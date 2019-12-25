#include "common.h"
#include "ports.h"
#include "timer_0.h"
#include "USART.h"
#include "buttons_and_switches.h"
#include "LCD.h"
#include "RGB_LED.h"
#include "buzzer.h"
#include "state_machine.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

volatile uint8_t event = NOTHING_IS_HAPPENING;
volatile uint8_t state = WAITING;

volatile uint8_t choice_counter = 0;
char/***/ choice[MAXIMUM_NUMBER_OF_CHOICES][MAXIMUM_NUMBER_OF_CHARACTERS];

void state_machine_initialize(void){

	RGB_LED_set_pink();
	
	LCD_print_first_row(" PA CAAAO MACO! ");
	_delay_ms(3100);
	state_machine_print_waiting_state();
	
	event = NOTHING_IS_HAPPENING;
	state = WAITING;
	
	RGB_LED_set_green();
	
	buzzer_activate_interaction_tone();
	
	USART_empty_the_RX_buffer();
}

uint8_t state_machine_get_event(void){
	
	if(USART_character_is_received())return CHOICE_IS_BEING_RECEIVED;
	
	else if(buttons_and_switches_start_button_is_pushed() && choice_counter > 1)return START; //mora biti bar dva izbora
	
	else if(buttons_and_switches_start_button_is_pushed())return ERROR;
	
	else return NOTHING_IS_HAPPENING;
}

void state_machine_print_waiting_state(void){
	
	LCD_print_first_row(" Unesi svoj ");
	char character = common_get_digit(choice_counter + 1);
	LCD_send_character(character);
	LCD_send_character('.');
	LCD_print_second_row("     izbor:     ");
}

void state_machine_update_choice_matrix(void){

	RGB_LED_set_red();
	
	char* string = USART_get_string();
	_delay_us(1700);					//ubaguje se displej ako se ne stavi delay
	UDR;								//to empty the UDR buffer. character 10 seems to make problem
	
	if(choice_counter < MAXIMUM_NUMBER_OF_CHOICES){
		
		if(strlen(string) > MAXIMUM_NUMBER_OF_CHARACTERS){
			
			LCD_print_in_two_rows("Prekoracila si", "opseg karaktera");
			
			_delay_ms(3000);	
			
			if(choice_counter == MAXIMUM_NUMBER_OF_CHOICES){
				
				RGB_LED_set_red();
				LCD_print_in_two_rows("Unela si maximum", " broj izbora :) ");
			}
			
			else state_machine_print_waiting_state();		
		}
		
		else{
			
			strcpy(choice[choice_counter], string);
			choice_counter++;
			
			USART_print_number(choice_counter);
			USART_print(". ");
			USART_print_line(string);
		
			if(choice_counter == MAXIMUM_NUMBER_OF_CHOICES){
				
				RGB_LED_set_red();
				LCD_print_in_two_rows("Unela si maximum", " broj izbora :) ");
			}
		
			else state_machine_print_waiting_state();
		
		}
		
	}
	
	else {
		
		LCD_print_in_two_rows("STOP IT, DAMN IT", "   IT HURTS!  ");
	
		_delay_ms(3000);
	
		LCD_print_in_two_rows("PRITISNI TASTER", "  BEZ EMOCIJE!  ");	
	}
	
	buzzer_activate_interaction_tone();
	RGB_LED_set_green();
	
	USART_empty_the_RX_buffer();
}

void state_machine_start(void){
	
	state = BINGOING_CHOICE;
	
	RGB_LED_set_dark_blue();
	
	LCD_print_in_two_rows(" Otpusti taster ", "i sacekaj odluku");
	
	buzzer_activate_button_has_been_pushed_tone();
	while(buttons_and_switches_start_button_is_pushed());
}

void state_machine_bingo_choice(void){
	
	uint32_t time_ms = 50;
	
	for(uint8_t number_of_dramatic_increments = 0; number_of_dramatic_increments < 7; number_of_dramatic_increments++){
		
		LCD_set_column_and_row(0,1);
		LCD_print("                ");
		
		if(number_of_dramatic_increments == 0)RGB_LED_set_light_blue();	
		
		else if(number_of_dramatic_increments == 1)RGB_LED_set_green();
		
		else if(number_of_dramatic_increments == 2)RGB_LED_set_dark_blue();	
		
		else if(number_of_dramatic_increments == 3)RGB_LED_set_red();
		
		else if(number_of_dramatic_increments == 4)RGB_LED_set_yellow();		
		
		else if(number_of_dramatic_increments == 5)RGB_LED_set_white();
		
		else if(number_of_dramatic_increments == 6)RGB_LED_set_pink();
		
		
		for(uint8_t number_of_choices = 0; number_of_choices < choice_counter; number_of_choices++){
			
			for(uint8_t i = 0; i < 3; i++){
						
				LCD_clear_screen();
				LCD_set_column_and_row(0,0);
				LCD_set_column_and_row(0,1);
				LCD_print("                ");
			}
			LCD_set_column_and_row(0,1);
			LCD_print("                ");
			LCD_set_column_and_row(0,0);
			LCD_print_first_row(choice[number_of_choices]);
			LCD_set_column_and_row(0,1);
			LCD_print("                ");
			
			buzzer_activate_bingo_tone();
			timer_0_delay_in_milliseconds(time_ms);
		}
		
		time_ms += 10;
	}
	
	srand(strlen(choice[0]) + strlen(choice[1]) + choice_counter + timer_0_get_timer_random_count());
	
	if((rand() % choice_counter + 1) == choice_counter)LCD_print_in_two_rows("Drink alcohol &", "enjoy the moment");
	
	//else if((rand() % choice_counter + 2) == (choice_counter + 1))LCD_print_in_two_rows("  Drop it like  ", "    it's hot!     ");
	
	//else if((rand() % choice_counter + 3) == (choice_counter + 2))LCD_print_in_two_rows("Zagrli nekog bez", "ikakve emocije!");
							
	else {
		
		for(uint8_t i = 0; i < 3; i++){
			
			LCD_clear_screen();
			LCD_set_column_and_row(0,0);
			LCD_set_column_and_row(0,1);
			LCD_print("                ");
		}
		LCD_set_column_and_row(0,1);
		LCD_print("                ");
		LCD_set_column_and_row(0,0);
		LCD_print_first_row(choice[rand() % choice_counter]);
		LCD_set_column_and_row(0,1);
		LCD_print("                ");
	}
		
	choice_counter = 0;
	
	RGB_LED_set_red();
	buzzer_activate_choice_has_been_made_tone();
	
	while(!buttons_and_switches_start_button_is_pushed());
	
	state = WAITING;
	RGB_LED_set_dark_blue();
	
	LCD_print_in_two_rows(" Otpusti taster ","i zapocni ponovo");

	buzzer_activate_button_has_been_pushed_tone();
	
	while(buttons_and_switches_start_button_is_pushed());
	
	state_machine_print_waiting_state();
	
	RGB_LED_set_green();
	buzzer_activate_interaction_tone();
	
	USART_print_line("");
	USART_empty_the_RX_buffer();
}

void state_machine_error_message(void){
	
	if(choice_counter < 2){
	
		RGB_LED_set_red();
	
		LCD_print_in_two_rows("Moras uneti bar ", "dva izbora maco ");

		buzzer_activate_button_has_been_pushed_tone();
	
		_delay_ms(2500);
	
		while(buttons_and_switches_start_button_is_pushed());
	
		state_machine_print_waiting_state();
		
		RGB_LED_set_green();
		buzzer_activate_interaction_tone();
		
		USART_empty_the_RX_buffer();
	}
}

void state_machine_routine(void){

	event = state_machine_get_event();

	switch(state){
		
		case WAITING: {
			
			switch(event){
				
				case START: state_machine_start();break;
				
				case CHOICE_IS_BEING_RECEIVED: state_machine_update_choice_matrix();break; //ulazi beskonacno u ovo
				
				case ERROR: state_machine_error_message();break;
				
			}
			
			break;
		}
		
		case BINGOING_CHOICE: {
			
			switch(event){
						
				default: state_machine_bingo_choice();break;
			}
			
		}
	}
}
