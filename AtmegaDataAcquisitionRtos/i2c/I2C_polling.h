/*
 * I2C_polling.h
 *
 * Created: 26/12/2013 14:43:40
 *  Author: Luca
 */ 


#ifndef I2C_POLLING_H_
#define I2C_POLLING_H_

#define F_I2C_400 0x02		   //@ 8MHz, F_I2C = 400KHz
#define F_I2C_100 0x20		   //@ 8MHz, F_I2C = 100KHz
#define F_I2C_400_16_MHZ 0x0C  //@ 16MHz, F_I2C = 400KHz
#define F_I2C_100_16_MHZ 0x48  //@ 16MHz, F_I2C = 100KHz

void init_i2c(unsigned char freq);

void transmit_start_condition(void);
void transmit_stop_condition(void);

void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char ack);

void write(unsigned char slave_adr, unsigned char reg_adr, unsigned char data[], unsigned char numByte);
void read(unsigned char slave_adr, unsigned char reg_adr, unsigned char data[], unsigned char numByte);

#endif /* I2C_POLLING_H_ */