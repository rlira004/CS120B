/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #08  Exercise #04
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=8S2UHSnmSPo	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
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
