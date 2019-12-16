#define F_CPU 8000000UL
#include <util/delay.h>
#include "I2C.h"
#include "LCD.h"

uint8_t led_pin;

void putnibble(char t)
{
	t <<= 4;
	i2c_send_packet(led_pin |= 0x04, SLA_W);		//SLA_W je i2c adresa shifotvana u levo za 1
	_delay_us(50);
	i2c_send_packet(led_pin | t, SLA_W);
	i2c_send_packet(led_pin &= ~0x04, SLA_W);
	_delay_us(50);
}

void LCD_send_byte(char c, char rs)
{
	char highc = 0;
	highc = c >> 4;
	if (rs == LCD_COMMAND)
		i2c_send_packet(led_pin &=~ 0x01, SLA_W);
	else
		i2c_send_packet(led_pin |= 0x01, SLA_W);
	putnibble(highc);
	putnibble(c);
}

void LCD_send_character(char c)
{
	char highc = 0;

	highc = c >> 4;
	i2c_send_packet (led_pin |= 0x01, SLA_W);
	putnibble(highc);
	putnibble(c);
}

void LCD_initialize()
{
	led_pin = 0;
	i2c_init();		//inicijalizovano u main-u
	_delay_ms(15);
	putnibble(0b00000011);
	_delay_ms(4);
	putnibble(0b00000011);
	_delay_us(100);
	putnibble(0b00000011);
	_delay_ms(1);
	putnibble(0b00000010);
	_delay_ms(1);
	LCD_send_byte(0x28, LCD_COMMAND);
	_delay_ms(1);
	LCD_send_byte(0x0C, LCD_COMMAND);
	_delay_ms(1);
	LCD_send_byte(0x06, LCD_COMMAND);
	_delay_ms(1);
	i2c_send_packet(led_pin |= 0x08, SLA_W);
	i2c_send_packet(led_pin &=~ 0x02, SLA_W);
	
	LCD_clear_screen();
}

void LCD_clear_screen()
{
	LCD_send_byte(0x01, LCD_COMMAND);
	_delay_us(1700);
}

void LCD_set_column_and_row(char col, char row)
{
	char adr;

	adr = 0x40*row + col;
	adr |= 0x80;
	LCD_send_byte(adr, LCD_COMMAND);
}

void LCD_print(/*const*/ char *str)
{
	uint8_t i = 0;

	/*
	for(i = 0; str[i] != '\0'; i++)
		lcd1602_send_char(str[i]);
	*/	
	
	while (str[i] != '\0')
	{
		LCD_send_character(str[i]);
		i++;
	}
}

void LCD_blink_cursor(uint8_t on_off)
{
	if(on_off)
		LCD_send_byte(0b1111,LCD_COMMAND);	//blink on
	else
		LCD_send_byte(0b1100,LCD_COMMAND);	//blink off
}

void LCD_print_first_row(char* string){
	
	LCD_clear_screen();
	
	LCD_set_column_and_row(0, 0);
	LCD_print(string);
}

void LCD_print_second_row(char* string){
	
	LCD_set_column_and_row(0, 1);
	LCD_print(string);
}

void LCD_print_in_two_rows(char* first_row_string, char* second_row_string){
	
	LCD_print_first_row(first_row_string);
	LCD_print_second_row(second_row_string);
}
