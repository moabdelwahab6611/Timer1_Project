/* 
 * File     : hal_ccp.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 10, 2023, 3:50 PM
 */

/**************************Includes-Section*****************************/
#include "hal_ccp.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;          /* @Brief : CCP1 Interrupt Handler. */
#endif
    
/*
 * @Brief : Callback pointer to function.
 */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;          /* @Brief : CCP2 Interrupt Handler. */
#endif
     
/*
 * @Brief          : PMW mode configuration for CCP1 or CCP2.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */   
static void CCP_PMW_MODE_CONFIG(const ccp_t *_ccp_obj);   

/*
 * @Brief          : To enable or disable the interrupt feature for CCP1 or CCP2.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);

/*
 * @Brief          : Timer selection in the Capture or Compare modes clock source for the CCP module.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */
static void CCP_Mode_Timer_Selection(const ccp_t *_ccp_obj);

/*
 * @Brief              : CCP1 or CCP2 Capture mode config.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj);

/*
 * @Brief              : CCP1 or CCP2 Compare mode config.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the CCP.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        if(CCP1_INST == _ccp_obj->ccp_inst)
        {
            /* @Brief : Disable CCP1. */
            CCP1_SET_MODE(CCP_DISABLE_MODULE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst)
        {
            /* @Brief : Disable CCP2. */
            CCP2_SET_MODE(CCP_DISABLE_MODULE);
        }
        else{/*****Nothing*****/}
        
        /* @Brief : CCP Capture mode initialization. */
        if(CCP_CAPTURE_MODE_CFG == _ccp_obj->ccp1_mode)
        {
            ret = CCP_Capture_Mode_Config(_ccp_obj);
        }
        /* @Brief : CCP Compare mode initialization. */
        else if(CCP_COMPARE_MODE_CFG == _ccp_obj->ccp1_mode)
        {
            ret = CCP_Compare_Mode_Config(_ccp_obj);
        }
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
        /* @Brief : CCP PWM mode initialization. */
        else if(CCP_PWM_MODE_CFG == _ccp_obj->ccp1_mode)
        {
            
        }
        else{/*****Nothing*****/}
#endif
        /* @Brief : CCP pin configurations. */
        ret = gpio_pin_intialize(&(_ccp_obj->ccp_pin));
        /* @Brief : CCP interrupt configurations for CCP1 and CCP2. */
        CCP_Interrupt_Config(_ccp_obj);
        /* @Brief : CCP PWM mode configurations for CCP1 and CCP2. */
        CCP_PMW_MODE_CONFIG(_ccp_obj);
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To de-initialize the CCP.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        if(CCP1_INST == _ccp_obj->ccp_inst)
            {
                CCP1_SET_MODE(CCP_DISABLE_MODULE);  /* @Brief : Disable CCP1. */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP1_InterruptDisable();            /* @Brief : Interrupt configuration. */
#endif
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst)
            {
                CCP2_SET_MODE(CCP_DISABLE_MODULE);  /* @Brief : Disable CCP2. */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP2_InterruptDisable();            /* @Brief : Interrupt configuration. */
#endif
            }
            else{/*****Nothing*****/}        
        ret = E_OK;
    }
    return ret;  
}

#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
/*
 * @Brief                 : To check Capture mode data status.
 * @Param _capture_status : Pointer to the CCP Capture mode data status.
 * @Return Status of the function.
 *          (E_OK)        : The function done successfully.
 *          (E_NOT_OK)    : The function has issue while performing this action.
 */
Std_ReturnType CCP_IsCapturedDataReady(uint8 *_capture_status)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _capture_status)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        if(CCP_CAPTURE_MODE_READY == PIR1bits.CCP1IF)
        {
            *_capture_status = CCP_CAPTURE_MODE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
            *_capture_status = CCP_CAPTURE_MODE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief               : To read Capture mode value.
 * @Param capture_value : Pointer to the CCP Capture mode value.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Read_Capture_Mode_Value(uint16 *capture_value)
{
    Std_ReturnType ret = E_NOT_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    
    if(NULL == capture_value)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        capture_temp_value.ccpr_low = CCPR1L;
        capture_temp_value.ccpr_high = CCPR1H;
        *capture_value = capture_temp_value.ccpr_16bit;
        ret = E_OK;
    }
    return ret;
}
#endif

