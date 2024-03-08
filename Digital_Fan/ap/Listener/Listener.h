#ifndef LISTENER_H_
#define LISTENER_H_
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "../Service/Service_DEC_FND.h"
#include "../Service/Service_INC_LCD.h"
#include "../Model/Model_AutoState.h"
#include "../Model/Model_ManualState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerState.h"
#include "../Model/Model_LCDTimerFlag.h"
#include "../Model/Model_TimerFlag.h"
#include "../../driver/Button/Button.h"
#include "../../Periph/Uart0/Uart0.h"

void Listener_init();

void Listener_checkTimerEvent();

void Listener_checkModeEvent();

void Listener_checkManualEvent();

#endif /* LISTENER_H_ */