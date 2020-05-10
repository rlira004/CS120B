/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #06  Exercise #02
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=Sx62MaYiE3E
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpB = 0x00;
unsigned char tmpA = 0x00;
unsigned char cnt = 0x00;
enum States {start, one, two, three, retwo, hold, reset } state;

void tick() {
	tmpA = ~PINA;
	switch(state) { //transitions
		case start:
			state = one;
			break;
		case one:
			if(tmpA == 0x00) {
				state = two;
			}
			else if(tmpA != 0x00)
			state = hold;
			break;
		case two:
			if(tmpA == 0x00) {
				state = three;
			}
			else if(tmpA != 0x00)
			state = hold;
			break;
		case three:
			if(tmpA == 0x00) {
				state = retwo;
			}
			else if(tmpA != 0x00)
			state = hold;
			break;
		case retwo:
			if(tmpA == 0x00) {
				state = one;
			}
			else if(tmpA != 0x00)
			state = hold;
			break;
		case hold:
			if(tmpA == 0x00)
				state = reset;
			else if (tmpA != 0x00)
				state = hold;
			break;
		case reset:
			if(tmpA == 0x00)
				state = reset;
			else if(tmpA == 0x01)
				state = one;
			break;		
		default:
			state = start;
			break;
	}
	switch(state) { //state
		case start:
			tmpB = 0x00;
			break;
		case one:
			tmpB = 0x01;
			break;
		case two:
			tmpB = 0x02;
			break;
		case three:
			tmpB = 0x04;
			break;
		case retwo:
			tmpB = 0x02;
			break;
		case hold:
			break;
		case reset:
			break;
		default:
			break;
	}
}


int main(void) {       
        // Insert DDR and PORT initializations
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00;
        //Insert your solution below 
	TimerSet (3000);
	TimerOn();
	state = start;
    while (1) {
	   tick();
	   while(!TimerFlag);
	   TimerFlag = 0; 
    	   PORTB = tmpB;
    }
    
}
