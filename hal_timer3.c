/* 
 * File     : hal_timer3.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 8, 2023, 11:12 PM
 */

/**************************Includes-Section*****************************/
#include "hal_timer3.h"
/***********************************************************************/

/********************Data Types Declarations-Section********************/
static uint16 timer3_preload = ZERO_INT;
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR3_InterruptHandler)(void) = NULL;    /* @Brief : Timer3 Interrupt Handler. */
#endif
       
/*
 * @Brief        : Timer3 Timer or Counter selection configuration.
 * @Param _timer : Pointer to the Timer3 module configurations.
 */
static inline void Timer3_Mode_Selection(const timer3_t *_timer);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the Timer3.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable Timer3. */
        TIMER3_DISABLE_MODULE();
        /* @Brief : Timer3 pre-scaler configuration. */
        TIMER3_PRESCALER_SELECTION(_timer->timer3_prescaler_value);
        /* @Brief : Selection of Timer3 Timer or Counter modes. */
        Timer3_Mode_Selection(_timer);
        /* @Brief : Timer3 pre-load value configuration. */
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);  
        timer3_preload = _timer->timer3_preload_value;
        /* @Brief : Timer3 Interrupt configuration. */ 
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
        /* @Brief : Timer3 Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        /* @Brief : Enable Timer3. */
        TIMER3_ENABLE_MODULE();
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
Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable Timer3. */
        TIMER3_DISABLE_MODULE();
        /* @Brief : Timer3 Interrupt configuration. */ 
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To write value Timer3 counter register.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Timer3 pre-load value configuration. */
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To read value Timer3 counter register.
 * @Param _timer       : Pointer to the Timer3 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr3l = ZERO_INT;
    uint8 l_tmr3h = ZERO_INT;
    if((NULL == _timer) || NULL == _value)
    {
        ret = E_NOT_OK;
    }
    else
    { 
         /* @Brief : Timer3 pre-load value configuration. */
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief : Callback pointer to function to Timer3 interrupt service routine.
 */
void TMR3_ISR(void)
{
    TIMER3_InterruptFlagClear();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);  
    if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief        : Timer3 Timer or Counter selection configuration.
 * @Param _timer : Pointer to the Timer3 module configurations.
 */
static inline void Timer3_Mode_Selection(const timer3_t *_timer)
{
    if(TIMER3_TIMER_MODE == _timer->timer3_mode)
    {
        TIMER3_ENABLE_TIMER_MODE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode)
    {
        TIMER3_ENABLE_COUNTER_MODE();
        if(TIMER3_ASYNCHRONOUS_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ENABLE_ASYNCHRONOUS_COUNTER_MODE();
        }
        else if(TIMER3_SYNCHRONOUS_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ENABLE_SYNCHRONOUS_COUNTER_MODE();
        }
        else{/*****Nothing*****/}
    }
    else{/*****Nothing*****/}
}
/***********************************************************************/