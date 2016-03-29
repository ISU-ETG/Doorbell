/*
 * util.c
 *
 * Created: 3/29/2016 1:14:12 PM
 *  Author: Eric
 */ 

#include "util.h"
#include "SoundPlayer.h"

volatile unsigned long ms;

void Util_Init(void)
{
	cli();
	
	TCCR0 = (1<<CS02);	//clk/8 for 1MHZ internal
	OCR0 = 250; 
	TIMSK |= (1<<OCIE0);  
	
	TCCR1A = 0X00; //Timer stopped
	TCCR1B = 0X00;
	
	//TIMSK |=  (1<<OCIE2);
	
	sei();
	
}

unsigned long Util_GetMillis() {
	unsigned long millis;
	
	cli();
	millis = ms;
	sei();
	
	return millis;
}

void Util_WaitMillis(unsigned int millis) {
	unsigned long endTime = millis + Util_GetMillis();
	
	while(Util_GetMillis() < endTime);
}

void Util_WaitMicros(unsigned int micros) {
	uint16_t end = micros << 1;
	
	TCNT3 = 0;
	TCCR3B = (1 << CS21); // No prescalar for 1MHZ clk.
	
	while(TCNT3 < end)
	{
		//SET_BIT(&DEBUGPORT, 0); //Debug1
	}
	//CLEAR_BIT(&DEBUGPORT, 0);
	//
}

//Call once with a non-zero timeout to start the timer
//Then each subsequent call with a zero timeout value
//will return true if condition and the time since the first
//call is less than the timeout amount, otherwise false
uint8_t Util_BlockWhile(uint8_t condition, uint16_t timeout) {
	static uint32_t endTime = 0;
	//uint32_t startTime = Util_GetMillis();
	
	if(timeout) {
		endTime = Util_GetMillis() + timeout;
	}
	
	return condition && Util_GetMillis() < endTime;
}

ISR(TIMER0_COMP_vect) {
	TCNT0 = 0;
	ms++;
	//DEBUGPORT ^= DEBUG2;
}

//Return true if light is being blocked
uint8_t check_Input(void)
{
	uint8_t laserPin = (PINE & (1<<6));
	uint8_t isBlocked = 0;
	
	isBlocked = (laserPin ? 1 : 0);
	
	return isBlocked;
}