/*
 * CFile1.c
 *
 * Created: 05/09/2019 14:07:09
 *  Author: tedes
 */ 

#include <avr/io.h>
#include "communication.h"
#include <stdio.h>


void My_serial_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(31>>8);
	UBRR0L = (unsigned char)31;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	fdevopen(My_serial_Transmit, My_serial_Receive);
}

int My_serial_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
	return(0);
}

int My_serial_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}