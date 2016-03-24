/*
 * ETG_Doorbell.c
 *
 * Created: 3/23/2016 1:00:38 PM
 *  Author: nbergman
 */ 


#include <avr/io.h>
#include "util.h"
#include "navButtons.h"

#define DEBUG1	(1<<PG0)
#define DEBUG2	(1<<PG1)
#define DEBUGPORT PORTG

int main(void)
{
	//nav_initPorts();
	uint8_t buttons = 0;
	DDRC &= ~(PB_DOWN | PB_LEFT |PB_RIGHT| PB_UP | PB_SEL); 
	
	//debug leds
	DDRG |= DEBUG1 | DEBUG2;
	PORTG &= ~(DEBUG1| DEBUG2);
	//DEBUGPORT &= _bv(DEBUG1) | _bv(DEBUG2);
	buttons = (PORTG & 0x80);
	
	 
    while(1)
    {
		buttons = nav_read();
		if(buttons & PB_SEL)
		{
			DEBUGPORT |= DEBUG1;	
		}else
		{
			DEBUGPORT &= ~DEBUG1;
		}
		
		
	    //TODO:: Please write your application code 
    }
}