#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "uart_transmission.h"

#define USART_BAUDRATE 9600

static volatile uint16_t pulse_0 = 0;
static volatile unsigned char i_0 = 0;
static volatile uint16_t pulse_1 = 0;
static volatile unsigned char i_1 = 0;
static volatile unsigned char data = 0;
static volatile unsigned char result_1 = 0;
static volatile unsigned char result_2 = 0;
void init_sonar();
void send_right_sonar_data();
void send_left_sonar_data();

int main(void)
{
    init_sonar();
	UART_init_recieve_by_interrupt(USART_BAUDRATE);
	sei();
	while(1)
	{
	    PORTB |= (1 << PORT0);
		_delay_us(15);
		PORTB &= ~( 1<< PORT0);
		_delay_ms(50);
		result_2 = pulse_0/58;
		PORTB |= (1 << PORT1);
		_delay_us(15);
		PORTB &= ~( 1<< PORT1);
		_delay_ms(50);
		result_1 = pulse_1/58;

	}
}

ISR(USART_RXC_vect){
	data = UDR;
	if(data == 1){
		// send_right_sonar_data();
		UART_transmit_char(result_1);
	} else if(data == 2){
		// send_left_sonar_data();
		UART_transmit_char(result_2);
	}
}

ISR(INT0_vect)
{
	if(i_0 == 1)
	{
		TCCR1B = 0;
		pulse_0 = TCNT1;
		TCNT1 = 0;
		i_0 = 0;
	} else
	{
		TCCR1B |= 1 << CS10;
		i_0 = 1;
	}
}

ISR(INT1_vect)
{
	if(i_1 == 1)
	{
		TCCR1B = 0;
		pulse_1 = TCNT1;
		TCNT1 = 0;
		i_1 = 0;
	} else
	{
		TCCR1B |= 1 << CS10;
		i_1 = 1;
	}
}

void init_sonar(){
    DDRD &= ~(1 << DD2) & ~(1 << DD3);
	DDRB |= (1 << DD0) | (1 << DD1);

	GICR |= (1 << INT0) | (1 << INT1);
	MCUCR |= (1 << ISC00) | (1 << ISC10) ;
}

void send_right_sonar_data(){
    PORTB |= (1 << PORT1);
    _delay_us(15);
    PORTB &= ~( 1<< PORT1);
    _delay_ms(50);
    result_1 = pulse_1/58;
	UART_transmit_char(result_1);
}

void send_left_sonar_data(){
    PORTB |= (1 << PORT0);
    _delay_us(15);
    PORTB &= ~( 1<< PORT0);
    _delay_ms(50);
    result_2 = pulse_0/58;
	UART_transmit_char(result_2);
}