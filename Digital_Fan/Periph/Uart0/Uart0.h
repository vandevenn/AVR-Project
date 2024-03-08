#ifndef UART0_H_
#define UART0_H_


#include <avr/io.h>

void UART0_init();
void UART0_Transmit( unsigned char data );
unsigned char UART0_Receive( void );
void UART0_print(char *str);
uint8_t UART0_Avail();
void UART0_ISR_Process();
uint8_t UART0_readyRxFlag();
void UART0_clearRxFlag();
void UART0_setRxFlag();
uint8_t * UART0_readRxBuff();


#endif /* UART0_H_ */

