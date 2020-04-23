/*
 * USART_polling.c
 *
 * Created: 25/08/2014 11:37:45
 *  Author: Luca
 */ 

#include <avr/io.h>

/* initialize UART */
void InitUART( unsigned char baudrate, unsigned char en2x )
{
	if (en2x)
	{
		UBRR0L = baudrate; /* set the baud rate */
		UCSR0A |= (1<<U2X0);
		UCSR0B = ( (1<<RXEN0) | (1<<TXEN0) ); /* enable UART receiver and transmitter */
	} 
	else
	{
		UBRR0L = baudrate; /* set the baud rate */
		UCSR0B = ( (1<<RXEN0) | (1<<TXEN0) ); /* enable UART receiver and transmitter */		
	}
}

/* Read and write functions */
unsigned char ReceiveByte( void )
{
	while ( !(UCSR0A & (1<<RXC0)) ) /* wait for incomming data */
	; /* return the data */
	return UDR0;
}

void TransmitByte( unsigned char data )
{
	while ( !(UCSR0A & (1<<UDRE0)) )
	; /* wait for empty transmit buffer */
	UDR0 = data; /* start transmittion */
}

void Transmit_float(float data)  /*litte endian, lsb first*/
{
	unsigned char ii = 0;
	unsigned char *temp_f = (unsigned char*)(&data);

	for (ii = 0; ii <= 3; ii++)
	TransmitByte(*(temp_f + ii));
}

void Transmit_ulong(unsigned long data)  /*litte endian, lsb first*/
{
	unsigned char i = 0;
	unsigned char *temp = (unsigned char*)(&data);

	for (i = 0; i <= 3; i++)
	TransmitByte(*(temp + i));
}

void Transmit_long(long data)
{
	unsigned char i = 0;
	unsigned char *temp = (unsigned char*)(&data);

	for (i = 0; i <= 3; i++)
	TransmitByte(*(temp + i));
}

void Transmit_uint(unsigned int data)   /*litte endian, lsb first*/
{
	unsigned char i = 0;
	unsigned char *temp = (unsigned char*)(&data);

	for (i = 0; i <= 1; i++)
	TransmitByte(*(temp + i));
}


void Transmit_int(int data)   /*litte endian, lsb first*/
{
	unsigned char i = 0;
	unsigned char *temp = (unsigned char*)(&data);

	for (i = 0; i <= 1; i++)
	TransmitByte(*(temp + i));
}

unsigned int receive_uint(void)
{
	unsigned char bytes[2];
	unsigned char i;

	for (i = 0; i<=1; i++){
		bytes[i] = ReceiveByte();
	}

	unsigned int *uint_ptr = (unsigned int*) &bytes[0];
	unsigned int temp = *uint_ptr;
	
	return temp;
}

float receive_float(void)
{
	unsigned char bytes[4];
	unsigned char i;

	for (i = 0; i<=3; i++){
		bytes[i] = ReceiveByte();
	}

	float *flo_ptr = (float*) &bytes[0];
	float temp = *flo_ptr;
	
	return temp;
}