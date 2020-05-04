/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name:
 *	Lab Section: 025
 *	Assignment: Lab#04  Exercise#02
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

enum States {Start, Wait, Inc, Keep_Inc, Dec, Keep_Dec, Stop_Inc, Stop_Dec, Dbl_Press, Stop_Dbl_Press} States;
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

		case Dec:
		if((tempA & 0x03) == 0x02)
			States = Keep_Dec;
		break;

		case Keep_Inc:
		if((tempA & 0x03) == 0x01)
			States = Keep_Inc;
		else if ((tempA & 0x03) == 0x00)
			States = Stop_Inc;
		else if((tempA & 0x03) == 0x03)
			States = Dbl_Press;
		break;

		case Keep_Dec:
		if((tempA & 0x03) == 0x02)
			States = Keep_Dec;
		else if ((tempA & 0x03) == 0x00)
			States = Stop_Dec;
		else if((tempA & 0x03) == 0x03)
			States = Dbl_Press;
		break;

		case Stop_Inc:
		if ((tempA & 0x03) == 0x00)
			States = Stop_Inc;
		else if ((tempA & 0x03) == 0x01)
			States = Inc;
		else if ((tempA & 0x03) == 0x02)
			States = Dec;
		break;

		case Stop_Dec:
		if ((tempA & 0x03) == 0x00)
			States = Stop_Dec;
		else if ((tempA & 0x03) == 0x02)
			States = Dec;
		else if ((tempA & 0x03) == 0x01)
			States = Inc;
		break;

		case Dbl_Press:
		if ((tempA & 0x03) == 0x11)
			States = Dbl_Press;
		else if ((tempA & 0x03) == 0x01)
			States = Dbl_Press;
		else if ((tempA & 0x03) == 0x10)
			States = Dbl_Press;
		else if ((tempA & 0x03) == 0x00)
			States = Stop_Dbl_Press;
		break;

		case Stop_Dbl_Press:
		States = Wait;
		break;
		
		default:
		break;
		
		
	}
	
	switch(States) {   // State actions
		case Wait:
		PORTC = 0x00;
		break;

		case Inc:
		if(PINC != 0x09)
			PORTC = PINC + 0x01;
		break;

		case Dec:
		if(PINC != 0x00)
			PORTC = PINC - 0x01;
		break;

		case Keep_Inc:
		break;

		case Keep_Dec:
		break;

		case Stop_Inc:
		break;

		case Stop_Dec:
		break;

		case Dbl_Press:
		break;

		case Stop_Dbl_Press:
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


