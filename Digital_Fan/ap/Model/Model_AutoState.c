#include "Model_AutoState.h"

uint8_t AutoStateData;

uint8_t Model_getAutoStateData()
{
	return AutoStateData;
}

void Model_setAutoStateData(uint8_t state)
{
	AutoStateData = state;
}