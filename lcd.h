#ifndef __LCD_H__
#define __LCD_H__

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL

#define LCD_RST_set  PORTC |=  (1<<0)    //external reset input
#define LCD_RST_clr  PORTC &=~ (1<<0)

#define LCD_DC_set   PORTC |=  (1<<1)    //data/command
#define LCD_DC_clr   PORTC &=~ (1<<1)

#define SDIN_set     PORTC |=  (1<<2)    //serial data input
#define SDIN_clr     PORTC &=~ (1<<2)

#define SCLK_set     PORTC |=  (1<<3)    //serial clock input
#define SCLK_clr     PORTC &= ~(1<<3)

void LCD_write_byte(unsigned char dat, unsigned char command);
void LCD_init();
void LCD_clear();
void LCD_set_XY(unsigned char X, unsigned char Y);

#endif
