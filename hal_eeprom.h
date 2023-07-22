/* 
 * File     : hal_eeprom.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 3, 2023, 5:49 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/**************************Includes-Section*****************************/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to access Flash Memory. */
#define ACCESS_FLASH_PROGRAM_MEMORY        1
/* @Brief : Macro to access EEPROM Memory. */
#define ACCESS_EEPROM_PROGRAM_MEMORY       0

/* @Brief : Macro to access Configuration Registers. */
#define ACCESS_CONFIGURATION_REGISTERS     1
/* @Brief : Macro to access Flash and EEPROM Registers. */
#define ACCESS_FLASH_EEPROM_REGISTERS      0

/* @Brief : Macro to allow to writing cycles in Flash and EEPROM memories. */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM    1
/* @Brief : Macro to inhibits  writing cycles in Flash and EEPROM memories. */
#define INHIBITS_WRITE_CYCLES_FLASH_EEPROM 0 

/* @Brief : Macro to initiate writing or reading in or from EEPROM memory. */
#define INITIATE_DATA_EEPROM_WRITE_ERASE   1
/* @Brief : Macro to indicator writing or reading in or from EEPROM memory has been completed. */
#define DATA_EEPROM_WRITE_ERASE_COMPLETED  0

/* @Brief : Macro to initiate reading data from EEPROM memory. */
#define INITIATE_DATA_EEPROM_READ          1
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/

/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To write data in the EEPROM.
 * @Param bAdd
 * @Param bData       
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);

/*
 * @Brief              : To read data from the EEPROM.
 * @Param bAdd
 * @Param bData        : Pointer to access certain data from the EEPROM and read it.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);
/***********************************************************************/
#endif	/* HAL_EEPROM_H */

