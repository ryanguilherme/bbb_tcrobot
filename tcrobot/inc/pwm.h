/**
 * PWM
 * This library modifies a PWM period and duty cycle based on it's path
 */

#ifndef BBB_TCROBOT_PWM_H
#define BBB_TCROBOT_PWM_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


/**
 * @name set_pwm_duty_cycle
 * @details Modifies a pwm duty cycle based on it's system path
 * @param pwm_path, pwm_value
 * @return void
 */
void set_pwm_duty_cycle(char* pwm_path, int pwm_duty_cycle);
void set_pwm_period(char* pwm_path, int pwm_period);
char* get_pwm_path(char pin[]);
void enable_pwm(char pin[]);

#endif //BBB_TCROBOT_PWM_H
