#include "Model_TimerState.h"

uint8_t TimerStateData;

uint8_t Model_getTimerStateData()
{
	return TimerStateData;
}

void Model_setTimerStateData(uint8_t state)
{
	TimerStateData = state;
}