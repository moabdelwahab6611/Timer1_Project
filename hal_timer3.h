/* 
 * File     : hal_timer3.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 8, 2023, 11:12 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to select Counter mode for Timer3. */
#define TIMER3_COUNTER_MODE              1
/* @Brief : Macro to select  Timer mode for Timer3. */
#define TIMER3_TIMER_MODE                0

/* @Brief : Macro for Timer3 Asynchronous selection. */
#define TIMER3_ASYNCHRONOUS_COUNTER_MODE 1
/* @Brief : Macro for Timer3 Synchronous selection. */
#define TIMER3_SYNCHRONOUS_COUNTER_MODE  0

/* @Brief : Macros to select Timer3 Pre-scaler clock input. */
#define TIMER3_PRESCALER_DIV_BY_1        0
#define TIMER3_PRESCALER_DIV_BY_2        1
#define TIMER3_PRESCALER_DIV_BY_4        2
#define TIMER3_PRESCALER_DIV_BY_8        3

/* @Brief : Macro to read or write from or in Timer3 8-Bit register. */
#define TIMER3_RW_8BIT_REGISTER_MODE     0

/* @Brief : Macro to read or write from or in Timer3 16-Bit register. */
#define TIMER3_RW_16BIT_REGISTER_MODE    1
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to enable Timer3 module. */
#define TIMER3_ENABLE_MODULE()                     (T3CONbits.TMR3ON = 1)
/* @Brief : Macro function to disable Timer3 module. */
#define TIMER3_DISABLE_MODULE()                    (T3CONbits.TMR3ON = 0)

/* @Brief : Macro function to enable Timer mode for Timer3. */
#define TIMER3_ENABLE_TIMER_MODE()                 (T3CONbits.TMR3CS = 0)
/* @Brief : Macro function to enable Counter mode for Timer3. */
#define TIMER3_ENABLE_COUNTER_MODE()               (T3CONbits.TMR3CS = 1)

/* @Brief : Macro function to enable Asynchronous Counter mode for Timer3. */
#define TIMER3_ENABLE_ASYNCHRONOUS_COUNTER_MODE()  (T3CONbits.T3SYNC = 1)
/* @Brief : Macro function to enable Synchronous Counter mode for Timer3. */
#define TIMER3_ENABLE_SYNCHRONOUS_COUNTER_MODE()   (T3CONbits.T3SYNC = 0)

/* @Brief : Macro function to select Timer3 Pre-scaler clock input. */
#define TIMER3_PRESCALER_SELECTION(_PRESCALER_)    (T3CONbits.T3CKPS = _PRESCALER_)

/* @Brief : Macro function to read or write from or in Timer3 8-Bit register. */
#define TIMER3_ENABLE_RW_8BIT_REGISTER_MODE()      (T3CONbits.RD16 = 0)
/* @Brief : Macro function to read or write from or in Timer3 16-Bit register. */
#define TIMER3_ENABLE_RW_16BIT_REGISTER_MODE()     (T3CONbits.RD16 = 1)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Timer3 configuration. */
typedef struct
{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*TMR3_InterruptHandler)(void);     /* @Brief : Timer3 Interrupt Handler. */
    interrupt_priority_cfg priority;         /* @Brief : Timer3 Priority configurations. */
#endif
    uint16 timer3_preload_value;             /* @Brief : Timer3 Pre-load configurations. */
    uint8 timer3_prescaler_value : 2;        /* @Brief : Timer3 Pre-scaler configurations. */
    uint8 timer3_mode : 1;                   /* @Brief : Timer3 Mode configurations. */
    uint8 timer3_counter_mode : 1;           /* @Brief : Timer3 Counter Mode configurations. */
    uint8 timer3_reg_rw_mode : 1;            /* @Brief : Timer3 Read or Write configurations. */
    uint8 timer3_reserved : 3;               /* @Brief : Timer3 Reserved Bits. */
}timer3_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the Timer3.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Init(const timer3_t *_timer);

/*
 * @Brief              : To de-initialize the Timer3.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);

/*
 * @Brief              : To write value Timer3 counter register.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value);

/*
 * @Brief              : To read value Timer3 counter register.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);
/***********************************************************************/
#endif	/* HAL_TIMER3_H */

