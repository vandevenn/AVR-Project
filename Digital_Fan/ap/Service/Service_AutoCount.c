#include "Service_AutoCount.h"
uint32_t timeTick = 0;

//자동모드
void Auto_excute()
{
	uint8_t ModeState = Model_getModeStateData();
	if(ModeState == AUTO)
	{
	_delay_ms(1);
	timeTick++;
	Fan_Auto_Modechange();
	}
}

//자동모드 상태변경
void Fan_Auto_Modechange()
{
	static uint32_t prevTime = 0;
	uint8_t AutoState = Model_getAutoStateData();
	switch(AutoState)
	{
		case Auto_OFF :
		if(timeTick - prevTime >= 50)
		{
			prevTime = timeTick;
			Model_setAutoStateData(Auto_FanPower1);
		}
		break;
		case Auto_FanPower1 :
		if(timeTick - prevTime >= 50)
		{
			prevTime = timeTick;
			Model_setAutoStateData(Auto_FanPower2);
		}
		break;
		case  Auto_FanPower2:
		if(timeTick - prevTime >= 50)
		{
			prevTime = timeTick;
			Model_setAutoStateData(Auto_FanPower3);
		}
		break;
		case Auto_FanPower3 :
		if(timeTick - prevTime >= 50)
		{
			prevTime = timeTick;
			Model_setAutoStateData(Auto_OFF);
		}
		break;
	}
}