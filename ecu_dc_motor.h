/* 
 * File     : ecu_dc_motor.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 29, 2023, 9:24 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/**************************Includes-Section*****************************/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro for DC Motor status on configuration. */
#define DC_MOTOR_STATUS_ON 0x01U
/* @Brief : Macro for DC Motor status off configuration. */
#define DC_MOTOR_STATUS_OFF 0x00U

/* @Brief : Macros for DC Motor pins configuration. */
#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/**********************Macro Declarations-Section***********************/
/* @Brief : DC Motor configuration. */
typedef struct
{
    pin_config_t dc_motor_pin[2]; /* @Brief : DC Motor pins configuration. */
}dc_motor_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the DC Motor OFF or ON.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);

/*
 * @Brief              : To make the DC Motor move right.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);

/*
 * @Brief              : To make the DC Motor move left.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);

/*
 * @Brief              : To stop the DC Motor.
 * @Param _dc_motor    : Pointer to the DC Motor module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);
/***********************************************************************/
#endif	/* ECU_DC_MOTOR_H */

