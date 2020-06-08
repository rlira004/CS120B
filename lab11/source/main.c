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
enum SpeakerStates {init, on, off, hold} Speaker_State;

#define tmpA (~PINA & 0x04)
void tick_Speaker() {
	 switch(Speaker_State) {
		case init:
			Speaker_State = off;
			break;
		case off:
			if (tmpA == 0x04) {
				Speaker_State = on;
			}
			else if (tmpA == 0x00) {
				Speaker_State = off;
			}
			break;
		case on:
			if(tmpA == 0x00) {
				Speaker_State = off;
			}
			else if (tmpA == 0x04) {
				Speaker_State = hold;
			}
			break;
		case hold:
			if(tmpA == 0x00) {
				Speaker_State = off;
			}
			else if (tmpA == 0x04) {
				Speaker_State = on;
			}
			break;
		default:
			Speaker_State = init;
			break;
}
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

int main(void){
	unsigned long threeLED_StateTimer = 0;
	unsigned long blinkingLED_StateTimer = 0;
	unsigned long Period = 1;
	unsigned long speaker_StateTimer = 0;


	TimerSet(Period);
	TimerOn();

	threeLEDs_States = threeLED_Start;
	blinkingLED_States = blinkingLED_Start;
	combine_State = Combine_start;
	Speaker_State = init;
	while (1)
	{
		if (speaker_StateTimer >= 2) {
			tick_Speaker();
			speaker_StateTimer = 0;
		}
		if (threeLED_StateTimer >= 300) {
			tick_threeLEDsSM();
			threeLED_StateTimer = 0;
		}
		if (blinkingLED_StateTimer >= 1000) {
			tick_blinkingLEDSM();
			blinkingLED_StateTimer = 0;
		}
		tick_Combine_State();

		while (!TimerFlag) {}
		TimerFlag = 0;

		threeLED_StateTimer += Period;
		blinkingLED_StateTimer += Period;
		speaker_StateTimer += Period;
	}
}
