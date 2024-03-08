#include "Uart0.h"
uint8_t uart0RxBuff[100];
uint8_t uart0RxCFlag;

void UART0_init()
{
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Rxd, Txd
	UCSR0B |= (1<<RXCIE0);			// 1byte Receive Interrupt Enable
	UCSR0A |= (1<<U2X0);		//x2 Mode
	UBRR0L = 207;				//Baud Rate 9600 bps
	
	
}
void UART0_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
	
}

unsigned char UART0_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void UART0_print(char *str)
{
	for(int i =0; str[i]; i++)
	{
		UART0_Transmit(str[i]);
	}
}

uint8_t UART0_Avail()
{
	if(!( UCSR0A & (1<<UDRE0)))
	{
		return 0;
	}
	return 1;
}



void UART0_ISR_Process()
{
	static	uint8_t	uart0Rxtail = 0;
	uint8_t rx0Data = UDR0;
	if(rx0Data == '\n')
	{
		uart0RxBuff[uart0Rxtail] = rx0Data;
		uart0Rxtail++;
		uart0RxBuff[uart0Rxtail] = 0;
		uart0Rxtail = 0;
		 UART0_setRxFlag();
	}
	else
	{
		uart0RxBuff[uart0Rxtail] = rx0Data;
		uart0Rxtail++;
	}
}

uint8_t UART0_readyRxFlag()
{
	return uart0RxCFlag;
}

void UART0_clearRxFlag()
{
	uart0RxCFlag = 0;
}

void UART0_setRxFlag()
{
	uart0RxCFlag = 1;
}

uint8_t * UART0_readRxBuff()
{
	return uart0RxBuff;
}