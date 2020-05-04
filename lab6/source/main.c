/*	Author: lab
 *  Partner(s) Name: Ricardo Lira rlira004@ucr.edu
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet (1000);
	TimerOn();
	unsigned char tmpB = 0x00;
    while (1) {
	    tmpB = ~tmpB;
	    PORTB = tmpB;
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
}
