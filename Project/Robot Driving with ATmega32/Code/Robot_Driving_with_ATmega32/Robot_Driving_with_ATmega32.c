
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	1000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

int main(void)
{
	DDRB=0x0f;
	/*PB0,PB1,PB2 and PB3 pins of PortB are declared output ( i/p1,i/p2,i/p3 and i/p4 pins of DC Motor Driver are connected)*/

	/*Start of infinite loop*/
	while(1)
	{
		PORTB=0x0A;
		/*Robot will move in forward direction*/

		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		/*Robot will move in forward direction for 2s*/

		PORTB=0x02;
		/*Robot will move in left direction*/

		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		/*Robot will move in left direction for 2s*/

		PORTB=0x08;
		/*Robot will move in right direction*/

		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		/*Robot will move in right direction for 2s*/

		PORTB=0x05;
		/*Robot will move in reverse direction*/

		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		/*Robot will move in reverse direction for 2s*/

		PORTB=0x0f;
		/*Robot will stop*/

		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		_delay_ms(500);
		/*Robot will stop for 2s*/
	}
}
/*End of program*/
