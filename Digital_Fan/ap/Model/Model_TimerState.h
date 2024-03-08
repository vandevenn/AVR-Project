#ifndef MODEL_TIMERSTATE_H_
#define MODEL_TIMERSTATE_H_
#include <avr/io.h>

enum{No_Timer, One_Min, Three_Min, Five_Min};

uint8_t Model_getTimerStateData();

void Model_setTimerStateData(uint8_t state);

#endif /* MODEL_TIMERSTATE_H_ */