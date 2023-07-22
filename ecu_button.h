/* 
 * File     : ecu_button.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 27, 2023, 1:49 AM
 */

#ifndef ECU__BUTTON_H
#define	ECU__BUTTON_H

/**************************Includes-Section*****************************/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Push Button Pressed / Released Status configuration. */
typedef enum
{
    BUTTON_PRESSED = 0,     /* @Brief : Push Button Pressed Status. */
    BUTTON_RELEASED         /* @Brief : Push Button Released Status. */
}button_state_t;

/* @Brief : Push Button Active High / Low Status configuration. */
typedef enum
{
    BUTTON_ACTIVE_HIGH,     /* @Brief : Push Button Active High. */
    BUTTON_ACTIVE_LOW       /* @Brief : Push Button Active Low. */
}button_active_t;

/* @Brief : Push Button configuration. */
typedef struct
{
    pin_config_t button_pin;                 /* @Brief : Push Button pin configuration. */
    button_state_t button_state;             /* @Brief : Push Button Status configuration. */
    button_active_t button_connection;       /* @Brief : Push Button connection Status configuration. */
}button_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be Input.
 * @Param btn          : Pointer to the Push Button configurations.
 * @Return  Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType button_initialize(const button_t *btn);

/*
 * @Brief              : Read the state of the Push Button.
 * @Param btn          : Pointer to the Push Button configurations.
 * @Param btn_state    : Pointer to the Push Button status configurations (@Ref button_state_t). 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);
/***********************************************************************/
#endif	/* ECU__BUTTON_H */

