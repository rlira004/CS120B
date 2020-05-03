/*	Author: Ricardo Lira
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

enum States {init, Start, Inc, Inc2, Dec, Dec2, Inc_rel, Dec_rel, Both, Both_rel} States;

unsigned char tempA = 0x00;

void tick(){
	tempA = ~PINA;
	switch (States)
	{
		case Start:
		States = init;
		break;
		
		case init:
		if ((tempA & 0x03) == 0x01)
		{
			States = Inc;
			}else if ((tempA & 0x03) == 0x02){
			States = Dec;
			}else{
			States = init;
		}
		break;
		case Inc:
		if((tempA & 0x03) == 0x01){
			States = Inc2;
		}
		break;
		case Dec:
		if((tempA & 0x03) == 0x02){
			States = Dec2;
		}
		break;
		case Inc2:
		if((tempA & 0x03) == 0x01){
			States = Inc2;
			}else if ((tempA & 0x03) == 0x00){
			States = Inc_rel;
			}else if((tempA & 0x03) == 0x03){
			States = Both;
		}
		break;
		case Dec2:
		if((tempA & 0x03) == 0x02){
			States = Dec2;
			}else if ((tempA & 0x03) == 0x00){
			States = Dec_rel;
			}else if((tempA & 0x03) == 0x03){
			States = Both;
		}
		break;
		case Inc_rel:
		if ((tempA & 0x03) == 0x00)
		{
			States = Inc_rel;
			}else if ((tempA & 0x03) == 0x01){
			States = Inc;
			}else if ((tempA & 0x03) == 0x02){
			States = Dec;
		}
		break;
		case Dec_rel:
		if ((tempA & 0x03) == 0x00)
		{
			States = Dec_rel;
			}else if ((tempA & 0x03) == 0x02){
			States = Dec;
			}else if ((tempA & 0x03) == 0x01){
			States = Inc;
		}
		break;
		case Both:
		if ((tempA & 0x03) == 0x11)
		{
			States = Both;
			}else if ((tempA & 0x03) == 0x01){
			States = Both;
			}else if ((tempA & 0x03) == 0x10){
			States = Both;
			}else if ((tempA & 0x03) == 0x00){
			States = Both_rel;
		}
		break;
		case Both_rel:
		States = init;
		break;
		
		default:
		break;
		
		
	}
	
	switch(States) {   // State actions
		case init:
		PORTC = 0x00;
		break;
		case Inc:
		if(PINC != 0x09){
			PORTC = PINC + 0x01;
		}
		break;
		case Dec:
		if(PINC != 0x00){
			PORTC = PINC - 0x01;
		}
		break;
		case Inc2:
		break;
		case Dec2:
		break;
		case Inc_rel:
		break;
		case Dec_rel:
		break;
		case Both:
		break;
		case Both_rel:
		PORTC = 0x00;
		break;
		default:
		break;
	} // State actions
	
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	States = Start;
	
	while (1)
	{
		tick();
	}
}
