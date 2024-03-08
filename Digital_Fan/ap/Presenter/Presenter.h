#ifndef PRESENTER_H_
#define PRESENTER_H_
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "../../Driver/FND/FND.h"
#include "../../Driver/I2C_LCD/I2C_LCD.h"
#include "../../Driver/Buzzer/Buzzer.h"
#include "../../Driver/Fan/Fan.h"
#include "../Model/Model_AutoState.h"
#include "../Model/Model_ManualState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerState.h"
#include "../Model/Model_LCDTimerFlag.h"
#include "../Model/Model_TimerFlag.h"
#include "../../Periph/Uart0/Uart0.h"

char buff[30];
uint16_t StopWatchData;

void Presenter_init();
void Presenter_disLCDData(uint8_t L_hour,uint8_t L_min,uint8_t L_sec,uint32_t L_millisec);
void Presenter_disFNDData(uint8_t F_hour,uint8_t F_min,uint8_t F_sec,uint32_t F_millisec);
void Presenter_soundBuzzer();
void Presenter_runFan();
void Presenter_disUART();

#endif /* PRESENTER_H_ */

