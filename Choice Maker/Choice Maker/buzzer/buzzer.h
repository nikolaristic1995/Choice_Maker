#ifndef BUZZER_H_
#define BUZZER_H_

#include "ports.h"

#define BUZZER_PORT PORTD

#define BUZZER_PIN 7

void				buzzer_initialize												(void);

void				buzzer_activate_tone											(uint8_t duty_cycle_percentage, uint32_t time_of_enabled_tone);

void				buzzer_activate_button_has_been_pushed_tone						(void);

void				buzzer_activate_countdown_tone									(void);

void				buzzer_activate_treatment_is_finished_tone						(void);

#endif /* BUZZER_H_ */
