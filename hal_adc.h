/* 
 * File     : hal_adc.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 5, 2023, 4:31 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/**************************Includes-Section*****************************/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_adc_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/*
 * @Brief : Analog-To-Digital port configuration control.
 * @Note  : Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *          When ADC_AN4_ANALOG_FUNCTIONALITY is configured this means that, 
 *          AN4, AN3, AN2, AN1, AN0 are analog functionality.
 *          @Ref : Analog-To-Digital port configuration control.
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY  0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

/* @Brief : Macro for ADC A/D Right Result Format. */
#define ADC_RESULT_RIGHT   0x01U
/* @Brief : Macro for ADC A/D Left Result Format. */
#define ADC_RESULT_LEFT    0x00U

/* @Brief : Macro to enable Voltage reference for ADC. */
#define ADC_VOLTAGE_REFERENCE_ENABLED    0x01U
/* @Brief : Macro to disable Voltage reference for ADC. */
#define ADC_VOLTAGE_REFERENCE_DISABLED   0x00U

/* @Brief : Macro to give indication for ADC conversion is completed. */
#define ADC_CONVERSION_COMPLETED  1
/* @Brief : Macro to give indication for ADC conversion is In-Progeress. */
#define ADC_CONVERSION_INPROGRESS 0
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/*
 * @Brief : A/D conversion status. 
 * @Note  : A/D conversion in progress.  
 *          A/D in idle State.
 */ 
#define ADC_CONVERSION_STATUS()(ADCON0bits.GO_nDONE)

/* @Brief : Macro function for ADC to start A/D conversion. */
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)

/*
 * @Brief : Analog-To-Digital control.
 * @Note  : ADC_CONVERTER_ENABLE() : To enable the Analog-To-Digital.
 *          ADC_CONVERTER_DISABLE() : To disable the Analog-To-Digital.
 */
#define ADC_CONVERTER_ENABLE()  (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)

/*
 * @Brief : Voltage reference configuration.
 * @Note  : ADC_ENABLE_VOLTAGE_REFERENCE() : Voltage reference : Vref+ & Vref-.
 *          ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage reference : VSS & VDD.
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()   do{ADCON1bits.VCFG1 = 1;\
                                            ADCON1bits.VCFG0 = 1;\
                                         }while(0)

#define ADC_DISABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 0;\
                                            ADCON1bits.VCFG0 = 0;\
                                         }while(0)

/*
 * @Brief : Analog-To-Digital port configuration control.
 * @Note  : Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *          When ADC_AN4_ANALOG_FUNCTIONALITY is configured this means that, 
 *          AN4, AN3, AN2, AN1, AN0 are analog functionality.
 *          @Ref : Analog-To-Digital port configuration control.
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/* @Brief : Macro function for ADC A/D Right Result Format. */
#define ADC_RESULT_RIGHT_FORMAT() (ADCON2bits.ADFM = 1)
/* @Brief : Macro function for ADC A/D Left Result Format. */
#define ADC_RESULT_LEFT_FORMAT()  (ADCON2bits.ADFM = 0)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : ADC Analog Channel Selection configuration. */
typedef enum
{
   ADC_CHANNEL_AN0 = 0,     /* @Brief : ADC Analog Channel 0 Selection. */
   ADC_CHANNEL_AN1,         /* @Brief : ADC Analog Channel 1 Selection. */
   ADC_CHANNEL_AN2,         /* @Brief : ADC Analog Channel 2 Selection. */
   ADC_CHANNEL_AN3,         /* @Brief : ADC Analog Channel 3 Selection. */
   ADC_CHANNEL_AN4,         /* @Brief : ADC Analog Channel 4 Selection. */
   ADC_CHANNEL_AN5,         /* @Brief : ADC Analog Channel 5 Selection. */
   ADC_CHANNEL_AN6,         /* @Brief : ADC Analog Channel 6 Selection. */
   ADC_CHANNEL_AN7,         /* @Brief : ADC Analog Channel 7 Selection. */
   ADC_CHANNEL_AN8,         /* @Brief : ADC Analog Channel 8 Selection. */
   ADC_CHANNEL_AN9,         /* @Brief : ADC Analog Channel 9 Selection. */
   ADC_CHANNEL_AN10,        /* @Brief : ADC Analog Channel 10 Selection. */
   ADC_CHANNEL_AN11,        /* @Brief : ADC Analog Channel 11 Selection. */
   ADC_CHANNEL_AN12         /* @Brief : ADC Analog Channel 12 Selection. */
}adc_channel_select_t;

