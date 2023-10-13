/*
 * ADC.c
 *
 * Created: 9/12/2023 12:31:18 PM
 *  Author: Omar Zakaria
 */ 

/* =========================== Includes =========================== */
#include "ADC.h"
/* ===================== Generic Variables ======================== */

static void (*ADC_INT_CALLBACK)(void) = NULL;

/* ======================== Public APIs =========================== */

void MCAL_ADC_Init(ADC_t* CONF){
	ADMUX|= CONF->ADC_REF <<6;
	ADMUX|= CONF->ADC_ADJ <<5;
	ADCSRA|= (CONF->ADC_PRESCALE);
	if (CONF->ADC_AUTO_TRIGGER_EN)
	{
		SFIOR|=CONF->ADC_TRIGGER<<5;
	}
	if (CONF->ADC_INT_EN)
	{
		sei();
		ADC_INT_CALLBACK = CONF->ADC_INT_HANDLER;
		ADCSRA|= ((CONF->ADC_INT_EN)<<3);
	}
	ADCSRA|=(1<<ADEN);
	
}
void MCAL_ADC_Deinit(ADC_t *CONF){
	ADMUX = 0;
	ADCSRA =0;
}

void MCAL_ADC_StartConversion(ADC_CHANNEL_t Channel){
	ADMUX|= (Channel & 0x0F);
	ADCSRA |= (1<<ADSC);
}

uint16_t MCAL_ADC_GetResult(ADC_t *CONF){
	while(ADCSRA &(1<<ADIF)==0);
	ADCSRA|=(1<<ADIF);
	if (CONF->ADC_RESOLUTION == ADC_10BIT_MODE)
	{
		return ADC;
	}
	
	else if (CONF->ADC_ADJ == ADC_LEFT_ADJUSTMENT && CONF->ADC_RESOLUTION ==ADC_8BIT_MODE)
	{
		return ADCH;
	}
	else return ADC;
}


ISR(ADC_vect){
	ADC_INT_CALLBACK();
}