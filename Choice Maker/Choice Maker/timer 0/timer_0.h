#ifndef TIMER_0_H_
#define TIMER_0_H_

#include <avr/io.h>

//clear timer on compare match and set OC0 on compare match
#define TCCRO_INITIAL_STATE 0x0B

//define bottom value
#define TCNT0_INITIAL_STATE 0x00

//define number of counts before the timer interrupt occurs
#define OCR0_INITIAL_STATE 0x7D

#define ENABLE_TIMER_0_OUTPUT_COMPARE_MATCH_INTERRUPT 0b00000010

#define NUMBER_OF_COUNTS 4
#define RESET_SUM_OF_IMPULSES_TIME_COUNT 5

#define ONE_SECOND 1000

extern volatile uint32_t timer_counter;
extern volatile uint16_t sum_of_impulses_timer;
extern volatile uint8_t reset_sum_of_impulses_time_count;
extern volatile uint32_t countdown_timer;
extern volatile uint8_t number_of_counts;
extern volatile uint16_t timer_random_count;

void						timer_0_initialize								(void);

void						timer_0_delay_in_milliseconds					(uint32_t time_of_delay_in_miliseconds);

uint8_t						timer_0_get_reset_sum_of_impulses_time_count	(void);

void						timer_0_reset_sum_of_impulses_time				(void);

uint8_t						timer_0_reset_sum_of_impulses_time_has_passed	(void);

void						timer_0_reset_countdown_timer					(void);

void						timer_0_reset_number_of_counts					(void);

uint8_t						timer_0_get_number_of_counts					(void);

uint8_t						timer_0_countdown_is_over						(void);

uint16_t					timer_0_get_timer_random_count					(void);

#endif /* TIMER_0_H_ */
