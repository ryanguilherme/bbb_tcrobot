#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define pwm0A_multiplex "/sys/devices/platform/ocp/ocp:P9_21_pinmux/state"
#define pwm0B_multiplex "/sys/devices/platform/ocp/ocp:P9_22_pinmux/state"
#define pwm2A_multiplex "/sys/devices/platform/ocp/ocp:P8_19_pinmux/state"
#define pwm2B_multiplex "/sys/devices/platform/ocp/ocp:P8_13_pinmux/state"  

#define pwm0 "/sys/class/pwm/pwmchip3/export"
#define pwm2 "/sys/class/pwm/pwmchip7/export"

#define pwm0A_period "/sys/class/pwm/pwmchip3/pwm0/period"
#define pwm0B_period "/sys/class/pwm/pwmchip3/pwm1/period"
#define pwm2A_period "/sys/class/pwm/pwmchip7/pwm0/period"
#define pwm2B_period "/sys/class/pwm/pwmchip7/pwm1/period"

#define pwm0A_enable "/sys/class/pwm/pwmchip3/pwm0/enable"
#define pwm0B_enable "/sys/class/pwm/pwmchip3/pwm1/enable"
#define pwm2A_enable "/sys/class/pwm/pwmchip7/pwm0/enable"
#define pwm2B_enable "/sys/class/pwm/pwmchip7/pwm1/enable"

#define pwm0A_dutty "/sys/class/pwm/pwmchip3/pwm0/dutty_cicle"
#define pwm0B_dutty "/sys/class/pwm/pwmchip3/pwm1/dutty_cicle"
#define pwm2A_dutty "/sys/class/pwm/pwmchip7/pwm0/dutty_cicle"
#define pwm2B_dutty "/sys/class/pwm/pwmchip7/pwm1/dutty_cicle"

#define period "20000000"

void write_file(char *filename, char *value){
    int fd = open(filename, O_WRONLY);
    write(fd, value, strlen(value));
    close(fd);
}

void multiplex_pwm(){
    write_file(pwm0A_multiplex, "pwm");
    write_file(pwm0B_multiplex, "pwm");
    write_file(pwm2A_multiplex, "pwm");
    write_file(pwm2B_multiplex, "pwm");
}


void export_pwm(){
    write_file(pwm0, "0");
    write_file(pwm0, "1");
    write_file(pwm2, "0");
    write_file(pwm2, "1");
}


void set_period(){
   write_file(pwm0A_period, period);
    write_file(pwm0B_period, period);
    write_file(pwm2A_period, period);
    write_file(pwm2B_period, period);
}

void pwm_enable(){
    write_file(pwm0A_enable, "1");
    write_file(pwm0B_enable, "1");
    write_file(pwm2A_enable, "1");
    write_file(pwm2B_enable, "1");
}

void set_dutty_cycle(int angle, char *pwm){
    double dutty_cycle =  200000 * ((angle * 1.0 / 18) + 2.5);
    char dutty_cycle_str[256];
    sprintf(dutty_cycle_str, "%d", (int)dutty_cycle);
    write_file(pwm, dutty_cycle_str);   
}

char* get_pwm_path(char *pin){
    if (strcmp(pin, "0A") == 0){
        return pwm0A_dutty;
    } else if (strcmp(pin, "0B") == 0){
        return pwm0B_dutty;
    } else if (strcmp(pin, "2A") == 0){
        return pwm2A_dutty;
    } else if (strcmp(pin, "2B") == 0){
        return pwm2B_dutty;
    }
    return NULL;
}

int main(){
    multiplex_pwm();
    export_pwm();
    set_period();
    pwm_enable();

    int angle;
    char pwm[256];

    
        printf("Angle: ");
        scanf("%d", &angle);
        printf("PWM: ");
        scanf("%s", pwm);
        set_dutty_cycle(angle, get_pwm_path(pwm));
    

    return 0;
}