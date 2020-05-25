/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #10  Exercise #01
 *	Exercise Description: [optional - include for your own benefit]
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;

enum threeLEDsSm { threeLED_Start, light1, light2, light3 } threeLEDs_States;
enum blinkingLEDSM { blinkingLED_Start, blinking_off, blinking_on } blinkingLED_States;
enum CombineLEDsSM { Combine_start } combine_State;

void tick_threeLEDsSM() {
	switch (threeLEDs_States) {
	case threeLED_Start:
		threeLEDs_States = light1;
		break;
	case light1:
		threeLEDs_States = light2;
		break;
	case light2:
		threeLEDs_States = light3;
		break;
	case light3:
		threeLEDs_States = light1;
		break;
	default:
		threeLEDs_States = threeLED_Start;
		break;
	}
	switch (threeLEDs_States) {
	case threeLED_Start:
		break;
	case light1:
		threeLEDs = 0x01;
		break;
	case light2:
		threeLEDs = 0x02;
		break;
	case light3:
		threeLEDs = 0x04;
		break;
	default:
		break;
	}
}

void tick_blinkingLEDSM() {
	switch (blinkingLED_States)
	{
	case blinkingLED_Start:
		blinkingLED_States = blinking_off;
		break;
	case blinking_off:
		blinkingLED_States = blinking_on;
		break;
	case blinking_on:
		blinkingLED_States = blinking_off;
		break;
	default:
		break;
	}
	switch (blinkingLED_States)
	{
	case blinkingLED_Start:
		break;
	case blinking_off:
		blinkingLED = 0x00;
		break;
	case blinking_on:
		blinkingLED = 0x08;
		break;
	default:
		break;
	}
}
void tick_Combine_State() {
	switch (combine_State) {
	case Combine_start:
		break;
	}
	switch (combine_State) {
	case Combine_start:
		PORTB = threeLEDs | blinkingLED;
		break;
	default:
		break;
	}
}

int main(void)
{
	TimerSet(1000);
	TimerOn();

	threeLEDs_States = threeLED_Start;
	blinkingLED_States = blinkingLED_Start;
	combine_State = Combine_start;

	while (1)
	{
		tick_threeLEDsSM();
		tick_blinkingLEDSM();
		tick_Combine_State();

		while (!TimerFlag) {}
		TimerFlag = 0;
	}
}
