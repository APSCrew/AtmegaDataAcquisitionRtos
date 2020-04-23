/*
 * USART_polling.h
 *
 * Created: 25/08/2014 11:38:13
 *  Author: Luca
 */ 


#ifndef USART_POLLING_H_
#define USART_POLLING_H_

#define BAUD_38400_16MHZ 25
#define BAUD_76800_16MHZ 12
#define BAUD_250000_16MHZ 3
#define BAUD_115200_2x_16MHZ 16
#define EN_2X 1
#define DIS_2X 0

#define ACK 0x06
#define NACK 0x15


void InitUART( unsigned char baudrate, unsigned char en2x);
unsigned char ReceiveByte( void );
void TransmitByte( unsigned char data );

void Transmit_ulong( unsigned long data );
void Transmit_long( long data );
void Transmit_float( float data );
void Transmit_uint( unsigned int data );
void Transmit_int( int data );


unsigned int receive_uint(void);
float receive_float(void);
#endif /* USART_POLLING_H_ */