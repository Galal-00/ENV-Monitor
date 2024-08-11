/*
 * UART.c
 *
 * Created: 8/11/2024 12:36:37 PM
 *  Author: galal
 */

#include <avr/io.h>
#include "UART.h"

void UART_Init()
{
	/* Set baud rate */
	UBRRH = (unsigned char)(BAUD_PRESCALE>>8);
	UBRRL = (unsigned char)BAUD_PRESCALE;
	
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	
	/* Set frame format: 8 data bit */
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(3<<UCSZ0);
}

void UART_TxChar(char ch)
{
	while(!(UCSRA & (1<<UDRE)));	// wait for empty transmit buffer
	UDR = ch;
}

char UART_RxChar()
{
	while(!(UCSRA & (1<<RXC)));		// wait until data is received
	return UDR;
}

void UART_SendString(char *str)
{
	uint16_t j = 0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}