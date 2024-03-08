#ifndef SERVICE_DEC_FND_H_
#define SERVICE_DEC_FND_H_
#include <avr/io.h>

#include "../Presenter/Presenter.h"
#include "../Model/Model_AutoState.h"
#include "../Model/Model_ManualState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerState.h"
#include "../Model/Model_LCDTimerFlag.h"
#include "../Model/Model_TimerFlag.h"
#include "../../Driver/FND/FND.h"

void FNDData_init();

void decmillisec();

void FNDDec_Run();

void setFNDData(uint8_t f_hour, uint8_t f_min,uint8_t f_sec, uint32_t f_millisec);

uint8_t getHour();

uint8_t getMin();

uint8_t getSec();

uint32_t getMillisec();

void Digital_Fan_Execute_Stop();

#endif /* SERVICE_DEC_FND_H_ */