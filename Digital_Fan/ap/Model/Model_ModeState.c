#include "Model_ModeState.h"

uint8_t ModeStateData;

uint8_t Model_getModeStateData()
{
	return ModeStateData;
}

void Model_setModeStateData(uint8_t state)
{
	ModeStateData = state;
}