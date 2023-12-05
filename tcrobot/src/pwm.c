#include "../inc/pwm.h"

void set_pwm_duty_cycle(char* pwm_path, int pwm_duty_cycle) {
    strcat(pwm_path, "/duty_cycle");
    int pwm_fd = open(pwm_path, O_WRONLY);
    if (pwm_fd == -1) {
        perror("Failed to open PWM duty cycle file");
        exit(EXIT_FAILURE);
    }

    char pwm_string[16];
    int pwm_string_length = snprintf(pwm_string, sizeof(pwm_string), "%d", pwm_duty_cycle);
    if (write(pwm_fd, pwm_string, pwm_string_length) == -1) {
        perror("Failed to set PWM duty cycle");
        exit(EXIT_FAILURE);
    }

    close(pwm_fd);
}

void set_pwm_period(char* pwm_path, int pwm_period) {
    strcat(pwm_path, "/period");
    int pwm_fd = open(pwm_path, O_WRONLY);
    if (pwm_fd == -1) {
        perror("Failed to open PWM period file");
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

char* get_pwm_path(char pin[]){
    char pwm_path[256];

    if (strcmp(pin, "0A") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip3/pwm0/");
    } else if (strcmp(pin, "0B") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip3/pwm1/");
    } else if (strcmp(pin, "1A") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip5/pwm0/");
    } else if (strcmp(pin, "1B") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip5/pwm1/");
    } else if (strcmp(pin, "2A") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip7/pwm0/");
    } else if (strcmp(pin, "2B") == 0) {
        sprintf(pwm_path, "/sys/class/pwm/pwmchip7/pwm1/");
    } else {
        printf("Invalid pin\n");
        return NULL;
    }

    return strdup(pwm_path);
}

void enable_pwm(char pin[]){
    char pwm_path[256];
    sprintf(pwm_path, "%s/enable", get_pwm_path(pin));

    int fd = open(pwm_path, O_WRONLY);
    if (fd < 0){
        printf("Error opening enable pwm file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);
}