/*
 * EXTI.c
 *
 * Created: 10/13/2023 9:31:16 PM
 *  Author: GTX
 */ 
#include "EXTI.h"

static void(* EXTIX_CALLBACK[3])(void) ;	


void MCAL_EXTI_Init(EXTI_t * CONF){
	EXTIX_CALLBACK[CONF->EXTIX] = CONF->P_IRQ_CallBack;
	switch (CONF->EXTIX){
		case 0:
		GICR|= (1<<INT0);
		break;
		case 1:
		GICR|= (1<<INT1);
		break;
		case 2:
		GICR|= (1<<INT2);
		break;
		default:
		break;
	}
	if(CONF->EXTIX != 2)
	MCUCR |= (CONF->TRIGGER)<<((CONF->EXTIX)*2);
	sei();
	
}

ISR(INT0_vect){
	EXTIX_CALLBACK[0]();
}
ISR(INT1_vect){
	EXTIX_CALLBACK[1]();
}
ISR(INT2_vect){
	EXTIX_CALLBACK[2]();
}