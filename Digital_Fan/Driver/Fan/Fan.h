#ifndef FAN_H_
#define FAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define Fan_ICR		ICR3
#define Fan_OCR		OCR3A
#define Fan_TCCRA	TCCR3A
#define Fan_TCCRB	TCCR3B
#define Fan_COM0	COM3A0
#define Fan_COM1	COM3A1
#define Fan_WGM3	WGM33
#define Fan_WGM2	WGM32
#define Fan_WGM1	WGM31
#define Fan_WGM0	WGM30
#define Fan_CS2		CS32
#define Fan_CS1		CS31
#define Fan_CS0		CS30

void Fan_init();
void Fan_makeHerz (uint16_t herz);
void Fan_On();
void Fan_off();
void Fan_Power1();
void Fan_Power2();
void Fan_Power3();
void Fan_Reverse();


#endif /* FAN_H_ */