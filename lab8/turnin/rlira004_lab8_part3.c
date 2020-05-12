/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #08  Exercise #03
 *	Exercise Description: [optional - include for your own benefit]
 *      youtube.com/watch?v=GKXGFO-McLc
 *      
 *      ---*In the Demo I mention the Potentiometer. I apologize, I'm tired lol. But yeah, the Potentiometer is not connected to this lab exercise.*---------------
 *	
 *
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
	unsigned short MAX = 118/2;
	//unsigned short my_short = ADC;
	//unsigned char my_char = (char)my_short;
	ADC_init();
	while(1){
		if(ADC < (MAX)) 
			PORTB = 0x00; 
		else if(ADC >= (MAX)) 
                        PORTB = ADC;
        }
}
