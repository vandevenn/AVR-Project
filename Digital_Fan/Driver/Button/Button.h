/*
 * button.h
 *
 * Created: 2023-11-03 오후 3:30:09
 *  Author: kccistc
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


enum {PUSHED, RELEASED};
enum{ACT_NONE, ACT_PUSHED, ACT_RELEASED};
   
typedef struct _button //typedef: 형변환(타입 재정의)
{
   volatile uint8_t *DDR; //DDR //volatile : 최적화하지 말아라 ,uint8_t :  정수형 숫자 반환(0~255)
   volatile uint8_t *PIN; //PIN
   uint8_t pinNum;         //pin number
   uint8_t prevState;      //static 
   // port
   // pin
   // static
}button_t;

uint8_t Button_GetState(button_t *btn);
void Button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);

#endif /* BUTTON_H_ */