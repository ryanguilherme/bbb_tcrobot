// todo
#include "../inc/pwm.h"

void servo_motor(char pin[], int angle){

    enable_pwm(pin);

    char pwm_path[256];
    
    sprintf(pwm_path, "%s/period", get_pwm_path(pin));

    int fd = open(pwm_path, O_WRONLY);
    if (fd < 0){
        printf("Error opening period file\n");
        return;
    }

    write(fd, "20000000", 8);
    close(fd);

    sprintf(pwm_path, "%s/duty_cycle", get_pwm_path(pin));

    fd = open(pwm_path, O_WRONLY);
    if (fd < 0){
        printf("Error opening dutty cicle file\n");
        return;
    }
    double dutty_cycle =  200000 * ((angle * 1.0 / 18) + 2.5);
    char dutty_cycle_str[256];
    
    sprintf(dutty_cycle_str, "%d", (int)dutty_cycle);
    write(fd, dutty_cycle_str, strlen(dutty_cycle_str));
    close(fd);
}