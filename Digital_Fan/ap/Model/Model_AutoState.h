#ifndef MODEL_AUTOSTATE_H_
#define MODEL_AUTOSTATE_H_
#include <avr/io.h>

enum{Auto_FanPower1,Auto_FanPower2,Auto_FanPower3,Auto_OFF};

uint8_t Model_getAutoStateData();

void Model_setAutoStateData(uint8_t state);

#endif /* MODEL_AUTOSTATE_H_ */