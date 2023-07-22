/* 
 * File     : hal_timer2.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 8, 2023, 7:38 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macros to select Timer2 post-scaler clock output. */
#define TIMER2_POSTSCALER_DIV_BY_1        0
#define TIMER2_POSTSCALER_DIV_BY_2        1
#define TIMER2_POSTSCALER_DIV_BY_3        2
#define TIMER2_POSTSCALER_DIV_BY_4        3
#define TIMER2_POSTSCALER_DIV_BY_5        4
#define TIMER2_POSTSCALER_DIV_BY_6        5
#define TIMER2_POSTSCALER_DIV_BY_7        6
#define TIMER2_POSTSCALER_DIV_BY_8        7
#define TIMER2_POSTSCALER_DIV_BY_9        8
#define TIMER2_POSTSCALER_DIV_BY_10       9
#define TIMER2_POSTSCALER_DIV_BY_11       10
#define TIMER2_POSTSCALER_DIV_BY_12       11
#define TIMER2_POSTSCALER_DIV_BY_13       12
#define TIMER2_POSTSCALER_DIV_BY_14       13
#define TIMER2_POSTSCALER_DIV_BY_15       14
#define TIMER2_POSTSCALER_DIV_BY_16       15

/* @Brief : Macros to select Timer2 pre-scaler clock input. */
#define TIMER2_PRESCALER_DIV_BY_1        0
#define TIMER2_PRESCALER_DIV_BY_4        1
#define TIMER2_PRESCALER_DIV_BY_16       2
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to enable Timer2 module. */
#define TIMER2_ENABLE_MODULE()                     (T2CONbits.TMR2ON = 1)
/* @Brief : Macro function to disable Timer2 module. */
#define TIMER2_DISABLE_MODULE()                    (T2CONbits.TMR2ON = 0)

/* @Brief : Macro function to select Timer2 pre-scaler clock input. */
#define TIMER2_PRRESCALER_SELECTION(_PRESCALER_)  (T2CONbits.T2CKPS = _PRESCALER_)
/* @Brief : Macro function to select Timer2 post-scaler clock output. */
#define TIMER2_POSTSCALER_SELECTION(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Timer2 configuration. */
typedef struct
{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*TMR2_InterruptHandler)(void);     /* @Brief : Timer2 Interrupt Handler. */
    interrupt_priority_cfg priority;         /* @Brief : Timer2 Priority configurations. */
#endif
    uint8 timer2_preload_value;              /* @Brief : Timer2 Pre-load configurations. */
    uint8 timer2_postscaler_value : 4;       /* @Brief : Timer2 Post-scaler configurations. */
    uint8 timer2_prescaler_value : 2;        /* @Brief : Timer2 Pre-scaler configurations. */   
    uint8 timer2_reserved : 2;               /* @Brief : Timer2 Reserved Bits. */   
}timer2_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the Timer2.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer);

/*
 * @Brief              : To de-initialize the Timer2.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);

/*
 * @Brief              : To write value Timer2 counter register.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);

/*
 * @Brief              : To read value Timer2 counter register.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);
/***********************************************************************/
#endif	/* HAL_TIMER2_H */

