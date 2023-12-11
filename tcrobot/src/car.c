#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/** PWM PERIOD / DUTY CYCLE **/
#define AVERAGE_SPEED           "200000"
#define DEFAULT_PERIOD          "200000"
#define DEFAULT_BASE_PERIOD     "20000000"
#define ARM_PERIOD              "20000000"

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

/** OBSTACLE SENSOR **/
#define OBSTACLE                "/sys/class/gpio/gpio20/value"

/** ARM PWM DIRECTORIES **/
#define P9_21_MUX               "/sys/devices/platform/ocp/ocp:P9_21_pinmux/state"
#define P9_22_MUX               "/sys/devices/platform/ocp/ocp:P9_22_pinmux/state"
#define P8_19_MUX               "/sys/devices/platform/ocp/ocp:P8_19_pinmux/state"
#define P8_13_MUX               "/sys/devices/platform/ocp/ocp:P8_13_pinmux/state"
#define PWM_EXPORT0             "/sys/class/pwm/pwmchip3/export"
#define PWM_EXPORT2             "/sys/class/pwm/pwmchip7/export"
#define BASE_ENABLE             "/sys/class/pwm/pwmchip7/pwm0/enable"
#define ELLBOW_ENABLE           "/sys/class/pwm/pwmchip7/pwm1/enable"
#define PULSE_ENABLE            "/sys/class/pwm/pwmchip3/pwm0/enable"
#define CLAW_ENABLE             "/sys/class/pwm/pwmchip3/pwm1/enable"
#define BASE_PERIOD             "/sys/class/pwm/pwmchip7/pwm0/period"
#define ELLBOW_PERIOD           "/sys/class/pwm/pwmchip7/pwm1/period"
#define PULSE_PERIOD            "/sys/class/pwm/pwmchip3/pwm0/period"
#define CLAW_PERIOD             "/sys/class/pwm/pwmchip3/pwm1/period"
#define BASE_DUTY_CYCLE         "/sys/class/pwm/pwmchip7/pwm0/duty_cycle"
#define ELLBOW_DUTY_CYCLE       "/sys/class/pwm/pwmchip7/pwm1/duty_cycle"
#define PULSE_DUTY_CYCLE        "/sys/class/pwm/pwmchip3/pwm0/duty_cycle"
#define CLAW_DUTY_CYCLE         "/sys/class/pwm/pwmchip3/pwm1/duty_cycle"

/** STEP MOTOR DIRECTORIES **/
#define GPIO_PATH               "/sys/class/gpio/gpio%d"
#define DIRECTION_FILE          "direction"
#define VALUE_FILE              "value"

void set_gpio_direction(int gpio, const char *direction) {
    char path[256];
    snprintf(path, sizeof(path), GPIO_PATH, gpio);
    strcat(path, "/" DIRECTION_FILE);

    int fd = open(path, O_WRONLY);
    write(fd, direction, strlen(direction));
    close(fd);
}

void set_gpio_value(int gpio, int value) {
    char path[256];
    snprintf(path, sizeof(path), GPIO_PATH, gpio);
    strcat(path, "/" VALUE_FILE);

    int fd = open(path, O_WRONLY);

    char str_value[2];
    snprintf(str_value, sizeof(str_value), "%d", value);
    write(fd, str_value, strlen(str_value));
    close(fd);
}

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

