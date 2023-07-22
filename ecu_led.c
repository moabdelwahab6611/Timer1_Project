/* 
 * File     : ecu_led.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 6:33 PM
 */

/**************************Includes-Section*****************************/
#include "ecu_led.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the LED OFF or ON.
 * @param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/*
 * @Brief              : Turn the LED ON.
 * @Param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL == led)
     {
        ret = E_NOT_OK;
     }
     else
     {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
     }
    return ret;
}

/*
 * @Brief              : Turn the LED OFF.
 * @Param led          : Pointer to the LED module configurations.
 * @Return  Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL == led)
     {
        ret = E_NOT_OK;
     }
     else
     {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
     }
    return ret;
}

/*
 * @Brief              : Toggle the LED.
 * @Param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL == led)
     {
        ret = E_NOT_OK;
     }
     else
     {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_toggle_logic(&pin_obj);
     }
    return ret;
}
/***********************************************************************/