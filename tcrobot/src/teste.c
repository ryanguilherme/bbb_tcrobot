#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/** PWM PERIOD / DUTY CYCLE **/
#define AVERAGE_SPEED           "170000"
#define DEFAULT_PERIOD          "200000"

/** REFLEXIVE INFRARED PINS **/
#define LEFT_SENSOR_VALUE       "/sys/class/gpio/gpio70/value"
#define MIDDLE_SENSOR_VALUE     "/sys/class/gpio/gpio71/value"
#define RIGHT_SENSOR_VALUE      "/sys/class/gpio/gpio72/value"

/** L298N INPUT PINS **/
#define IN1_VALUE               "/sys/class/gpio/gpio60/value"
#define IN2_VALUE               "/sys/class/gpio/gpio48/value"
#define IN3_VALUE               "/sys/class/gpio/gpio49/value"
#define IN4_VALUE               "/sys/class/gpio/gpio117/value"
#define IN1_DIRECTION           "/sys/class/gpio/gpio60/direction"
#define IN2_DIRECTION           "/sys/class/gpio/gpio48/direction"
#define IN3_DIRECTION           "/sys/class/gpio/gpio49/direction"
#define IN4_DIRECTION           "/sys/class/gpio/gpio117/direction"

/** WHEELS PWM DIRECTORIES **/
#define PWM_EXPORT              "/sys/class/pwm/pwmchip5/export"
#define LEFT_WHEEL_ENABLE       "/sys/class/pwm/pwmchip5/pwm0/enable"
#define RIGHT_WHEEL_ENABLE      "/sys/class/pwm/pwmchip5/pwm1/enable"
#define LEFT_WHEEL_PERIOD       "/sys/class/pwm/pwmchip5/pwm0/period"
#define RIGHT_WHEEL_PERIOD      "/sys/class/pwm/pwmchip5/pwm1/period"
#define LEFT_WHEEL_DUTY_CYCLE   "/sys/class/pwm/pwmchip5/pwm0/duty_cycle"
#define RIGHT_WHEEL_DUTY_CYCLE  "/sys/class/pwm/pwmchip5/pwm1/duty_cycle"
#define P9_14_MUX               "/sys/devices/platform/ocp/ocp:P9_14_pinmux/state"
#define P9_16_MUX               "/sys/devices/platform/ocp/ocp:P9_16_pinmux/state"

int main() {
    int fd;
    char ls_value, ms_value, rs_value;

    fd = open(P9_14_MUX, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return 1;
    }

    write(fd, "pwm", 3);
    close(fd);

    fd = open(P9_16_MUX, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return 1;
    }

    write(fd, "pwm", 3);
    close(fd);

    fd = open(PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return 1;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return 1;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(LEFT_WHEEL_PERIOD, O_WRONLY);
    if (fd < 0) {
        printf("Error opening period file\n");
        return 1;
    }

    write(fd, DEFAULT_PERIOD, 6);
    close(fd);

    fd = open(RIGHT_WHEEL_PERIOD, O_WRONLY);
    if (fd < 0) {
        printf("Error opening period file\n");
        return 1;
    }

    write(fd, DEFAULT_PERIOD, 6);
    close(fd);

    fd = open(LEFT_WHEEL_ENABLE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening enable file\n");
        return 1;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(RIGHT_WHEEL_ENABLE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening enable file\n");
        return 1;
    }

    write(fd, "1", 1);
    close(fd);

    // Set GPIOs direction

    fd = open(IN1_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN2_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN3_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN4_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "0", 1);
    close(fd);

    char left_wheel;
    char right_wheel;

    left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(left_wheel, DEFAULT_PERIOD, 6);
    close(left_wheel);

    right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(right_wheel, DEFAULT_PERIOD, 6);
    close(right_wheel);

    usleep(250000);

    while(1) {
        fd = open(LEFT_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening sensor value file\n");
            return 1;
        }
        read(fd, &ls_value, 1);
        close(fd);

        fd = open(MIDDLE_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening sensor value file\n");
            return 1;
        }
        read(fd, &ms_value, 1);
        close(fd);

        fd = open(RIGHT_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening sensor value file\n");
            return 1;
        }
        read(fd, &rs_value, 1);
        close(fd);

        if(ls_value == '1') {printf("LEFT: BLACK | ");}
        else         {printf("LEFT: WHITE | ");}
        if(rs_value == '1') {printf("RIGHT: BLACK\n");}
        else         {printf("RIGHT: WHITE\n");}

        if ((ls_value == '1') && (rs_value == '1')) {
            left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(left_wheel, AVERAGE_SPEED, 6);
            close(left_wheel);

            right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(right_wheel, AVERAGE_SPEED, 6);
            close(right_wheel);
        }
        else if ((ls_value == '1') && (rs_value == '0')) {
            left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(left_wheel, "0", 1);
            close(left_wheel);

            right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(right_wheel, AVERAGE_SPEED, 6);
            close(right_wheel);
        }
        else if ((ls_value == '0') && (rs_value == '1')) {
            left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(left_wheel, AVERAGE_SPEED, 6);
            close(left_wheel);

            right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(right_wheel, "0", 1);
            close(right_wheel);
        }
        else if ((ls_value == '0') && (rs_value == '0')) {
            left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(left_wheel, "0", 1);
            close(left_wheel);

            right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
            write(right_wheel, "0", 1);
            close(right_wheel);
        }

        
    }
}
    
