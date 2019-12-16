/*
 * LCD.h
 *
 * Created: 06/12/2019 19:32:30
 *  Author: Nikola
 *2x16 characters
 */ 


#ifndef LCD_H_
#define LCD_H_


#include <avr/io.h>
/////////////////////////////////////////
/* LCD1602 (HD44780) AVR library
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Rewritten by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#define LED_PIN 0

#define LCD_ADDR 0x3F			
#define SLA_W LCD_ADDR << 1
#define LCD_COMMAND 0
#define LCD_DATA 1

/*
 * LCD initialization
 */
void LCD_initialize(void);

/**
 * Sending byte to lcd
 * @c: byte
 * @rs: type of data
 */
void LCD_send_byte(char c, char rs);

/**
 * Sending char to lcd
 * @c: char
 */
void LCD_send_character(char c);

/*
 * Clear LCD
 */
void LCD_clear_screen(void);

/**
 * Move cursor on lcd
 * @col: X
 * @row: Y
 */
void LCD_set_column_and_row(char col, char row);

/**
 * Writing string on the lcd
 * @str: string
 */
void LCD_print(/*const*/ char *str);

/**
 * Turn on blinking cursor
 */
void LCD_blink_cursor(uint8_t on_off);

void LCD_print_first_row(char* string);

void LCD_print_second_row(char* string);

void LCD_print_in_two_rows(char* first_row_string, char* second_row_string);

#endif /* LCD_H_ */