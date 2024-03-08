#include "Service_INC_LCD.h"

static uint32_t L_millisec;
static uint8_t L_sec;
static uint8_t L_min;
static uint8_t L_hour;

void LCDtime_init()
{
	L_millisec = 0;
	L_sec = 0;
	L_min = 0;
	L_hour = 0;
}



void IncMilisec()
{
	uint8_t autoState = Model_getAutoStateData();
	uint8_t ManualState = Model_getManualStateData();
	uint8_t LCDTimerFlag = Model_getLCDTimerFlagData();
	
	if((autoState != Auto_OFF) && (LCDTimerFlag == 1)) 
	{
		L_millisec = (L_millisec + 1) % 1000;
		if(L_millisec) return; // if는 0이 아닐때는 True -> return, 0일때는 false -> 다음 행을 실행
		
		L_sec = (L_sec + 1) %60;
		if(L_sec) return;
		
		L_min = (L_min + 1) %60;
		if(L_min) return;
		
		L_hour = (L_hour + 1 ) %24;
	}
	
	else if((ManualState != Manual_OFF) && (LCDTimerFlag == 1))
	{
		L_millisec = (L_millisec + 1) % 1000;
		if(L_millisec) return; // if는 0이 아닐때는 True -> return, 0일때는 false -> 다음 행을 실행
		
		L_sec = (L_sec + 1) %60;
		if(L_sec) return;
		
		L_min = (L_min + 1) %60;
		if(L_min) return;
		
		L_hour = (L_hour + 1 ) %24;
	}
}

void INC_LCD_run()
{
	Presenter_disLCDData(L_hour, L_min, L_sec, L_millisec);
	Presenter_soundBuzzer();
	Presenter_runFan();
	Presenter_disUART();
}