/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	if(tmpA >= 0x46)
		PORTB = 0x02;
	if(tmpA > 0x05 && tmpA < 0x46)
		PORTB = 0x04;
	if(tmpA <= 0x05)
		PORTB = 0x00;	
    }
	return 0;
}


















