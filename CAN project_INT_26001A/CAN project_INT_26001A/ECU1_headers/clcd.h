/* 
 * File:   clcd.h
 * Author: karthik
 *
 * Created on 2 September, 2026, 4:25 PM
 */

#ifndef CLCD_H
#define CLCD_H

void init_clcd(void);
void clcd_cmd(unsigned char cmd);
void clcd_putch(unsigned char data);
void clcd_print(const char *str);

#endif