#include "Presenter.h"
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

void Presenter_init()
{
	FND_init();
	I2C_LCD_init();
	Fan_init();
	Buzzer_init();
	UART0_init();
	stdout = &OUTPUT;
}

void Presenter_disLCDData(uint8_t L_hour,uint8_t L_min,uint8_t L_sec,uint32_t L_millisec)
{
	sprintf(buff, "Time %02d: %02d: %02d" , L_hour, L_min, L_sec);
	LCD_writeStringXY(0,0, buff);
	
	uint8_t modeState = Model_getModeStateData();
	uint8_t autoState = Model_getAutoStateData();
	uint8_t manualState = Model_getManualStateData();
	
	if(modeState == AUTO)
	{
		switch(autoState) {
			case Auto_OFF :
			sprintf(buff, "Wind:AOFF");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case Auto_FanPower1 :
			sprintf(buff, "Wind:A1  ");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case  Auto_FanPower2:
			sprintf(buff, "Wind:A2  ");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case Auto_FanPower3 :
			sprintf(buff, "Wind:A3  ");
			LCD_writeStringXY(1,0, buff);
			break;
		}	
	}
	
	if(modeState == MANUAL)
	{
		switch(manualState) {
			case Manual_OFF :
			sprintf(buff, "Wind:MOFF");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case Manual_FanPower1 :
			sprintf(buff, "Wind:M1  ");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case  Manual_FanPower2:
			sprintf(buff, "Wind:M2  ");
			LCD_writeStringXY(1,0, buff);
			break;
			
			case Manual_FanPower3 :
			sprintf(buff, "Wind:M3  ");
			LCD_writeStringXY(1,0, buff);
			break;
		}
	}
	
	
	sprintf(buff, " 2 FAN");
	LCD_writeStringXY(1,9, buff);
}


void Presenter_disFNDData(uint8_t F_hour,uint8_t F_min,uint8_t F_sec,uint32_t F_millisec)
{
	StopWatchData = (F_min * 100) + (F_sec);
	FND_setFndData(StopWatchData);
}


void Presenter_soundBuzzer()
{
	uint8_t modeState = Model_getModeStateData();
	static int previousState_one = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	uint8_t ManualState = Model_getManualStateData();
	uint8_t currentState_one = ManualState;

	if(modeState == MANUAL)
	{
		if (previousState_one != currentState_one) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_one) {
				case Manual_OFF :
				Buzzer_powerOFFSound();
				break;
				
				case Manual_FanPower1 :
				Buzzer_powerOnSound();
				break;
				
				case  Manual_FanPower2:
				Buzzer_powerOnSound();
				break;
				
				case Manual_FanPower3 :
				Buzzer_powerOnSound();
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState_one = currentState_one;
		}
	}

	
	static int previousState_two = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	uint8_t AutoState = Model_getAutoStateData();
	uint8_t currentState_two = AutoState;

	if(modeState == AUTO)
	{
		if (previousState_two != currentState_two) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_two) {
				case Auto_OFF :
				Buzzer_powerOFFSound();
				break;
				
				case Auto_FanPower1 :
				Buzzer_powerOnSound();
				break;
				
				case  Auto_FanPower2:
				Buzzer_powerOnSound();
				break;
				
				case Auto_FanPower3 :
				Buzzer_powerOnSound();
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState_two = currentState_two;
		}		
	}
	
}




void Presenter_runFan()
{
	uint8_t modeState = Model_getModeStateData();
	static int previousState_one = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	uint8_t ManualState = Model_getManualStateData();
	uint8_t currentState_one = ManualState;
	
	if(modeState == MANUAL)
	{
		if (previousState_one != currentState_one) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_one) {
				case Manual_OFF :
				Fan_off();
				break;
				
				case Manual_FanPower1 :
				Fan_Power1();
				break;
				
				case  Manual_FanPower2:
				Fan_Power2();
				break;
				
				case Manual_FanPower3 :
				Fan_Power3();
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState_one = currentState_one;
		}
	}
	
	
	
	static int previousState_two = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	uint8_t AutoState = Model_getAutoStateData();
	uint8_t currentState_two = AutoState;

	if(modeState == AUTO)
	{
		if (previousState_two != currentState_two) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_two) {
				case Auto_OFF :
				Fan_off();
				break;
				
				case Auto_FanPower1 :
				Fan_Power1();
				break;
				
				case  Auto_FanPower2:
				Fan_Power2();
				break;
				
				case Auto_FanPower3 :
				Fan_Power3();
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState_two = currentState_two;
		}
	}
}

void Presenter_disUART()
{
	uint8_t modeState = Model_getModeStateData();
	static int previousState = 0;  // 초기값으로 음수를 사용하여 초기 상태와 다르게 설정
	uint8_t ManualState = Model_getManualStateData();
	uint8_t AutoState = Model_getAutoStateData();
	uint8_t currentState_M = ManualState;
	uint8_t currentState_A = AutoState;

	if(modeState == MANUAL)
	{
		if (previousState != currentState_M) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_M) {
				case Manual_OFF :
				printf("FanOff\n");
				break;
				
				case Manual_FanPower1 :
				printf("FanPower1\n");
				break;
				
				case  Manual_FanPower2:
				printf("FanPower2\n");
				break;
				
				case Manual_FanPower3 :
				printf("FanPower3\n");
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState = currentState_M;
		}
	}

	if(modeState == AUTO)
	{
		if (previousState != currentState_A) {
			// 상태가 변경되었을 때만 출력
			switch(currentState_A) {
				case Auto_OFF :
				printf("FanOff\n");
				break;
				
				case Auto_FanPower1 :
				printf("FanPower1\n");
				break;
				
				case  Auto_FanPower2:
				printf("FanPower2\n");
				break;
				
				case Auto_FanPower3 :
				printf("FanPower3\n");
				break;
			}
			// 상태가 변경된 경우에만 이전 상태를 갱신
			previousState = currentState_A;
		}
	
	
	}
	
}
