/*
 * USART.c
 *
 * Created: 8/19/2023 4:25:00 AM
 *  Author: RTX
 */ 

#ifndef HAL_USART_H
#define	HAL_USART_H

/* ----------------- Includes -----------------*/
#include "../GPIO/GPIO.h"
#include <avr/interrupt.h>

/* ----------------- Macro Declarations -----------------*/

#define USART_BAUD_RATE_2400			2400
#define USART_BAUD_RATE_4800			4800
#define USART_BAUD_RATE_9600			9600
#define USART_BAUD_RATE_14400			14400
#define USART_BAUD_RATE_19200			19200
#define USART_BAUD_RATE_28800			28800
#define USART_BAUD_RATE_38400			38400
#define USART_BAUD_RATE_57600			57600
#define USART_BAUD_RATE_76800			76800
#define USART_BAUD_RATE_115200			115200
#define USART_BAUD_RATE_230400			230400
#define USART_BAUD_RATE_250000			250000

/* ----------------- Data Type Declarations -----------------*/

typedef enum{
	USART_5_DATA_BITS,
	USART_6_DATA_BITS,
	USART_7_DATA_BITS,
	USART_8_DATA_BITS,
	USART_9_DATA_BITS
	}USART_N_BITS_t;

typedef enum {
	USART_NO_PARITY,
	RESERVED,
	USART_EVEN_PARITY,
	USART_ODD_PARITY
	}USART_PARITY_t;
	
typedef enum{
	USART_1_STOP_BIT,
	USART_2_STOP_BIT
}USART_STOP_BITS_t;
	
typedef struct{
	uint32 USART_Baudrate;
	uint8 USART_TX_EN : 1;
	uint8 USART_RX_EN : 1;
	uint8 USART_RXCIE_INT_EN : 1;
	uint8 USART_TXCIE_INT_EN : 1;
	uint8 USART_UDRIE_INT_EN : 1;
	USART_N_BITS_t USART_DATA:2;
	USART_PARITY_t USART_PARITY:2;
	USART_STOP_BITS_t USART_STOP:1;
	void (*UART_RXCIE_InterruptHandler)(void);
	void (*UART_TXCIE_InterruptHandler)(void);
	void (*UART_UDRIE_InterruptHandler)(void);

}USART_Config_t;

/* ----------------- Software Interfaces Declarations -----------------*/
void USART_Init(const USART_Config_t *usart_t);
void USART_DeInit(void);
void USART_SendByteBlocking(const uint8_t *data);
uint8 USART_RecieveByteBlocking(void);
uint8 USART_RecieveNonByteBlocking(void);

#endif