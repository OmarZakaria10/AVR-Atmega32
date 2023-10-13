#ifndef RELAY_H
#define	RELAY_H

/* ----------------- Includes -----------------*/
#include "relay_cfg.h"
#include "../../MCAL/GPIO/GPIO.h"
/* ----------------- Macro Declarations -----------------*/
#define REALY_ON_STATUS  0x01U
#define REALY_OFF_STATUS 0x00U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType relay_initialize(const relay_t *_relay);
Std_ReturnType relay_turn_on(const relay_t *_relay);
Std_ReturnType relay_turn_off(const relay_t *_relay);

#endif