#if(CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
/*
 * @Brief                 : To check Compare mode Compare status if completed or not.
 * @Param _compare_status : Pointer to the CCP Compare mode data status.
 * @Return Status of the function.
 *          (E_OK)        : The function done successfully.
 *          (E_NOT_OK)    : The function has issue while performing this action.
 */
    Std_ReturnType CCP_IsCompareCompleted(uint8 *_compare_status)
    {
        Std_ReturnType ret = E_NOT_OK;
        if(NULL == _compare_status)
        {
            ret = E_NOT_OK;
        }
        else
        { 
        if(CCP_COMPARE_MODE_READY == PIR1bits.CCP1IF)
        {
            *_compare_status = CCP_COMPARE_MODE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
            *_compare_status = CCP_COMPARE_MODE_NOT_READY;
        }
            ret = E_OK;
        }
        return ret; 
    }

/*
 * @Brief               : To read Compare mode value.
 * @Param _ccp_obj      : Pointer to the CCP module configurations. 
 * @Param compare_value 
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Set_Compare_Mode_Value(const ccp_t *_ccp_obj, uint16 compare_value)
{
    Std_ReturnType ret = E_NOT_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    
    if(NULL == _ccp_obj)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        capture_temp_value.ccpr_16bit = compare_value;
   
        if(CCP1_INST == _ccp_obj->ccp_inst)
        {
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;  
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst)
        {
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;
        }
        else{/*****Nothing*****/}
        ret = E_OK;
    }
    return ret; 
}    
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
Std_ReturnType CCP_Set_PWM_Duty(const ccp_t *_ccp_obj, const uint16 _duty)
{
    Std_ReturnType ret = E_NOT_OK;
    uint16 l_duty_temp = 0;
    if(NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        l_duty_temp = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
            
        if(CCP1_INST == _ccp_obj->ccp_inst)
        {
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst)
        {
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else{/*****Nothing*****/}
            ret = E_OK;
        }

        return ret;
    }
    
/*
 * @Brief               : To start PWM mode.
 * @Param _ccp_obj      : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
Std_ReturnType CCP_Start_PWM(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        if(CCP1_INST == _ccp_obj->ccp_inst)
        {
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst)
        {
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{/*****Nothing*****/}
        ret = E_OK;
    }
    return ret;  
}
    
/*
 * @Brief               : To stop PWM mode.
 * @Param _ccp_obj      : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)      : The function done successfully.
 *          (E_NOT_OK)  : The function has issue while performing this action.
 */
    Std_ReturnType CCP_Stop_PWM(const ccp_t *_ccp_obj)
    {
        Std_ReturnType ret = E_NOT_OK;
        if(NULL == _ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        { 
            if(CCP1_INST == _ccp_obj->ccp_inst)
            {
                CCP1CONbits.CCP1M = CCP_DISABLE_MODULE;
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst)
            {
                CCP2CONbits.CCP2M = CCP_DISABLE_MODULE;
            }
            else{/*****Nothing*****/}
        }
        ret = E_OK;
        return ret;  
    }
#endif
    
/*
 * @Brief : Callback pointer to function to CCP1 interrupt service routine.
 */
void CCP1_ISR(void)
{
    CCP1_InterruptFlagClear(); 
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief : Callback pointer to function to CCP2 interrupt service routine.
 */
void CCP2_ISR(void)
{
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
    else{/*****Nothing*****/}
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
/*
 * @Brief          : PMW mode configuration for CCP1 or CCP2.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */
 static void CCP_PMW_MODE_CONFIG(const ccp_t *_ccp_obj)
 {
    if(CCP1_INST == _ccp_obj->ccp_inst)
    {
        /* Brief : CCP1 PWM mode variant initialization. */
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant)
        {
            CCP1_SET_MODE(CCP_PWM_MODE);
        }  
        else{/*****Nothing*****/}
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst)
    {
        /* Brief : CCP2 PWM mode variant initialization. */
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant)
        {
            CCP2_SET_MODE(CCP_PWM_MODE);
        }  
        else{/*****Nothing*****/}
    }
    else{/*****Nothing*****/}
            
            
       /* Brief : CCP PWM mode frequency initialization. */
    PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->pwm_frequency * 4.0 * _ccp_obj->timer2_prescaler_value * 
                   _ccp_obj->timer2_postscaler_value)) - 1);
 }
