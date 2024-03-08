#include "Fan.h"

void Fan_init()
{
	DDRE |= (1<<3);
	//WGM 33323130 1110, TIME3, Fast PWM 14 Mode
	Fan_TCCRB |= (1<<Fan_WGM3) | (1<<Fan_WGM2);
	Fan_TCCRA |= (1<<Fan_WGM1	) | (0<<Fan_WGM0);
	//cs323130 011 Prescaler 1/64
	Fan_TCCRB |= (0<<Fan_CS2) | (1<<Fan_CS1) | (1<<Fan_CS0);
	//TOP 설정 ICR3,Frequency 1Khz
}
void Fan_makeHerz (uint16_t herz)
{	
	Fan_ICR = (250000 / herz) - 1;
	Fan_OCR = ICR3 / 2;
}

void Fan_On()
{
	// Out Pin , Non-Inverting Mode
	Fan_TCCRA |= (1<<Fan_COM1) | (0<<Fan_COM0);
}

void Fan_off()
{
	Fan_TCCRA &= ~((1<<Fan_COM1) | (1<<Fan_COM0));
}

//미풍
void Fan_Power1()
{
	Fan_On();
	Fan_makeHerz(1000);
}
//약풍
void Fan_Power2()
{
	Fan_On();
	Fan_makeHerz(2000);
}
//강풍
void Fan_Power3()
{
	Fan_On();
	Fan_makeHerz(3000);
}
//역회전
void Fan_Reverse()
{
		DDRE |= (1<<3);
		//WGM 33323130 1110, TIME3, Fast PWM 14 Mode
		Fan_TCCRB |= (1<<Fan_WGM3) | (1<<Fan_WGM2);
		Fan_TCCRA |= (1<<Fan_WGM1	) | (0<<Fan_WGM0);
		//cs323130 011 Prescaler 1/64
		Fan_TCCRB |= (0<<Fan_CS2) | (1<<Fan_CS1) | (1<<Fan_CS0);
		//TOP 설정 ICR3,Frequency 1Khz
}