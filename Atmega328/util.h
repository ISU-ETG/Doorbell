#ifndef UTIL_H

#define UTIL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SoundPlayer.h"

#define NULL	0

void Util_Init();
void Util_Close();

unsigned long Util_GetMillis();
unsigned long Util_GetMicros();

void Util_WaitMillis(unsigned int millis);
void Util_WaitMicros(unsigned int micros);

uint8_t Util_BlockWhile(uint8_t condition, uint16_t timeout);

extern volatile unsigned long ms;

#endif
