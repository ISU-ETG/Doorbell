/*
 * navButtons.h
 *
 * Created: 3/23/2016 1:16:04 PM
 *  Author: Noah Bergman
 */ 



#ifndef NAVBUTTONS_H_
#define NAVBUTTONS_H_

#include <avr/io.h>
#include "util.h"
//Navigation Buttons
#define PB_DOWN		(1<<PC7)
#define PB_RIGHT	(1<<PC6)
#define PB_UP		(1<<PC5)
#define PB_SEL		(1<<PC4)
#define PB_LEFT		(1<<PC3)

#define NAVPORT		PORTC
#define NAVDDR		DDRC

//Initialize PC3 - 7 as inputs for navigation
void nav_initPorts(void);

uint8_t nav_read(void);

#endif /* NAVBUTTONS_H_ */