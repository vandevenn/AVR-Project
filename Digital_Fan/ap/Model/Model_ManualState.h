#ifndef MODEL_MANUALSTATE_H_
#define MODEL_MANUALSTATE_H_
#include <avr/io.h>

enum{Manual_FanPower1,Manual_FanPower2,Manual_FanPower3,Manual_OFF};

uint8_t Model_getManualStateData();

void Model_setManualStateData(uint8_t state);

#endif /* MODEL_MANUALSTATE_H_ */