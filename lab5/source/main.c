/*	Author: Ricardo Lira
 *  Partner(s) Name: 
 *	Lab Section: 025
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void countSystem();
unsigned char counter;
unsigned char prevButton;
enum StateMachine { start, init, wait, historyCheck, calc, reset } currentState, nextState;

unsigned char countOperator(unsigned char);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    while (1) 
    {
        countSystem();
    }
    return 1;
}

void countSystem()
{
    switch(currentState)//transition
    {
	case start :
	        nextState = init;
        	break;
		    
        case init :
		nextState = wait;
        	break;

        case wait :
		nextState = historyCheck;
		    break;      	
	
	case historyCheck :
		if(PINA == prevButton)
		{
		    nextState = wait;
	            break;
		}
		else if ((prevButton == 0x03) && (PINA == 0x00))
		{
                    nextState = reset;
		    break;
		}
		else
		{
		    nextState = calc;
          	    break;
		}

        case calc :
		nextState = wait;
		break;

	case reset :
		nextState = wait;
		break;
	default :
		break;
    }
    switch(currentState) //action
    {
	case start :
                break;
		    
        case init :
	        PORTB = 0x07;
		counter = 0x07;
		prevButton = 0x00;
		
                break;
        case wait:
                
	        break;
	
	case historyCheck :
                
                break;
	case reset : 
		counter = 0x00;
		break;
		
	case calc:
		prevButton = PINA;
		counter = countOperator(counter);
		break;
	default : 
	        break;
    }
    PORTC = counter;
    currentState = nextState;
}

unsigned char countOperator(unsigned char counter)
{
    if( PINA == 0x01 )
    {   
	if(counter == 9)
	{
            return counter;
	}
	else
	{
	    return counter + 0x01;
	}
    }
    else if(PINA == 0x02)
    {
	if(counter == 0)
	{
	    return counter;
	}
	else
	{
	    return counter - 0x01;
	}
    }
    else 
    {
        return counter;
    }
}
