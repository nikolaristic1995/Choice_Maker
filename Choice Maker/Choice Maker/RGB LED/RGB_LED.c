#include "USART.h"
#include <util/delay.h>
#include "RGB_LED.h"

void RGB_LED_initialize(void){

	RGB_LED_set_red();
}

void RGB_LED_send_logic_zero(void){

	SET_BIT(RGB_LED_PORT, RGB_LED_PIN);
	_delay_us(T0H);

	RESET_BIT(RGB_LED_PORT, RGB_LED_PIN);
	_delay_us(T0L);
}

void RGB_LED_send_logic_one(void){

	SET_BIT(RGB_LED_PORT, RGB_LED_PIN);
	_delay_us(T1H);

	RESET_BIT(RGB_LED_PORT, RGB_LED_PIN);
	_delay_us(T1L);
}

void  RGB_LED_send_byte(uint8_t byte){
	
	uint8_t digit_position = 0b10000000;

	for(uint8_t number_of_digits = 0; number_of_digits < 8; number_of_digits++){

		if (byte & digit_position)RGB_LED_send_logic_one();
		
		else RGB_LED_send_logic_zero();
		
		digit_position >>= 1;
	}
}

void RGB_LED_send_reset(void){

	RESET_BIT(RGB_LED_PORT, RGB_LED_PIN);
	_delay_us(RESET_TIME);
}

void RGB_LED_set_color(uint8_t red, uint8_t green, uint8_t blue){
	
	for(uint8_t number_of_attempts = 0; number_of_attempts < NUMBER_OF_ATTEMPTS; number_of_attempts++){
		
		RGB_LED_send_byte(red);
		RGB_LED_send_byte(green);
		RGB_LED_send_byte(blue);
		RGB_LED_send_reset();
	}
}

void RGB_LED_set_light_blue(void){
	
	RGB_LED_set_color(DONT_SHINE, SHINE, SHINE);
}

void RGB_LED_set_dark_blue(void){

	RGB_LED_set_color(DONT_SHINE, DONT_SHINE, SHINE);
}

void RGB_LED_set_green(void){

	RGB_LED_set_color(DONT_SHINE, SHINE, DONT_SHINE);
}

void RGB_LED_set_yellow(void){

	RGB_LED_set_color(SHINE, SHINE, DONT_SHINE);
}

void RGB_LED_set_pink(void){

	RGB_LED_set_color(SHINE, DONT_SHINE, SHINE);
}

void RGB_LED_set_red(void){

	RGB_LED_set_color(SHINE, DONT_SHINE, DONT_SHINE);
}

void RGB_LED_set_white(void){
	
	RGB_LED_set_color(SHINE, SHINE, SHINE);
}

void RGB_LED_light_show(void){
	
	RGB_LED_set_light_blue();
	_delay_ms(500);
	
	RGB_LED_set_green();
	_delay_ms(500);
	
	RGB_LED_set_dark_blue();
	_delay_ms(500);
	
	RGB_LED_set_red();
	_delay_ms(500);
	
	 RGB_LED_set_yellow();
	_delay_ms(500);
	
	RGB_LED_set_pink();
	_delay_ms(500);	
	
	RGB_LED_set_white();
	_delay_ms(500);	
}
