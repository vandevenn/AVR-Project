#include "Model_LCDTimerFlag.h"

uint8_t LCDTimerFlagData;

uint8_t Model_getLCDTimerFlagData()
{
	return LCDTimerFlagData;
}

void Model_setLCDTimerFlagData(uint8_t state)
{
	LCDTimerFlagData = state;
}