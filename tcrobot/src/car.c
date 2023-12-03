//
// Created by ryan on 03/12/23.
//

#include "../inc/car.h"


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int read_sensor_value(const char* sensor_path) {
    int sensor_fd = open(sensor_path, O_RDONLY);
    if (sensor_fd == -1) {
        perror("Failed to open sensor file");
        exit(EXIT_FAILURE);
    }

    char sensor_value;
    if (read(sensor_fd, &sensor_value, sizeof(sensor_value)) == -1) {
        perror("Failed to read sensor value");
        exit(EXIT_FAILURE);
    }

    close(sensor_fd);

    return sensor_value - '0';
}

void set_motor_pwm(const char* motor_pwm_path, int pwm_value) {
    int motor_pwm_fd = open(motor_pwm_path, O_WRONLY);
    if (motor_pwm_fd == -1) {
        perror("Failed to open motor PWM file");
        exit(EXIT_FAILURE);
    }

    char pwm_string[16];
    int pwm_string_length = snprintf(pwm_string, sizeof(pwm_string), "%d", pwm_value);
    if (write(motor_pwm_fd, pwm_string, pwm_string_length) == -1) {
        perror("Failed to set motor PWM value");
        exit(EXIT_FAILURE);
    }

    close(motor_pwm_fd);
}

int main() {
    while (1) {
        int left_sensor_value = read_sensor_value(LEFT_SENSOR_PATH);
        int right_sensor_value = read_sensor_value(RIGHT_SENSOR_PATH);
        int center_sensor_value = read_sensor_value(CENTER_SENSOR_PATH);

        if (center_sensor_value == 1) {
            // Move forward
            set_motor_pwm(LEFT_MOTOR_PWM_PATH, PWM_PERIOD);
            set_motor_pwm(RIGHT_MOTOR_PWM_PATH, PWM_PERIOD);
        } else if (left_sensor_value == 1) {
            // Turn right
            set_motor_pwm(LEFT_MOTOR_PWM_PATH, PWM_PERIOD);
            set_motor_pwm(RIGHT_MOTOR_PWM_PATH, 0);
        } else if (right_sensor_value == 1) {
            // Turn left
            set_motor_pwm(LEFT_MOTOR_PWM_PATH, 0);
            set_motor_pwm(RIGHT_MOTOR_PWM_PATH, PWM_PERIOD);
        } else {
            // Stop
            set_motor_pwm(LEFT_MOTOR_PWM_PATH, 0);
            set_motor_pwm(RIGHT_MOTOR_PWM_PATH, 0);
        }
    }

    return 0;
}

