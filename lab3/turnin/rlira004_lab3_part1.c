/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #3  Exercise #1
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
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tmpA[2] = { 0x00 };
    int i;
    int j;
    /* Insert your solution below */
    while (1) {
        PORTC = 0x00;
	tmpA[0] = PINA;
        tmpA[1] = PINB; 
        PORTD = ((PINB << 4) | PINA);
        for(i = 0; i < 8; i++) {
	    for(j = 0; j < 2; j++) {
                if(tmpA[j] & (0x01))
                    PORTC++;
                tmpA[j] = (tmpA[j] >> 1);
            }
        }
     }
	return 0;
}
