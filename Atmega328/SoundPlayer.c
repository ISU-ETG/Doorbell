/*
 * SoundPlayer.c
 *
 * Created: 11/11/2015 3:47:14 PM
 *  Author: Eric
 */ 
#include "SoundPlayer.h"

void SoundPlayer_Init(SoundPlayer *sp, volatile uint8_t *port, uint8_t resetPin, uint8_t dataPin, uint8_t clockPin, uint8_t busyPin) {
	sp->port = port;
	sp->dataPin = dataPin;
	sp->resetPin = resetPin;
	sp->clockPin = clockPin;
	sp->busyPin = busyPin;
	
	//DDR register is adjacent to the associated PORT
	SET_BIT(port - 1, resetPin);
	SET_BIT(port - 1, dataPin);
	SET_BIT(port - 1, clockPin);
	CLEAR_BIT(port - 1, busyPin);
	
	SET_BIT(port, resetPin);
	SET_BIT(port, clockPin);
	CLEAR_BIT(port, dataPin);
	CLEAR_BIT(port, busyPin);
	
	Util_Init();
	
	Util_WaitMillis(10);
	
	SoundPlayer_Reset(sp);
}

void SoundPlayer_SendCommand(SoundPlayer *sp, uint16_t command) {
	int8_t bit;
	
	CLEAR_BIT(sp->port, sp->clockPin);
	
	Util_WaitMicros(1000);
	
	if(CHECK_BIT(command, 15))
		SET_BIT(sp->port, sp->dataPin);
	else
		CLEAR_BIT(sp->port, sp->dataPin);
	
	Util_WaitMicros(1000);
	
	SET_BIT(sp->port, sp->clockPin);
	
	for(bit = 14; bit >= 0; bit--) {
		Util_WaitMicros(200);
		
		CLEAR_BIT(sp->port, sp->clockPin);
		
		if(CHECK_BIT(command, bit))
			SET_BIT(sp->port, sp->dataPin);
		else
			CLEAR_BIT(sp->port, sp->dataPin);
		
		Util_WaitMicros(200);
		
		SET_BIT(sp->port, sp->clockPin);
	}
}

void SoundPlayer_SetTrack(SoundPlayer *sp, uint16_t track) {
	SoundPlayer_SendCommand(sp, (track < 512) ? track : 511);
}

void SoundPlayer_Play(SoundPlayer *sp) {
	SoundPlayer_SendCommand(sp, SP_PLAY);
	
	//Initialize the blocking timeout of 50ms
	Util_BlockWhile(0, 50);
	
	//PIN is two bytes before the associated PORT
	//Block until the busy pin goes high, or 50ms has passed
	while(Util_BlockWhile( !CHECK_BIT(*(sp->port - 2), sp->busyPin), 0 ));
	
	//Block until the busy signal goes low
	while(CHECK_BIT(*(sp->port - 2), sp->busyPin));
	
	//Wait 10ms. Otherwise the module can get confused with repeated play requests.
	Util_WaitMillis(10);
}

void SoundPlayer_Stop(SoundPlayer *sp) {
	SoundPlayer_SendCommand(sp, SP_STOP);
}

void SoundPlayer_SetVolume(SoundPlayer *sp, uint8_t vol) {
	SoundPlayer_SetVolume(sp, SP_VOL(vol));
}

void SoundPlayer_Reset(SoundPlayer *sp) {
	CLEAR_BIT(sp->port, sp->resetPin);
	
	Util_WaitMillis(100);
	
	SET_BIT(sp->port, sp->resetPin);
	
	Util_WaitMillis(800);
}
