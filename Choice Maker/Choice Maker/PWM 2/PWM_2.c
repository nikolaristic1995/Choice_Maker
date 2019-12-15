#include <math.h>
#include "ports.h"
#include "PWM_2.h"
#include "buzzer.h"

void PWM_2_initialize(void){
	
	ports_set_OC2_pin_direction_to_output();
	TCCR2 = TCCR2_INITIAL_STATE;
}

void PWM_2_enable_non_inverted_wave_form(void){

	TCCR2 = (TCCR2 & (~(1 << COM20))) | (1 << COM21);
}

void PWM_2_disable(void){
	
	TCCR2 &= ~((1 << COM20) | (1 << COM21));
	RESET_BIT(PORTD, D7);
}

void PWM_2_set_duty_cycle_percentage(float percantage){
	
	OCR2 = (uint8_t)(round(percantage * 255.0f / 100.0f));
}

float PWM_2_get_duty_cycle_percentage(void){
	
	return ((float)OCR2 * 100.0f / 255.0f);
}

void PWM_2_minimaly_increase_duty_cycle_percantage(void){
	
	if(OCR2 < 255)OCR2++;
}

void PWM_2_minimaly_decrease_duty_cycle_percantage(void){
	
	if(OCR2 > 0)OCR2--;
}
