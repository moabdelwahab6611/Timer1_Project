/* 
 * File     : mcal_interrupt_gen_cfg.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 3, 2023, 2:42 AM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/**************************Includes-Section*****************************/

/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/
#define INTERRUPT_FEATURE_ENABLE 1U
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE            INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE      INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

#define USART_TX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define USART_RX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE

#define  CCP1_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define  CCP2_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
/***********************************************************************/

/********************Data Types Declarations-Section********************/

/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/

/***********************************************************************/
#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

