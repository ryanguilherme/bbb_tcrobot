//
// Created by ryan on 03/12/23.
//

#include "../inc/setup.h"
#include <fcntl.h>
#include <unistd.h>

void export_gpio(int gpio_number) {
    FILE *export_file = fopen(GPIO_EXPORT_PATH, "w");
    if (export_file == NULL) {
        printf("Failed to open %s\n", GPIO_EXPORT_PATH);
        exit(1);
    }

    fprintf(export_file, "%d", gpio_number);
    fclose(export_file);
}

void setup_pinmux(char pin[], char mode[]){
    char pinmux_path[256];
    sprintf(pinmux_path, "/sys/devices/platform/ocp/ocp:%s_pinmux/state", pin);

    int fd = open(pinmux_path, O_WRONLY);
    if (fd < 0){
        printf("Error opening ocp file\n");
        return;
    }

    write(fd, mode, strlen(mode));
    close(fd);
}

void export_pwms(){
    int fd;
    for(int i = 3; i <= 7; i+=2){
        char pwm_path[256];
        sprintf(pwm_path, "/sys/class/pwm/pwmchip%d/export", i);

        fd = open(pwm_path, O_WRONLY);
        if (fd < 0){
            printf("Error opening enable pwm file\n");
            return;
        }

        write(fd, "1", 1);
        close(fd);

        fd = open(pwm_path, O_WRONLY);
        if (fd < 0){
            printf("Error opening enable pwm file\n");
            return;
        }

        write(fd, "0", 1);
        close(fd);
    }
}

int main() {
    int gpio_numbers[] = {60, 48, 49, 117, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75};
    int num_gpios = sizeof(gpio_numbers) / sizeof(gpio_numbers[0]);

    for (int i = 0; i < num_gpios; i++) {
        export_gpio(gpio_numbers[i]);
        printf("Exported GPIO %d\n", gpio_numbers[i]);
    }

    return 0;
}