/*	Author: Ricardo Lira rlira004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #10  Exercise #01
 *	Exercise Description: [optional - include for your own benefit]
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
#include "bit.h"

unsigned char tmpB = 0x00;

enum SM_Task {SM_output};

int SM_TaskTick(int state){
	unsigned char x = 0;
	x = GetKeypadKey();
	
	switch(state){
		case SM_output:
			switch(x){
				case '\0':
					tmpB = 0x1F;
					break;
				case '1':
					tmpB = 0x01;
					break;
				case '2':
					tmpB = 0x02;
					break;
				case '3':
					tmpB = 0x03;
					break;
				case '4':
					tmpB = 0x04;
					break;
				case '5':
					tmpB = 0x05;
					break;
				case '6':
					tmpB = 0x06;
					break;
				case '7':
					tmpB = 0x07;
					break;
				case '8':
					tmpB = 0x08;
					break;
				case '9':
					tmpB = 0x09;
					break;
				case 'A':
					tmpB = 0x0A;
					break;
				case 'B':
					tmpB = 0x0B;
					break;
				case 'C':
					tmpB = 0x0C;
					break;
				case 'D':
					tmpB = 0x0D;
					break;
				case '*':
					tmpB = 0x0E;
					break;
				case '0':
					tmpB = 0x00;
					break;
				case '#':
					tmpB = 0x0F;
					break;
				default:
					tmpB = 0x1B;
					break;
			}
			state = SM_output;
			PORTB = tmpB;
			break;
	}
	return state;
}

int main(void)
{
    DDRA = 0xF0; PORTA = 0x0F; 
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned long int SM_TaskTick_time = 20;
	unsigned long int tmpGCD = 10;
	unsigned long int GCD = tmpGCD;
	unsigned long int SM_Task_period = SM_TaskTick_time/GCD;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = 0;
	task1.period = SM_Task_period;
	task1.elapsedTime = SM_Task_period;
	task1.TickFct = &SM_TaskTick;
	
	TimerSet(GCD);
	TimerOn();
	
	unsigned short i;
    while (1) {
		for (i = 0; i < numTasks; i++){
			if (tasks[i] ->elapsedTime == tasks[i] ->period ){
				tasks[i] ->state = tasks[i] ->TickFct(tasks[i] ->state);
				tasks[i] ->elapsedTime = 0;
			}
			tasks[i] ->elapsedTime += 1;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
  }
	return 0;
}
