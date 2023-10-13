/*
 * TIMER0.h
 *
 * Created: 9/9/2023 10:27:01 AM
 *  Author: Omar Zakaria
 */ 

/* =========================== Includes =========================== */
#include "TIMER0.h"
/* ===================== Generic Variables ======================== */

static void (*TIMER0_OVF_CALLBACK)(void) = NULL;
static void (*TIMER0_OCR_CALLBACK)(void) = NULL;

static uint8_t OVF_COUNT;
/* ======================== Public APIs =========================== */

void MCAL_TIMER0_Init(TIMER0_t* CONF){
	TCCR0 |= CONF->MODE;
	if (TIMER0_MODE_FAST_PWM_NONINVERTING == CONF->MODE || TIMER0_MODE_FAST_PWM_INVERTING == CONF->MODE)
	{
		pin_config_t T0_O={PORTB_INDEX,GPIO_PIN3,GPIO_DIRECTION_OUTPUT,GPIO_LOW};
		gpio_pin_intialize(&T0_O);
	}
	TCCR0|= CONF->CLOCK_SOURCE;
	
		if(CONF->CLOCK_SOURCE == TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING_EDGE || CONF->CLOCK_SOURCE == TIMER0_CLOCK_SOURCE_EXTERNAL_RISING_EDGE)
		{
			pin_config_t T0_I={PORTB_INDEX,GPIO_PIN0,GPIO_DIRECTION_INPUT,GPIO_LOW};
			gpio_pin_intialize(&T0_I);
		}
	if (1==CONF->OCR_INT){
		TIMSK|= (1<<OCIE0);
		sei();
		TIMER0_OCR_CALLBACK = CONF->OCR_INT_HANDLER;
	}
	if (1== CONF->OVF_INT){
		TIMSK|= (1<<TOIE0);
		sei();
		TIMER0_OVF_CALLBACK= CONF->OVF_INT_HANDLER;
	}
		
}

void MCAL_TIMER0_DeInit(){
	TCCR0 &= ~((1<<0)|(1<<1)|(1<<2));
}

void MCAL_TIMER0_Stop(){
	TIMSK |= TIMER0_NO_CLOCK_SOURCE;
}

uint8_t * MCAL_TIMER0_GetCompareValue(){
	return OCR0;
}

void MCAL_TIMER0_SetCompareValue(uint8_t u8_TicksNumber){
	OCR0 = u8_TicksNumber;
}

uint8_t * MCAL_TIMER0_GetCounterValue(){
	return TCNT0;
}
void MCAL_TIMER0_SetCounterValue(uint8_t u8_TicksNumber){
	TCNT0 = u8_TicksNumber;
}

uint8_t * MCAL_TIMER0_GetOverflowValue(){
	return OVF_COUNT;
}
void MCAL_TIMER0_SetOverflowValue(uint8_t u8_TicksNumber){
	OVF_COUNT = u8_TicksNumber;
}

void MCAL_TIMER0_DutyCycle(TIMER0_t* CONF,uint8_t Duty_Cycle){
	Duty_Cycle = Duty_Cycle/100.0 *255.0;
		if(CONF->MODE == TIMER0_MODE_FAST_PWM_NONINVERTING)
		{
			OCR0 = Duty_Cycle;
		}
		else if(CONF->MODE == TIMER0_MODE_FAST_PWM_INVERTING)
		{
			OCR0 = (uint8)(255 - Duty_Cycle);
		}
}

ISR(TIMER0_COMP_vect)
{
	TIMER0_OCR_CALLBACK();
}

ISR(TIMER0_OVF_vect)
{
	OVF_COUNT++;
	TIMER0_OVF_CALLBACK();
}