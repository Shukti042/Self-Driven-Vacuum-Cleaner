#define F_CPU 1000000UL
#include <avr/io.h>
#include "MrLCDmega32.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "uart_transmission.h"

#define USART_BAUDRATE 9600

int main(void)
{
	unsigned char count_a = 0;
	unsigned char count_b = 0;
	unsigned char show_a[4];
	Initialise();
	UART_init(USART_BAUDRATE);
	_delay_ms(100);

	while(1)
	{
		/* Send_A_String("Distance Sensor");
		GoToMrLCDLocation(1,2); */
		UART_transmit_char(1);
		count_a = UART_receive_char();
		Send_A_String("Distance1=");
		itoa(count_a,show_a,10);
		Send_A_String(show_a);
		GoToMrLCDLocation(15,1);
		Send_A_String("cm");
		GoToMrLCDLocation(1,2);
		UART_transmit_char(2);
		count_b = UART_receive_char();
		Send_A_String("Distance2=");
		itoa(count_b,show_a,10);
		Send_A_String(show_a);
		GoToMrLCDLocation(15,2);
		Send_A_String("cm");
		GoToMrLCDLocation(1,1);
		Send_A_Command(0x01);
	}
}

