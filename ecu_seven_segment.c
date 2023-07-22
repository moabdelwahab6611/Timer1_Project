/* 
 * File     : ecu_seven_segment.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 30, 2023, 11:50 PM
 */

/**************************Includes-Section*****************************/
#include "ecu_seven_segment.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the Seven Segment OFF or ON.
 * @Param seg          : Pointer to the Seven Segment module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
       ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN0]));  /* @Brief : Initialize Pin0. */
       ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN1]));  /* @Brief : Initialize Pin1. */
       ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN2]));  /* @Brief : Initialize Pin2. */
       ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN3]));  /* @Brief : Initialize Pin3. */
    }   
    return ret;
}

/* 
 * @Brief              : To write on the assigned pin. 
 * @Param seg          : Pointer to the Seven Segment module configurations.
 * @Param number
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
      ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), number & 0x01);         /* @Brief : Write logic on Pin0. */
      ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), (number>>1) & 0x01);    /* @Brief : Write logic on Pin1. */
      ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), (number>>2) & 0x01);    /* @Brief : Write logic on Pin2. */
      ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), (number>>3) & 0x01);    /* @Brief : Write logic on Pin3. */
    }   
    return ret;
} 
/***********************************************************************/