/*
 * util.h
 *
 * Created: 3/23/2016 1:21:39 PM
 *  Author: nbergman
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#include <avr/io.h>

#define SETBIT(reg,bit)		reg |= (bit)
#define CLEARBIT(reg,bit)	reg &= ~(bit)
#define TOGGLEBIT(reg,bit)	reg ^= (bit)

#define _bv(bit)			(1<<bit)



#endif /* UTIL_H_ */