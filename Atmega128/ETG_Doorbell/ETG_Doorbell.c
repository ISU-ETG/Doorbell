/*
 * ETG_Doorbell.c
 *
 * Created: 3/23/2016 1:00:38 PM
 *  Author: nbergman
 */ 


#include <avr/io.h>
#include <stdint.h>
#include "util.h"
#include "navButtons.h"

#define DEBUG1		_bv(PG0)
#define DEBUG2		_bv(PG1)
#define DEBUGPORT	PORTG
#define DEBUGDDR	DDRG

int main(void)
{
	navBtn_t navBtn;
	
	nav_initPorts();
	
	//debug leds
	DEBUGDDR |= DEBUG1 | DEBUG2;
	DEBUGPORT |= (DEBUG1| DEBUG2);
	
	 int i = 0;
	 
    while(1)
    {
		
		//if(navButtons == 0xF0)DEBUGPORT ^= DEBUG1;
		for(i=0; i < 10000; i ++);
		
		switch(navBtn)
		{
			case (~PB_SEL)& PB_MASK:
				DEBUGPORT ^= DEBUG1;
				break;
			
			case PB_LEFT: 
				DEBUGPORT |= DEBUG2;
				break;
				
			case ~PB_RIGHT:
				DEBUGPORT &= ~(DEBUG2);
				break;
				
			case ~PB_UP:
				DEBUGPORT |= DEBUG1;
				break;
				
			case ~PB_DOWN:
				DEBUGPORT &= ~(DEBUG1);
				break;
				
			default:	
				break;
				
		}
		
	    //TODO:: Please write your application code 
    }
}