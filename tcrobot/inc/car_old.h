//
// Created by ryan on 03/12/23.
//

#ifndef BBB_TCROBOT_CAR_H
#define BBB_TCROBOT_CAR_H

#include <stdio.h>
#include "pwm.h"
#include "file.h"

/** SYSTEM PATHING DEFINITION **/

// REFLEXIVE INFRARED SENSORS
#define LEFT_SENSOR_PATH "/sys/class/gpio/gpio70/value"
#define RIGHT_SENSOR_PATH "/sys/class/gpio/gpio71/value"
#define CENTER_SENSOR_PATH "/sys/class/gpio/gpio72/value"

// DC MOTORS
#define LEFT_MOTOR_PWM_PATH "/sys/class/pwm/pwmchip5/pwm0"
#define RIGHT_MOTOR_PWM_PATH "/sys/class/pwm/pwmchip5/pwm1"

#define PWM_PERIOD 200000 // WHEELs DC MOTORS PWM (5 KHz)

#endif //BBB_TCROBOT_CAR_H
