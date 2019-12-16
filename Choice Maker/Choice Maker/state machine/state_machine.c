#include <avr/interrupt.h>
#include <avr/io.h>
#include "common.h"
#include "ports.h"
#include "timer_0.h"
#include "USART.h"
#include "buttons_and_switches.h"
#include "I2C.h"
#include "LCD.h"
#include "RGB_LED.h"
#include "PWM_2.h"
#include "buzzer.h"
#include "state_machine.h"
#include <util/delay.h>
#include "state_machine.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

volatile uint8_t event = NOTHING_IS_HAPPENING;
volatile uint8_t state = WAITING;

volatile uint8_t choice_counter = 0;
char* choice[MAXIMUM_NUMBER_OF_CHOICES][MAXIMUM_NUMBER_OF_CHARACTERS];

void state_machine_initialize(void){

	RGB_LED_set_red();
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" PA CAAAO MACO! ");
	_delay_ms(3100);
	LCD_print_waiting_state();
	
	srand(time(0));
	
	event = NOTHING_IS_HAPPENING;
	state = WAITING;
	RGB_LED_set_green();
	
	if(USART_character_is_received()){
	
		USART_get_string(); //empty the buffer
		_delay_us(1700); //ubaguje se displej ako se ne stavi delay
		UDR; //to empty the UDR buffer. character 10 seems to make problem
	}
}

uint8_t state_machine_get_event(void){
	
	if(USART_character_is_received())return CHOICE_IS_BEING_RECEIVED;
	
	else if(buttons_and_switches_start_button_is_pushed() && choice_counter > 1)return START; //mora biti bar dva izbora
	
	else if(buttons_and_switches_start_button_is_pushed())return ERROR;
	
	else return NOTHING_IS_HAPPENING;
}

void LCD_print_waiting_state(void){
	
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" Unesi svoj ");
	char character = common_get_digit(choice_counter + 1);
	LCD_send_character(character);
	LCD_print(".");
	LCD_set_column_and_row(0, 1);
	LCD_print("     izbor:     ");
}

void state_machine_update_choice_matrix(void){

	RGB_LED_set_red();
	char* string;
	
	if(choice_counter < MAXIMUM_NUMBER_OF_CHOICES){
		
		string = USART_get_string();
		
		if(strlen(string) > MAXIMUM_NUMBER_OF_CHARACTERS){
			
			LCD_clear_screen();
			LCD_set_column_and_row(0,0);
			LCD_print("Prekoracila si");
			LCD_set_column_and_row(0,1);
			LCD_print("opseg karaktera");
			
			_delay_us(1700); //ubaguje se displej ako se ne stavi delay
			UDR; //to empty the UDR buffer. character 10 seems to make problem
			
			_delay_ms(3000);	
			
			if(choice_counter == MAXIMUM_NUMBER_OF_CHOICES){
				
				LCD_clear_screen();
				LCD_set_column_and_row(0,0);
				LCD_print("Unela si maximum");
				LCD_set_column_and_row(0,1);
				LCD_print(" broj izbora :) ");
			}
			
			else LCD_print_waiting_state();		
		}
		
		else{
			
			strcpy(choice[choice_counter], string);
			choice_counter++;
		
			//for(uint8_t i = 0; i < choice_counter; i++)USART_print_line(choice[i]);  //proveravao stringove
	
			_delay_us(1700); //ubaguje se displej ako se ne stavi delay
			UDR; //to empty the UDR buffer. character 10 seems to make problem
		
			if(choice_counter == MAXIMUM_NUMBER_OF_CHOICES){
			
				LCD_clear_screen();
				LCD_set_column_and_row(0,0);
				LCD_print("Unela si maximum");
				LCD_set_column_and_row(0,1);
				LCD_print(" broj izbora :) ");
			}
		
			else LCD_print_waiting_state();
		
		}
		
	}
	
	else{
		
		USART_get_string();	//praznjenje buffera
		_delay_us(1700);	//zakuca se bez ovoga
		UDR;				//praznjenje buffera
		
		LCD_clear_screen();
		LCD_set_column_and_row(0,0);
		LCD_print(" STOP IT IVANA! ");
		LCD_set_column_and_row(0,1);
		LCD_print("   IT HURTS!  ");
	}
	
	buzzer_activate_countdown_tone();
	RGB_LED_set_green();
}

void state_machine_start(void){
	
	state = BINGOING_CHOICE;
	
	RGB_LED_set_dark_blue();
	
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" Otpusti taster ");
	LCD_set_column_and_row(0, 1);
	LCD_print("i sacekaj odluku");
	
	buzzer_activate_button_has_been_pushed_tone();
	while(buttons_and_switches_start_button_is_pushed());
	
	if(USART_character_is_received()){
			
		USART_get_string(); //empty the buffer
		_delay_us(1700); //ubaguje se displej ako se ne stavi delay
		UDR; //to empty the UDR buffer. character 10 seems to make problem
	}
}

