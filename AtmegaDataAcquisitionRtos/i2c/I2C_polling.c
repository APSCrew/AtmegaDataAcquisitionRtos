/*
 * I2C_polling.c
 *
 * Created: 26/12/2013 14:42:12
 *  Author: Luca
 */

#include <avr/io.h>
#include "I2C_polling.h"


void init_i2c(unsigned char f){
	TWSR = 0x00;       // set prescaler = 1
	TWBR = f;
	TWCR |= (1<<TWEN); // enable TW
}

void i2c_start(void){
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ( !(TWCR & (1<<TWINT)) ) ;
}

void i2c_stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	for(int k=0; k<100;k++) ;
}

void i2c_write(unsigned char data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) ) ;
}

unsigned char i2c_read(unsigned char ackValue){
	TWCR = (1<<TWINT) | (1<<TWEN) | (ackValue<<TWEA);
	while ( !(TWCR & (1<<TWINT)) ) ;

	return TWDR;
}


/*
  la procedura di scrittura e lettura non sono come l'esempio del libro!
  si riferiscono ai lucidi in powerpoint
*/
void write(unsigned char adr, unsigned char adr_reg, unsigned char data[], unsigned char nByte){
	unsigned char i;

	i2c_start();
	i2c_write((adr<<1) | (0<<0)); //write SLA+W on i2c bus

	i2c_write(adr_reg);           // write address register on i2c bus

	for (i=0;i<nByte;i++)         // NB:   1 <= nBytes <= n
	{
		i2c_write(data[i]);       // write n-Bytes on i2c bus
	}

	i2c_stop();

}
void read(unsigned char adr, unsigned char adr_reg, unsigned char data[], unsigned char nByte){

	unsigned char i;

	i2c_start();
	i2c_write((adr<<1) | (0<<0));  // write SLA+W on i2c bus
	i2c_write(adr_reg);            // write address register on i2c bus

	i2c_start();
	i2c_write((adr<<1) | (1<<0));  //write SLA+R on i2c bus

	for (i=0;i<nByte;i++)          // NB:   1 <= nBytes <= n
	{
		if ( i == (nByte-1) )
		{
			data[i] = i2c_read(0); // read data and send NACK
		}
		else
		{
			data[i] = i2c_read(1); // read data and send ACK
		}
	}

	i2c_stop();
}