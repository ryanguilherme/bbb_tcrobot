#include "../inc/pwm.h"

void set_pwm_duty_cycle(const char* pwm_path, int pwm_duty_cycle) {
    strcat(pwm_path, "/duty_cycle");
    int pwm_fd = open(pwm_path, O_WRONLY);
    if (pwm_fd == -1) {
        perror("Failed to open PWM file");
        exit(EXIT_FAILURE);
    }

    char pwm_string[16];
    int pwm_string_length = snprintf(pwm_string, sizeof(pwm_string), "%d", pwm_duty_cycle);
    if (write(pwm_fd, pwm_string, pwm_string_length) == -1) {
        perror("Failed to set PWM value");
        exit(EXIT_FAILURE);
    }

    close(pwm_fd);
}

void set_pwm_period(const char* pwm_path, int pwm_period) {
    strcat(pwm_path, "/period");
    int pwm_fd = open(pwm_path, O_WRONLY);
    if (pwm_fd == -1) {
        perror("Failed to open PWM file");
        exit(EXIT_FAILURE);
    }

    char pwm_string[16];
    int pwm_string_length = snprintf(pwm_string, sizeof(pwm_string), "%d", pwm_period);
    if (write(pwm_fd, pwm_string, pwm_string_length) == -1) {
        perror("Failed to set PWM period");
        exit(EXIT_FAILURE);
    }

    close(pwm_fd);
}