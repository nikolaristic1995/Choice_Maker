/*
 * state_machine.h
 *
 * Created: 14/12/2019 00:00:05
 *  Author: Nikola
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#define WAITING 0
#define BINGOING_CHOICE 1

#define NOTHING_IS_HAPPENING 0
#define CHOICE_IS_BEING_RECEIVED 1
#define START 2
#define ERROR 3

#define MAXIMUM_NUMBER_OF_CHOICES 8
#define MAXIMUM_NUMBER_OF_CHARACTERS 32
#define NULL_TERMINATOR '\0'

extern volatile uint8_t event;
extern volatile uint8_t state;
extern volatile uint8_t choice_counter;
extern char* choice[MAXIMUM_NUMBER_OF_CHOICES][MAXIMUM_NUMBER_OF_CHARACTERS];

void				state_machine_initialize				(void);

uint8_t				state_machine_get_event					(void);

void				LCD_print_waiting_state					(void);

void				state_machine_update_choice_matrix		(void);

void				state_machine_start						(void);

void				state_machine_bingo_choice				(void);

void				 state_machine_error_message			(void);

void				state_machine_routine					(void);

#endif /* STATE_MACHINE_H_ */
