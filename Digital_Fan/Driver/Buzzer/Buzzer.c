#include "Buzzer.h"

void Buzzer_init(){
	DDRB |= (1<<5);
	
	//TIM3, Fast PWM Mode, Top ICR3, DutyCycle OCR3A,
	//Prescaler 1/64, Non_Invert Mode, Frequency 1KHz
	//DutyCycle 50%
	
	//WGN33323130 1110, TIM3 Fast PWM 14 Mode
	BUZZER_TCCRB |= (1<<BUZZER_WGM3) | (1<<BUZZER_WGM2);
	BUZZER_TCCRA |= (1<<BUZZER_WGM1) | (0<<BUZZER_WGM0);
	//TCCR3A 값이 0으로 초기화 되어 있어서 WRM30에서 OR연산을 해도 0으로 출력된다.
	
	//cs323130 Prescaler 1/64
	BUZZER_TCCRB |= (0<<BUZZER_CS2) | (1<<BUZZER_CS1) | (1<<BUZZER_CS0);
}

void Buzzer_makeHerz(uint16_t herz){
	//100 ~ 4000hz
	if(herz > 4000) herz = 4000;
	else if(herz < 100) herz = 100;
	BUZZER_ICR = (250000/ herz) - 1;//1hz를 가지고 값을 맞춘다
	BUZZER_OCR = BUZZER_ICR / 2;
}

void Buzzer_soundON(){//Non-inverting Mode
	BUZZER_TCCRA |= (1<<BUZZER_COM1) | (0<<BUZZER_COM0);
};

void Buzzer_soundOff(){
	BUZZER_TCCRA &= ~(1<<BUZZER_COM1) | (1<<BUZZER_COM0);
};

void Buzzer_powerOnSound(){
	Buzzer_soundON();
	Buzzer_makeHerz(1046);//6옥타브 도
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(1318);//6옥타브 미
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(1568);//6옥타브 솔
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(2093);//7옥타브 도
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_soundOff();
}

void Buzzer_powerOFFSound(){
	Buzzer_soundON();
	Buzzer_makeHerz(2093);//7옥타브 도
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(1568);//6옥타브 솔
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(1318);//6옥타브 미
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_makeHerz(1046);//6옥타브 도
	_delay_ms(100);
	BUZZER_TCNT = 0 ;
	Buzzer_soundOff();
}