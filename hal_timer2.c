/* 
 * File     : hal_timer2.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 8, 2023, 7:38 PM
 */

/**************************Includes-Section*****************************/
#include "hal_timer2.h"
/***********************************************************************/

/********************Data Types Declarations-Section********************/
static uint8 timer2_preload = ZERO_INT;
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR2_InterruptHandler)(void) = NULL;   /* @Brief : Timer2 Interrupt Handler. */
#endif  
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the Timer2.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable Timer2. */
        TIMER2_DISABLE_MODULE();
        
        /* @Brief : Timer2 pre-scaler configuration. */
        TIMER2_PRRESCALER_SELECTION(_timer->timer2_prescaler_value);
        /* @Brief : Timer2 post-scaler configuration. */
        TIMER2_POSTSCALER_SELECTION(_timer->timer2_postscaler_value);
        /* @Brief : Timer2 pre-load value configuration. */
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
         /* @Brief : Timer2 Interrupt configuration. */ 
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
        /* @Brief : Timer2 Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        /* @Brief : Enable Timer2. */
        TIMER2_ENABLE_MODULE();
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To de-initialize the Timer3.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_DeInit(const timer2_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable Timer2. */
        TIMER2_DISABLE_MODULE();
        /* @Brief : Timer2 Interrupt configuration. */ 
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();      /* @Brief : Disable Interrupt for Timer2. */ 
#endif
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To write value Timer2 counter register.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* Brief : @Timer2 Pre-load configuration. */
        TMR2 = _value;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To read value Timer2 counter register.
 * @Param _timer       : Pointer to the Timer2 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Timer2 Pre-load value configuration. */
        *_value = TMR2;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief : Callback pointer to function to Timer2 interrupt service routine.
 */
void TMR2_ISR(void)
{
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
    else{/*****Nothing*****/}
}
/***********************************************************************/