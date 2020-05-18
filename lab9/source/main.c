/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #09  Exercise #01
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency)
			TCCR3B &= 0x08;
		else
			TCCR3B |= 0x03;
		
		if(frequency < 0.954)
			OCR3A = 0xFFFF;
		else if(frequency > 31250)
			OCR3A = 0x0000;
		else
			OCR3A = (short)(8000000 / (128 * frequency)) -1;
		TCNT3 = 0;
		current_frequency = frequency;
	}
}
void PWM_on(){
	TCCR3A	=  (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
enum States{start, wait, C, D, E} state;
unsigned char d7;
unsigned char c0;
unsigned char c1;

void Tick(){
	d7 = (~PIND & 0x80);
	c0 = (~PINC & 0x01);
	c1 = (~PINC & 0x02);

	switch(state){
		case start:
			state = wait;
			break;
		case wait:
			if(d7){
				if(!c1 || !c0)
				state = C;
				else
				state = wait;
			}
			else if(c0)
				state = D;
			else if(c1)
				state = E;
			else
				state = wait;
			break;
		case C:
			if(d7)
				state = C;
			else if ((d7 && c0) || (d7 && c1) || (!d7))
				state = wait;
			break;
		case D:
			if(c0)
				state = D;
			else if((c0 && d7) || (c0 && c1) || (!c0))
				state = wait;
			break;
		case E:
			if((c1 && d7) || (c1 && c0) || (!c1))
				state = wait;
			else if(c1)
                                state = E;
			break;
		default:
			state = start;
			break;
	}
	switch(state){
		case start:
			set_PWM(0);
			break;
		case wait:
			set_PWM(0);
			break;
		case C:
			set_PWM(261.63);
			break;
		case D:
			set_PWM(293.66);
			break;
		case E:
			set_PWM(329.63);
			break;
		default:
			break;
	}
}

int main(void){
	//DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0x00; PORTD = 0xFF; 
	PWM_on();
		state = start;
	while(1){
		Tick();
	}
}
