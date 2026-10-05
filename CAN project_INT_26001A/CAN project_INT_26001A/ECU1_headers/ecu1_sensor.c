#include <xc.h>
#include <stdint.h>

#include "ecu1_sensor.h"
#include "adc.h"
#include "digital_keypad.h"

uint16_t get_speed(void)
{
    uint16_t adc_value;

    adc_value = read_adc(SPEED_ADC_CHANNEL);

    return (uint16_t)(((uint32_t)adc_value * 100U) / 1023U);
}

unsigned char get_gear_pos(void)
{
    static unsigned char gear = 0;
    unsigned char key;

    key = read_digital_keypad(STATE_CHANGE);

    if (key == SWITCH1)
    {
        if (gear < MAX_GEAR)
        {
            gear++;
        }
    }
    else if (key == SWITCH2)
    {
        if (gear > 0)
        {
            gear--;
        }
    }

    return gear;
}