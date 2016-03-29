/*
 * ETG_Doorbell.c
 *
 * Created: 3/23/2016 1:00:38 PM
 *  Author: nbergman
 */ 


#include <avr/io.h>
#include <stdint.h>
#include "util.h"
#include "joystick.h"
#include "SoundPlayer.h"




int main(void)
{
	
	SoundPlayer wtvMod;
	
	nav_initPorts();
	SoundPlayer_Init(&wtvMod, &PORTD, 4, 3, 5, 2);
	
	Joystick_t joystick =NONE;
	DDRE &= ~((1<<6)|(1<<7)); //Signal Inputs
	
	//debug leds
	DEBUGDDR |= DEBUG1 | DEBUG2;
	DEBUGPORT |= ~(DEBUG1| DEBUG2);
	
	 int i = 0;
	 
    while(1)
    {
		
		joystick = nav_read();
		uint8_t isBlocked = 0;
		

		
		switch(joystick)
		{
			case LEFT:
				DEBUGPORT |= DEBUG1;
				break;
			case RIGHT:
				DEBUGPORT ^= DEBUG1;
				break;
			case UP:
				DEBUGPORT |= DEBUG2;
				break;
			case DOWN:
				DEBUGPORT ^= DEBUG2;
				break;
			case SEL:
				DEBUGPORT |= (DEBUG1|DEBUG2);
				break;
			default:
				//DEBUGPORT ^= (DEBUG1);
				break;
		}
		
			//static int i = 0;
			isBlocked = check_Input();
			
			
			if(isBlocked)
			{
				SoundPlayer_SetTrack(&wtvMod, 2);
				Util_WaitMillis(10);
				SoundPlayer_Play(&wtvMod);
				Util_WaitMillis(15000);
			}
			
		
		//DEBUGPORT ^= (DEBUG2);
		//Util_WaitMicros(128);
		//DEBUGPORT &= ~(DEBUG2);
		//TOGGLE_BIT(wtvMod.port, wtvMod.clockPin);
		//TOGGLE_BIT(wtvMod.port, wtvMod.dataPin);
		//TOGGLE_BIT(wtvMod.port, wtvMod.resetPin);
		/*SoundPlayer_SetTrack(&wtvMod, 2);
		DEBUGPORT &= ~(DEBUG2);
		Util_WaitMillis(10);
		
		SoundPlayer_Play(&wtvMod);
		Util_WaitMillis(1000);
	*/
			
	}
		
	    //TODO:: Please write your application code 
}