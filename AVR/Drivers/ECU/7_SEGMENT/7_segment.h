
#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "7_segment_cfg.h"

/* Section: Macro Declarations */
#define SEGEMENT_PIN0 0
#define SEGEMENT_PIN1 1
#define SEGEMENT_PIN2 2
#define SEGEMENT_PIN3 3

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */


typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;


typedef struct{
    pin_config_t segment_pins[8];
    segment_type_t segment_type;
}segment_ND_t;

/* Section: Function Declarations */
Std_ReturnType seven_segement_intialize(const segment_t *seg);
Std_ReturnType seven_segement_write_number(const segment_t *seg, uint8 number);
Std_ReturnType seven_segement_ND_intialize(const segment_ND_t *seg);
Std_ReturnType seven_segement_ND_write_number(const segment_ND_t *seg, uint8 number);
Std_ReturnType seven_segement_port_intialize(port_index_t port,segment_type_t type);
Std_ReturnType seven_segement_port_write_number(port_index_t port, uint8 number,segment_type_t type);

#endif	/* ECU_SEVEN_SEGMENT_H */