void setup_arm(){
    int fd;

    set_gpio_direction(66, "out");
    set_gpio_direction(67, "out");
    set_gpio_direction(68, "out");
    set_gpio_direction(69, "out");

    /** DEFINE PINS AS PWM **/
    fd = open(P9_21_MUX, O_WRONLY);
    write(fd, "pwm", 3);
    close(fd);

    fd = open(P9_22_MUX, O_WRONLY);
    write(fd, "pwm", 3);
    close(fd);

    fd = open(P8_19_MUX, O_WRONLY);
    write(fd, "pwm", 3);
    close(fd);

    fd = open(P8_13_MUX, O_WRONLY);
    write(fd, "pwm", 3);
    close(fd);

    /** EXPORT PWM **/
    fd = open(PWM_EXPORT0, O_WRONLY);
    write(fd, "0", 1);
    close(fd);

    fd = open(PWM_EXPORT0, O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    fd = open(PWM_EXPORT2, O_WRONLY);
    write(fd, "0", 1);
    close(fd);

    fd = open(PWM_EXPORT2, O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    /** SET PERIOD **/
    fd = open(BASE_PERIOD, O_WRONLY);
    write(fd, DEFAULT_BASE_PERIOD, 8);
    close(fd);

    fd = open(ELLBOW_PERIOD, O_WRONLY);
    write(fd, ARM_PERIOD, 8);
    close(fd);

    fd = open(PULSE_PERIOD, O_WRONLY);
    write(fd, ARM_PERIOD, 8);
    close(fd);

    fd = open(CLAW_PERIOD, O_WRONLY);
    write(fd, ARM_PERIOD, 8);
    close(fd);

    /** ENABLE PWM **/
    fd = open(BASE_ENABLE, O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    fd = open(ELLBOW_ENABLE, O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    fd = open(PULSE_ENABLE, O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    fd = open(CLAW_ENABLE, O_WRONLY);
    write(fd, "1", 1);
    close(fd);


}

void move_base(int angle){
    int fd;
    fd = open(BASE_DUTY_CYCLE, O_WRONLY);
    double dutty_cycle =  200000 * ((angle * 1.0 / 18) + 2.5);
    char dutty_cycle_str[256];
    sprintf(dutty_cycle_str, "%d", (int)dutty_cycle);
    write(fd, dutty_cycle_str, strlen(dutty_cycle_str));
    close(fd);
}

void move_arm(int angle, char *pwm){
    int fd;
    fd = open(pwm, O_WRONLY);
    double dutty_cycle =  200000 * ((angle * 1.0 / 18) + 2.5);
    char dutty_cycle_str[256];
    sprintf(dutty_cycle_str, "%d", (int)dutty_cycle);
    write(fd, dutty_cycle_str, strlen(dutty_cycle_str));
    close(fd);
}

void move_bra(int angle, char *path){
    int fd;

    if(angle == 90){
        fd = open(path, O_WRONLY);
        write(fd, "1500000", 7);
    }else if(angle == 180){
        fd = open(path, O_WRONLY);
        write(fd, "2500000", 7);
    }else if(angle == 0){
        fd = open(path, O_WRONLY);
        write(fd, "500000", 6);
    }
    close(fd);
}

//Função para mover o  motor de passos com a quantidade indicada de passos no sentido indicado
void stepp_motor(int passos, int in){ 
    set_gpio_value(66, 0);
    set_gpio_value(67, 1);
    set_gpio_value(69, 1);
    set_gpio_value(68, 0);
    while (passos--) {
        if (in) {
            //Rotate the motor clockwise
            set_gpio_value(66, 1);
            set_gpio_value(67, 0);
            set_gpio_value(68, 0);
            set_gpio_value(69, 0);

            // Delay for some time
            usleep(2000);

            set_gpio_value(66, 1);
            set_gpio_value(67, 1);
            set_gpio_value(68, 0);
            set_gpio_value(69, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 1);
            set_gpio_value(68, 0);
            set_gpio_value(69, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 1);
            set_gpio_value(68, 1);
            set_gpio_value(69, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(68, 1);
            set_gpio_value(69, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(68, 1);
            set_gpio_value(69, 1);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(68, 0);
            set_gpio_value(69, 1);

            usleep(2000);

            set_gpio_value(66, 1);
            set_gpio_value(67, 0);
            set_gpio_value(68, 0);
            set_gpio_value(69, 1);

            usleep(2000);
        } else {
            set_gpio_value(66, 1);
            set_gpio_value(67, 0);
            set_gpio_value(69, 0);
            set_gpio_value(68, 0);

            // Delay for some time
            usleep(2000);

            set_gpio_value(66, 1);
            set_gpio_value(67, 1);
            set_gpio_value(69, 0);
            set_gpio_value(68, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 1);
            set_gpio_value(69, 0);
            set_gpio_value(68, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 1);
            set_gpio_value(69, 1);
            set_gpio_value(68, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(69, 1);
            set_gpio_value(68, 0);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(69, 1);
            set_gpio_value(68, 1);

            usleep(2000);

            set_gpio_value(66, 0);
            set_gpio_value(67, 0);
            set_gpio_value(69, 0);
            set_gpio_value(68, 1);

            usleep(2000);

            set_gpio_value(66, 1);
            set_gpio_value(67, 0);
            set_gpio_value(69, 0);
            set_gpio_value(68, 1);

            usleep(2000);

        }
        // // Stop the motor
        // set_gpio_value(66, 0);
        // set_gpio_value(67, 0);
        // set_gpio_value(68, 0);
        // set_gpio_value(69, 0);



    }

    set_gpio_value(66, 0);
    set_gpio_value(67, 1);
    set_gpio_value(69, 1);
    set_gpio_value(68, 0);

}

void mov1(){
    move_bra(0, BASE_DUTY_CYCLE);
    usleep(2000000);
    // move_arm(50, PULSE_DUTY_CYCLE);
    usleep(2000000);
    stepp_motor(130, 1);
    usleep(1500000);
    move_bra(180, BASE_DUTY_CYCLE);
    usleep(8000000);
    stepp_motor(110, 0);
    usleep(1500000);
    move_bra(90, BASE_DUTY_CYCLE);
    usleep(3000000);
}

void mov2(){
    move_base(180);
    usleep(2000000);
    move_arm(50, PULSE_DUTY_CYCLE);
    usleep(1500000);
    stepp_motor(100, 1);
    usleep(1500000);
    move_base(0);
    usleep(2000000);
    move_base(90);
    usleep(2000000);
    stepp_motor(100, 0);
}

void configure_car(){
    int fd;
    /** DEFINE P9_14 AND P9_16 MUX AS PWM **/
    fd = open(P9_14_MUX, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return;
    }

    write(fd, "pwm", 3);
    close(fd);

    fd = open(P9_16_MUX, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return;
    }

    write(fd, "pwm", 3);
    close(fd);

    /** EXPORT PWM 1A AND PWM 1B **/
    fd = open(PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return;
    }

    write(fd, "0", 1);
    close(fd);

    fd = open(PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        printf("Error opening mux file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    /** SET BOTH WHEELS PERIOD AS 200000ns TO TARGET 5KHz **/
    fd = open(LEFT_WHEEL_PERIOD, O_WRONLY);
    if (fd < 0) {
        printf("Error opening period file\n");
        return;
    }

    write(fd, DEFAULT_PERIOD, 6);
    close(fd);

    fd = open(RIGHT_WHEEL_PERIOD, O_WRONLY);
    if (fd < 0) {
        printf("Error opening period file\n");
        return;
    }

    write(fd, DEFAULT_PERIOD, 6);
    close(fd);

    /** ENABLE BOTH WHEELS PWM **/
    fd = open(LEFT_WHEEL_ENABLE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening enable file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    fd = open(RIGHT_WHEEL_ENABLE, O_WRONLY);
    if (fd < 0) {
        printf("Error opening enable file\n");
        return;
    }

    write(fd, "1", 1);
    close(fd);

    /** SET GPIOS DIRECTIONS AS OUTPUT (out) **/
    fd = open(IN1_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN2_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN3_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return;
    }

    write(fd, "out", 3);
    close(fd);

    fd = open(IN4_DIRECTION, O_WRONLY);
    if (fd < 0) {
        printf("Error opening direction file\n");
        return;
    }

    write(fd, "out", 3);
    close(fd);
}

void move_car(){
    int fd;
    char ls_value, ms_value, rs_value;

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
            return;
        }
        read(fd, &ls_value, 1);
        close(fd);

        fd = open(MIDDLE_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening middle sensor value file\n");
            return;
        }
        read(fd, &ms_value, 1);
        close(fd);

        fd = open(RIGHT_SENSOR_VALUE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening right sensor value file\n");
            return;
        }
        read(fd, &rs_value, 1);
        close(fd);

        fd = open(OBSTACLE, O_RDONLY);
        if (fd < 0) {
            printf("Error opening obstacle value file\n");
            return;
        }
        read(fd, &obstacle, 1);
        close(fd);

        if(ls_value == '1') {printf("LEFT: BLACK | ");}
        else         {printf("LEFT: WHITE | ");}
        if(rs_value == '1') {printf("RIGHT: BLACK\n");}
        else         {printf("RIGHT: WHITE\n");}

        if (obstacle == '1') {
            move_nowhere();
            printf("OBSTACLE DETECTED!\n");
            mov1();
        }
        else if ((ls_value == '0') && (ms_value == '1') && (rs_value == '0')) {
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

int main() {
    configure_car();
    setup_arm();

    set_gpio_value(66, 0);
    set_gpio_value(67, 1);
    set_gpio_value(69, 1);
    set_gpio_value(68, 0);

    move_car();
}

