#ifndef MODEL_MODESTATE_H_
#define MODEL_MODESTATE_H_
#include <avr/io.h>

enum{MANUAL,AUTO};
	
uint8_t Model_getModeStateData();

void Model_setModeStateData(uint8_t state);

#endif /* MODEL_MODESTATE_H_ */