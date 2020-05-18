/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #08  Exercise #04
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

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTD = 0x00; 
	//unsigned short MAX = 8;
	ADC_init();
	while(1){
		if(ADC < 45) 
			PORTB = 0x00; 
		else if(ADC <= 55)  
			PORTB = 0x01;
		else if(ADC <= 65)
                        PORTB = 0x02;
		else if(ADC <= 75)
                        PORTB = 0x04;
                else if(ADC <= 85)
                        PORTB = 0x08;
		else if(ADC <= 95)
                        PORTB = 0x10;
                else if(ADC <= 105)
                        PORTB = 0x20;
		else if(ADC <= 115)
                        PORTB = 0x40;
                else 
                        PORTB = 0x80;
        }
}
