/* 
 * File     : mcal_external_interrupt.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 2, 2023, 9:34 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/**************************Includes-Section*****************************/
#include "mcal_interrupt_config.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* @Brief : This routine clears the interrupt enable for the external interrupt INT0.*/
#define EXT_INT0_InterruptDisable()         (INTCONbits.INT0IE = 0)
/* @Brief : This routine sets the interrupt enable for the external interrupt INT0. */
#define EXT_INT0_InterruptEnable()          (INTCONbits.INT0IE = 1)
/* @Brief : This routine clears the interrupt flag for the external interrupt INT0. */
#define EXT_INT0_InterruptFlagClear()       (INTCONbits.INT0IF = 0)
/* @Brief : This routine set the edge detect for the external interrupt to negative edge. */
#define EXT_INT0_RisingEdgeSet()            (INTCON2bits.INTEDG0 = 1)
/* @Brief : This routine set the edge detect for the external interrupt to positive edge. */
#define EXT_INT0_FallingEdgeSet()           (INTCON2bits.INTEDG0 = 0)

/* @Brief : This routine clears the interrupt enable for the external interrupt INT1. */
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1IE = 0)
/* @Brief : This routine sets the interrupt enable for the external interrupt INT1. */
#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1IE = 1)
/* @Brief : This routine clears the interrupt flag for the external interrupt INT1. */
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1IF = 0)
/* @Brief : This routine set the edge detect for the external interrupt to negative edge. */
#define EXT_INT1_RisingEdgeSet()            (INTCON2bits.INTEDG1 = 1)
/* @Brief : This routine set the edge detect for the external interrupt to positive edge. */
#define EXT_INT1_FallingEdgeSet()           (INTCON2bits.INTEDG1 = 0)

/* @Brief : This routine clears the interrupt enable for the external interrupt INT2. */
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2IE = 0)
/* @Brief : This routine sets the interrupt enable for the external interrupt INT2. */
#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2IE = 1)
/* @Brief : This routine clears the interrupt flag for the external interrupt INT2. */
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2IF = 0)
/* @Brief : This routine set the edge detect for the external interrupt to negative edge. */
#define EXT_INT2_RisingEdgeSet()            (INTCON2bits.INTEDG2 = 1)
/* @Brief : This routine set the edge detect for the external interrupt to positive edge. */
#define EXT_INT2_FallingEdgeSet()           (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* @Brief : This routine set the INT1 external interrupt priority to be high priority. */
#define EXT_INT1_SetHighPriority()           (INTCON3bits.INT1IP = 1)
/* @Brief : This routine set the INT1 external interrupt priority to be low priority. */
#define EXT_INT1_SetLowPriority()            (INTCON3bits.INT1IP = 0)
/* @Brief : This routine set the INT2 external interrupt priority to be high priority. */
#define EXT_INT2_SetHighPriority()           (INTCON3bits.INT2IP = 1)
/* @Brief : This routine set the INT2 external interrupt priority to be low priority. */
#define EXT_INT2_SetLowPriority()            (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* @Brief : This routine clears the interrupt enable for the external interrupt RBx. */
#define EXT_RBx_InterruptDisable()         (INTCONbits.RBIE = 0)
/* @Brief : This routine sets the interrupt enable for the external interrupt RBx. */
#define EXT_RBx_InterruptEnable()          (INTCONbits.RBIE = 1)
/* @Brief : This routine clears the interrupt flag for the external interrupt RBx. */
#define EXT_RBx_InterruptFlagClear()       (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* @Brief : This routine set the RBx external interrupt priority to be high priority. */
#define EXT_RBx_Set_Priority_High()            (INTCON2bits.RBIP = 1)
/* @Brief : This routine set the RBx external interrupt priority to be low priority. */
#define EXT_RBx_Set_Priority_Low()             (INTCON2bits.RBIP = 0)
#endif

#endif
/***********************************************************************/

/********************Data Types Declarations-Section********************/
typedef void (*InterruptHandler)(void);  /* @Brief : External Interrupt Handler Declaration. */

/* @Brief : External INTx Interrupt Edge Type Selection configuration. */
typedef enum
{
    INTERRUPT_FALLING_EDGE = 0,                 /* @Brief : Falling Edge Selection. */
    INTERRUPT_RISING_EDGE                       /* @Brief : Rising Edge Selection. */
}interrupt_INTx_edge;

/* @Brief : External INTx Interrupt Source Selection configuration. */
typedef enum
{
    INTERRUPT_EXTERNAL_INT0 =  0,               /* @Brief : External INTx Interrupt 0 Source Selection configuration. */
    INTERRUPT_EXTERNAL_INT1,                    /* @Brief : External INTx Interrupt 1 Source Selection configuration. */
    INTERRUPT_EXTERNAL_INT2                     /* @Brief : External INTx Interrupt 2 Source Selection configuration. */
}interrupt_INTx_src;

/* @Brief : External INTx Interrupt configuration. */
typedef struct
{
    void (* EXT_InterruptHandler)(void);        /* @Brief : External Interrupt Handler. */
    pin_config_t mcu_pin;                       /* @Brief : MCU External INTx Interrupt Pins configuration. */
    interrupt_INTx_edge edge;                   /* @Brief : External INTx Edge Type Selection configuration. */
    interrupt_INTx_src source;                  /* @Brief : External INTx Interrupt Source configuration. */
    interrupt_priority_cfg priority;            /* @Brief : External INTx Interrupt Priority configuration. */
}interrupt_INTx_t;

 /* @Brief : External RBx Interrupt configuration. */
typedef struct
{
    void (* EXT_InterruptHandler_HIGH)(void);   /* @Brief : External Interrupt High Priority Handler. */
    void (* EXT_InterruptHandler_LOW)(void);    /* @Brief : External Interrupt Low Priority Handler. */
    pin_config_t mcu_pin;                       /* @Brief : MCU External Interrupt RBx Pins configuration. */
    interrupt_priority_cfg priority;            /* @Brief : External RBx Interrupt Priority configuration. */
}interrupt_RBx_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the External INTx Interrupts and enable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To de-initialize the External INTx Interrupts and disable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To initialize the External RBx Interrupts and enable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);

/*
 * @Brief              : To de-initialize the External RBx Interrupts and disable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);
/***********************************************************************/
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */
