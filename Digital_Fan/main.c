#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ap/APmain.h"

int main(void)
{
   APMain_init();
    while (1) 
    {
		APMain_execute();
    }
}

