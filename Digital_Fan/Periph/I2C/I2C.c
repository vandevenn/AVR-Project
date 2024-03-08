#include "I2C.h"



void I2C_init()
{
	IC2_DDR |= (1<<IC2_SCL) | (1<<IC2_SDA);
	TWBR = 72;		//100khz SCL
	//TWBR = 32;		200khz SCL
	//TWBR = 12;		400khz SCL
	TWSR = 0;
}

void I2C_txByte(uint8_t SLA_W, uint8_t data)
{
	// 1. Start 신호 송신,
	I2C_start();
	// 2. Device address 7bit + write 1bit + ack 1bit
	I2C_txDevAddr(SLA_W);
	// 3. Data  송신
	I2C_txData(data);
	// 4. Stop 신호 송신
	I2C_stop();
}

void I2C_start()
{
	//Send START condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//Wait for TWINT flag set. This indicates that the START condition has been transmitted
	while (!(TWCR & (1<<TWINT)));
}

void I2C_txDevAddr(uint8_t SLA_W)
{	//Load SLA_W into TWDR Register.
	TWDR = SLA_W;
	// Clear  TWINT bit in TWCR to start transmission of address
	TWCR = (1<<TWINT) |(1<<TWEN);
	// This indicates that the SLA+W has been transmitted, and ACK/NACK has been received
	while (!(TWCR & (1<<TWINT)))
	;
}

void I2C_txData(uint8_t data)
{	// Load DATA into TWDR Register.
	TWDR = data;
	// Clear TWINT bit in TWCR to start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	//Wait for TWINT flag set. This indicates that the DATA has been transmitted, and ACK/NACK 	has been received
	while (!(TWCR & (1<<TWINT)));
}

void I2C_stop()
{
	// Transmit STOP condition
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}