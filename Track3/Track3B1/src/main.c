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
#include <avr/interrupt.h>
#include <util/delay.h>

#define MAX_COUNTER 10
#define TIME_REMAINING 31250

int counter = 0;
int elapsedSec = 0;

void lcd_command( unsigned char dat );
void initTimer(void);
void lcd_writeChar( unsigned char dat );
void lcd_writeLine1(char text1[]);

int main (void)
{

	init();
	//set_cursor(0,0);
	lcd_writeLine1("Tekst");
	//lcd_writeChar('A');
	/*
	initTimer();
	while(1){
		set_cursor(0,1);
		char write = '0' + counter;
		lcd_writeChar(write);
		_delay_ms(1);
	}//*/
	while(1){

	}

	return 1;
}

ISR ( TIMER1_OVF_vect )
{
	TCNT1 = TIME_REMAINING; // Herlaad de timer
	counter += 1;
	if(counter >= MAX_COUNTER)
		counter = 0;	// reset counter
}

ISR ( TIMER2_OVF_vect )
{
	elapsedSec++;
	TCNT2 = 15;	// set timer to 1 MS
	if(elapsedSec == 15) // check if 15 MS passed
		PORTD = 0x80;
	if(elapsedSec == 40){ // check if another 25 MS passed
		PORTC = 0x00;
		elapsedSec = 0;
	}
}

void init(void)
{
	_delay_ms(350);
	/* 8 bit display
	lcd_command(0x33);
	lcd_command(0x22);
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x01);
	lcd_command(0x06);
	lcd_command(0x80);//*/
	//* 4 bit display
	lcd_command( 0x02 );
	lcd_command( 0x28 );
	lcd_command( 0x0C );
	lcd_command( 0x06 );
	lcd_command( 0x80 );//*/
}

void set_cursor(int position, int row){
	switch(row){
		case 0:
			lcd_command(0x80 + position);
			break;
		case 1:
			lcd_command(0xC0 + position);
			break;
	}
}

void lcd_writeLine1 (char text1[]){
	lcd_command(0x80);
	for(int i=0;i<16;i++)
		lcd_writeChar(text1[1]);
}

void display_text(char text1[])
{
	for (int i=0; i<16; i++) {
		lcd_writeChar( text1[i] );
	}
}

void initTimer()
{
	DDRC |= (1 << 0);
	  
	TIMSK |= (1 << TOIE1 ); // Enable overflow interrupt
	sei () ; // Enable global interrupts
	  
	TCNT1 = TIME_REMAINING; // Set timeremaining
	  
	TCCR1B |= ((1 << CS10 ) | (1 << CS11 )) ; // Set up timer at Fcpu /64
}

void lcd_command(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x08;
	_delay_ms(10);
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x08;
	_delay_ms(10);
	PORTC = 0x00;
}

void lcd_writeChar(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x0C;
	_delay_ms(10);
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x0C;
	_delay_ms(10);
	PORTC = 0x00;
}