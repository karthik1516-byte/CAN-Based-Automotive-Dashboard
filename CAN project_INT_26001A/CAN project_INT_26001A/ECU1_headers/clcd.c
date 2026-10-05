#include <xc.h>
#include "clcd.h"

#define _XTAL_FREQ 20000000

#define CLCD_DATA_PORT PORTD
#define CLCD_DATA_TRIS TRISD

#define CLCD_RS RB4
#define CLCD_EN RB5

void clcd_cmd(unsigned char cmd)
{
    CLCD_RS = 0;

    CLCD_DATA_PORT = cmd;

    CLCD_EN = 1;
    __delay_us(100);
    CLCD_EN = 0;

    __delay_ms(2);
}

void clcd_putch(unsigned char data)
{
    CLCD_RS = 1;

    CLCD_DATA_PORT = data;

    CLCD_EN = 1;
    __delay_us(100);
    CLCD_EN = 0;

    __delay_us(100);
}

void clcd_print(const char *str)
{
    while (*str != '\0')
    {
        clcd_putch(*str);
        str++;
    }
}

void init_clcd(void)
{
    CLCD_DATA_TRIS = 0x00;

    TRISB4 = 0;
    TRISB5 = 0;

    CLCD_RS = 0;
    CLCD_EN = 0;

    __delay_ms(20);

    clcd_cmd(0x38);     // 8-bit, 2-line
    clcd_cmd(0x0C);     // Display ON, cursor OFF
    clcd_cmd(0x06);     // Increment cursor
    clcd_cmd(0x01);     // Clear display

    __delay_ms(2);
}