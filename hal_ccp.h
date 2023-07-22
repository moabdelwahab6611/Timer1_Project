/* 
 * File     : hal_ccp.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 10, 2023, 3:50 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_ccp_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to enable CCP module. */
#define CCP_DISABLE_MODULE                 ((uint8)0x00)

/* @Brief : Macros to Capture mode edge type selection configuration for CCP. */
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_FALLING_EDGE   ((uint8)0x07)

/* @Brief : Macros for Compare mode pin voltage low selection configuration for CCP. */
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
/* @Brief : Macros for Compare mode pin voltage high selection configuration for CCP. */
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)

/* @Brief : Macros to Compare mode toggle on match configuration for CCP. */
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)

/* @Brief : Macro to Compare mode software interrupt generation for CCP. */
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)

/* @Brief : Macro to Compare mode for event generation for CCP. */
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)

/* @Brief : Macro to PWM mode selection configuration for CCP. */
#define CCP_PWM_MODE                       ((uint8)0x0C)

/* @Brief : Macro for CCP Capture mode state. */
#define CCP_CAPTURE_MODE_READY             0x01
#define CCP_CAPTURE_MODE_NOT_READY         0x00

/* @Brief : Macro for CCP Compare mode state is ready. */
#define CCP_COMPARE_MODE_READY             0x01
/* @Brief : Macro for CCP Compare mode state is not ready. */
#define CCP_COMPARE_MODE_NOT_READY         0x00

/* @Brief : Macros to select Timer2 Post-scaler clock output for CCP. */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1        1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2        2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3        3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4        4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5        5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6        6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7        7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8        8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9        9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10       10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11       11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12       12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13       13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14       14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15       15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16       16

/* Brief : Macros to select Timer2 Pre-scaler clock input for CCP. */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to select CCP1 mode. */
#define CCP1_SET_MODE(_CONFIG) (CCP1CONbits.CCP1M = _CONFIG)

/* @Brief : Macro function to select CCP2 mode. */
#define CCP2_SET_MODE(_CONFIG) (CCP2CONbits.CCP2M = _CONFIG)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : CCP mode selection configuration. */
typedef enum
{
    CCP_CAPTURE_MODE_CFG = 0,      /* @Brief : CCP Capture mode selection configuration. */
    CCP_COMPARE_MODE_CFG,          /* @Brief : CCP Compare mode selection configuration. */
    CCP_PWM_MODE_CFG               /* @Brief : CCP PWM mode selection configuration. */
}ccp_mode_t;

/* @Brief : CCP1 or CCP2 selection configuration. */
typedef enum
{
    CCP1_INST = 0,                 /* @Brief : CCP1 selection configuration. */
    CCP2_INST                      /* @Brief : CCP2 selection configuration. */
}ccp_inst_t;

/* @Brief : CCP1 and CCP2 capture mode timer selection configuration. */
typedef enum
{
    CCP1_CCP2_TIMER3 = 0,          /* @Brief : CCP1 and CCP2 operating with Timer3 selection configuration. */    
    CCP1_TIMER1_CCP2_TIMER3,       /* @Brief : CCP1 operating with Timer1 and CCP2 operating with Timer3 selection configuration. */
    CCP1_CCP2_TIMER1               /* @Brief : CCP1 and CCP2 operating with Timer1 selection configuration. */
}ccp_capture_timer_t;

/* 
 * Brief       : Defines the values to convert from 16-Bit to two 8-Bit and vice versa.
 * Description : Used to get two 8-Bit value from 16-Bit also to combine two 8-Bit value to get 16-Bit.
 */
typedef union
{
    struct
    {
       uint8 ccpr_low;     /* @Brief : CCPR 8-Bit low register value. */
       uint8 ccpr_high;    /* @Brief : CCPR 8-Bit high register value. */
    };
    struct
    {
       uint8 ccpr_16bit;   /* @Brief : Read CCPR as 16-Bit register value. */
    };
}CCP_REG_T;

/* #Brief : CCP configuration. */
typedef struct
{
    ccp_inst_t ccp_inst;                         /* @Brief : CCP1 or CCP2 selection configuration. */
    ccp_mode_t ccp1_mode;                        /* @Brief : CCP Mode selection configuration. */
    uint8 ccp_mode_variant;                      /* @Brief : CCP1 or CCP2 PWM mode variant configuration. */       
    pin_config_t ccp_pin;                        /* @Brief : CCP Pin configuration. */
    ccp_capture_timer_t ccp_capture_timer;       /* @Brief : CCP1 or CCP2 Capture Timer configuration. */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*CCP1_InterruptHandler)(void);         /* @Brief : CCP1 Interrupt Handler. */
    interrupt_priority_cfg CCP1_priority;        /* @Brief : CCP1 Priority configuration. */
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*CCP2_InterruptHandler)(void);         /* @Brief : CCP2 Interrupt Handler. */
    interrupt_priority_cfg CCP2_priority;        /* @Brief : CCP2 Priority configuration. */   
#endif
#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    uint32 pwm_frequency;                       /* @Brief : CCP1 or CCP2 PWM mode frequency configuration. */  
    uint8 timer2_postscaler_value : 4;          /* @Brief : CCP1 or CCP2 Timer2 Post-scaler configuration. */  
    uint8 timer2_prescaler_value : 2;           /* @Brief : CCP1 or CCP2 Timer2 Pre-scaler configuration. */  
#endif
}ccp_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the CCP.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj);

/*
 * @Brief              : To de-initialize the CCP.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
/*
 * @Brief                 : To check Capture mode data status.
 * @Param _capture_status : Pointer to the CCP Capture mode data status.
 * @Return Status of the function.
 *          (E_OK)        : The function done successfully.
 *          (E_NOT_OK)    : The function has issue while performing this action.
 */
Std_ReturnType CCP_IsCapturedDataReady(uint8 *_capture_status);

/*
 * @Brief               : To read Capture mode value.
 * @Param capture_value : Pointer to the CCP Capture mode value.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Read_Capture_Mode_Value(uint16 *capture_value);
#endif

#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
/*
 * @Brief                 : To check Compare mode Compare status if completed or not.
 * @Param _compare_status : Pointer to the CCP Compare mode data status.
 * @Return Status of the function.
 *          (E_OK)        : The function done successfully.
 *          (E_NOT_OK)    : The function has issue while performing this action.
 */
Std_ReturnType CCP_IsCompareCompleted(uint8 *_compare_status);

/*
 * @Brief               : To read Compare mode value.
 * @Param _ccp_obj      : Pointer to the CCP module configurations. 
 * @Param compare_value 
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Set_Compare_Mode_Value(const ccp_t *_ccp_obj, uint16 compare_value);    
#endif

#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
/*
 * @Brief               : To set duty cycle for PWM mode.
 * @Param _ccp_obj      : Pointer to the CCP module configurations.
 * @Param _duty 
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Set_PWM_Duty(const ccp_t *_ccp_obj, const uint16 _duty);
    
/*
 * @Brief               : To start PWM mode.
 * @Param _ccp_obj      : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Start_PWM(const ccp_t *_ccp_obj);
    
/*
 * @Brief               : To stop PWM mode.
 * @Param _ccp_obj      : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Stop_PWM(const ccp_t *_ccp_obj);
#endif
/***********************************************************************/
#endif	/* HAL_CCP_H */

