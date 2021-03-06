/*
 * navButtons.h
 *
 * Created: 3/23/2016 1:16:04 PM
 *  Author: Noah Bergman
 */ 



#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>
#include "util.h"

//Navigation Buttons
//NOTE: This configuration is changed from schematic labeling to match orientation.
#define PB_RIGHT	_bv(PC7)
#define PB_UP		_bv(PC6)
#define PB_LEFT		_bv(PC5)
#define PB_SEL		_bv(PC4)
#define PB_DOWN		_bv(PC3)

#define PB_MASK		(0xF8)		//BUTTON MASK

//BUTTON PRESS IS ACTIVE LOW
/*
#define PB_DOWN_PRESS	((~PB_DOWN)& PB_MASK)
#define PB_RIGHT_PRESS	((~PB_RIGHT)& PB_MASK)
#define PB_UP_PRESS		((~PB_UP)& PB_MASK)
#define PB_SEL_PRESS	((~PB_SEL)& PB_MASK)
#define PB_LEFT_PRESS	((~PB_LEFT)& PB_MASK)
*/

//NAVIGATION PORT AND DDR
#define NAVPIN		PINC
#define NAVDDR		DDRC

typedef enum {
	NONE,
	RIGHT,
	UP,
	LEFT,
	SEL,
	DOWN
} Joystick_t;

/*
* not used - for experimentation
typedef union
{
	struct
	{
		uint8_t DOWN	: 1;
		uint8_t RIGHT	: 1;
		uint8_t UP		: 1;
		uint8_t SEL		: 1;
		uint8_t LEFT	: 1;
	}btn;
	uint8_t navRead;
}navBtn_t;
*/


//Initialize PC3 - 7 as inputs for navigation
void nav_initPorts(void);


//Read the joystick buttons and return the button that is pressed.
Joystick_t nav_read(void);

#endif /* NAVBUTTONS_H_ */