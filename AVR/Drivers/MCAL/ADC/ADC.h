/*
 * ADC.h
 *
 * Created: 9/12/2023 12:31:42 PM
 *  Author: Omar Zakaria
 */ 


#ifndef ADC_H_
#define ADC_H_
/* =========================== Includes =========================== */
#include "../GPIO/GPIO.h"
#include <avr/interrupt.h>

/* =============== Macros Configuration References ================ */

#define ADC_LEFT_ADJUSTMENT					1
#define ADC_RIGHT_ADJUSTMENT				0



#define ADC_10BIT_MODE						1
#define ADC_8BIT_MODE						0


/* ----------------- Data Type Declarations -----------------*/
typedef enum{
	AREF,	
	AVCC,
	RESERVED,
	INTERNAL_2_56
	}ADC_REFERENCE_t;

typedef enum{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC5,
	ADC6,
	ADC7
	
	}ADC_CHANNEL_t;
	
typedef enum{
	ADC_PRESCALE_2 = 1,
	ADC_PRESCALE_4,
	ADC_PRESCALE_8,
	ADC_PRESCALE_16,
	ADC_PRESCALE_32,
	ADC_PRESCALE_64,
	ADC_PRESCALE_128
	
	}ADC_PRESCALE_t;
	
typedef enum{
	ADC_FREE_RUNNING,
	ADC_ANALOG_COMP,
	ADC_EXT_INT0,
	ADC_COMP_MATCH_TMR0,
	ADC_OVERFLOW_TMR0,
	ADC_COMP_MATCH_TMR1B,
	ADC_OVERFLOW_TMR1,
	ADC_TMR1_CAP_EVENT
	}ADC_TRIGGER_t;


typedef struct{
	uint8_t ADC_REF;
	//uint8_t ADC_CHANNEL;
	uint8_t ADC_AUTO_TRIGGER_EN;
	uint8_t ADC_RESOLUTION;
	uint8_t ADC_ADJ;
	uint8_t ADC_INT_EN;
	uint8_t ADC_PRESCALE;
	uint8_t ADC_TRIGGER;
	void (*ADC_INT_HANDLER) (void);
 	}ADC_t;

/* =========== APIs Supported by "MCAL ADC DRIVER" ============= */
void MCAL_ADC_Init(ADC_t *CONF);
void MCAL_ADC_Deinit(ADC_t *CONF);
void MCAL_ADC_StartConversion(ADC_CHANNEL_t Channel);
uint16_t MCAL_ADC_GetResult(ADC_t *CONF);



#endif /* ADC_H_ */