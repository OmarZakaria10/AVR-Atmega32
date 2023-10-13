/* 
 * File:   hal_usart.c
 * 
 */

#include "USART.h"
#include "avr/interrupt.h"

	void (*RXCIE_InterruptHandler_Callback)(void);
	void (*TXCIE_InterruptHandler_Callback)(void);
	void (*UDRIE_InterruptHandler_Callback)(void);

void USART_Init(const USART_Config_t *usart_t) {
	if (usart_t->USART_RX_EN)
		UCSRB |= (1<<RXEN) ;
	
	if (usart_t->USART_TX_EN)
		UCSRB |= (1<<TXEN);
		
		
	UCSRC = 0x80 |(usart_t->USART_PARITY <<4) |(usart_t->USART_STOP <<3)
	|(usart_t->USART_DATA<<1);
	if (usart_t->USART_DATA == USART_9_DATA_BITS)
	{
		UCSRC |= (1<<URSEL);	
		UCSRC |= (1<<UCSZ0);
		UCSRC |= (1<<UCSZ1);
		UCSRB |= (1<<UCSZ2);
	}
	uint16 ubrr_value =0;
	ubrr_value = (uint16)(((F_CPU / (usart_t->USART_Baudrate * 16UL))) - 1);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
	
	if (usart_t->USART_RXCIE_INT_EN || usart_t->USART_TXCIE_INT_EN || usart_t->USART_UDRIE_INT_EN)
	{
		sei();
		
		if (usart_t->USART_RXCIE_INT_EN){
		
			RXCIE_InterruptHandler_Callback = usart_t->UART_RXCIE_InterruptHandler;
			UCSRB |= (1<<RXCIE);
		}
		
		if (usart_t->USART_TXCIE_INT_EN){
	
			TXCIE_InterruptHandler_Callback = usart_t->UART_TXCIE_InterruptHandler;
			UCSRB |= (1<<TXCIE);
		}
		if (usart_t->USART_UDRIE_INT_EN){
		
			UDRIE_InterruptHandler_Callback = usart_t->UART_UDRIE_InterruptHandler;
			UCSRB |= (1 << UDRIE);
		}
	}
}
void USART_DeInit(void)
{
	while(!READ_BIT(UCSRA,UDRE));
	
	UBRRL = 0x00;
	UCSRB &= ~(0x02);
	UCSRC = 0x86;
	UBRRH = 0x00;
}

void USART_SendByteBlocking(const uint8 *data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR = data;
}


uint8 USART_RecieveByteBlocking(void)
{
	while(!READ_BIT(UCSRA,RXC));
    return UDR;		
}


uint8 USART_RecieveNonByteBlocking(void){
	if(READ_BIT(UCSRA,RXC));
	return UDR;
}


ISR(USART_RXC_vect)
{
	RXCIE_InterruptHandler_Callback();
}

ISR(USART_TXC_vect)
{
	TXCIE_InterruptHandler_Callback();
}

ISR(USART_UDRE_vect)
{
	//UDR = 'f';
	UDRIE_InterruptHandler_Callback();
}