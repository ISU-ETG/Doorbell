/*
 * lcd.c
 *
 * Created: 3/29/2016 5:24:00 PM
 *  Author: nbergman
 */ 

#include "lcd.h"


/// Initialize PORTF0:7 and PORTA0:2 to Communicate with LCD
void lcd_init(void)
{
	//Set port to output
	DDRF  |= 0xFF; //Pins 0 - 7
	DDRA &= ~(EN_PIN|RS_PIN| RW_PIN);	//CTL_port

	LCD_PORT_CTL &= ~(EN_PIN | RW_PIN | RS_PIN);

	//Delay 40msec after power applied
	Util_WaitMillis(40);

	//Wake up
	lcd_sendCommand(0x30);
	Util_WaitMillis(5);

	lcd_sendCommand(0x30);
	Util_WaitMicros(160);

	lcd_sendCommand(0x30);
	Util_WaitMicros(160);

	lcd_sendCommand(0x38);			//Function set 8 bit / 2line
	Util_WaitMillis(1);

	//lcd_sendCommand(0x28);			//Function 4 bit / 2 lines
	//Util_WaitMillis(1);

	lcd_sendCommand(0x10);			//Set cursor
	Util_WaitMillis(1);

	lcd_sendCommand(HD_BLINK_ON | HD_CURSOR_ON | HD_DISPLAY_ON);
	//lcd_sendCommand(0x0C);
	Util_WaitMillis(1);

	lcd_sendCommand(0x06);			//Increment Cursor / No Display Shift
	Util_WaitMillis(1);


	lcd_sendCommand(0x01);			//Return Home
	Util_WaitMillis(10);

	lcd_clear();
	Util_WaitMillis(10);

}

///Send Char to LCD
void lcd_putc(char data)
{
	//Select - Send Data
	LCD_PORT_CTL |= RS_PIN | EN_PIN;
	LCD_PORT_CTL &= ~(RW_PIN);
	
	//Send the data
	LCD_PORT_DATA |= lcd_revC(data);
	Util_WaitMicros(10);
	LCD_PORT_CTL &= ~(EN_PIN); //Clock in Data
	Util_WaitMicros(10);
	LCD_PORT_DATA = 0x00; //Clear port
	
	
	//TODO: Poll Busy flag
}

///Send Character array to LCD
void lcd_puts(char data[])
{
	//While not equal to null
	while(*data != '\0')
	{
		lcd_putc(*data);
		data++;
	}
}

///Send Command to LCD - Position, Clear, Etc.
void lcd_sendCommand(uint8_t data)
{
	
	//Enable High
	LCD_PORT_CTL |= EN_PIN;
	LCD_PORT_CTL &= ~(RW_PIN | RS_PIN); // Write Command

	//Send High nibble
	LCD_PORT_DATA |= lcd_revC(data);
	Util_WaitMicros(10);
	LCD_PORT_CTL &= ~(EN_PIN); //Clock in Data
	Util_WaitMicros(10);
	LCD_PORT_DATA = 0x00; //Clear port
	
	//TODO: Poll Busy Flag

}


///Clear LCD Screen
void lcd_clear(void)
{
	lcd_sendCommand(HD_LCD_CLEAR);

}

///Return Cursor to 0,0
void lcd_home(void)
{
	lcd_sendCommand(HD_RETURN_HOME);
}

///Goto 0 indexed line number
void lcd_gotoLine(uint8_t lineNum)
{

	//Address of the four line elements
	static const uint8_t lineAddress[] = {0x00, 0x40, 0x14, 0x54};

	lineNum = (0x03 & lineNum); // Mask input for 0 - 3
	lcd_sendCommand(LCD_DDRAM_WRITE | lineAddress[lineNum]);

}

uint8_t lcd_revC(uint8_t n) {
	n = (n & 0b11110000 >> 4) | (n & 0b00001111 << 4);  // efghabcd
	n =(n & 0b11001100 >> 2) | (n & 0b00110011 << 2);  // ghefcdab
	n = (n & 0b10101010 >> 1) |( n & 0b01010101 << 1);  // hgfedcba
	return n;
}