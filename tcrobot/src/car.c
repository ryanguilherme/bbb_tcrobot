/**
 * CAR MAIN CODE
 * This code allows a car, controlled by two DC_MOTORS, follow a black line, via BeagleBone Black Linux
 */

#include "../inc/car.h"

int main() {
    while (1) {
        int left_sensor_value = read_file(LEFT_SENSOR_PATH);
        int right_sensor_value = read_file(RIGHT_SENSOR_PATH);
        int center_sensor_value = read_file(CENTER_SENSOR_PATH);

        if (center_sensor_value == 1) {
            // Move forward
            set_pwm_duty_cycle(LEFT_MOTOR_PWM_PATH, PWM_PERIOD);
            set_pwm_duty_cycle(RIGHT_MOTOR_PWM_PATH, PWM_PERIOD);
        } else if (left_sensor_value == 1) {
            // Turn right
            set_pwm_duty_cycle(LEFT_MOTOR_PWM_PATH, PWM_PERIOD);
            set_pwm_duty_cycle(RIGHT_MOTOR_PWM_PATH, 0);
        } else if (right_sensor_value == 1) {
            // Turn left
            set_pwm_duty_cycle(LEFT_MOTOR_PWM_PATH, 0);
            set_pwm_duty_cycle(RIGHT_MOTOR_PWM_PATH, PWM_PERIOD);
        } else {
            // Stop
            set_pwm_duty_cycle(LEFT_MOTOR_PWM_PATH, 0);
            set_pwm_duty_cycle(RIGHT_MOTOR_PWM_PATH, 0);
        }
    }

    return 0;
}

