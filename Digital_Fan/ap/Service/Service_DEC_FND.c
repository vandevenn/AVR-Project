#include "Service_DEC_FND.h"

static uint32_t F_millisec;
static uint8_t F_sec;
static uint8_t F_min;
static uint8_t F_hour;

void FNDData_init()
{
	F_millisec = 0;
	F_sec = 0;
	F_min = 0;
	F_hour = 0;
}

void setFNDData(uint8_t f_hour, uint8_t f_min,uint8_t f_sec, uint32_t f_millisec)
{
	F_millisec = f_millisec;
	F_sec = f_sec;
	F_min = f_min;
	F_hour = f_hour;
}

uint8_t getHour()
{
	return F_hour;
}

uint8_t getMin()
{
	return F_min;
	
}

uint8_t getSec()
{
	return F_sec;
	
}

uint32_t getMillisec()
{
	return F_millisec;
}



void decmillisec()
{
	uint8_t TimerFlag = Model_getTimerFlagData();
	
	if(TimerFlag == 0) return;
	if((F_millisec == 0)&&(F_sec == 0)&&(F_min == 0)&&(F_hour == 0)) return;
	if(F_millisec == 0) F_millisec = 999;
	else F_millisec = (F_millisec - 1);
	if(F_millisec < 500) FND_colonON();
	else FND_colonoff();
	if(F_millisec != 999) return;

	if (F_sec == 0) F_sec = 59;
	else F_sec = (F_sec - 1);
	if (F_sec != 59) return;
	
	if (F_min == 0) F_min = 59;
	else F_min = (F_min - 1);
	if (F_min != 59) return;
	
	if (F_hour == 0) F_hour = 23;
	else F_hour = (F_hour - 1);
}


void Digital_Fan_Execute_Stop()
{
	if((F_millisec == 0)&&(F_sec == 0)&&(F_min == 0)&&(F_hour == 0))
	{
		Fan_off();
		Model_setTimerFlagData(0);
		Model_setLCDTimerFlagData(0);
	}
}

void FNDDec_Run()
{
	Presenter_disFNDData(F_hour, F_min, F_sec, F_millisec);
	Presenter_soundBuzzer();
	Presenter_runFan();
	Presenter_disUART();
}