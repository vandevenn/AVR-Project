#include "Listener.h"
uint8_t *rxString;
button_t btnMode, btnRun, btnOff, btnTimer;

void Listener_init()
{
	Button_init(&btnMode, &DDRA, &PINA, 0);
	Button_init(&btnRun, &DDRA, &PINA, 1);
	Button_init(&btnOff, &DDRA, &PINA, 2);
	Button_init(&btnTimer, &DDRA, &PINA, 3);
	UART0_init();
	rxString = UART0_readRxBuff();
}

void Listener_checkTimerEvent()
{
	uint8_t TimerState = Model_getTimerStateData();
	switch(TimerState)
	{
		case No_Timer:
		Listener_checkModeEvent();
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			setFNDData(0, 1,0, 0);
			Model_setTimerFlagData(1);
			Model_setLCDTimerFlagData(1);
			Fan_On();
			StopWatchData = 0;
			TimerState = One_Min;
			Model_setTimerStateData(TimerState);
		}
		break;
		
		case One_Min:
		Listener_checkModeEvent();
		Digital_Fan_Execute_Stop();
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			setFNDData(0, 3,0, 0);
			Model_setTimerFlagData(1);
			Model_setLCDTimerFlagData(1);
			Fan_On();
			StopWatchData = 0;
			TimerState = Three_Min;
			Model_setTimerStateData(TimerState);
		}
		break;
		
		case Three_Min:
		Listener_checkModeEvent();
		Digital_Fan_Execute_Stop();
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			setFNDData(0, 5,0, 0);
			Model_setTimerFlagData(1);
			Model_setLCDTimerFlagData(1);
			Fan_On();
			StopWatchData = 0;
			TimerState = Five_Min;
			Model_setTimerStateData(TimerState);
		}
		break;
		
		case Five_Min:
		Listener_checkModeEvent();
		Digital_Fan_Execute_Stop();
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			setFNDData(0, 0,0, 0);
			Model_setTimerFlagData(0);
			Model_setLCDTimerFlagData(1);
			Fan_On();
			StopWatchData = 0;
			TimerState = No_Timer;
			Model_setTimerStateData(TimerState);
		}
		break;
	}
}

void Listener_checkModeEvent()
{
	uint8_t ModeState = Model_getModeStateData();
	switch(ModeState)
	{
		case MANUAL:
		Listener_checkManualEvent();
		if(Button_GetState(&btnMode) == ACT_RELEASED){
			Model_setAutoStateData(Auto_OFF);
			ModeState = AUTO;
			Model_setModeStateData(ModeState);
		}
		break;
		
		case AUTO:
		if(Button_GetState(&btnMode) == ACT_RELEASED){
			Model_setManualStateData(Manual_OFF);
			ModeState = MANUAL;
			Model_setModeStateData(ModeState);
		}
		break;
	}	
}


void Listener_checkManualEvent()
{
	uint8_t modeState = Model_getModeStateData();
	uint8_t ManualState = Model_getManualStateData();
	
	if (modeState != MANUAL) return;
	
	switch(ManualState)
	{
		case Manual_FanPower1:
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower2;
			Model_setManualStateData(ManualState);
		}
		
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
			Model_setManualStateData(ManualState);
		}
		
		break;
		
		case Manual_FanPower2:
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower3;
			Model_setManualStateData(ManualState);
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
			Model_setManualStateData(ManualState);
		}
		
		break;
		
		case Manual_FanPower3:
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_OFF;
			Model_setManualStateData(ManualState);
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
			Model_setManualStateData(ManualState);
		}
		
		break;
		
		case Manual_OFF:
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower1;
			Model_setManualStateData(ManualState);
		}
		break;
	}
	
	if(UART0_readyRxFlag())
	{
		UART0_clearRxFlag();
		if(!strcmp(rxString, "FanPower1\n"))
		{
			Model_setManualStateData(Manual_FanPower1);
		}
		else if(!strcmp(rxString, "FanPower2\n"))
		{
			Model_setManualStateData(Manual_FanPower2);
		}
		else if(!strcmp(rxString, "FanPower3\n"))
		{
			Model_setManualStateData(Manual_FanPower3);
		}
		else if(!strcmp(rxString, "FanOff\n"))
		{
			Model_setManualStateData(Manual_OFF);
		}
	}
}

