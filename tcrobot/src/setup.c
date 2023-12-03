//
// Created by ryan on 03/12/23.
//

#include "../inc/setup.h"

void export_gpio(int gpio_number) {
    FILE *export_file = fopen(GPIO_EXPORT_PATH, "w");
    if (export_file == NULL) {
        printf("Failed to open %s\n", GPIO_EXPORT_PATH);
        exit(1);
    }

    fprintf(export_file, "%d", gpio_number);
    fclose(export_file);
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