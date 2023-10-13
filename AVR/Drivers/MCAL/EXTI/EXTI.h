/*
 * EXTI.h
 *
 * Created: 10/13/2023 9:29:11 PM
 *  Author: Omar Zakaria
 */ 



#ifndef EXTI_H_
#define EXTI_H_

/* =========================== Includes =========================== */
#include <avr/interrupt.h>



/* =============== Macros Configuration References ================ */
#define		EXTI0						0
#define		EXTI1						1
#define		EXTI2						2

/* ============= User type definitions  =============== */

typedef enum {
	EXTI_LOW_LEVEL,
	EXTI_ANY_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE
	}EXTI_Trigger_t;

typedef struct {
	
	uint8_t EXTIX ;
	EXTI_Trigger_t TRIGGER ;
	void(* P_IRQ_CallBack)(void) ;	
	}EXTI_t;

/* =========== APIs ================ */

void MCAL_EXTI_Init(EXTI_t * CONF);



#endif /* EXTI_H_ */