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

volatile uint8_t event = NOTHING_IS_HAPPENING;
volatile uint8_t state = WAITING;

volatile uint8_t choice_counter = 0;
char* choice[MAXIMUM_NUMBER_OF_CHOICES];

void state_machine_initialize(void){

	RGB_LED_set_red();
	LCD_clear_screen();
	LCD_set_column_and_row(0, 0);
	LCD_print(" PA CAAAO MACO! ");
	_delay_ms(3100);
	LCD_print_waiting_state();
	
	event = NOTHING_IS_HAPPENING;
	state = WAITING;
	RGB_LED_set_green();
}

uint8_t state_machine_get_event(void){
	
	if(USART_character_is_received())return CHOICE_IS_BEING_RECEIVED;
	
	else if(buttons_and_switches_start_button_is_pushed() && choice_counter > 1)return START; //mora biti bar dva izbora
	
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
//8 izbora je limit
void state_machine_update_choice_matrix(void){

	RGB_LED_set_red();
	
	if(choice_counter < MAXIMUM_NUMBER_OF_CHOICES){
		
		choice[choice_counter] = USART_get_string();
		
		if(strlen(choice[choice_counter]) > 32){
			
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
			
			choice_counter++;
		
			for(uint8_t i = 0; i < choice_counter; i++)USART_print_line(choice[i]);
	
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
	LCD_clear_screen(); //ovo mozda nece biti potrebno
	RGB_LED_set_red();  //ovo mozda nece biti potrebno	
}

void state_machine_bingo_choice(void){
	
	uint8_t time_ms = 200;
	
	for(uint8_t number_of_dramatic_increments = 0; number_of_dramatic_increments < 5; number_of_dramatic_increments++){
		
		for(uint8_t number_of_choices = 0; number_of_choices < choice_counter; number_of_choices++){
		
			LCD_clear_screen();
			LCD_set_column_and_row(0,0);
			LCD_print(choice[number_of_choices]);
			buzzer_activate_button_has_been_pushed_tone();
			_delay_ms(100);
			
		}
		
		time_ms += 100;
	}
	
	buzzer_activate_treatment_is_finished_tone();
	while(1);
}

void state_machine_routine(void){

	event = state_machine_get_event();

	switch(state){
		
		case WAITING: {
			
			switch(event){
				
				case START: state_machine_start();break;
				
				case CHOICE_IS_BEING_RECEIVED: state_machine_update_choice_matrix();break; //ulazi beskonacno u ovo
				
			}
			
			break;
		}
		
		case BINGOING_CHOICE: {
			
			switch(event){
						
				default: state_machine_bingo_choice();
			}
			
		}
	}
}
