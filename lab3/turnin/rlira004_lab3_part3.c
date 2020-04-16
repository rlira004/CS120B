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
    DDRA = 0x00; PORTA = 0xFF; 
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	tmpA = (PINA & 0x0F);
        tmpB = (PINA & 0xF0);
	
	if(tmpA > 0x00 && tmpA < 0x03) {
		PORTC = 0x60;
	}
	if(tmpA > 0x02 && tmpA < 0x05) {
                PORTC = 0x60;
        }
	if(tmpA > 0x04 && tmpA < 0x07) {
                PORTC = 0x38;
        }
	if(tmpA > 0x06 && tmpA < 0x0A) {
                PORTC = 0x3C;
        }
	if(tmpA > 0x09 && tmpA < 0x0D) {
                PORTC = 0x3E;
        }
	if(tmpA > 0x0C && tmpA < 0x10) {
                PORTC = 0x3F;
        }	
	if(tmpB == 0x30) {
		PORTC = PORTC | 0x01 << 7; 
	}
    }
	return 0;
}










