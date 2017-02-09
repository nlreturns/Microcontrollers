/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void wait(int ms);
char currentPos;

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect )
{
	if(currentPos == 0x00){	//check if you haven't reached 00000000
		currentPos = 0x01;
		PORTD = currentPos;
	}else{
		currentPos = currentPos >> 1;	// bitshift to next LED
		PORTD = currentPos;
	}
	wait(50);
}

/******************************************************************/
ISR( INT1_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	if(currentPos == 0x00){	//check if you haven't reached 00000000
		currentPos = 0x01;
		PORTD = currentPos;
		}else{
		currentPos = currentPos >> 1;	// bitshift to next LED
		PORTD = currentPos;
	}
}

int main (void)
{
	DDRD = 0xF0;	// port d input 7-4 output 3-0
	currentPos = 0x10;	// set current position LED
	PORTD = currentPos;

	EICRA |= 0x0B;		// INT1 falling edge, INT0 rising edge 00001011
	EIMSK |= 0x03;		// Enable INT1 & INT0

	sei();	// enable global interupt system

	while(1){

		wait(50);
	}

	return 0;
}
