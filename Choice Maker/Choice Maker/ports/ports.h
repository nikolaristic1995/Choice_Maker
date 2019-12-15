#ifndef PORTS_H_
#define PORTS_H_

#include <stdint-gcc.h>
#include <avr/io.h>

#define SET_BIT(PORTx,n) PORTx|=(1<<n)
#define RESET_BIT(PORTx,n) PORTx&=~(1<<n)
#define TOGGLE_BIT(PORTx,n) PORTx^=(1<<n)
#define READ_PIN(PINx,n) PINx&(1<<n)

#define PORTA_INITIAL_DIRECTION 0b01111111
#define PORTB_INITIAL_DIRECTION 0b00000000
#define PORTC_INITIAL_DIRECTION 0b11111111
#define PORTD_INITIAL_DIRECTION 0b10110010

#define PORTA_INITIAL_STATE 0b10000000
#define PORTB_INITIAL_STATE 0b11111111
#define PORTC_INITIAL_STATE 0b00000000
#define PORTD_INITIAL_STATE 0b01001100 

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

#define B0 0
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6
#define B7 7

#define C0 0
#define C1 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5
#define C6 6
#define C7 7

#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

void							ports_initialize													(void);

void							ports_set_PINxn_of_PORTA_direction_to_output						(uint8_t xn);

void							ports_set_PINxn_of_PORTA_direction_to_input							(uint8_t xn);

void							ports_set_PINxn_of_PORTB_direction_to_output						(uint8_t xn);

void						    ports_set_PINxn_of_PORTB_direction_to_input							(uint8_t xn);

void							ports_set_PINxn_of_PORTC_direction_to_output						(uint8_t xn);

void							ports_set_PINxn_of_PORTC_direction_to_input							(uint8_t xn);

void							ports_set_PINxn_of_PORTD_direction_to_output						(uint8_t xn);

void							ports_set_PINxn_of_PORTD_direction_to_input							(uint8_t xn);

uint8_t							ports_read_port_A													(void);

uint8_t							ports_read_port_B													(void);

uint8_t							ports_read_port_C													(void);

uint8_t							ports_read_port_D													(void);

void							ports_set_OC1A_pin_direction_to_output								(void);

void							ports_set_OC2_pin_direction_to_output								(void);

void							ports_set_OC1A_pin_direction_to_input								(void);

#endif /* PORTS_H_ */

/*                       ***PINOUT***

                            PORTA
PA0 - OUTPUT (CS1 PIN OF THE GLCD)
PA1 - OUTPUT (CS2 PIN OF THE GLCD)
PA2 - OUTPUT (DI (RS) PIN OF THE GLCD)
PA3 - OUTPUT (RW PIN OF THE GLCD)
PA4 - OUTPUT (E (EN) PIN OF THE GLCD)
PA5 - OUTPUT (RST PIN OF THE GLCD)
PA6 - OUTPUT (RGB LED DATA INPUT PIN)
PA7 - INPUT  (BUTTON SAVE PARAMETERS)

                            PORTB
PB0 - INPUT  (BUTTON GLCD CURSOR UP)
PB1 - INPUT  (BUTTON GLCD CURSOR DOWN)
PB2 - INPUT  (INCREMENT / DECREMENT)
PB3 - INPUT  (BY 1)
PB4 - INPUT  (BY 10)
PB5 - INPUT  (BY 100)
PB6 - INPUT  (BY 1000)
PB7 - INPUT  (BY 10000)

                            PORTC
PC0 - OUTPUT (D0 PIN OF THE GRAPHIC LCD DISPLAY)
PC1 - OUTPUT (D1 PIN OF THE GRAPHIC LCD DISPLAY)
PC2 - OUTPUT (D2 PIN OF THE GRAPHIC LCD DISPLAY)
PC3 - OUTPUT (D3 PIN OF THE GRAPHIC LCD DISPLAY)
PC4 - OUTPUT (D4 PIN OF THE GRAPHIC LCD DISPLAY)
PC5 - OUTPUT (D5 PIN OF THE GRAPHIC LCD DISPLAY)
PC6 - OUTPUT (D6 PIN OF THE GRAPHIC LCD DISPLAY)
PC7 - OUTPUT (D7 PIN OF THE GRAPHIC LCD DISPLAY)

                            PORTD
PD0 - INPUT  (BUTTON RESTART)  
PD1 - OUTPUT (TXD PIN OF USART) 
PD2 - INPUT  (BUTTON START)
PD3 - INPUT  (BUTTON PAUSE)
PD4 - OUTPUT (PWM SIGNAL FOR CONTROLING THE ELECTROPNEUMATIC SOLENOID VALVE) 
PD5 - OUTPUT (TOP VALUE FOR PWM 1)
PD6 - INPUT  (BUTTON RESET)
PD7 - OUTPUT (PWM SIGNAL FOR CONTROLING THE BUZZER)
*/
