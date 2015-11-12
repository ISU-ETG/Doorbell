/*
 * ETG_DoorBell.c
 *
 * Created: 11/11/2015 3:17:23 PM
 * Author : Eric
 */ 

#include <avr/io.h>
#include "SoundPlayer.h"

int main(void)
{
    SoundPlayer sp;
	
	DDRB |= 1 << 5;
	
	//Use PORTD 2-5 (arduino 2-5)
	//2 - reset
	//3 - data
	//4 - clock
	//5 - busy
	SoundPlayer_Init(&sp, &PORTD, 2, 3, 4, 5);
	
	while(1) {
		static int i = 0;
		
		SoundPlayer_SetTrack(&sp, i++);
		Util_WaitMillis(10);
		SoundPlayer_Play(&sp);
	}
}
