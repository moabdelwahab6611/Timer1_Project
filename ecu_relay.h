/* 
 * File     : ecu_relay.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 28, 2023, 2:51 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/**************************Includes-Section*****************************/
#include "ecu_relay_cfg.h"  
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* Brief : Relay Status On configuration. */
#define RELAY_STATUS_ON 0x01U
/* Brief : Relay Status Off configuration. */
#define RELAY_STATUS_OFF 0x00U
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* Brief : Relay configuration. */
typedef struct
{
    uint8 relay_port : 4;       /* Brief : Relay Port configuration. */
    uint8 relay_pin : 3;        /* Brief : Relay Pin configuration. */
    uint8 relay_status :1;      /* Brief : Relay Status configuration. */
}relay_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the Relay OFF or ON.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_initialize(const relay_t *_relay);

/*
 * @Brief              : Turn the Relay ON.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_turn_on(const relay_t *_relay);

/*
 * @Brief              : Turn the Relay OFF.
 * @Param _relay       : Pointer to the Relay module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType relay_turn_off(const relay_t *_relay);
/***********************************************************************/
#endif	/* ECU_RELAY_H */

