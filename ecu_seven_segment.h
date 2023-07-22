/* 
 * File     : ecu_seven_segment.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 30, 2023, 11:46 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/**************************Includes-Section*****************************/
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macros that defines Seven Segment pin configuration. */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Seven Segment Common Anode or Cathode selection configuration. */
typedef enum
{
    SEGMENT_COMMON_ANODE,       /* @Brief : Seven Segment Common Anode selection configuration. */
    SEGMENT_COMMON_CATHODE      /* @Brief : Seven Segment Common Cathode selection configuration. */     
}segment_type_t;

/* @Brief : Seven Segment configuration. */
typedef struct
{
    pin_config_t segment_pins[4];   /* @Brief : Seven Segment pins configuration. */
    segment_type_t segment_type;    /* @Brief : Seven Segment Anode or Cathode selection configuration. */
}segment_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the Seven Segment OFF or ON.
 * @Param seg          : Pointer to the Seven Segment module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg);

/* 
 * @Brief              : To write on the assigned pin. 
 * @Param seg          : Pointer to the Seven Segment module configurations.
 * @Param number
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);
/***********************************************************************/
#endif	/* ECU_SEVEN_SEGMENT_H */

