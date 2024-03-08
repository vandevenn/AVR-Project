#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_ICR ICR1
#define BUZZER_OCR OCR1A
#define BUZZER_TCNT TCNT1
#define BUZZER_TCCRA TCCR1A
#define BUZZER_TCCRB TCCR1B
#define BUZZER_COM0 COM1A0
#define BUZZER_COM1 COM1A1
#define BUZZER_WGM0 WGM10
#define BUZZER_WGM1 WGM11
#define BUZZER_WGM2 WGM12
#define BUZZER_WGM3 WGM13
#define BUZZER_CS0  CS10
#define BUZZER_CS1  CS11
#define BUZZER_CS2  CS12

void Buzzer_init();
void Buzzer_makeHerz(uint16_t herz);
void Buzzer_soundON();
void Buzzer_soundOff();
void Buzzer_powerOnSound();
void Buzzer_powerOFFSound();

#endif /* BUZZER_H_ */