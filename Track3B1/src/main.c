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
#include <asf.h>
#include <avr/interrupt.h>

#define MAX_COUNTER 10
#define TIME_REMAINING 31250

int counter = 0;

void lcd_command( unsigned char dat );
void lcd_writeChar( unsigned char dat );

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	

	board_init();
	set_cursor(0,0);
	display_text("Testtekst");

	while(1){
		set_cursor(0,1);
		char write = '0' + counter;
		lcd_writeChar(write);
		_delay_ms(10);
	}

	/* Insert application code here, after the board has been initialized. */
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
	TCNT2 = 40000;
	PORTD = 0x80;
	_delay_ms(15);
	PORTC = 0x00;
	_delay_ms(25);
}

void init(void)
{
	lcd_command( 0x02 );
	lcd_command( 0x28 );
	lcd_command( 0x0C );
	lcd_command( 0x06 );
	lcd_command( 0x80 );
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

void display_text(char text1[])
{
	for (int i=0; i<16; i++) {
		lcd_writeChar( text1[i] );
	}
}

void lcd_command(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x08;
	_delay_ms(1);
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x08;
	_delay_ms(1);
	PORTC = 0x00;
}

void lcd_writeChar(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x0C;
	_delay_ms(1);
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x0C;
	_delay_ms(1);
	PORTC = 0x00;
}