#endif

/*
 * @Brief          : To enable or disable the interrupt feature for CCP1 or CCP2.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj)
{
    /* @Brief : CCP1 Interrupt configuration. */ 
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
        
    /* @Brief : CCP1 Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable(); 
    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority)
    {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority)
    {
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    }
    else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif   
        
    /* Brief : CCP2 Interrupt configuration. */ 
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptEnable();
    CCP2_InterruptFlagClear();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
        
    /* Brief : CCP2 Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable(); 
    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP2_priority)
    {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority)
    {
        INTERRUPT_GlobalInterruptLowEnable();
        CCP2_LowPrioritySet();
    }
    else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif                                  
}

/*
 * @Brief          : Timer selection in the Capture or Compare modes clock source for the CCP module.
 * @Param _ccp_obj : Pointer to the CCP module configurations.
 */
static void CCP_Mode_Timer_Selection(const ccp_t *_ccp_obj)
{
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer)
    {
        /* @Brief : Timer3 is the Capture clock source for the CCP module. */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    
    else if (CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer)
    {
        /* @Brief : Timer1 is the Capture clock source for the CCP1 and Timer3 for the CCP2 module. */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if (CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer)
    {
        /* @Brief : Timer1 is the Capture clock source for the CCP module. */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief              : CCP1 or CCP2 Capture mode config.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == _ccp_obj->ccp_inst)
    {
        /* @Brief : CCP1 Capture mode variants initialization. */
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : 
            CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_1_RISING_EDGE : 
            CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_4_RISING_EDGE : 
            CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_16_FALLING_EDGE : 
            CCP1_SET_MODE(CCP_CAPTURE_MODE_16_FALLING_EDGE);
            break;    
                
            default : ret = E_NOT_OK; /*****Not supported variant*****/
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst)
    {
        /* @Brief : CCP2 Capture mode variants initialization. */
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : 
            CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_1_RISING_EDGE : 
            CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_4_RISING_EDGE : 
            CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
            break;
                
            case CCP_CAPTURE_MODE_16_FALLING_EDGE : 
            CCP2_SET_MODE(CCP_CAPTURE_MODE_16_FALLING_EDGE);
            break;    
                
            default : ret = E_NOT_OK; /*****Not supported variant*****/
        }
    }  
    else{/*****Nothing*****/}
    /* @Brief : CCP1 or CCP2 Capture mode Timer clock source selection. */
    CCP_Mode_Timer_Selection(_ccp_obj);
    return ret;
}

/*
 * @Brief              : CCP1 or CCP2 Compare mode config.
 * @Param _ccp_obj     : Pointer to the CCP module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == _ccp_obj->ccp_inst)
    {
        /* @Brief : CCP1 Compare mode variants initialization. */
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW : 
            CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
            break;
                
            case CCP_COMPARE_MODE_SET_PIN_HIGH : 
            CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
            break;
                
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : 
            CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
            break;
                
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : 
            CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
            break;    
                
            case CCP_COMPARE_MODE_GEN_EVENT : 
            CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
            break;
                
            default : ret = E_NOT_OK; /*****Not supported variant*****/
            } 
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst)
    {
        /* @Brief : CCP2 Compare mode variants initialization. */
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW : 
            CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
            break;
                
            case CCP_COMPARE_MODE_SET_PIN_HIGH : 
            CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
            break;
                
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : 
            CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
            break;
                
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : 
            CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
            break;    
                
            case CCP_COMPARE_MODE_GEN_EVENT : 
            CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
            break;
                
            default : ret = E_NOT_OK; /*****Not supported variant*****/
        }
    }  
    else{/*****Nothing*****/}
    /* @Brief : CCP1 or CCP2 Compare mode Timer clock source selection. */
    CCP_Mode_Timer_Selection(_ccp_obj);
    return ret;
}
/***********************************************************************/