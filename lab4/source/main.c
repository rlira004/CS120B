/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, One, Two} state;

void Tick() {
    switch(state) {//transitions
	case Start:
		PORTB = 0xF0;
		break;

	default:
		state = Start;
		break;
    }
    switch(state) {//actions
	case Start:
		PORTB = 0xF0;
		break;

	default:
		break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    state = Start;
    while (1) {
	Tick();
    }
    return 1;
}
