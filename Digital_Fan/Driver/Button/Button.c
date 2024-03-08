#include "Button.h"


void Button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum) //포인터 변수 (주소 저장) 
{ //init= 초기화 // 버튼을 사용하기 전에 초기화 시키겠다
	btn -> DDR = ddr; //btn: 구조체 멤버
	btn -> PIN = pin;
	btn -> pinNum = pinNum;
	btn -> prevState = RELEASED;
	*btn-> DDR &= ~(1 << btn -> pinNum); // DDR   방향 설정
}


uint8_t Button_GetState(button_t *btn)
{
	//static uint8_t prevState = 1; //이전 값
	uint8_t curState = *btn -> PIN & (1 << btn->pinNum); //현재 값 // 버튼을 눌렀는지 안눌렀는지
	
	//
	if((curState == PUSHED) && (btn->prevState == RELEASED)) {
		_delay_ms(10);
		btn->prevState = PUSHED;
		return ACT_PUSHED;
	}
	else if((curState != PUSHED) && (btn->prevState == PUSHED)){
		_delay_ms(10);
		btn->prevState = RELEASED;
		return ACT_RELEASED;
	}
	return ACT_NONE;
}
