/* 
 * File     : ecu_dc_motor.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 29, 2023, 9:24 PM
 */

/**************************Includes-Section*****************************/
#include "ecu_dc_motor.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the DC Motor OFF or ON.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));  /* @Brief : To initialize DC Motor pin1. */
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));  /* @Brief : To initialize DC Motor pin2. */
    }   
    return ret; 
}

/*
 * @Brief              : To make the DC Motor move right.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);  /* @Brief : To write logic high on DC Motor pin1. */
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);   /* @Brief : To write logic low on DC Motor pin2. */
    }
    return ret;
}

/*
 * @Brief              : To make the DC Motor move left.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);    /* @Brief : To write logic low on DC Motor pin1. */ 
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);   /* @Brief : To write logic high on DC Motor pin2. */
    }
    return ret;
}

/*
 * @Brief              : To stop the DC Motor.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);  /* @Brief : To write logic low on DC Motor pin1. */
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);  /* @Brief : To write logic low on DC Motor pin2. */        
    }
    return ret;
}
/***********************************************************************/