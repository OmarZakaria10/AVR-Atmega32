
#include "7_segment.h"

uint8_t volatile seg_common_anode_values[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t volatile seg_common_cathode_values[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_intialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGEMENT_PIN0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGEMENT_PIN1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGEMENT_PIN2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGEMENT_PIN3]));
    }
    return ret;
}

/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9)){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN0]), number & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN1]), (number>>1) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN2]), (number>>2) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN3]), (number>>3) & 0x01);
    }
    return ret;
}

/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_ND_intialize(const segment_ND_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_intialize(&(seg->segment_pins[0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[3]));
        ret = gpio_pin_intialize(&(seg->segment_pins[4]));
        ret = gpio_pin_intialize(&(seg->segment_pins[5]));
        ret = gpio_pin_intialize(&(seg->segment_pins[6]));
        ret = gpio_pin_intialize(&(seg->segment_pins[7]));        
    }
    return ret;
}
/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_ND_write_number(const segment_ND_t *seg, uint8 number)
{
        Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9)){
        ret = E_NOT_OK;
    }
    else{    
        if (seg->segment_type==SEGMENT_COMMON_ANODE)
        {
        ret = gpio_pin_write_logic(&(seg->segment_pins[0]), seg_common_anode_values[number] & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[1]), (seg_common_anode_values[number]>>1) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[2]), (seg_common_anode_values[number]>>2) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[3]), (seg_common_anode_values[number]>>3) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[4]), (seg_common_anode_values[number]>>4) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[5]), (seg_common_anode_values[number]>>5) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[6]), (seg_common_anode_values[number]>>6) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[7]), (seg_common_anode_values[number]>>7) & 0x01);
        }
        else if (seg->segment_type==SEGMENT_COMMON_CATHODE)
        {
        ret = gpio_pin_write_logic(&(seg->segment_pins[0]), seg_common_cathode_values[number] & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[1]), (seg_common_cathode_values[number]>>1) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[2]), (seg_common_cathode_values[number]>>2) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[3]), (seg_common_cathode_values[number]>>3) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[4]), (seg_common_cathode_values[number]>>4) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[5]), (seg_common_cathode_values[number]>>5) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[6]), (seg_common_cathode_values[number]>>6) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[7]), (seg_common_cathode_values[number]>>7) & 0x01);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_port_intialize(port_index_t port,segment_type_t type)
{
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER-1) || (port <0)){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_port_direction_intialize(port ,0xFF);
        if (SEGMENT_COMMON_ANODE == type)
        {
            gpio_port_write_logic(port,0XFF);
        }
        else gpio_port_write_logic(port,0x00);
        
    }
    return ret;
}
/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segement_port_write_number(port_index_t port, uint8 number,segment_type_t type)
{
    Std_ReturnType ret = E_OK;

        if (SEGMENT_COMMON_ANODE == type)
        {
            gpio_port_write_logic(port,seg_common_anode_values[number]);
        }
        else if (SEGMENT_COMMON_CATHODE ==type)
        {
            gpio_port_write_logic(port,seg_common_cathode_values[number]);
        }
        else
        {
            ret =E_NOT_OK;
        }
    
    return ret ;
}