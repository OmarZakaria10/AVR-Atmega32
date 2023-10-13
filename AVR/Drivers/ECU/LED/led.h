/* 
 * File:   ecu_led.h
 * Author: Omar Zakaria
 * 
 * 
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "led_cfg.h"

#include "../../MCAL/GPIO/GPIO.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name : 2;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;

/* Section: Function Declarations */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

