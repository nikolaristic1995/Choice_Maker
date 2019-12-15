#include <avr/interrupt.h>
#include <avr/io.h>
#include "common.h"
#include "ports.h"
#include "timer_0.h"
#include "USART.h"
#include "buttons_and_switches.h"
#include "I2C.h"
#include "LCD.h"
#include "RGB_LED.h"
#include "PWM_2.h" 
#include "buzzer.h"
#include "state_machine.h"
#include <util/delay.h>

int main(void){
	
    sei();
	
    LCD_initialize();
    ports_initialize();
    timer_0_initialize();
    PWM_2_initialize();
    USART_initialize();
	buttons_and_switches_initialize();
    RGB_LED_initialize();
	buzzer_initialize();
	state_machine_initialize();
	
	USART_print_line("APLIKACIJA JE ZAPOCETA");
	
    while (INFINITE_LOOP){
		
		state_machine_routine();
    } 
}

//Svi projektni kodovi se mogu naci na GMX mailu.
