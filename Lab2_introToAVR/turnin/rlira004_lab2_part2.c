/*	Author: rlira004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
    /* Insert your solution below */
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xFF; PORTC = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpA = 0x00;
    
while (1) {
tmpA = ((PINA & 0x08)>>3) +
((PINA & 0x04)>>2) +
((PINA & 0x02)>>1) +
(PINA & 0x01);  




PORTC = 0x04 - tmpA;
}
    return 0;
}
