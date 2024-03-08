#include "APmain.h"

ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}

ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect)
{
	decmillisec();
	IncMilisec();
}
void APMain_init()
{
	Presenter_init();
	Listener_init();
	LCDtime_init();
	FNDData_init();
	TIM0_init();
	TIM2_init();

	sei();
	Model_setAutoStateData(Auto_OFF);
	Model_setLCDTimerFlagData(1);
	Model_setManualStateData(Manual_OFF);
	Model_setTimerFlagData(0);
	Model_setModeStateData(MANUAL);
	Model_setTimerStateData(No_Timer);
}

void APMain_execute()
{
	Listener_checkTimerEvent();
	Listener_checkModeEvent();
	Listener_checkManualEvent();
	
	
	INC_LCD_run();
	FNDDec_Run();
	Auto_excute();
}