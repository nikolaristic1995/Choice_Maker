#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "common.h"
#include "USART.h"
#include <util/delay.h>

char string[32];

void USART_initialize(void){

	USART_initialize_with_baud_rate(9600);
}

void USART_initialize_with_baud_rate(long USART_BAUDRATE){
	
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

char USART_get_character(void){
	
	while((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}

char* USART_get_string(void){
	
	char character = '\0';
	uint8_t iterator = 0;

	do{
		
		character = USART_get_character();
		
	}while(character == NEW_LINE);
	
	while(character != ENTER){
		
		string[iterator] = character;
		iterator++;
		character = USART_get_character();
	}

	string[iterator] = '\0';
	
	return(string);
}

void USART_print_character(char character){
	
	while(!(UCSRA & (1 << UDRE)));
	UDR = character;
}

void USART_print(char *string){
	
	unsigned char i = 0;
	
	while(string[i] != 0){
		
		USART_print_character(string[i]);
		i++;
	}
}

void USART_print_line(char *string){
	
	USART_print(string);
	USART_print_character('\n');
}

void USART_print_number(uint32_t number){

	char string_number[11] = {'0','0','0','0','0','0','0','0','0','0','\0'};
	
	string_number[0] = common_get_tenth_digit(number);
	string_number[1] = common_get_ninth_digit(number);
	string_number[2] = common_get_eighth_digit(number);
	string_number[3] = common_get_seventh_digit(number);
	string_number[4] = common_get_sixth_digit(number);
	string_number[5] = common_get_fifth_digit(number);
	string_number[6] = common_get_fourth_digit(number);
	string_number[7] = common_get_third_digit(number);
	string_number[8] = common_get_second_digit(number);
	string_number[9] = common_get_first_digit(number);

	if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0' && string_number[4] == '0'
	&& string_number[5] == '0' && string_number[6] == '0' && string_number[7] == '0' && string_number[8] == '0'){
		
		char* new_string_number = &string_number[9];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0' && string_number[4] == '0'
	&& string_number[5] == '0' && string_number[6] == '0' && string_number[7] == '0'){
		
		char* new_string_number = &string_number[8];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0' && string_number[4] == '0'
	&& string_number[5] == '0' && string_number[6] == '0'){
		
		char* new_string_number = &string_number[7];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0' && string_number[4] == '0'
	&& string_number[5] == '0'){
		
		char* new_string_number = &string_number[6];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0' && string_number[4] == '0'){
		
		char* new_string_number = &string_number[5];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0' && string_number[3] == '0'){
		
		char* new_string_number = &string_number[4];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0' && string_number[2] == '0'){
		
		char* new_string_number = &string_number[3];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0' && string_number[1] == '0'){
		
		char* new_string_number = &string_number[2];
		USART_print(new_string_number);
	}
	
	else if(string_number[0] == '0'){
		
		char* new_string_number = &string_number[1];
		USART_print(new_string_number);
	}
	
	else{
		
		USART_print(string_number);
	}
}

void USART_print_float(float float_number){
	
	uint16_t integer_part =  trunc(float_number);
	
	float fraction_part = float_number - integer_part;

	uint16_t after_point_number = (uint16_t)(fraction_part * 100);
	
	char string_after_point_number[4] = {'0','0','\0'};
	
	string_after_point_number[0] = common_get_third_digit(after_point_number);
	string_after_point_number[1] = common_get_second_digit(after_point_number);
	
	USART_print_number(integer_part);
	USART_print_character('.');
	USART_print(string_after_point_number);
}

void USART_echo(void){

	char* echo = USART_get_string();
	USART_print_line(echo);
}

bool USART_character_is_received(void){
	
	if((UCSRA & (1 << RXC)) == 0)return false;
	
	else return true;  
}

void USART_empty_the_RX_buffer(void){

	//if(USART_character_is_received()){
	for(uint8_t iterator = 0; iterator < 50; iterator++){
	
				uint8_t junk = UDR;
				_delay_us(1700);		//ubaguje se displej ako se ne stavi delay
	}
	//}
}
