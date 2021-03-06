#include "common.h"
#include "ports.h"
#include "timer_0.h"
#include "USART.h"
#include "buttons_and_switches.h"
#include "LCD.h"
#include "RGB_LED.h"
#include "PWM_2.h" 
#include "buzzer.h"
#include "state_machine.h"
#include <avr/interrupt.h>

int main(void){
	
    sei();
	
	RGB_LED_initialize();
    LCD_initialize();
    ports_initialize();
    timer_0_initialize();
    PWM_2_initialize();
	USART_initialize();
	buttons_and_switches_initialize();
	buzzer_initialize();
	state_machine_initialize();

	USART_print_line("APLIKACIJA JE ZAPOCETA <3");
	
    while (INFINITE_LOOP){
		
		state_machine_routine();
    } 
}

//ne radi ispis u dva reda, plus clearovanje bufera moze da zakoci aplikaciju. Testiraj i na mobilnom.

//Svi projektni kodovi se mogu naci na GMX mailu.
