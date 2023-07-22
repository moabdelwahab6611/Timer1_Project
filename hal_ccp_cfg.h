/* 
 * File     : hal_ccp_cfg.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 10, 2023, 3:50 PM
 */

#ifndef HAL_CCP_CFG_H
#define	HAL_CCP_CFG_H

/**************************Includes-Section*****************************/

/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macros to select the mode for CCP1 or CCP2. */
#define CCP_CFG_CAPTURE_MODE_SELECTED     0x00
#define CCP_CFG_COMPARE_MODE_SELECTED     0x01
#define CCP_CFG_PWM_MODE_SELECTED         0x02

/* @Brief : Macro for CCP1 selected mode. */
#define CCP1_CFG_SELECTED_MODE (CCP_CFG_COMPARE_MODE_SELECTED)
/* @Brief : Macro for CCP2 selected mode. */
#define CCP2_CFG_SELECTED_MODE (CCP_CFG_COMPARE_MODE_SELECTED)
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/

/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/

/***********************************************************************/
#endif	/* HAL_CCP_CFG_H */

