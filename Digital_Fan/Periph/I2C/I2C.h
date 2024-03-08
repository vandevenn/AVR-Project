#ifndef I2C_H_
#define I2C_H_

#include "avr/io.h"
#define IC2_DDR		DDRD
#define IC2_SCL		0
#define IC2_SDA		1

void I2C_init();
void I2C_txByte(uint8_t SLA_W, uint8_t data);
void I2C_start();
void I2C_stop();
void I2C_txDevAddr(uint8_t SLA_W);
void I2C_txData(uint8_t data);

#endif /* I2C_H_ */

