#include "ports.h"

void ports_initialize(void){
	
	// output pin direction => 1
	// input  pin direction => 0

	DDRA  = PORTA_INITIAL_DIRECTION;
	PORTA = PORTA_INITIAL_STATE;

	DDRB  = PORTB_INITIAL_DIRECTION;
	PORTB = PORTB_INITIAL_STATE;

	DDRC  = PORTC_INITIAL_DIRECTION;
	PORTC = PORTC_INITIAL_STATE;

	DDRD  = PORTD_INITIAL_DIRECTION;
	PORTD = PORTD_INITIAL_STATE;
}

void  ports_set_PINxn_of_PORTA_direction_to_output(uint8_t xn){
	
	SET_BIT(DDRA, xn);
}

void  ports_set_PINxn_of_PORTA_direction_to_input(uint8_t xn){
	
	RESET_BIT(DDRA, xn);
}

void  ports_set_PINxn_of_PORTB_direction_to_output(uint8_t xn){
	
	SET_BIT(DDRB, xn);
}

void  ports_set_PINxn_of_PORTB_direction_to_input(uint8_t xn){
	
	RESET_BIT(DDRB, xn);
}

void  ports_set_PINxn_of_PORTC_direction_to_output(uint8_t xn){
	
	SET_BIT(DDRC, xn);
}

void  ports_set_PINxn_of_PORTC_direction_to_input(uint8_t xn){
	
	RESET_BIT(DDRC, xn);
}

void  ports_set_PINxn_of_PORTD_direction_to_output(uint8_t xn){
	
	SET_BIT(DDRD, xn);
}

void  ports_set_PINxn_of_PORTD_direction_to_input(uint8_t xn){
	
	RESET_BIT(DDRD, xn);
}

uint8_t ports_read_port_A(void){

	uint8_t port_state = 0;
	for(uint8_t i = 0; i < 7; i++)port_state |= (READ_PIN(PINA, i) << i);

	return port_state;
}

uint8_t ports_read_port_B(void){

	uint8_t port_state = 0;
	for(uint8_t i = 0; i < 7; i++)port_state |= (READ_PIN(PINB, i) << i);

	return port_state;
}

uint8_t ports_read_port_C(void){

	uint8_t port_state = 0;
	for(uint8_t i = 0; i < 7; i++)port_state |= (READ_PIN(PINC, i) << i);

	return port_state;
}

uint8_t ports_read_port_D(void){

	uint8_t port_state = 0;
	for(uint8_t i = 0; i < 7; i++)port_state |= (READ_PIN(PIND, i) << i);

	return port_state;
}

void ports_set_OC1A_pin_direction_to_output(void){
	
	ports_set_PINxn_of_PORTD_direction_to_output(D5);
}

void ports_set_OC2_pin_direction_to_output(void){
	
	ports_set_PINxn_of_PORTD_direction_to_output(D7);
}

void ports_set_OC1A_pin_direction_to_input(void){
	
	ports_set_PINxn_of_PORTD_direction_to_input(D5);
}
