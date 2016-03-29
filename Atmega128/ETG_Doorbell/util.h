/*
 * util.h
 *
 * Created: 3/23/2016 1:21:39 PM
 *  Author: Eric
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define DEBUG1		_bv(PG0)
#define DEBUG2		_bv(PG1)
#define DEBUGPORT	PORTG
#define DEBUGDDR	DDRG

#define SETBIT(reg,bit)		reg |= (bit)
#define CLEARBIT(reg,bit)	reg &= ~(bit)
#define TOGGLEBIT(reg,bit)	reg ^= (bit)

#define _bv(bit)			(1<<bit)

#define NULL	0

void Util_Init();
void Util_Close();

unsigned long Util_GetMillis();
unsigned long Util_GetMicros();

void Util_WaitMillis(unsigned int millis);
void Util_WaitMicros(unsigned int micros);

uint8_t Util_BlockWhile(uint8_t condition, uint16_t timeout);

extern volatile unsigned long ms;

uint8_t check_Input(void);


#endif /* UTIL_H_ */