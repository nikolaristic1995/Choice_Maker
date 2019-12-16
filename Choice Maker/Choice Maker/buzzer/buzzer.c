#include "buzzer.h"
#include "timer_0.h"
#include "PWM_2.h"

void buzzer_initialize(void){
	
	//buzzer_activate_countdown_tone();
}

void buzzer_activate_tone(uint8_t duty_cycle_percentage, uint32_t time_of_enabled_tone){
	
	PWM_2_set_duty_cycle_percentage(duty_cycle_percentage);
	PWM_2_enable_non_inverted_wave_form();
	
	timer_0_delay_in_milliseconds(time_of_enabled_tone);
	PWM_2_disable();
}

void buzzer_activate_button_has_been_pushed_tone(void){
	
	buzzer_activate_tone(196, 50);
}

void buzzer_activate_interaction_tone(void){
	
	buzzer_activate_tone(50, 100);
}

void buzzer_activate_bingo_tone(void){
	
	buzzer_activate_tone(255, 100);
}

void buzzer_activate_choice_has_been_made_tone(void){

	PWM_2_set_duty_cycle_percentage(50);

	for(uint8_t i = 0; i < 3; i++){
		
		for(uint8_t j = 0; j < 3; j++){
			
			PWM_2_enable_non_inverted_wave_form();
			timer_0_delay_in_milliseconds(50);
			
			PWM_2_disable();
			timer_0_delay_in_milliseconds(50);
		}
		
		timer_0_delay_in_milliseconds(400);
	}
}
