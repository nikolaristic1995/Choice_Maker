#ifndef PWM_2_H_
#define PWM_2_H_

#define PRESCALER 8.0f

#define FAST_PWM_WITH_PRESCALER_8_AND_TURNED_OFF 0b01001010

#define TCCR2_INITIAL_STATE FAST_PWM_WITH_PRESCALER_8_AND_TURNED_OFF

void					PWM_2_initialize											(void);

void					PWM_2_enable_non_inverted_wave_form							(void);

void					PWM_2_disable												(void);

void					PWM_2_set_duty_cycle_percentage								(float percantage);

float					PWM_2_get_duty_cycle_percentage								(void);

void					PWM_2_minimaly_increase_duty_cycle_percantage				(void);

void					PWM_2_minimaly_decrease_duty_cycle_percentage				(void);

#endif /* PWM_2_H_ */
