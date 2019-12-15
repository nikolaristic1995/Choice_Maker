/*
 * state_machine.h
 *
 * Created: 14/12/2019 00:00:05
 *  Author: Nikola
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#define WAITING 0
#define UPDATING_CHOICE_BUFFER 1

#define NOTHING_IS_HAPPENING 0
#define CHOICE_IS_BEING_RECEIVED 1
#define CHOICE_RECEIVING_IS_OVER 2

#define MAXIMUM_NUMBER_OF_CHOICES 10
#define CHOICE_STRING_MAXIMUM_NUMBER_OF_CHARACTERS 32
#define NULL_TERMINATOR '\0'

extern volatile uint8_t event;
extern volatile uint8_t state;
extern volatile uint8_t choice_counter;
extern char* choice[MAXIMUM_NUMBER_OF_CHOICES];

void				state_machine_initialize				(void);

uint8_t				state_machine_get_event					(void);

void				state_machine_update_choice_matrix		(void);

void				state_machine_routine					(void);

#endif /* STATE_MACHINE_H_ */
