/*
 * SPI.c
 *
 * Created: 8/24/2023 4:05:37 PM
 *  Author: GTX
 */ 
/* =========================== Includes =========================== */
#include "SPI.h"

/* ===================== Generic Variables ======================== */
static void (*SPI_InterruptHandler)(void) = NULL;
/* ======================== Public APIs =========================== *

/* ================================================================
 * @Fn 				- MCAL_SPI_Init
 * @brief 			- Initializes SPI according to the specified parameters in SPI_Config_t
 * @param [in] 		- Config : a pointer to SPI_Config_t structure that contains the configuration information for the specified SPI Module
 * @retval 			- None
 * Note 			- None
 * 					- None
 */
void MCAL_SPI_Init(SPI_Config_t *Config){
	
	if (Config ->IRQ_Enable)
	SPI_InterruptHandler = Config->P_IRQ_CallBack;
	uint8 temp=0;
	temp |= (Config->SPI_Mode << 4) |(Config->Data_Order << 5);
	temp |= (Config->CLK_Phase <<2) |(Config->CLK_Polarity <<3);
	temp |= (Config->BaudRate_Prescaler & 0x3) ;
	SPSR |= (Config ->BaudRate_Prescaler &0X4 >>2);
	temp |= (1<<6) | (Config->IRQ_Enable <<7); //enable SPI / 
	SPCR= temp;
}

/* ================================================================
 * @Fn 				- MCAL_SPI_DeInit
 * @brief 			- Resets Selected SPI Module
 * @retval 			- none
 * Note 			- Reset The Module & Disable Global Interrupt
 */
void MCAL_SPI_DeInit(void)
{
	/* Put all writeable regiter in reset mode */
	SPCR= 0x00;
	CLEAR_BIT (SPSR , SPI2X);
}

/* ================================================================
 * @Fn 				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected SPI
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_Config_t *Config)
{
	/*
	 * Port Pin Alternate Functions
	 *   PB7      SCK (SPI Bus Serial Clock)
	 *   PB6      MISO (SPI Bus Master Input/Slave Output)
	 *   PB5      MOSI (SPI Bus Master Output/Slave Input)
	 *   PB4      SS (SPI Slave Select Input) 
	 */
	pin_config_t SPI_GPIO_Config;
	
	/* Master */
	if (Config->SPI_Mode == SPI_MODE_MASTER)
	{
		/* PB7      SCK: Master Clock output */
		SPI_GPIO_Config.pin = GPIO_PIN7;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_OUTPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB6      MISO: Master Data input */
		SPI_GPIO_Config.pin = GPIO_PIN6;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_INPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB5      MOSI: SPI Master Data output */
		SPI_GPIO_Config.pin = GPIO_PIN5;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_OUTPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB4      SS: SPI Master Data Output */
		SPI_GPIO_Config.pin = GPIO_PIN4;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_OUTPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
	}
	/* Slave */
	else 
	{
		/* PB7      SCK:  Slave Clock input pin */
		SPI_GPIO_Config.pin = GPIO_PIN7;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_INPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB6      MISO: Slave Data output pin */
		SPI_GPIO_Config.pin = GPIO_PIN6;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_OUTPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB5      MOSI: Slave Data input */
		SPI_GPIO_Config.pin = GPIO_PIN5;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_INPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
		
		/* PB4      SS: SPI Slave Select input */
		SPI_GPIO_Config.pin = GPIO_PIN4;
		SPI_GPIO_Config.direction = GPIO_DIRECTION_INPUT;
		SPI_GPIO_Config.port = PORTB_INDEX;
		gpio_pin_intialize( &SPI_GPIO_Config);
	}
	
}
/* ================================================================
 * @Fn 				- MCAL_SPI_Send_Data
 * @brief 			- Send Buffer With SPI
 * @param [in] 		- pTxBuffer : Pointer to buffer Which holds the Tx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_SPI_Send_Data(uint8 *pTxBuffer, enum SPI_Polling_Mechanism Polling_En)
{
	/* Start transmission, Write data to SPI data register */
	SPDR = *pTxBuffer;
	
	/* Wait for transmission complete */
	if (Polling_En == SPI_enable)
	{
		while ( !(READ_BIT(SPSR , SPIF)));
	}
}

/* ================================================================
 * @Fn 				- MCAL_SPI_Recieve_Data
 * @brief 			- Receive Buffer With SPI
 * @param [in] 		- pRxBuffer : Pointer to buffer which holds Rx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_Recieve_Data(uint8 *pRxBuffer, enum SPI_Polling_Mechanism Polling_En)
{
	/* Wait for reception complete */
	if (Polling_En == SPI_enable)
	{
		while (!(READ_BIT(SPSR , SPIF)));
	}
	
	/* Start reception, Write data to SPI data register */
	*pRxBuffer = SPDR;
}

/* ================================================================
 * @Fn 				- MCAL_SPI_TX_RX
 * @brief 			- Transmit and Receive Data
 * @param [in] 		- pTxBuffer : Pointer to buffer which holds Transmit and Received data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_TX_RX(uint8 *pTxBuffer, enum SPI_Polling_Mechanism Polling_En)
{
	/* Start transmission, Write data to SPI data register */
	SPDR = *pTxBuffer;
	
	/* Wait for transmission complete */
	if (Polling_En == SPI_enable)
	{
		while (!(READ_BIT(SPSR , SPIF)));
	}
	
	/* =================================================== */
	
	/* Wait for reception complete */
	if (Polling_En == SPI_enable)
	{
		while (!(READ_BIT(SPSR , SPIF)));
	}
	
	/* Start reception, Write data to SPI data register */
	*pTxBuffer = SPDR;
}