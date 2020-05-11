/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #06  Exercise #03
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

enum States {Start, Wait, Inc, Keep_Inc, Fin_Inc, Dec, Keep_Dec, Fin_Dec, Reset, Fin_Reset} States;
unsigned char tempA = 0x00;

void tick(){
	tempA = ~PINA;
	switch (States)
	{
		case Start:
		States = Wait;
		break;
		
		case Wait:
		if ((tempA & 0x03) == 0x01)
			States = Inc;
		else if ((tempA & 0x03) == 0x02)
			States = Dec;
		else
			States = Wait;
		break;

		case Inc:
		if((tempA & 0x03) == 0x01)
			States = Keep_Inc;
		break;

		case Keep_Inc:
			if ((tempA & 0x03) == 0x01)
				States = Keep_Inc;
			else if ((tempA & 0x03) == 0x00)
				States = Fin_Inc;
			else if ((tempA & 0x03) == 0x03)
				States = Reset;
			break;

		case Fin_Inc:
			if ((tempA & 0x03) == 0x00)
				States = Fin_Inc;
			else if ((tempA & 0x03) == 0x01)
				States = Inc;
			else if ((tempA & 0x03) == 0x02)
				States = Dec;
			break;

		case Dec:
			if ((tempA & 0x03) == 0x02)
				States = Keep_Dec;
			break;

		case Keep_Dec:
		if((tempA & 0x03) == 0x02)
			States = Keep_Dec;
		else if ((tempA & 0x03) == 0x00)
			States = Fin_Dec;
		else if((tempA & 0x03) == 0x03)
			States = Reset;
		break;

		case Fin_Dec:
		if ((tempA & 0x03) == 0x00)
			States = Fin_Dec;
		else if ((tempA & 0x03) == 0x02)
			States = Dec;
		else if ((tempA & 0x03) == 0x01)
			States = Inc;
		break;

		case Reset:
		if ((tempA & 0x03) == 0x11)
			States = Reset;
		else if ((tempA & 0x03) == 0x01)
			States = Reset;
		else if ((tempA & 0x03) == 0x10)
			States = Reset;
		else if ((tempA & 0x03) == 0x00)
			States = Fin_Reset;
		break;

		case Fin_Reset:
		States = Wait;
		break;
		
		default:
		break;
		
		
	}
	
	switch(States) {   // State actions
		case Wait:
		PORTB = 0x07;
		break;

		case Inc:
		if(PINB != 0x09)
			PORTB = PINB + 0x01;
		break;

		case Dec:
		if(PINB != 0x00)
			PORTB = PINB - 0x01;
		break;

		case Keep_Inc:
		break;

		case Keep_Dec:
		break;

		case Fin_Inc:
		break;

		case Fin_Dec:
		break;

		case Reset:
		break;

		case Fin_Reset:
		PORTB = 0x07;
		break;

		default:
		break;
	} // State actions
	
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	States = Start;
	while (1)
	{
		tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}


