
#ifndef SERVICE_AUTOCOUNT_H_
#define SERVICE_AUTOCOUNT_H_
#include <avr/io.h>
#include "../Presenter/Presenter.h"
#include "../Model/Model_AutoState.h"
#include "../Model/Model_ManualState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerState.h"
#include "../Model/Model_LCDTimerFlag.h"
#include "../Model/Model_TimerFlag.h"

void Auto_excute();

void Fan_Auto_Modechange();

#endif /* SERVICE_AUTOCOUNT_H_ */