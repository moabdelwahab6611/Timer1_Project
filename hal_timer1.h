/* 
 * File     : hal_timer1.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 8, 2023, 3:24 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to counter mode selection for Timer1. */
#define TIMER1_COUNTER_MODE              1
/* @Brief : Macro to timer mode selection for Timer1. */
#define TIMER1_TIMER_MODE                0

/* @Brief : Macro for Timer1 asynchronous counter mode configuration. */
#define TIMER1_ASYNCHRONOUS_COUNTER_MODE 1
/* @Brief : Macro for Timer1 synchronous counter mode configuration. */
#define TIMER1_SYNCHRONOUS_COUNTER_MODE  0

/* @Brief : Macro to enable Timer1 oscillator. */  
#define TIMER1_ENABLE_OSCILLATOR         1
/* @Brief : Macro to disable Timer1 oscillator. */                                                   
#define TIMER1_DISABLE_OSCILLATOR        0

/* @Brief : Macros to select Timer1 Pre-scaler clock input. */
#define TIMER1_PRESCALER_DIV_BY_1       0
#define TIMER1_PRESCALER_DIV_BY_2       1
#define TIMER1_PRESCALER_DIV_BY_4       2
#define TIMER1_PRESCALER_DIV_BY_8       3

/* @Brief : Macro to read or write from or in Timer1 8-Bit register. */
#define TIMER1_RW_8BIT_REGISTER_MODE     0

/* @Brief : Macro to read or write from or in Timer1  16-Bit register. */
#define TIMER1_RW_16BIT_REGISTER_MODE    1
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to enable Timer1 module. */
#define TIMER1_ENABLE_MODULE()                     (T1CONbits.TMR1ON = 1)
/* @Brief : Macro function to disable Timer1 module. */
#define TIMER1_DISABLE_MODULE()                    (T1CONbits.TMR1ON = 0)

/* @Brief : Macro function to enable timer mode for Timer1. */
#define TIMER1_ENABLE_TIMER_MODE()                 (T1CONbits.TMR1CS = 0)
/* @Brief : Macro function to enable counter mode for Timer1. */
#define TIMER1_ENABLE_COUNTER_MODE()               (T1CONbits.TMR1CS = 1)

/* @Brief : Macro function to enable asynchronous counter mode for Timer1. */
#define TIMER1_ENABLE_ASYNCHRONOUS_COUNTER_MODE()  (T1CONbits.T1SYNC = 1)
/* @Brief : Macro function to enable synchronous counter mode for Timer1. */
#define TIMER1_ENABLE_SYNCHRONOUS_COUNTER_MODE()   (T1CONbits.T1SYNC = 0)

/* @Brief : Macro function to enable or to disable Timer1 oscillator. */
#define TIMER1_ENABLE_HW_OSCILLATOR()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_DISABLE_HW_OSCILLATOR()             (T1CONbits.T1OSCEN = 0)

/* @Brief : Macro function to select Timer1 pre-scaler clock input. */
#define TIMER1_PRESCALER_SELECTION(_PRESCALER_)  (T1CONbits.T1CKPS = _PRESCALER_)

/* @Brief : Macro function to check Timer1 clock status. */
#define TIMER1_SYSTEM_CLK_STATUS()                 (T1CONbits.T1RUN)

/* @Brief : Macro function to read or write from or in Timer1 8-Bit register. */
#define TIMER1_ENABLE_RW_8BIT_REGISTER_MODE()      (T1CONbits.RD16 = 0)
/* @Brief : Macro function to read or write from or in Timer1 16-Bit register. */
#define TIMER1_ENABLE_RW_16BIT_REGISTER_MODE()      (T1CONbits.RD16 = 1)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Timer1 configuration. */
typedef struct
{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*TMR1_InterruptHandler)(void);        /* @Brief : Timer1 Interrupt Handler. */
    interrupt_priority_cfg priority;            /* @Brief : Timer1 Priority configuration. */
#endif
    uint16 timer1_preload_value;                /* @Brief : Timer1 Pre-load configuration. */
    uint8 timer1_prescaler_value : 2;           /* @Brief : Timer1 Pre-scaler configuration. */
    uint8 timer1_mode : 1;                      /* @Brief : Timer1 Mode configuration. */
    uint8 timer1_counter_mode : 1;              /* @Brief : Timer1 Counter Mode configuration. */
    uint8 timer1_osc_cfg : 1;                   /* @Brief : Timer1 Oscillator configuration. */
    uint8 timer1_reg_rw_mode : 1;               /* @Brief : Timer1 R/W configuration. */
    uint8 timer1_reserved : 2;                  /* @Brief : Timer1 Reserved Bits. */
}timer1_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the Timer1.
 * @Param _timer       : Pointer to the Timer1 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer1_Init(const timer1_t *_timer);

/*
 * @Brief              : To de-initialize the Timer1.
 * @Param _timer       : Pointer to the Timer1 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);

/*
 * @Brief              : To write value Timer1 counter register.
 * @Param _timer       : Pointer to the Timer1 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);

/*
 * @Brief              : To read value Timer1 counter register.
 * @Param _timer       : Pointer to the Timer1 module configurations.
 * @Param _value       : Pointer to access value to read it from the register. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);
/***********************************************************************/
#endif	/* HAL_TIMER1_H */

