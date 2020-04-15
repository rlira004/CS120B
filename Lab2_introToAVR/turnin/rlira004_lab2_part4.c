/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #2  Exercise #4
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
DDRB = 0x00; PORTB = 0xFF;
DDRC = 0x00; PORTC = 0xFF;
DDRD = 0xFF; PORTD = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;
   
while (1) {
if((PINA + PINB + PINC) >= 0x8C) {
tmpA = 0x01;
}
if((PINA - PINC) >= 0x50) {
tmpB = 0x02;
}
if((PINC - PINA) >= 0x50) {
tmpB = 0x02;
}
tmpC = ((PINA + PINB + PINC) & 0xFC) ;
PORTD = tmpA + tmpB + tmpC ;

}
    return 0;
}
