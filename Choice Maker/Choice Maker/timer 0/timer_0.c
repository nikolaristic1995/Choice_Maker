#include <avr/interrupt.h>
#include <stdbool.h>
#include "timer_0.h"
//#include "GLCD.h"
#include "buzzer.h"

volatile uint32_t timer_counter = 0;
volatile uint16_t reset_sum_of_impulses_timer = 0;
volatile uint8_t reset_sum_of_impulses_time_count = RESET_SUM_OF_IMPULSES_TIME_COUNT;
volatile uint32_t countdown_timer = 0;
volatile uint8_t number_of_counts = NUMBER_OF_COUNTS;
volatile uint16_t timer_random_count = 0;

ISR (TIMER0_COMP_vect){

	timer_counter++;
	countdown_timer++;
	reset_sum_of_impulses_timer++;
	timer_random_count++;
}

void timer_0_initialize(void){

	TCCR0  = TCCRO_INITIAL_STATE;
	TCNT0  = TCNT0_INITIAL_STATE;
	OCR0   = OCR0_INITIAL_STATE;
	TIMSK  = ENABLE_TIMER_0_OUTPUT_COMPARE_MATCH_INTERRUPT;
}

void timer_0_delay_in_milliseconds(uint32_t time_of_delay_in_milliseconds){

	timer_counter = 0;
	while(timer_counter != time_of_delay_in_milliseconds);
}

void timer_0_reset_sum_of_impulses_time(void){
	
	reset_sum_of_impulses_timer = 0;
	reset_sum_of_impulses_time_count = RESET_SUM_OF_IMPULSES_TIME_COUNT;
}

uint8_t timer_0_get_reset_sum_of_impulses_time_count(void){
	
	return reset_sum_of_impulses_time_count;
}

uint8_t	timer_0_reset_sum_of_impulses_time_has_passed(void){
	
	if(reset_sum_of_impulses_timer == ONE_SECOND){
		
		reset_sum_of_impulses_timer = 0;
		reset_sum_of_impulses_time_count--;
		
		//GLCD_print_sum_of_impulses_time_count();
	}
	
	if(!reset_sum_of_impulses_time_count)return true;
	
	else return false;
}

void timer_0_reset_countdown_timer(void){
	
	countdown_timer = 0;
}

void timer_0_reset_number_of_counts(void){
	
	number_of_counts = NUMBER_OF_COUNTS;
}

uint8_t timer_0_get_number_of_counts(void){
	
	return number_of_counts;
}

uint8_t timer_0_countdown_is_over(void){

	if(countdown_timer == ONE_SECOND){
		
		countdown_timer = 0;
		number_of_counts--;
		
		//GLCD_print_number_of_counts();
		
		//if(number_of_counts)buzzer_activate_countdown_tone();
	}
	
	if(!number_of_counts)return true;
	
	else return false;
}

uint16_t timer_0_get_timer_random_count(void){
	
	return timer_random_count;
}
