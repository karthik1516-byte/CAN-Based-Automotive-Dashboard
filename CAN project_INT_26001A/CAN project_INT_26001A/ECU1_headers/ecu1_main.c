#include <xc.h>
#include <stdint.h>

#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"
#include "clcd.h"

#define _XTAL_FREQ 20000000

void main(void)
{
    uint16_t speed;
    unsigned char gear;

    init_adc();
    init_digital_keypad();
    init_can();
    init_uart();
    init_clcd();

    /* Initial display */
    clcd_cmd(0x80);
    clcd_print("ECU1");

    clcd_cmd(0xC0);
    clcd_print("INITIALIZING");

    __delay_ms(2000);

    clcd_cmd(0x01);
    __delay_ms(2);

    while (1)
    {
        /* Get speed */
        speed = get_speed();

        /* Get gear */
        gear = get_gear_pos();

        /* Send speed through CAN */
        can_transmit(SPEED_MSG_ID,
                     (uint8_t *)&speed,
                     2);

        /* Send gear through CAN */
        can_transmit(GEAR_MSG_ID,
                     &gear,
                     1);

        /* Display speed */
        clcd_cmd(0x80);
        clcd_print("SPEED : ");

        clcd_putch((speed / 100) + '0');
        clcd_putch(((speed / 10) % 10) + '0');
        clcd_putch((speed % 10) + '0');

        /* Display gear */
        clcd_cmd(0xC0);
        clcd_print("GEAR  : ");
        clcd_putch(gear + '0');

        __delay_ms(100);
    }
}