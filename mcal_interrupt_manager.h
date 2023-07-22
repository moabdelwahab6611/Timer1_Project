/* 
 * File     : mcal_interrupt_manager.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 2, 2023, 9:36 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/**************************Includes-Section*****************************/
#include "mcal_interrupt_config.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/

/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief : Callback pointer to function to External INT0 interrupt service routine.
 */
void INT0_ISR(void);
/*
 * @Brief : Callback pointer to function to External INT1 interrupt service routine.
 */
void INT1_ISR(void);
/*
 * @Brief : Callback pointer to function to External INT2 interrupt service routine.
 */
void INT2_ISR(void);

/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB4_Source
 */
void RB4_ISR(uint8 RB4_Source);
/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB5_Source
 */
void RB5_ISR(uint8 RB5_Source);
/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB6_Source
 */
void RB6_ISR(uint8 RB6_Source);
/*
 * @Brief : External Interrupt RB4 MCAL Helper function.
 * @Param RB7_Source
 */
void RB7_ISR(uint8 RB7_Source);

/*
 * @Brief : Callback pointer to function to ADC interrupt service routine.
 */
void ADC_ISR(void);

/*
 * @Brief : Callback pointer to function to Timer0 interrupt service routine.
 */
void TMR0_ISR(void);
/*
 * @Brief : Callback pointer to function to Timer1 interrupt service routine.
 */
void TMR1_ISR(void);
/*
 * @Brief : Callback pointer to function to Timer2 interrupt service routine.
 */
void TMR2_ISR(void);
/*
 * @Brief : Callback pointer to function to Timer3 interrupt service routine.
 */
void TMR3_ISR(void);

/*
 * @Brief : Callback pointer to function to USART Transmit interrupt service routine.
 */
void USART_TX_ISR(void);
/*
 * @Brief : Callback pointer to function to USART Receive interrupt service routine.
 */
void USART_RX_ISR(void);

/*
 * @Brief : Callback pointer to function to MSSP I2C interrupt service routine.
 */
void MSSP_I2C_ISR(void);
/*
 * @Brief : Callback pointer to function to MSSP I2C Bus Collision interrupt service routine.
 */
void MSSP_I2C_BC_ISR(void);

/*
 * @Brief : Callback pointer to function to CCP1 interrupt service routine.
 */
void CCP1_ISR(void);
/*
 * @Brief : Callback pointer to function to CCP2 interrupt service routine.
 */
void CCP2_ISR(void);
/***********************************************************************/
#endif	/* MCAL_INTERRUPT_MANAGER_H */

