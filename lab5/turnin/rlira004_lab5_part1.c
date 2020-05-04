/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=TD9GekdwIOI
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
    /* Insert your solution below */
    while (1) {
        PORTC = 0x00;
	tmpA = PINA;
	if(tmpA == 0xFF) {
		PORTC = 0x40;
	}
	if(tmpA == 0x7C) {
		PORTC = 0x70;
	}
	if(tmpA == 0xF8) {
		PORTC = 0x3C;
	}
	if(tmpA == 0x01 || tmpA == 0x02) {
		PORTC = 0x60;
	}
	if(tmpA > 0x02 && tmpA < 0x05) {
                PORTC = 0x70;
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
    }
	return 1;
}
