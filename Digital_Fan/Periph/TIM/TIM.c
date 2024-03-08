#include "TIM.h"

void TIM0_init()
{
	TCCR0 |= (1<<CS02) | (0<<CS01) | (1<<CS00);   // /128 Prescaler
	TIMSK |= (1<<TOIE0);
	TCNT0 = 130;
}

void TIM2_init()
{	//CTC mode
	TCCR2 |= (0<<CS22) | (1<<CS21) | (1<<CS20);   // /64 Prescaler
	TCCR2 |= (1<<WGM21)	| (0<<WGM20);
	TIMSK |= (1<<OCIE2);
	OCR2 = 250-1; //TOP값, Period 1ms
}

