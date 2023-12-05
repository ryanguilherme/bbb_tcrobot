/**
 * SERVOS SG90 LIBRARY
 * This library control SG90 servos movement
 */

#ifndef SG90_H
#define SG90_H

#include <fcntl.h>
#include <unistd.h>

void servo_motor(char pin[], int angle);

#endif // SG90_H