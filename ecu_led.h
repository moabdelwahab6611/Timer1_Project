/* 
 * File     : ecu_led.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 6:33 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/**************************Includes-Section*****************************/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : LED On / Off status  configuration. */
typedef enum
{
    LED_OFF,
    LED_ON
}led_status_t;

/* @Brief : LED configuration. */
typedef struct
{
    uint8 port_name : 4;    /* @Brief : LED Port configuration. */
    uint8 pin : 3;          /* @Brief : LED Pin configuration. */
    uint8 led_status : 1;   /* @Brief : LED Status configuration. */
}led_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the LED OFF or ON.
 * @param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_initialize(const led_t *led);

/*
 * @Brief              : Turn the LED ON.
 * @Param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_on(const led_t *led);

/*
 * @Brief              : Turn the LED OFF.
 * @Param led          : Pointer to the LED module configurations.
 * @Return  Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_off(const led_t *led);

/*
 * @Brief              : Toggle the LED.
 * @Param led          : Pointer to the LED module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType led_turn_toggle(const led_t *led);
/***********************************************************************/
#endif	/* ECU_LED_H */

