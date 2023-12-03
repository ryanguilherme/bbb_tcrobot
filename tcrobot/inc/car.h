//
// Created by ryan on 03/12/23.
//

#ifndef BBB_TCROBOT_CAR_H
#define BBB_TCROBOT_CAR_H

#define LEFT_SENSOR_PATH "/sys/class/gpio/gpio70/value"
#define RIGHT_SENSOR_PATH "/sys/class/gpio/gpio71/value"
#define CENTER_SENSOR_PATH "/sys/class/gpio/gpio72/value"

#define LEFT_MOTOR_PWM_PATH "/sys/class/pwm/pwmchip0/pwm0/duty_cycle"
#define RIGHT_MOTOR_PWM_PATH "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"

#define PWM_PERIOD 200000

#endif //BBB_TCROBOT_CAR_H
