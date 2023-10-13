/*
 * I2C.c
 *
 * Created: 8/30/2023 12:49:34 PM
 *  Author: GTX
 */ 
#include "I2C.h"
#include <util/delay.h>
//(((F_CPU/SCL_Clock)-16)/(2*prescaler)) TWBR
static void (*I2C_INTERRUPT_HANDLER )(void)= NULL;

void I2C_Generate_Start(START_Condition Start){

		// Transmit START condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

		// Wait for START condition to be transmitted
		//while (!(TWCR & (1 << TWINT)));
		if (Start == Repeated_START)
		while(!I2C_Get_FlagStatus(REP_START_SENT));
		else
		while(!I2C_Get_FlagStatus(START_SENT));
}

void I2C_Generate_Stop(){
	
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2CWrite(uint8_t *pTxData) {
	int i =0 ;
	
		//for (i = 0; i < Data_Length;i++)
		//{
			/* 6. Write in the DR register the data to be sent */
			TWDR = pTxData;

				TWCR = (1 << TWINT) | (1 << TWEN);

				// Wait for data transmission to complete
				while (!(TWCR & (1 << TWINT)));
				

			/* 8. Wait for EV8 */
			/* EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition. */
		

//}
}

void I2CRead(uint8 ack,uint8_t *pTxData) {
	// Enable or disable acknowledging of received data
	int i =0 ;
	if (ack)
	TWCR |= (1 << TWEA);
	else
	TWCR &= ~(1 << TWEA);


	// Start data reception
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for data reception to complete
	while (!(TWCR & (1 << TWINT)));

	// Return received data
	pTxData=TWDR;
}


void I2C_Send_Address(uint8_t Device_Address,I2C_Direction Direction){
	uint8_t temp = ((Device_Address<<1) |Direction);
	I2CWrite(temp);
	
}

void MCAL_I2C_MASTER_TX( uint8_t Device_Address, uint8_t *pTxData, uint8_t Data_Length, STOP_Condition Stop, START_Condition Start){
	I2C_Generate_Start(Start);
	I2C_Send_Address(Device_Address,Transmitter);
	while(!I2C_Get_FlagStatus(MT_SLA_ACK));
	I2CWrite(pTxData);
	while(!I2C_Get_FlagStatus(MT_DATA_ACK));
	if (Stop == With_STOP)
	{
		I2C_Generate_Stop(Stop);
	}
	
	
}
void MCAL_I2C_MASTER_RX( uint8_t Device_Address, uint8_t *pRxData, uint8_t Data_Length, STOP_Condition Stop, START_Condition Start){
	I2C_Generate_Start(Start);
	I2C_Send_Address(Device_Address,Receiver);
	I2CRead(1,pRxData);
	I2C_Generate_Stop(Stop);
}




void MCAL_I2C_Init(I2C_Config_t *I2C_Config){
		// Set I2C clock frequency
		TWBR = ((F_CPU / I2C_Config->I2C_BUS_FREQUENCY) - 16) / 2;
		TWSR |= I2C_Config->I2C_PRESCALER & (uint8_t)0x3;
		TWAR = I2C_Config->I2C_SLAVE_ADDRESS<<1;
		if (I2C_Config->I2C_GEN_CALL == I2C_GEN_CALL_EN)
			TWAR |= (1<<TWGCE);
			
		if (I2C_Config->I2C_INT == I2C_INT_EN)
			{
				I2C_INTERRUPT_HANDLER = I2C_Config->I2C_INT_Handler;
				SET_BIT(TWCR,TWIE);
				sei();
			}
		// Enable I2C
		TWCR = (1 << TWEN);
		

}

void MCAL_I2C_DeInit(void){
	TWCR =0;
	TWSR =0;
	TWBR =0;
	TWAR =0;
}
I2C_Flagstatus I2C_Get_FlagStatus( uint8_t Flag){
	I2C_Flagstatus Bit_Status = RESET;

	if (Flag == (TWSR&0xF8))
	{
		Bit_Status=SET;
	}
		
		return Bit_Status;
		
	}

uint8_t I2C_FlagStatus( ){
	 
	return(TWSR&0xF8);
	

}




uint8_t MCAL_I2C_Slave_RX(){
//using interrupt
	static uint8_t data;

	switch (I2C_FlagStatus()) {
		case TW_SR_SLA_ACK:
		// Slave address received with acknowledgment
		break;

		case TW_SR_DATA_ACK:
		// Data received with acknowledgment
		data = TWDR;

		// Process received data
		// ...

		break;

		case TW_ST_SLA_ACK:
		// Slave address received in write mode with acknowledgment
		break;

		case TW_ST_DATA_ACK:
		// Data requested by master with acknowledgment
		TWDR = data;

		// Send data
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

		break;

		case TW_ST_DATA_NACK:
		case TW_SR_DATA_NACK:
		case TW_SR_STOP:
		default:
		// Error handling or other cases
		break;
	}

	// Clear interrupt flag
	TWCR |= (1 << TWINT);
	
}


ISR(TWI_vect) {
	I2C_INTERRUPT_HANDLER();
}

















