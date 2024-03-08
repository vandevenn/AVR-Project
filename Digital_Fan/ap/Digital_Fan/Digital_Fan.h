#ifndef DIGITAL_FAN_H_
#define DIGITAL_FAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../Driver/Button/Button.h"
#include "../../Driver/Buzzer/Buzzer.h"
#include "../../Driver/FND/FND.h"
#include "../../Driver/I2C_LCD/I2C_LCD.h"
#include "../../Driver/Fan/Fan.h"
#include "../../Periph/Uart0/Uart0.h"
#include "../../Periph/TIM/TIM.h"

uint8_t ModeState;
uint8_t ManualState;
uint8_t AutoState;
uint8_t TimerState;
uint8_t TimerFlag;
uint8_t LCDTimerFlag;
button_t btnMode, btnRun, btnOff, btnTimer;
uint16_t L_millisec, F_millisec;
uint8_t L_sec, F_sec;
uint8_t L_min, F_min;
uint8_t L_hour, F_hour;
uint16_t StopWatchData;

char buff[30];

enum{MANUAL,AUTO};
enum{Auto_FanPower1,Auto_FanPower2,Auto_FanPower3,Auto_OFF};
enum{Manual_FanPower1,Manual_FanPower2,Manual_FanPower3,Manual_OFF};
enum{No_Timer, One_Min, Three_Min, Five_Min};

void Digital_Fan_init();

void Fan_Manual_eventButton();

void Fan_Manual_Run();

void Manual_execute();

void Auto_excute();

void Fan_Auto_Modechange();

void Fan_Auto_Run();

void Digital_Fan_Execute();

void Digital_Fan_Execute_Timer();

void Digital_Fan_Execute_Stop();

void incMilisec();

void decMilisec();

	
#endif /* DIGITAL_FAN_H_ */