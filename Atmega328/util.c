#include "util.h"

volatile unsigned long ms;

void Util_Init() {
	cli();
	
	//Init timer0 with /64 prescaler
	//And OCR0A to fire every 1ms
	TCCR0A = 0x00;
	TCCR0B = 0x03;
	OCR0A = 250;
	TIMSK0 = 1 << OCIE0A;
	
	TCCR1A = 0x00;
	TCCR1B = 0;//1 << CS11; // /8 prescaler
	TCCR1C = 0x00;
	TIMSK1 = 0;
	
	sei();
	
	ms = 0;
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
	
	TCNT1 = 0;
	TCCR1B = 1 << CS11; // /8 prescaler (0.5us period)
	
	while(TCNT1 < end);
		//TOGGLE_BIT(&PORTB, 1);
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

ISR(TIMER0_COMPA_vect) {
	TCNT0 = 0;
	ms++;
}
