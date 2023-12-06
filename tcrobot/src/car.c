#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/** PWM PERIOD / DUTY CYCLE **/
#define AVERAGE_SPEED           "200000"
#define DEFAULT_PERIOD          "200000"

/** REFLEXIVE INFRARED PINS **/
#define LEFT_SENSOR_VALUE       "/sys/class/gpio/gpio72/value"
#define MIDDLE_SENSOR_VALUE     "/sys/class/gpio/gpio70/value"
#define RIGHT_SENSOR_VALUE      "/sys/class/gpio/gpio71/value"

/** L298N INPUT PINS **/
#define IN1_VALUE               "/sys/class/gpio/gpio60/value"          // RIGHT WHEEL
#define IN2_VALUE               "/sys/class/gpio/gpio48/value"          // RIGHT WHEEL
#define IN3_VALUE               "/sys/class/gpio/gpio49/value"          // RIGHT WHEEL
#define IN4_VALUE               "/sys/class/gpio/gpio117/value"         // RIGHT WHEEL
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

#define OBSTACLE          "/sys/class/gpio/gpio74/value"

void move_forward() {
    int fd;
    fd = open(IN1_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN2_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN3_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN4_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);
}

void move_left() {
    int fd;
    fd = open(IN1_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN2_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN3_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN4_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);
}

void move_right() {
    int fd;
    fd = open(IN1_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN2_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(IN3_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN4_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);
}

void move_nowhere() {
    int fd;
    fd = open(IN1_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN2_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN3_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(IN4_VALUE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening value file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);
}

int main() {
    int fd;
    char ls_value, ms_value, rs_value;

    /** DEFINE P9_14 AND P9_16 MUX AS PWM **/
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

    /** EXPORT PWM 1A AND PWM 1B **/
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

    /** SET BOTH WHEELS PERIOD AS 200000ns TO TARGET 5KHz **/
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

    /** ENABLE BOTH WHEELS PWM **/
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

    /** SET GPIOS DIRECTIONS AS OUTPUT (out) **/
    fd = open(IN1_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN2_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN3_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN4_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return 1;
    }

    write(fd, "out", 3);
    close(fd);

    char left_wheel;
    char right_wheel;
    char obstacle;

    left_wheel = open(LEFT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(left_wheel, DEFAULT_PERIOD, 6);
    close(left_wheel);

    right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(right_wheel, DEFAULT_PERIOD, 6);
    close(right_wheel);

    usleep(250000);

    left_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(left_wheel, AVERAGE_SPEED, 6);
    close(left_wheel);

    right_wheel = open(RIGHT_WHEEL_DUTY_CYCLE, O_WRONLY);
    write(right_wheel, AVERAGE_SPEED, 6);
    close(right_wheel);

    while(1) {
        fd = open(LEFT_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening left sensor value file\n");
            return 1;
        }
        read(fd, &ls_value, 1);
        close(fd);

        fd = open(MIDDLE_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening middle sensor value file\n");
            return 1;
        }
        read(fd, &ms_value, 1);
        close(fd);

        fd = open(RIGHT_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening right sensor value file\n");
            return 1;
        }
        read(fd, &rs_value, 1);
        close(fd);

        fd = open(OBSTACLE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening obstacle value file\n");
            return 1;
        }
        read(fd, &obstacle, 1);
        close(fd);

        if(ls_value == '1') {printf("LEFT: BLACK | ");}
        else         {printf("LEFT: WHITE | ");}
        if(rs_value == '1') {printf("RIGHT: BLACK\n");}
        else         {printf("RIGHT: WHITE\n");}

        if ((ls_value == '0') && (ms_value == '1') && (rs_value == '0')) {
            move_forward();
        }
        else if (((ls_value == '1') && (ms_value == '1') && (rs_value == '0')) || ((ls_value == '1') && (ms_value == '0') && (rs_value == '0'))) {
            move_left();
        }
        else if (((ls_value == '0') && (ms_value == '1') && (rs_value == '1')) || ((ls_value == '0') && (ms_value == '0') && (rs_value == '1'))) {
            move_right();
        }
        else {
            move_nowhere();
        }


    }
}

