/*
 * SPI.h
 *
 * Created: 8/24/2023 4:05:50 PM
 *  Author: GTX
 */ 


#ifndef SPI_H_
#define SPI_H_

/* =========================== Includes =========================== */

#include "../GPIO/GPIO.h"
#include <avr/interrupt.h>

/* =============== Macros Configuration References ================ */

// @ref SPI_MODE_DEFINE
#define SPI_MODE_MASTER							1 	/* SPCR.Bit 4 – MSTR:?Master/Slave Select -> 1: Master configuration */
#define SPI_MODE_SLAVE							0

// @ref FRAME_FORMAT_DEFINE
#define FRAME_FORMAT_MSB_FIRST					0	/* SPCR.Bit 5 – DORD:?Data Order -> 0: MSB transmitted first */
#define FRAME_FORMAT_LSB_FIRST				    1

// @ref CLK_POLARITY_DEFINE
#define CLK_POLARITY_RISING_FALLING				0	/* SPCR.Bit 3 – CPOL:?Clock Polarity -> 0: Rising Falling */
#define CLK_POLARITY_FALLING_RISING				1  /*								        1: Falling Rising */

// @ref CLK_PHASE_DEFINE
#define CLK_PHASE_SAMPLE_SETUP					0		/* SPCR.Bit 2 – CPHA:?Clock Phase -> 0: Sample Setup */
#define CLK_PHASE_SETUP_SAMPLE				    1	

// @ref IRQ_ENABLE_DEFINE
#define IRQ_ENABLE_NONE							0		/* SPCRBit 7 – SPIE:?SPI Interrupt Enable -> 0: Disable */
#define IRQ_ENABLE								1	

// @ref BAUDERATE_PRESCALER_DEFINE

#define BAUDERATE_PRESCALER_2					(uint8) (100)
#define BAUDERATE_PRESCALER_4					(uint8) (000)
#define BAUDERATE_PRESCALER_8					(uint8) (101)
#define BAUDERATE_PRESCALER_16					(uint8) (001)
#define BAUDERATE_PRESCALER_32					(uint8) (110)
#define BAUDERATE_PRESCALER_64					(uint8) (111)
#define BAUDERATE_PRESCALER_128					(uint8) (011)

enum SPI_Polling_Mechanism
{
	SPI_disable,
	SPI_enable
};

/* ============= User type definitions (structures) =============== */

typedef struct
{
	uint8 	SPI_Mode :1;					// specifies SPI MODE Master/Slave
	// This parameter must be set based on @ref SPI_MODE_DEFINE

	uint8	 Data_Order :1;				// specifies Data MSB transmit first or LSB transmit first
	// This parameter must be set based on @ref FRAME_FORMAT_DEFINE

	uint8	CLK_Polarity :1;				// specifies SPI clock Polarity Rising Falling or Falling Rising
	// This parameter must be set based on @ref CLK_POLARITY_DEFINE

	uint8	CLK_Phase :1;					// specifies SPI clock Phase Sample Setup or Setup Sample
	// This parameter must be set based on @ref CLK_PHASE_DEFINE
	
	uint8	BaudRate_Prescaler ;		    // specifiesRelationship between SCK and Oscillator Frequency
	// This parameter must be set based on @ref BAUDERATE_PRESCALER_DEFINE

	uint8	IRQ_Enable:1;					// specifies SPI IRQ
	// This parameter must be set based on @ref IRQ_ENABLE_DEFINE

	void (*P_IRQ_CallBack)(void);		//set the C Function which will be called once IRQ Happens

}SPI_Config_t;

/* =========== APIs Supported by "MCAL SPI DRIVER" ================ */

void MCAL_SPI_Init(SPI_Config_t *Config);
void MCAL_SPI_DeInit(void);

void MCAL_SPI_GPIO_Set_Pins(SPI_Config_t *Config);

void MCAL_SPI_Send_Data(uint8 *pTxBuffer, enum SPI_Polling_Mechanism Polling_En);
void MCAL_SPI_Recieve_Data(uint8 *pRxBuffer, enum SPI_Polling_Mechanism Polling_En);

void MCAL_SPI_TX_RX(uint8 *pTxBuffer, enum SPI_Polling_Mechanism Polling_En);



#endif /* SPI_H_ */