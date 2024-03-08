#include "GPIO.h"

//특정포트 (8ea) init
void Gpio_initPort(volatile uint8_t *DDR, uint8_t dir)
{
	if(dir == OUTPUT)
	{
		*DDR = 0xff; //OUTPUT mode
	}
	else{
		*DDR = 0x00; //INPUT mode
	}
}

//특정포트의 Pin(1ea) init
void Gpio_initPin(volatile uint8_t *DDR, uint8_t pinNum, uint8_t dir)
{
	if(dir == OUTPUT) {
		*DDR |= (1<<pinNum);
		//DDRD |= (1<<0);
	}
	else {*DDR &= ~(1<<pinNum);
	}
}

//특정포트 (8ea) PORT
void Gpio_writePort(volatile uint8_t *PORT, uint8_t data)
{
	*PORT = data; //data PORT OUTPUT
}

//특정포트의 Pin(1ea) PORT
void Gpio_writePin(volatile uint8_t *PORT, uint8_t pinNum, uint8_t state)
{
	if(state == GPIO_PIN_SET){
		*PORT |= (1<<pinNum);
	}
	else {*PORT &= ~(1<<pinNum);
	}
}//1이면 출력 아니면 0

//특정포트 (8ea) PIN
uint8_t Gpio_readPort(volatile uint8_t *PIN)
{
	return *PIN;
}

//특정포트의 Pin(1ea) PIN
uint8_t Gpio_readPin(volatile uint8_t *PIN, uint8_t pinNum)
{
	return ((*PIN &(1<<pinNum)) != 0);
	//버튼이 눌려지면 0 반환
	//버튼이 안눌려지면 0이 아닌 값 반환
}