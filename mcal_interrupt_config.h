/* 
 * File     : mcal_interrupt_config.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 2, 2023, 9:30 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/**************************Includes-Section*****************************/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to enable interrupts. */
#define INTERRUPT_ENABLE    1
/* @Brief : Macro to disable interrupts. */
#define INTERRUPT_DISABLE   0

/* @Brief : Macro for interrupts Occur. */
#define INTERRUPT_OCCUR     1
/* @Brief : Macro for interrupts to Not OCcur. */
#define INTERRUPT_NOT_OCCUR 0

/* @Brief : Macro to enable interrupts priority. */
#define INTERRUPT_PRIORITY_ENABLE    1
/* @Brief : Macro to disable interrupts priority. */
#define INTERRUPT_PRIORITY_DISABLE   0
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* @Brief : Macro function to enable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsEnable()  (RCONbits.IPEN = 1)
/* @Brief : Macro function to disable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)

/* @Brief : Macro function to enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* @Brief : Macro function to disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/* @Brief : Macro function to enable low priority global interrupts. */ 
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/* @Brief : Macro function to disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)
#else
/* @Brief : Macro function to enable global interrupts. */ 
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)
/* @Brief : Macro function to disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/* @Brief : Macro function to enable peripheral interrupts. */ 
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* @Brief : Macro function to disable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Priority configuration. */
typedef enum
{
    INTERRUPT_LOW_PRIORITY = 0,     /* @Brief : Low Priority Selection. */
    INTERRUPT_HIGH_PRIORITY         /* @Brief : High Priority Selection. */
}interrupt_priority_cfg;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/

/***********************************************************************/
#endif	/* MCAL_INTERRUPT_CONFIG_H */
