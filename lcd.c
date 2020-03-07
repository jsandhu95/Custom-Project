/*    Author: jsand021 - Jeevan Sandhu
*  Partner(s) Name:
*    Lab Section: 23
*    Assignment: Custom Project
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/

#include "includes/lcd.h"

void LCD_write_byte(unsigned char dat, unsigned char command)
{
	unsigned char i;
	
	if (command == 1)
	LCD_DC_clr;
	else
	LCD_DC_set;

	for(i=0;i<8;i++)
	{
		if(dat&0x80)
		SDIN_set;
		else
		SDIN_clr;
		SCLK_clr;
		dat = dat << 1;
		SCLK_set;
	}
}

void LCD_init() 
{
	LCD_RST_clr;
	_delay_us(1);
	LCD_RST_set;

	_delay_us(1);

	LCD_write_byte(0x21, 1);	// set LCD mode
	LCD_write_byte(0xc8, 1);	// set bias voltage
	LCD_write_byte(0x06, 1);	// temperature correction
	LCD_write_byte(0x13, 1);	// 1:48
	LCD_write_byte(0x20, 1);	// use bias command, vertical
	LCD_write_byte(0x0c, 1);	// set LCD mode,display normally
	LCD_clear();	                // clear the LCD
}

void LCD_clear() 
{
	unsigned int i;

	LCD_write_byte(0x0c, 1);
	LCD_write_byte(0x80, 1);

	for (i=0; i<504; i++)
	{
		LCD_write_byte(0, 0);
	}
}

void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 1);	// column
	LCD_write_byte(0x80 | X, 1);    // row
}
