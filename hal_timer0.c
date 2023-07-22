/* 
 * File     : hal_timer0.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 7, 2023, 4:08 PM
 */

/**************************Includes-Section*****************************/
#include "hal_timer0.h"
/***********************************************************************/

/********************Data Types Declarations-Section********************/
static uint16 timer0_preload = ZERO_INT;
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR0_InterruptHandler)(void) = NULL;      /* @Brief : Timer0 Interrupt Handler. */
#endif
   
/*
 * @Brief        : Timer0 Pre-scaler configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Prescaler_Config(const timer0_t *_timer);

/*
 * @Brief        : Timer0 Timer or Counter selection configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Mode_Selection(const timer0_t *_timer);

/*
 * @Brief        : Timer0 register size configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Reigster_Size_Config(const timer0_t *_timer);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the Timer0.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Init(const timer0_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        /* @Brief : Disable Timer0. */
        TIMER0_DISABLE_MODULE();
        /* @Brief : Timer0 Pre-scaler configuration. */
        Timer0_Prescaler_Config(_timer);
        /* @Brief : Selection of Timer0 Timer mode or Counter mode. */
        Timer0_Mode_Selection(_timer);
        /* @Brief : Timer0 register configuration. */
        Timer0_Reigster_Size_Config(_timer);
        /* @Brief : Timer0 Pre-load value configuration. */
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);  
        timer0_preload = _timer->timer0_preload_value;
        /* @Brief : Timer0 Interrupt configuration. */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
        /* @Brief : Timer0 Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();        
#endif
#endif 
        /* @Brief : Enable Timer0. */
        TIMER0_ENABLE_MODULE();
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief              : To de-initialize the Timer0.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_DeInit(const timer0_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        /* @Brief : Disable Timer0. */
        TIMER0_DISABLE_MODULE();
        /* @Brief : Timer0 Interrupt configuration. */ 
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
#endif 
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief              : To write value Timer0 counter register.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Param _value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        /* @Brief : Timer0 pre-load value configuration. */
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief              : To read value Timer0 counter register.
 * @Param _timer       : Pointer to the Timer0 module configurations.
 * @Param _value       : Pointer to access value to read it from the register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr0l = ZERO_INT;
    uint8 l_tmr0h = ZERO_INT;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief : Callback pointer to function to Timer0 interrupt service routine.
 */
void TMR0_ISR(void)
{
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);  
    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief        : Timer0 Pre-scaler configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Prescaler_Config(const timer0_t *_timer)
{
    if(TIMER0_ENABLE_PRESCALER_CFG == _timer->prescaler_status_cfg)
    {
        TIMER0_ENABLE_PRESCALER();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_DISABLE_PRESCALER_CFG == _timer->prescaler_status_cfg)
    {
       TIMER0_DISABLE_PRESCALER(); 
    }
    else{/*****Nothing*****/}
}


/*
 * @Brief        : Timer0 Timer or Counter selection configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Mode_Selection(const timer0_t *_timer)
{
    if(TIMER0_TIMER_MODE == _timer->timer0_mode)
    {
        TIMER0_ENABLE_TIMER_MODE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode)
    {
        TIMER0_ENABLE_COUNTER_MODE();
        if(TIMER0_RISING_EDGE_CFG == _timer->timer0_counter_edge)
        {
           TIMER0_ENABLE_RISING_EDGE(); 
        }
        else if(TIMER0_FALLING_EDGEE_CFG == _timer->timer0_counter_edge)
        {
           TIMER0_ENABLE_FALLING_EDGE(); 
        }
        else{/*****Nothing*****/}
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief        : Timer0 register size configuration.
 * @Param _timer : Pointer to the Timer0 module configurations.
 */
static inline void Timer0_Reigster_Size_Config(const timer0_t *_timer)
{
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
       TIMER0_ENABLE_8BIT_REGISTER_MODE(); 
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
       TIMER0_ENABLE_16BIT_REGISTER_MODE(); 
    }
    else{/*****Nothing*****/}
}
/***********************************************************************/