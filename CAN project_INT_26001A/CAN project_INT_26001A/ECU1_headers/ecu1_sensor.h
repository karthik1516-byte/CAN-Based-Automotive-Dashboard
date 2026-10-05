#ifndef ECU1_SENSOR_H
#define ECU1_SENSOR_H

#include <stdint.h>
#include "digital_keypad.h"

#define MAX_GEAR            6
#define SPEED_ADC_CHANNEL   CHANNEL4

uint16_t get_speed(void);
unsigned char get_gear_pos(void);

#endif