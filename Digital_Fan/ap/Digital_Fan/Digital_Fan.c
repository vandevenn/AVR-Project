#include "Digital_Fan.h"
//FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);
//uint32_t timeTick = 0;
uint8_t *rxString;

//초기화
void Digital_Fan_init()
{
	Fan_init();
	TIM2_init();
	Button_init(&btnMode, &DDRA, &PINA, 0);
	Button_init(&btnRun, &DDRA, &PINA, 1);
	Button_init(&btnOff, &DDRA, &PINA, 2);
	Button_init(&btnTimer, &DDRA, &PINA, 3);
	ModeState = MANUAL;
	ManualState = Manual_OFF;
	AutoState = Auto_OFF;
	UART0_init();
	//stdout = &OUTPUT;
	rxString = UART0_readRxBuff();
	TimerState = No_Timer;
	F_millisec = 0;
	F_sec = 0;
	F_min = 0;
	F_hour = 0;
	L_millisec = 0;
	L_sec = 0;
	L_min = 0;
	L_hour = 0;
	TimerFlag = 0;
	LCDTimerFlag = 1;
	I2C_LCD_init();
	Buzzer_init();
	FND_init();
	TIM0_init();
}

// 수동 모드 상태변경
void Fan_Manual_eventButton()
{
	switch(ManualState)
	{
		case Manual_OFF :
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower1;
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
		}
		break;
		case Manual_FanPower1 :
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower2;
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
		}
		break;
		case Manual_FanPower2 :
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_FanPower3;
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
		}
		break;
		case Manual_FanPower3 :
		if(Button_GetState(&btnRun) == ACT_RELEASED){
			ManualState = Manual_OFF;
		}
		else if(Button_GetState(&btnOff) == ACT_RELEASED){
			ManualState = Manual_OFF;
		}
		break;
	}
	//uart 수신
	if(UART0_readyRxFlag())
	{
		UART0_clearRxFlag();
		if(!strcmp(rxString, "FanPower1\n"))
		{
			ManualState = Manual_FanPower1;
		}
		else if(!strcmp(rxString, "FanPower2\n"))
		{
			ManualState = Manual_FanPower2;
		}
		else if(!strcmp(rxString, "FanPower3\n"))
		{
			ManualState = Manual_FanPower3;
		}
		else if(!strcmp(rxString, "FanOff\n"))
		{
			ManualState = Manual_OFF;
		}
	}
}

