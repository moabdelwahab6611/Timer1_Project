/* 
 * File     : ecu_relay.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 28, 2023, 2:51 AM
 */

/**************************Includes-Section*****************************/
#include "ecu_relay.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the Relay OFF or ON.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_initialize(const relay_t *_relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/*
 * @Brief              : Turn the Relay ON.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_turn_on(const relay_t *_relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/*
 * @Brief              : Turn the Relay OFF.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_turn_off(const relay_t *_relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status}; 
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}
/***********************************************************************/