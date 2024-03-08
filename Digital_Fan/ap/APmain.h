#ifndef APMAIN_H_
#define APMAIN_H_
#include <avr/io.h>	
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "Model/Model_AutoState.h"
#include "Model/Model_ManualState.h"
#include "Model/Model_ModeState.h"
#include "Model/Model_TimerState.h"
#include "Model/Model_LCDTimerFlag.h"
#include "Model/Model_TimerFlag.h"
#include "Listener/Listener.h"
#include "Service/Service_DEC_FND.h"
#include "Service/Service_INC_LCD.h"
#include "Service/Service_AutoCount.h"
#include "Presenter/Presenter.h"
#include "../Periph/TIM/TIM.h"
#include "../Periph/Uart0/Uart0.h"
#include "../Periph/GPIO/GPIO.h"
#include "../Periph/I2C/I2C.h"

void APMain_init();

void APMain_execute();

#endif /* APMAIN_H_ */