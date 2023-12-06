#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_PATH "/sys/class/gpio/gpio%d"
#define DIRECTION_FILE "direction"
#define VALUE_FILE "value"

void set_gpio_direction(int gpio, const char *direction) {
    char path[256];
    snprintf(path, sizeof(path), GPIO_PATH, gpio);
    strcat(path, "/" DIRECTION_FILE);

    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open direction file");
        exit(1);
    }

    write(fd, direction, strlen(direction));
    close(fd);
}

void set_gpio_value(int gpio, int value) {
    char path[256];
    snprintf(path, sizeof(path), GPIO_PATH, gpio);
    strcat(path, "/" VALUE_FILE);

    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open value file");
        exit(1);
    }

    char str_value[2];
    snprintf(str_value, sizeof(str_value), "%d", value);
    write(fd, str_value, strlen(str_value));
    close(fd);
}

int main() {
    // Set GPIO direction to output
    set_gpio_direction(66, "out");
    set_gpio_direction(67, "out");
    set_gpio_direction(68, "out");
    set_gpio_direction(69, "out");

    int n;
    printf("Digite o numero de passos: ");
    scanf("%d", &n);
    int in;
    printf("Digite o sentido (0 antihorario 1 horario): ");
    scanf("%d", &in);
    while (n--) {
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


    return 0;
}
