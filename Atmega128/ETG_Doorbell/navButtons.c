/*
 * navButtons.c
 *
 * Created: 3/23/2016 1:01:45 PM
 *  Author: Noah Bergman
 */ 

#include "navButtons.h"

void nav_initPorts(void)
{
	//CLEARBIT(NAVDDR, _bv(PB_DOWN) | _bv(PB_UP) | _bv(PB_RIGHT) | _bv(PB_LEFT) | _bv(PB_SEL));
	NAVDDR &= ~(PB_DOWN | PB_LEFT |PB_RIGHT| PB_UP | PB_SEL); 
	 
}

Joystick_t nav_read()
{
	uint8_t btn = ~NAVPIN;
	Joystick_t joyStick = NONE;
	
	if(btn & PB_DOWN)
		joyStick = DOWN;
	else if(btn & PB_RIGHT)
		joyStick = RIGHT;
	else if(btn & PB_UP)
		joyStick = UP;
	else if(btn & PB_SEL)
		joyStick = SEL;
	else if(btn & PB_LEFT)
		joyStick = LEFT;
	
	return joyStick;
}