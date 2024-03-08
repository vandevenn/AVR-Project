#ifndef SERVICE_INC_LCD_H_
#define SERVICE_INC_LCD_H_

#include <avr/io.h>
#include "../Presenter/Presenter.h"
#include "../Model/Model_AutoState.h"
#include "../Model/Model_ManualState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerState.h"
#include "../Model/Model_LCDTimerFlag.h"
#include "../Model/Model_TimerFlag.h"

void LCDtime_init();

void IncMilisec();

void INC_LCD_run();


#endif /* SERVICE_INC_LCD_H_ */