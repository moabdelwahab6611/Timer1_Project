/* 
 * File     : hal_eeprom.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 3, 2023, 5:49 PM
 */

/**************************Includes-Section*****************************/
#include "hal_eeprom.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To write data in the EEPROM.
 * @Param bAdd
 * @Param bData       
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData)
{
    Std_ReturnType ret = E_OK;
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    EEDATA = bData;
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_REGISTERS;
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    INTERRUPT_GlobalInterruptDisable();
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    while(EECON1bits.WR);
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES_FLASH_EEPROM;
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

/*
 * @Brief              : To read data from the EEPROM.
 * @Param bAdd
 * @Param bData        : Pointer to access certain data from the EEPROM and read it.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData)
{
   Std_ReturnType ret = E_NOT_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_REGISTERS;
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        *bData = EEDATA;
       ret = E_OK; 
    }
   return ret; 
}
/***********************************************************************/