#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init(long USART_BAUDRATE){
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

void UART_init_recieve_by_interrupt(long USART_BAUDRATE){
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

unsigned char UART_receive_char() {
	while((UCSRA & (1 << RXC)) == 0){}
	return UDR;
}

void UART_transmit_char(char ch) {
	while(!(UCSRA & (1 << UDRE))){}
	UDR = ch;
}

void UART_transmit_string(char *str){
	unsigned char i = 0;
	do{
		UART_transmit_char(str[i]);
		i++;
	} while ((str[i] != 0));
}
