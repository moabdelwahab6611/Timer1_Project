/* 
 * File     : hal_timer0.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 7, 2023, 4:08 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to enable Pre-scaler for Timer0. */
#define TIMER0_ENABLE_PRESCALER_CFG  1
/* @Brief : Macro to disable Pre-scaler for Timer0. */
#define TIMER0_DISABLE_PRESCALER_CFG 0

/* @Brief : Macros to select Raising Edge type for Timer0. */
#define TIMER0_RISING_EDGE_CFG       1
/* @Brief : Macros to select Falling Edge type for Timer0. */
#define TIMER0_FALLING_EDGEE_CFG     0

/* @Brief : Macros for timer mode selection for Timer0. */
#define TIMER0_TIMER_MODE            1
/* @Brief : Macro for counter mode selection for Timer0. */
#define TIMER0_COUNTER_MODE          0

/* @Brief : Macro to select 8-Bit register size for Timer0. */
#define TIMER0_8BIT_REGISTER_MODE    1
/* @Brief : Macro to select 16-Bit register size for Timer0. */
#define TIMER0_16BIT_REGISTER_MODE   0
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to enable Timer0 module. */
#define TIMER0_ENABLE_MODULE()              (T0CONbits.TMR0ON = 1)
/* @Brief : Macro function to disable Timer0 module. */
#define TIMER0_DISABLE_MODULE()             (T0CONbits.TMR0ON = 0)

/* @Brief : Macro function to enable Timer0 Pre-scaler. */
#define TIMER0_ENABLE_PRESCALER()           (T0CONbits.PSA = 0)
/* @Brief : Macro function to disable Timer0 Pre-scaler. */
#define TIMER0_DISABLE_PRESCALER()          (T0CONbits.PSA = 1)

/* @Brief : Macro function to enable rising edge for Timer0. */
#define TIMER0_ENABLE_RISING_EDGE()         (T0CONbits.T0SE = 0)
/* @Brief : Macro function to enable falling edge for Timer0. */
#define TIMER0_ENABLE_FALLING_EDGE()        (T0CONbits.T0SE = 1)

/* @Brief : Macro function to enable timer mode for Timer0. */
#define TIMER0_ENABLE_TIMER_MODE()          (T0CONbits.T0CS = 0)
/* @Brief : Macro function to enable counter mode for Timer0. */
#define TIMER0_ENABLE_COUNTER_MODE()        (T0CONbits.T0CS = 1)

/* @Brief : Macro function to enable 8-Bit register mode for Timer0. */
#define TIMER0_ENABLE_8BIT_REGISTER_MODE()  (T0CONbits.T08BIT = 1)
/* @Brief : Macro function to enable 16-Bit register mode for Timer0. */
#define TIMER0_ENABLE_16BIT_REGISTER_MODE() (T0CONbits.T08BIT = 0)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : To select Timer0 Pre-scaler clock input configurations. */
typedef enum
{
    TIMER0_PRRESCALER_DIV_BY_2 = 0,
    TIMER0_PRRESCALER_DIV_BY_4,        
    TIMER0_PRRESCALER_DIV_BY_8,
    TIMER0_PRRESCALER_DIV_BY_16,
    TIMER0_PRRESCALER_DIV_BY_32,
    TIMER0_PRRESCALER_DIV_BY_64,
    TIMER0_PRRESCALER_DIV_BY_128,
    TIMER0_PRRESCALER_DIV_BY_256,        
}timer0_prescaler_select_t;

/* @Brief : Timer0 configuration. */
typedef struct
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*TMR0_InterruptHandler)(void);                /* @Brief : Timer0 Interrupt Handler. */
    interrupt_priority_cfg priority;                    /* @Brief : Timer0 Priority configuration. */
#endif 
    timer0_prescaler_select_t prescaler_value;          /* @Brief : Timer0 Pre-scaler configuration. */
    uint16 timer0_preload_value;                        /* @Brief : Timer0 Pre-load configuration. */
    uint8 prescaler_status_cfg  : 1;                    /* @Brief : Timer0 Pre-scaler status configuration. */
    uint8 timer0_counter_edge : 1;                      /* @Brief : Timer0 Counter Mode Edge Type configuration. */
    uint8 timer0_mode : 1;                              /* @Brief : Timer0 Mode configuration. */
    uint8 timer0_register_size : 1;                     /* @Brief : Timer0 Register Size Selection configurations. */
    uint8 timer0_reserved : 4;                          /* @Brief : Timer0 Reserved Bits. */
}timer0_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the Timer0.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Init(const timer0_t *_timer);

/*
 * @Brief              : To de-initialize the Timer0.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);

/*
 * @Brief              : To write value Timer0 counter register.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value);

/*
 * @Brief              : To read value Timer0 counter register.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Param _value       : Pointer to access value to read it from the register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);
/***********************************************************************/
#endif	/* HAL_TIMER0_H */