//수동 모드 팬 동작
void Fan_Manual_Run()
{
	static int previousState = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	int currentState = ManualState;

	if (previousState != currentState) {
		// 상태가 변경되었을 때만 출력
		switch(currentState) {
			case Manual_OFF :
			Fan_off();
			printf("FanOff\n");
			//풍량
			sprintf(buff, "Wind:MOFF");
			LCD_writeStringXY(1,0, buff);
			//OFF buzzer
			Buzzer_powerOFFSound();
			break;
			case Manual_FanPower1 :
			Fan_Power1();
			printf("FanPower1\n");
			//풍량
			sprintf(buff, "Wind:M1  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
			case  Manual_FanPower2:
			Fan_Power2();
			printf("FanPower2\n");
			//풍량
			sprintf(buff, "Wind:M2  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
			case Manual_FanPower3 :
			Fan_Power3();
			printf("FanPower3\n");
			//풍량
			sprintf(buff, "Wind:M3  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
		}
		// 상태가 변경된 경우에만 이전 상태를 갱신
		previousState = currentState;
	}
}

//수동모드
void Manual_execute()
{
	Fan_Manual_eventButton();
	Fan_Manual_Run();
}

////자동모드
//void Auto_excute()
//{
	//_delay_ms(1);
	////timeTick++;
	//Fan_Auto_Modechange();
	//Fan_Auto_Run();
//}
//
////자동모드 상태변경
//void Fan_Auto_Modechange()
//{
	//static uint32_t prevTime = 0;
	//switch(AutoState)
	//{
		//case Auto_OFF :
		//if(timeTick - prevTime >= 45)
		//{
			//prevTime = timeTick;
			//AutoState = Auto_FanPower1;
		//}
		//break;
		//case Auto_FanPower1 :
		//if(timeTick - prevTime >= 30)
		//{
			//prevTime = timeTick;
			//AutoState = Auto_FanPower2;
		//}
		//break;
		//case  Auto_FanPower2:
		//if(timeTick - prevTime >= 30)
		//{
			//prevTime = timeTick;
			//AutoState = Auto_FanPower3;
		//}
		//break;
		//case Auto_FanPower3 :
		//if(timeTick - prevTime >= 30)
		//{
			//prevTime = timeTick;
			//AutoState = Auto_OFF;
		//}
		//break;
	//}
//}

//자동모드 실행
void Fan_Auto_Run()
{
	static int previousState = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	int currentState = AutoState;

	if (previousState != currentState) {
		// 상태가 변경되었을 때만 출력
		switch(currentState) {
			case Auto_OFF :
			Fan_off();
			printf("FanOff\n");
			//풍량
			sprintf(buff, "Wind:AOFF");
			LCD_writeStringXY(1,0, buff);
			//OFF buzzer
			Buzzer_powerOFFSound();
			break;
			case Auto_FanPower1 :
			Fan_Power1();
			printf("FanPower1\n");
			//풍량
			sprintf(buff, "Wind:A1  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
			case  Auto_FanPower2:
			Fan_Power2();
			printf("FanPower2\n");
			//풍량
			sprintf(buff, "Wind:A2  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
			case Auto_FanPower3 :
			Fan_Power3();
			printf("FanPower3\n");
			//풍량
			sprintf(buff, "Wind:A3  ");
			LCD_writeStringXY(1,0, buff);
			//ON buzzer
			Buzzer_powerOnSound();
			break;
		}
		// 상태가 변경된 경우에만 이전 상태를 갱신
		previousState = currentState;
	}
}

//수동모드,자동모드 변경
void Digital_Fan_Execute()
{
	
	if (ModeState == MANUAL)
	{
		Manual_execute();
		if (Button_GetState(&btnMode) == ACT_RELEASED)
		{
			ModeState = AUTO;
		}
	}
	else if (ModeState == AUTO)
	{
		Auto_excute();
		if (Button_GetState(&btnMode) == ACT_RELEASED)
		{
			ModeState = MANUAL;
		}
	}
	//제품명.
	sprintf(buff, " 2 FAN");
	LCD_writeStringXY(1,9, buff);
}

//1분, 3분, 5분 Timer 기능 추가
void Digital_Fan_Execute_Timer()
{
	sprintf(buff, "Time %02d: %02d: %02d" , L_hour, L_min, L_sec);
	LCD_writeStringXY(0,0, buff);
	
	
	switch(TimerState)
	{
		case No_Timer:
		Digital_Fan_Execute();
		if (Button_GetState(&btnTimer) == ACT_RELEASED)
		{
			F_millisec = 0;
			F_sec = 0;
			F_min = 1;
			F_hour = 0;
			TimerFlag = 1;
			LCDTimerFlag = 1;
			Fan_On();
			StopWatchData = 0;
			TimerState = One_Min;
		}
		break;
		
		case One_Min:
		Digital_Fan_Execute_Stop();
		if (Button_GetState(&btnTimer) == ACT_RELEASED)
		{
			F_millisec = 0;
			F_sec = 0;
			F_min = 3;
			F_hour = 0;
			TimerFlag = 1;
			LCDTimerFlag = 1;
			Fan_On();
			StopWatchData = 0;
			TimerState = Three_Min;
		}
		break;
		
		case Three_Min:
		Digital_Fan_Execute_Stop();
		if (Button_GetState(&btnTimer) == ACT_RELEASED)
		{
			F_millisec = 0;
			F_sec = 0;
			F_min = 5;
			F_hour = 0;
			TimerFlag = 1;
			LCDTimerFlag = 1;
			Fan_On();
			StopWatchData = 0;
			TimerState = Five_Min;
		}
		break;
		
		case Five_Min:
		Digital_Fan_Execute_Stop();
		if (Button_GetState(&btnTimer) == ACT_RELEASED)
		{
			F_millisec = 0;
			F_sec = 0;
			F_min = 0;
			F_hour = 0;
			TimerFlag = 0;
			LCDTimerFlag = 1;
			Fan_On();
			StopWatchData = 0;
			TimerState = No_Timer;
		}
		break;
	}
	StopWatchData = (F_min * 100) + (F_sec);
	FND_setFndData(StopWatchData);
}

//timer 후 종료
void Digital_Fan_Execute_Stop()
{
	if((F_millisec == 0)&&(F_sec == 0)&&(F_min == 0)&&(F_hour == 0))
	{
		Fan_off();
		TimerFlag = 0;
		LCDTimerFlag = 0;
	}
	
	else
	{
		Digital_Fan_Execute();
	}
}

// 1ms 씩 증가시키는 함수
void incMilisec()
{
	L_millisec = (L_millisec + 1) % 1000;
	if(L_millisec) return; // if는 0이 아닐때는 True -> return, 0일때는 false -> 다음 행을 실행
	
	L_sec = (L_sec + 1) %60;
	if(L_sec) return;
	
	L_min = (L_min + 1) %60;
	if(L_min) return;
	
	L_hour = (L_hour + 1 ) %24;

}
// 1ms 씩 감소시키는 함수
void decMilisec()
{
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