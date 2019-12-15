/*
 * LCD_explanation.h
 *
 * Created: 13/12/2019 23:39:46
 *  Author: Nikola
 */ 


#ifndef LCD_EXPLANATION_H_
#define LCD_EXPLANATION_H_





#endif /* LCD_EXPLANATION_H_ */

/*			LCD_EXPLANATION:

This is code for LCD 2x16 characters.
I2C file is needed to be included in order to adress the LCD. 
In I2C.h set the macros:

							1. #define SDA_pin 1	 //PC1
							2. #define SCL_pin 0	 //PC0
							
							
In LCD.h set the macro:

							1. #define LCD_ADDR 0x3F //use arduino sketch to find out this address
							
Usable functions:

							1. void				LCD_initialize					(void);						//initializes the LCD and I2C
							2. void				LCD_clear_screen				(void);						//clears the screen and resets the postition of the cursor
							3. void				LCD_set_column_and_row			(char column, char row);	//sets the position of the cursor
							4. void				LCD_print						(const char *str);			//prints a string on the screen
							5. void				LCD_blink_cursor				(uint8_t on_off);			//blinks cursor
							6. void				LCD_send_character				(char character);			//prints a character to screen

*/