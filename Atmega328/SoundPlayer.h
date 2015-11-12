/*
 * SoundPlayer.h
 *
 * Created: 11/11/2015 3:45:38 PM
 *  Author: Eric
 */ 


#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_

#include "util.h"
#include <avr/io.h>

#define CLEAR_BIT(port, bit)	(*(port) &= ~(1<<(bit)))
#define SET_BIT(port, bit)		(*(port) |= (1<<(bit)))
#define TOGGLE_BIT(port, bit)	(*(port) ^= (1<<(bit)))
#define CHECK_BIT(data, bit)	(!!( (data) & (1 << (bit))))

#define	SP_PLAY					0xFFFE
#define SP_STOP					0xFFFF
#define SP_VOL(n)				(0xFFF0 + ((n) < 8) ? (n) : 7)

typedef struct {
	volatile uint8_t *port;
	uint8_t resetPin, dataPin, clockPin, busyPin;
} SoundPlayer;

void SoundPlayer_Init(SoundPlayer *sp, volatile uint8_t *port, uint8_t resetPin, uint8_t dataPin, uint8_t clockPin, uint8_t busyPin);

void SoundPlayer_SendCommand(SoundPlayer *sp, uint16_t command);

void SoundPlayer_SetTrack(SoundPlayer *sp, uint16_t track);
void SoundPlayer_Play(SoundPlayer *sp);
void SoundPlayer_Stop(SoundPlayer *sp);
void SoundPlayer_SetVolume(SoundPlayer *sp, uint8_t vol);

void SoundPlayer_Reset();


#endif /* SOUNDPLAYER_H_ */
