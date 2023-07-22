/* 
 * File     : application.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 6:46 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/**************************Includes-Section*****************************/
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/

/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
extern keypad_t keypad1;
extern led_t led1;
extern chr_4bit_lcd_t lcd_1;
extern chr_8bit_lcd_t lcd_2;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
void application_intialize(void);
/***********************************************************************/
#endif	/* APPLICATION_H */

