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
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <led.c>

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

void OpgaveB1(){
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;

	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;

	while (1)
	{
		PORTA = ADCH;
		PORTB = ADCL;
	}
}

void OpgaveB2(){
	DDRF = 0x00;
	DDRA = 0xFF;

	ADMUX = 0b11100001;
	ADCSRA = 0b10000110;

	while (1)
	{
		ADCSRA |= 1<<6;
		while (ADCSRA & 1<<6);
		PORTA = ADCH;
		wait(500);
	}
}

void OpgaveB3(){
	DDRF = 0x00;
	DDRA = 0xFF;

	ADMUX =  0b11100001;
	ADCSRA = 0b11100110;
	
	init_lcd_4bit();
	wait(500);
	char temp[15];

	while (1)
	{
		clear();
		int i = ADCH;
		sprintf(temp, "%i�C", i);
		wait(100);
		display(temp);
		wait(100);
		memset(temp, 0, 15);
		PORTA = ADCH;
		wait(2500);
	}
}

int main( void )
{
	OpgaveC1();
}
