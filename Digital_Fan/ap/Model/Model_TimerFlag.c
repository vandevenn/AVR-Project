#include "Model_TimerFlag.h"

uint8_t TimerFlagData;

uint8_t Model_getTimerFlagData()
{
	return TimerFlagData;
}

void Model_setTimerFlagData(uint8_t state)
{
	TimerFlagData = state;
}