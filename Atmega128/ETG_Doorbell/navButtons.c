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
	DDRC &= ~(PB_DOWN | PB_LEFT |PB_RIGHT| PB_UP | PB_SEL);  
}

uint8_t nav_read(void)
{
	return (PINC & 0xF8);
	
}

