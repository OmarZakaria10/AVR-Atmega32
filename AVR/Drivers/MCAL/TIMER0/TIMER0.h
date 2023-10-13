/*
 * TIMER0.h
 *
 * Created: 9/9/2023 10:27:01 AM
 *  Author: Omar Zakaria
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

/* =========================== Includes =========================== */
#include "../GPIO/GPIO.h"
#include <avr/interrupt.h>

/* =============== Macros Configuration References ================ */

//@ref TIMER0_MODE_DEFINE
#define TIMER0_MODE_NORMAL									((uint8)(0))
#define TIMER0_MODE_CTC										((uint8)(1<<3))
#define TIMER0_MODE_FAST_PWM_INVERTING						((uint8)(0x78))
#define TIMER0_MODE_FAST_PWM_NONINVERTING					((uint8)(0x68))

typedef enum {
	TIMER0_NO_CLOCK_SOURCE,
	TIMER0_CLOCK_SOURCE_INTERNAL_NO_PRESCALER,
	TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_8,
	TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_64,
	TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_256,
	TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_1024,
	TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING_EDGE,
	TIMER0_CLOCK_SOURCE_EXTERNAL_RISING_EDGE
	
	}TIMER0_CLOCK_SOURCE_t;
	
	
/* ============= User type definitions (structures) =============== */
typedef struct
{
	uint8_t MODE;
	TIMER0_CLOCK_SOURCE_t CLOCK_SOURCE;
	uint8_t OVF_INT;
	uint8_t OCR_INT;
	void (* OVF_INT_HANDLER)(void);
	void (* OCR_INT_HANDLER)(void);
	
	}TIMER0_t;

/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */
void MCAL_TIMER0_Init(TIMER0_t* CONF);
void MCAL_TIMER0_DeInit();
void MCAL_TIMER0_Stop();

uint8_t * MCAL_TIMER0_GetCompareValue();
void MCAL_TIMER0_SetCompareValue(uint8_t u8_TicksNumber);

uint8_t * MCAL_TIMER0_GetCounterValue();
void MCAL_TIMER0_SetCounterValue(uint8_t u8_TicksNumber);

uint8_t * MCAL_TIMER0_GetOverflowValue();
void MCAL_TIMER0_SetOverflowValue(uint8_t u8_TicksNumber);

void MCAL_TIMER0_DutyCycle(TIMER0_t* CONF,uint8_t Duty_Cycle);

#endif /* TIMER0_H_ */