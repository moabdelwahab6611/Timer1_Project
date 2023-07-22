/* 
 * File     : ecu_chr_lcd.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 1, 2023, 4:10 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/**************************Includes-Section*****************************/
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to clear Character LCD. */
#define _LCD_CLEAR                      0X01

/* @Brief : Macro to return home. */
#define _LCD_RETURN_HOME                0x02

/* @Brief : Macros Character LCD entry mode Dec and INC  status configuration. */
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07

/* @Brief : Macros for Character LCD cursor position. */
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14

/* @Brief : Macro for Character LCD display position. */
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C

/* @Brief : Macro to turn Character LCD display on and cursor off and underline off. */
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
/* @Brief : Macro to turn Character LCD display on and cursor on and underline off. */
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
/* @Brief : Macro to turn Character LCD display on and cursor off and underline on. */
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
/* @Brief : Macro to turn Character LCD display on and cursor on and underline on. */
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
/* @Brief : Macro to turn Character LCD display off and cursor off. */
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08

/* @Brief : Macros for Character LCD to mode two line selection. */
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

/* @Brief : Macro for Character LCD to start CGRAM. */
#define _LCD_CGRAM_START                0x40
/* @Brief : Macro for Character LCD to start DDRAM. */
#define _LCD_DDRAM_START                0x80

/* @Brief : Macros for Character LCD rows configurations. */
#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : 4-Bit Character LCD configuration. */
typedef struct
{
    pin_config_t lcd_rs;        /* @Brief : 4-Bit Character LCD rs pin configuration. */
    pin_config_t lcd_en;        /* @Brief : 4-Bit Character LCD en pin configuration. */
    pin_config_t lcd_data[4];   /* @Brief : 4-Bit Character LCD data configuration. */
}chr_4bit_lcd_t;

/* @Brief : 8-Bit Character LCD configuration. */
typedef struct
{
    pin_config_t lcd_rs;         /* @Brief : 8-Bit Character LCD rs pin configuration. */
    pin_config_t lcd_en;         /* @Brief : 8-Bit Character LCD en pin configuration. */  
    pin_config_t lcd_data[8];    /* @Brief : 8-Bit Character LCD data configuration. */
}chr_8bit_lcd_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/* 
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the 4-Bit Character LCD OFF or ON.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_intialize(const chr_4bit_lcd_t *lcd);

/* 
 * @Brief              : To send commands to 4-Bit Character LCD command register.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param command
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_command(const chr_4bit_lcd_t *lcd, uint8 command);

/* 
 * @Brief              : To send data to 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param data         : The data that we need to send to the Character LCD.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_4bit_lcd_t *lcd, uint8 data);

/*
 * @Brief              : To send data on 4-Bit Character LCD in specific row and column in accordance of courser position.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param data
 * @Return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_4bit_lcd_t *lcd,uint8 row, uint8 column, uint8 data);

/*
 * @Brief              : To print a string on 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_string(const chr_4bit_lcd_t *lcd, uint8 *str);


/*
 * @Brief              : To print the desired string on 4-Bit Character LCD in specific row and column in accordance of courser position. 
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param str
 * @Return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_4bit_lcd_t *lcd, uint8 row, uint8 column, uint8 *str);

/*
 * @Brief              : To print custom character in specific row and column on 4-Bit Character LCD. 
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param _chr
 * @Param mem_pos
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_4bit_lcd_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos);

/* 
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the 8-Bit Character LCD OFF or ON.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_intialize(const chr_8bit_lcd_t *lcd);

/* 
 * @Brief              : To send commands to 8-Bit Character LCD command register.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param command
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_command(const chr_8bit_lcd_t *lcd, uint8 command);

/* 
 * @Brief              : To send data to 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param data         : The data that we need to send to the Character LCD.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_8bit_lcd_t *lcd, uint8 data);

/*
 * @Brief              : To send data on 8-Bit Character LCD in specific row and column in accordance of courser position.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param data
 * @Return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_8bit_lcd_t *lcd,uint8 row, uint8 column, uint8 data);

/*
 * @Brief              : To print a string on 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_string(const chr_8bit_lcd_t *lcd, uint8 *str);

/*
 * @Brief              : To print the desired string on 8-Bit Character LCD in specific row and column in accordance of courser position. 
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param str
 * @Return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_8bit_lcd_t *lcd, uint8 row, uint8 column, uint8 *str);

/*
 * @Brief              : To print custom character in specific row and column on 8-Bit Character LCD. 
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Param _chr
 * @Param mem_pos
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_8bit_lcd_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos);

/*
 * @Brief              : To convert value of 8-Bits to string. 
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);

/*
 * @Brief              : To convert value of 16-Bits to string.
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);

/*
 * @Brief              : To convert value of 32-Bits to string.
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);
/***********************************************************************/
#endif	/* ECU_CHR_LCD_H */