void state_machine_bingo_choice(void){
	
	uint32_t time_ms = 200;
	
	for(uint8_t number_of_dramatic_increments = 0; number_of_dramatic_increments < 7; number_of_dramatic_increments++){
		
		if(number_of_dramatic_increments == 0)RGB_LED_set_light_blue();	
		
		else if(number_of_dramatic_increments == 1)RGB_LED_set_green();
		
		else if(number_of_dramatic_increments == 2)RGB_LED_set_dark_blue();	
		
		else if(number_of_dramatic_increments == 3)RGB_LED_set_red();
		
		else if(number_of_dramatic_increments == 4)RGB_LED_set_yellow();		
		
		else if(number_of_dramatic_increments == 5)RGB_LED_set_white();
		
		else if(number_of_dramatic_increments == 6)RGB_LED_set_pink();
		
		
		for(uint8_t number_of_choices = 0; number_of_choices < choice_counter; number_of_choices++){
		
			if(strlen(choice[number_of_choices]) > 16){
		
				LCD_clear_screen();
		
				LCD_set_column_and_row(0, 0);
				for(uint8_t i = 0; i < 16; i++)LCD_send_character(choice[number_of_choices][i]);
		
				LCD_set_column_and_row(0, 1);
				for(uint8_t i = 16; i < strlen(choice[number_of_choices]); i++)LCD_send_character(choice[number_of_choices][i]);
			
				buzzer_activate_button_has_been_pushed_tone();
				timer_0_delay_in_milliseconds(time_ms);
			}
		
			else{
		
				LCD_clear_screen();
				LCD_set_column_and_row(0,0);
				LCD_print(choice[number_of_choices]);
				buzzer_activate_button_has_been_pushed_tone();
				timer_0_delay_in_milliseconds(time_ms);	
			
			}
		}
		
		time_ms += 30;
	}
	
	srand(strlen(choice[0]) + strlen(choice[1]));
	int final_choice = rand() % choice_counter;
	
	if((rand() % choice_counter + 1) == choice_counter){
		
		final_choice = choice_counter;
		
		LCD_clear_screen();
		LCD_set_column_and_row(0, 0);
		LCD_print(" Idi u kafanu! ");
	}
	
	else if((rand() % choice_counter + 2) == (choice_counter + 1)){
		
		final_choice = choice_counter + 1;
		
		LCD_clear_screen();
		LCD_set_column_and_row(0, 0);
		LCD_print("  Drop it like  ");	
		LCD_set_column_and_row(0, 1);
		LCD_print("    it's hot!     ");
	}
	
	else if((rand() % choice_counter + 3) == (choice_counter + 2)){
			
		final_choice = choice_counter + 2;
			
		LCD_clear_screen();
		LCD_set_column_and_row(0, 0);
		LCD_print("Zagrli nekog bez");
		LCD_set_column_and_row(0, 1);
		LCD_print("ikakve emocije!");
	}
	
	else{
		
		if(strlen(choice[final_choice]) > 16){
			
			LCD_clear_screen();
			
			LCD_set_column_and_row(0, 0);
			for(uint8_t i = 0; i < 16; i++)LCD_send_character(choice[final_choice][i]);
			
			LCD_set_column_and_row(0, 1);
			for(uint8_t i = 16; i < strlen(choice[final_choice]); i++)LCD_send_character(choice[final_choice][i]);
		}
		
		else{
			
			LCD_clear_screen();
			LCD_set_column_and_row(0, 0);
			LCD_print(choice[final_choice]);
			
		}
	
	}
		
	choice_counter = 0;
	
	RGB_LED_set_red();
	buzzer_activate_treatment_is_finished_tone();
	
	while(!buttons_and_switches_start_button_is_pushed());
	
	state = WAITING;
	RGB_LED_set_dark_blue();
	
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" Otpusti taster ");
	LCD_set_column_and_row(0, 1);
	LCD_print("i zapocni ponovo");
	
	buzzer_activate_button_has_been_pushed_tone();
	
	while(buttons_and_switches_start_button_is_pushed());
	
	LCD_print_waiting_state();
	RGB_LED_set_green();
	
	if(USART_character_is_received()){
			
		USART_get_string(); //empty the buffer
		_delay_us(1700); //ubaguje se displej ako se ne stavi delay
		UDR; //to empty the UDR buffer. character 10 seems to make problem
	}
}

void state_machine_error_message(void){
	
	RGB_LED_set_red();
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print("Moras uneti bar ");
	LCD_set_column_and_row(0, 1);
	LCD_print("dva izbora maco ");
	buzzer_activate_button_has_been_pushed_tone();
	while(buttons_and_switches_start_button_is_pushed());
	LCD_print_waiting_state();
	RGB_LED_set_green();
	
	if(USART_character_is_received()){
			
		USART_get_string(); //empty the buffer
		_delay_us(1700); //ubaguje se displej ako se ne stavi delay
		UDR; //to empty the UDR buffer. character 10 seems to make problem
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
