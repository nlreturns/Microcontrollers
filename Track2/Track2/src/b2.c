#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void wait( int ms );

ISR( INT1_vect )
{
    PORTD |= (1<<5);		
}

ISR( INT2_vect )
{
    PORTD &= ~(1<<5);		
}

/*
int main( void )
{
	DDRD = 0xF0;	// port d input 7-4 output 3-0
	char currentPos = 0x01;	// set current position LED

	EICRA |= 0x1A;		// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;		// Enable INT2 & INT1

	return 0;
}*/