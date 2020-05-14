/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #07  Exercise #01
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "timer.h"


enum States {Start, Increment, Decrement, Reset, Wait, Hold}state;

unsigned char inc;
unsigned char dec;
unsigned char tmpA = 0x00;
unsigned char cnt = 0;

void Tick(){
	inc = (~PINA & 0x01);
	dec = (~PINA & 0x02);

	switch(state){
		case Start:
			state = Wait;
			break;
		case Wait:
			if(inc && dec)
				state = Reset;
			else if(inc && !dec)
				state = Increment;
			else if (!inc && dec)
				state = Decrement;
			else
				state = Wait;
			break;
		case Increment:
			if(inc && !dec)
				state = Hold;
			else if (inc && dec)
				state = Reset;
			else
				state = Wait;
			break;
		case Decrement:
			if(!inc && dec)
				state = Hold;
			else if (inc && dec)
				state = Reset;
			else
				state = Wait;
			break;
		case Hold:
			if(inc && dec)
				state = Reset;
			else if (inc && !dec){
				if((cnt % 9)==0)
					state = Increment;
				else
					state = Hold;
			}
			else if(!inc && dec){
				if((cnt % 9)==0)
					state = Decrement;
				else
					state = Hold;
			}
			else
				state = Wait;
			break;
		case Reset:
			state = Wait;
			break;
		default:
			state = Start;
			break;
	}
	
	switch(state){
		case Start:
			break;
		case Increment:
		    	if(tmpA < 9)
				tmpA++;
			break;
		case Decrement:
			if(tmpA > 0)
				tmpA--;
			break;
		case Reset:
			tmpA = 0x00;
			break;
		case Wait:
			break;
		case Hold:
			cnt++;
			break;
		default:
			break;
	}
	
}

int main(void)
{
    	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	TimerSet(125);
	TimerOn();

	LCD_init();
	LCD_ClearScreen();

	state = Start;
	
	while (1)
	{
		Tick();
		LCD_Cursor(1);
		LCD_WriteData(tmpA + '0');
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
