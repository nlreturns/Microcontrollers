#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void wait(int ms);
void display(int digit);

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

void display(int digit){

	switch(digit){
		case 0:
			PORTA = 0b00111111;
			break;
		case 1:
			PORTA = 0b00000110;
			break;
		case 2:
			PORTA = 0b01011011;
			break;
		case 3:
			PORTA = 0b01001111;
			break;
		case 4:
			PORTA = 0b01100110;	
			break;
		case 5:
			PORTA = 0b01101101;
			break;
		case 6:
			PORTA = 0b01111101;
			break;
		case 7:
			PORTA = 0b00000111;
			break;
		case 8:
			PORTA = 0b01111111;
			break;
		case 9:
			PORTA = 0b01101111;
			break;
		case 10:
			PORTA = 0b01110111;
			break;
		case 11:
			PORTA = 0b01111111;
			break;
		case 12:
			PORTA = 0b00111001;
			break;
		case 13:
			PORTA = 0b00111111;
			break;
		case 14:
			PORTA = 0b01111001;
			break;
		case 15:
			PORTA = 0b01110001;
			break;
		default:
			PORTA = 0b01111001;
			break;
	}

}

int main( void )
{
	DDRA = 0xFF;

	while(1){
		//*
		for(int i = 0; i < 20; i++){
			display(i);
			wait(10);
		}//*/
		//display(1);
		//display(10);
	}

	return 1;
}