#include "Model_ManualState.h"

uint8_t ManualStateData;

uint8_t Model_getManualStateData()
{
	return ManualStateData;
}

void Model_setManualStateData(uint8_t state)
{
	ManualStateData = state;
}