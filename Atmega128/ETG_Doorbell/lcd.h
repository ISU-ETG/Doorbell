/*
 * lcd.h
 *
 * Created: 3/29/2016 5:24:12 PM
 *  Author: nbergman
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <stdint.h>
#include "util.h"

#define BIT0		0x01
#define BIT1		0x02
#define BIT2		0x04
#define BIT3		0x08
#define BIT4		0x10
#define BIT5		0x20
#define BIT6		0x40
#define BIT7		0x80


//Defines for LCD Control Commands
#define HD_LCD_CLEAR 		0x01
#define HD_RETURN_HOME		0X02

#define HD_CURSOR_SHIFT_DEC	0X05
#define HD_CURSOR_SHIFT_INC	0X07
#define HD_DISPLAY_CONTROL	3
#define HD_DISPLAY_ON 		0x04
#define HD_CURSOR_ON		0x02
#define HD_BLINK_ON			0x01
#define HD_CURSOR_MOVE_LEFT 0x10
#define HD_CURSOR_MOVE_RIGHT 0x14
#define HD_DISPLAY_SHIFT_LEFT 0x18
#define HD_DISPLAY_SHIFT_RIGHT 0x1C

#define LCD_WIDTH 20
#define LCD_HEIGHT 4

#define LCD_DDRAM_WRITE 0x80
#define LCD_CGRAM_WRITE 0x40

#define EN_PIN  	(1<<PA0)
#define RW_PIN		(1<<PA1)
#define RS_PIN		(1<<PA2)
#define LCD_PORT_CTL		PORTA
#define LCD_PORT_DATA		PORTF

/// Initialize PORTB0:6 to Communicate with LCD
void lcd_init(void);

///Send Char to LCD
void lcd_putc(char data);

///Send Character array to LCD
void lcd_puts(char data[]);

///Send Command to LCD - Position, Clear, Etc.
void lcd_sendCommand(uint8_t data);

///Send toggle enable and clear port
//void lcd_sendNibble(uint8_t theNibble);
//void inline lcd_dataEN(void);

///Clear LCD Screen
void lcd_clear(void);

///Return Cursor to 0,0
void lcd_home(void);

///Goto Line on LCD - 0 Indexed
void lcd_gotoLine(uint8_t lineNum);

uint8_t	lcd_revC(uint8_t theData);

#endif /* LCD.H_H_ */