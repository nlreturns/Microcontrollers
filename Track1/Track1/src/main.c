/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: 			Janwillem.dooms@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
void wait( int ms );
void b2(void);
void b3(void);
void b4(void);
void b5(void);
void b6(void);
void b7(void);
void setCharliePlexingLed(int lednr);


typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x81, 100},{0x42, 100},{0x24, 100},{0x18, 100},
		{0x28, 50},{0x48, 50},{0x88, 50},
			{0x84, 50},{0x82, 50},{0x80, 50},{0x00,0},
};

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

/************************************************************************/
/* Exercise B2 - switches pin 7 and 8 on port D                                                               */
/************************************************************************/
void b2(void)
{
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	
	PORTD = 0b01000000;
	while (1)
	{
		PORTD ^= 0b11000000;	// switch bit 7 and 8
		wait ( 500 );	
	}
};

/************************************************************************/
/* Excercise B3 - Switch a LED based on buttonpress.                                                                     */
/************************************************************************/
void b3(void)
{
	DDRD = 0xFF;				// All pins PORTD are set to output
	DDRC = 0x00;				// All pins PORTC are set to input
	while (1)
	{
		if(PINC & 1){				// if PINC.0 is pressed: cont;
			PORTD ^= 0b10000000;	// switch bit 8
			wait ( 50 );
		}
	}
};

void b4 (void){
	DDRD = 0xFF;			// open all ports
	PORTD = 0x01;			// set the first bit
	char currentVal = 0x01;	// var to check your current position
	
	while(1){
		if(currentVal == 0x00){				//check if you haven't reached 00000000
			currentVal = 0x01;
			PORTD = currentVal;
		}else{
			currentVal = currentVal << 1;	// bitshift to next LED
			PORTD = currentVal;
		}
		wait(50);
	}
}

void b5(void){
	DDRD = 0xFF;	// DPORT output.
	
	while(1){
		
		int index = 0;	// initialise index within while(true)
		
		while(pattern[index].delay != 0){
			PORTD = pattern[index].data;	// set data
			wait(pattern[index].delay);		// set delay
			index++;
		}
		
	}
}

void b6(void){
	DDRD = 0xFF;	// DPORT output
	DDRC = 0x00;	// CPORT input
	PORTD = 0x80;	// PORTD.8 ON
	int ms = 1000;
	while(1){
		if(PINC & 1){		// check button press for switch
			if(ms == 1000){
				ms = 250;
			}else{
				ms = 1000;
			}
		}
		PORTD ^= 0x80;	// blink
		wait(ms);		// use set wait value
	}
}

void b7(void){
	DDRD = 0xFF;	// set port D to output
	DDRC = 0x00;	// set port C to input
	while(1){
		
		if(PINC & 0x01){
			if(PINC & 0x02){
				if(PINC & 0x04){
					setCharliePlexingLed(0);
				}else{
					setCharliePlexingLed(1);
				}
			}else if(PINC & 0x04){
				setCharliePlexingLed(2);
			}else{
				setCharliePlexingLed(3);
			}
		}else if(PINC & 0x02){
			if(PINC & 0x04){
				setCharliePlexingLed(4);
			}else{
				setCharliePlexingLed(5);
			}
		}
		
		PORTD = 0x00;
	}
}

void setCharliePlexingLed(int lednr) {
	PORTD ^= 0x01 >> lednr;
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	
	b6();

	return 1;
}