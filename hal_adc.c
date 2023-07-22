/* 
 * File     : hal_adc.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 5, 2023, 4:31 PM
 */

/**************************Includes-Section*****************************/
#include "hal_adc.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/

/*
 * @brief : Callback pointers for (ADC) interrupt. 
 */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (* ADC_InterruptHandler)(void) = NULL;  /* @Brief : Timer3 Interrupt Handler. */
#endif

/*
 * @Brief      : ADC channel and Port configuration.
 * @Param _adc : Pointer to the ADC module configurations.
 */        
static inline void adc_input_channel_port_config(adc_channel_select_t channel);

/*
 * @Brief      : Select ADC result format.
 * @Param _adc : Pointer to the ADC module configurations.
 */
static inline void select_result_format(const adc_config_t *_adc);

/*
 * @Brief      : Voltage reference configuration.
 * @Param _adc : Pointer to the ADC module configurations.
 */
static inline void configure_voltage_reference(const adc_config_t *_adc);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/

Std_ReturnType ADC_Init(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Disable the ADC. */
        ADC_CONVERTER_DISABLE();
        /* @Brief : Configure the acquisition time. */
        ADCON2bits.ACQT = _adc->acquisition_time;
        /* @Brief : Configure the conversion clock. */
        ADCON2bits.ADCS = _adc->conversion_clock;
        /* @Brief : Configure the default channel. */
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_config(_adc->adc_channel);
        /* @Brief : ADC Interrupt configuration. */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        /* @Brief : ADC Priority configuration. */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority){ADC_HighPrioritySet();}
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority){ADC_LowPrioritySet();}
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif
        /* @Brief : Configure the result format. */
        select_result_format(_adc);
        /* @Brief : Configure the voltage reference. */
        configure_voltage_reference(_adc);
        /* @Brief : Enable the ADC. */      
        ADC_CONVERTER_ENABLE();
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief              : To de-initialize the ADC.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_DeInit(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Disable the ADC. */
        ADC_CONVERTER_DISABLE();
        /* @Brief : Configure the interrupt. */
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
        ret = E_OK;
    }   
    return ret; 
}

/*
 * @Brief              : To select ADC channel.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Param channel
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Configure the default channel. */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_config(channel);  
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief              : To start conversion by ADC.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief                   : To check if conversion by ADC has been completed or not.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param conversion_status : Pointer to the ADC conversion status.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE)); 
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief                   : To check the conversion result.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param conversion_result : Pointer to the ADC conversion result.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_result)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        ret = E_OK;
    }   
    return ret;
}

/*
 * @Brief                   : To get conversion data from ADC.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param channel
 * @Param conversion_result : Pointer to the ADC conversion result.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel, adc_result_t *conversion_result)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_conversion_status = ZERO_INT;
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Select A/D channel. */
        ret = ADC_SelectChannel(_adc, channel);
        /* @Brief : Start ADC conversion. */
        ret = ADC_StartConversion(_adc);
        /* @Brief : Check if conversion is completed. */
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_result);
    }   
    return ret;
}        

/*
 * @Brief               : To start conversion interrupt.
 * @Param _adc          : Pointer to the ADC module configurations.
 * @Param channel
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Select A/D channel. */
        ret = ADC_SelectChannel(_adc, channel);
        /* @Brief : Start ADC conversion. */
        ret = ADC_StartConversion(_adc);
    }   
    return ret;
}

/*
 * @Brief      : ADC channel and Port configuration.
 * @Param _adc : Pointer to the ADC module configurations.
 */ 
static inline void adc_input_channel_port_config(adc_channel_select_t channel)
{
   switch(channel)
   {
       case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA5_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISE_RE0_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISE_RE1_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISE_RE2_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISB_RB2_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISB_RB3_POSN); break;  /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break; /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break; /* @Brief : Disable the digital output driver. */
       case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break; /* @Brief : Disable the digital output driver. */
   }
}

/*
 * @Brief      : Select ADC result format.
 * @Param _adc : Pointer to the ADC module configurations.
 */
static inline void select_result_format(const adc_config_t *_adc)
{
    if(ADC_RESULT_RIGHT == _adc->result_format)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

/*
 * @Brief      : Voltage reference configuration.
 * @Param _adc : Pointer to the ADC module configurations.
 */
static inline void configure_voltage_reference(const adc_config_t *_adc)
{
    if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->result_format)
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }  
}

/*
 * @Brief : Callback pointer to function to ADC interrupt service routine.
 */
void ADC_ISR(void)
{
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler )
    {
        ADC_InterruptHandler();
    }
    else{/*****Nothing*****/}
}
/***********************************************************************/