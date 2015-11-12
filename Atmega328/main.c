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
	
	//Use PORTB 0-3 (arduino 8-11)
	//8 - reset
	//9 - data
	//10 - clock
	//11 - busy
	SoundPlayer_Init(&sp, &PORTB, 0, 1, 2, 3);
	
	while(1) {
		static int i = 0;
		SoundPlayer_SetTrack(&sp, i++);
		Util_WaitMillis(10);
		SoundPlayer_Play(&sp);
		Util_WaitMillis(2000);
	}
}

