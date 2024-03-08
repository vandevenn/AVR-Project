#include "I2C_LCD.h"


uint8_t lcdControlData;  // 8bit D/E/W/RS/0000

// LCD data write Mode

// 1번째는 LCD 제어 명령 RS bit : 0
// RS bit : 0
// 2번째는 실제 데이터를 write
// RS bit : 1
// R/W bit : 0
// Enable bit : 0 or 1

void I2C_LCD_init()
{
	lcdControlData = 0;
	I2C_init();
	
	_delay_ms(15);
	LCD_writeNibble(0x30);
	_delay_ms(5);
	LCD_writeNibble(0x30);
	_delay_ms(1);
	LCD_writeNibble(0x30);
	LCD_writeNibble(0x20);
	LCD_writeCmdData(LCD_4BIT_FUNCTION_SET);
	LCD_writeCmdData(LCD_DISPLAY_OFF);
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);
	LCD_writeCmdData(LCD_ENTRY_MODE_SET);
	LCD_writeCmdData(LCD_DISPLAY_ON);
	LCD_backLightOn();
// 	Gpio_init();
// 	_delay_ms(15);
// 	LCD_writeCmdData(LCD_FUNCTION_SET);		// LCD_FUNCTION_SET   Data[7:0] : 001110xx (0x38) // 8-bit, 2-line, 5*8
// 	_delay_ms(5);
// 	LCD_writeCmdData(LCD_FUNCTION_SET);		// LCD_FUNCTION_SET   Data[7:0] : 001110xx (0x38) // 8-bit, 2-line, 5*8
// 	_delay_ms(1);
// 	LCD_writeCmdData(LCD_FUNCTION_SET);		// LCD_FUNCTION_SET   Data[7:0] : 001110xx (0x38) // 8-bit, 2-line, 5*8
// 	LCD_writeCmdData(LCD_FUNCTION_SET);		// LCD_FUNCTION_SET   Data[7:0] : 001110xx (0x38) // 8-bit, 2-line, 5*8
// 	LCD_writeCmdData(LCD_DISPLAY_OFF);		// LCD_DISPLAY_OFF	  Data[7:0] : 00001000 (0x08)
// 	LCD_writeCmdData(LCD_DISPLAY_CLEAR);	// LCD_DISPLAY_CLEAR  Data[7:0] : 00000001 (0x01)
// 	LCD_writeCmdData(LCD_ENTRY_MODE_SET);	// LCD_ENTRY_MODE_SET Data[7:0] : 00000110 (0x06)
// 	LCD_writeCmdData(LCD_DISPLAY_ON);		// LCD_DISPLAY_ON     Data[7:0] : 00001100 (0x0C)

}
void LCD_sendToI2C(uint8_t sla_w, uint8_t data)
{
	I2C_txByte(sla_w,data);
	
}

void LCD_backLightOn()
{
	lcdControlData |= (1<<LCD_BACKLIGHT);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}

void Gpio_init()
{
	LCD_CONTROL_DDR |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_E);
	LCD_DATA_DDR |= 0xff;
}

void Gpio_writeControlData(uint8_t data)
{
	LCD_CONTROL_PORT = data;
}

void Gpio_writeData(uint8_t data)
{
	LCD_DATA_PORT = data;
}

void LCD_cmdMode()
{
	//RS : 0
	lcdControlData &= ~(1<<LCD_RS); // instruction Register (RS : 0)
	//Gpio_writeControlData(lcdControlData);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}

void LCD_charMode()
{
	lcdControlData |= (1<<LCD_RS); // Data Register (RS : 1)
	//Gpio_writeControlData(lcdControlData);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}

void LCD_writeMode()
{
	lcdControlData &= ~(1<<LCD_RW); // Write Mode (RW : 0)
	//Gpio_writeControlData(lcdControlData);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}

void LCD_enableHigh()
{
	lcdControlData |= (1<<LCD_E); // Enable High Signal (E : 1)
	//Gpio_writeControlData(lcdControlData);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	_delay_ms(1);
}

void LCD_enableLow()
{
	lcdControlData &= ~(1<<LCD_E); // Enable Low Signal (E : 0)
	//Gpio_writeControlData(lcdControlData);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	_delay_ms(1);
}

void LCD_writeByte(uint8_t data)
{
	//Gpio_writeData(data);
	LCD_writeNibble(data);
	data <<= 4;
	LCD_writeNibble(data);
}

void LCD_writeNibble(uint8_t data)
{
	LCD_enableHigh();
	lcdControlData = (lcdControlData & 0x0f) | (data & 0xf0);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	LCD_enableLow();
}


void LCD_writeCmdData(uint8_t data)
{	// LCD control process
	LCD_cmdMode();
	LCD_writeMode();
	//LCD_enableHigh();
	LCD_writeByte(data);
	//LCD_enableLow();
}

void LCD_writeCharData(uint8_t data)
{	// LCD write process
	LCD_charMode();
	LCD_writeMode();
	//LCD_enableHigh();
	LCD_writeByte(data);
	//LCD_enableLow();
}

void LCD_writeString(char *str)
{
	for(int i=0; str[i]; i++)
	{
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col)
{
	col%=16;
	row%=2;
	uint8_t lcdregisterAddress = (0x40 * row) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char *str)
{
	LCD_gotoXY(row, col);
	LCD_writeString(str);
}

void LCD_displayClear()
{
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);
}
