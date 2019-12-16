#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 8000000UL
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define NEW_LINE 10
#define ENTER 13

extern char string[32];

void					USART_initialize						(void);

void					USART_initialize_with_baud_rate			(long USART_BAUDRATE);

char					USART_get_character						(void);

char*					USART_get_string						(void);

void					USART_print_character					(char character);

void					USART_print								(char *string);

void					USART_print_line						(char *string);

void					USART_print_number						(uint32_t number);

void					USART_print_float						(float float_number);

void					USART_echo								(void);

bool					USART_character_is_received				(void);

void					USART_empty_the_RX_buffer				(void);

#endif /* USART_H_ */
