// TRACK CLEANER ROBOT SETUP LIBRARY
// DESCRIPTION: This library is used to setup basic pins at system startup

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"

#ifndef BBB_TCROBOT_SETUP_H
#define BBB_TCROBOT_SETUP_H

void export_gpio(int gpio_number);

#endif //BBB_TCROBOT_SETUP_H