/*
 * @Brief : To select A/D Acquisition time.
 * @Note  : Acquisition time (sampling time) is the time required for the (ADC)
 *          to capture the input voltage during sampling.
 * @Note  : Acquisition time of a Successive Approximation Register (SAR) (ADC) is the amount of time
 *          that required to charge the holding capacitor (CHOLD) on the front end of an (ADC).
 */
typedef enum
{
   ADC_0_TAD = 0,
   ADC_2_TAD,  
   ADC_4_TAD,
   ADC_6_TAD,
   ADC_8_TAD,
   ADC_12_TAD,
   ADC_16_TAD,  
   ADC_20_TAD,        
}adc_acquisition_time_t;

/* 
 * @Brief : To select A/D conversion clock.
 * @Note  : If the A/D FRC clock selected, a delay of one TCY (instruction cycle)
 *          is added before the A/D clock starts.
 * @Note  : This allow the SLEEP instruction to be executed before starting conversion. 
 */
typedef enum 
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8, 
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64       
}adc_conversion_clock_t;

/* @Brief : ADC configuration. */
typedef struct
{
    #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);        /* @Brief : ADC Interrupt Handler. */
    interrupt_priority_cfg priority;            /* @Brief : ADC Priority configurations. */
    #endif 
    adc_acquisition_time_t acquisition_time;    /* @Brief : ADC Acquisition time configuration @Ref : adc_acquisition_time_t . */
    adc_conversion_clock_t conversion_clock;    /* @Brief : ADC Conversion  Clock configuration @Ref : adc_conversion_clock_t . */
    adc_channel_select_t   adc_channel;         /* @Brief : ADC Channel Selection configuration @Ref : adc_channel_select_t . */
    uint8 voltage_reference : 1;                /* @Brief : ADC Voltage Reference configuration @Ref : Voltage reference configuration . */
    uint8 result_format     : 1;                /* @Ref : ADC To A/D result format Selection configuration. */
    uint8 ADC_Reserved      : 6;                /* @Brief : ADC Reserved Bits. */
}adc_config_t;

typedef uint16 adc_result_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the ADC.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_Init(const adc_config_t *_adc);

/*
 * @Brief              : To de-initialize the ADC.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_DeInit(const adc_config_t *_adc);

/*
 * @Brief              : To select ADC channel.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Param channel
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel);

/*
 * @Brief              : To start conversion by ADC.
 * @Param _adc         : Pointer to the ADC module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc);

/*
 * @Brief                   : To check if conversion by ADC has been completed or not.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param conversion_status : Pointer to the ADC conversion status.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status);

/*
 * @Brief                   : To check the conversion result.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param conversion_result : Pointer to the ADC conversion result.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_result);

/*
 * @Brief                   : To get conversion data from ADC.
 * @Param _adc              : Pointer to the ADC module configurations.
 * @Param channel
 * @Param conversion_result : Pointer to the ADC conversion result.
 * @Return Status of the function.
 *          (E_OK)          : The function done successfully.
 *          (E_NOT_OK)      : The function has issue while performing this action.
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel, adc_result_t *conversion_result);

/*
 * @Brief               : To start conversion interrupt.
 * @Param _adc          : Pointer to the ADC module configurations.
 * @Param channel
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel);
/***********************************************************************/
#endif	/* HAL_ADC_H */

