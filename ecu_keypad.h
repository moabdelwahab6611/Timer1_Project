/* 
 * File     : ecu_keypad.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 31, 2023, 6:50 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/**************************Includes-Section*****************************/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* Brief : KeyPad rows configuration. */
#define ECU_KEYPAD_ROWS    4
/* Brief : KeyPad columns configuration. */
#define ECU_KEYPAD_COLUMNS 4
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* Brief : KeyPad configuration. */
typedef struct
{
    pin_config_t keypad_rows_pins[ECU_KEYPAD_ROWS];       /* Brief : KeyPad rows configuration. */
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS]; /* Brief : KeyPad columns configuration. */
}keypad_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT or INPUT.
 * @Param _keypad_obj  : Pointer to the KeyPad module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);

/*
 * @Brief              : To get the value from a certain row or column.
 * @Param _keypad_obj  : Pointer to the KeyPad module configurations.
 * @Param value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);
/***********************************************************************/
#endif	/* ECU_KEYPAD_H */

