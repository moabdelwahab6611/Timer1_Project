/* 
 * File     : ecu_chr_lcd.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 1, 2023, 4:10 PM
 */

/**************************Includes-Section*****************************/
#include "ecu_chr_lcd.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief              :  Used to send commands for 4-Bits Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param _data_command.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_send_4bits(const chr_4bit_lcd_t *lcd, uint8 _data_command);

/*
 * @Brief              : To send enable signal for 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_4bit_lcd_t *lcd);

/*
 * @Brief              : To set cursor of 4-Bit Character LCD in specific column and row.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_4bit_lcd_t *lcd, uint8 row, uint8 coulmn);

/*
 * @Brief              : To send enable signal for 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_8bit_lcd_t *lcd);

/*
 * @Brief              : To set cursor of 8-Bit Character LCD in specific column and row.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_8bit_lcd_t *lcd, uint8 row, uint8 coulmn);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/* 
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the 4-Bit Character LCD OFF or ON.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_intialize(const chr_4bit_lcd_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_intialize(&(lcd->lcd_rs)); 
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INT; l_data_pins_counter < 4; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

/* 
 * @Brief              : To send commands to 4-Bit Character LCD command register.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param command
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_command(const chr_4bit_lcd_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/* 
 * @Brief              : To send data to 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param data         : The data that we need to send to the Character LCD.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_4bit_lcd_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

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
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_4bit_lcd_t *lcd,uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

/*
 * @Brief              : To print a string on 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_4bit_send_string(const chr_4bit_lcd_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_4bit_send_string_pos(const chr_4bit_lcd_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
                                         const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = 0; lcd_counter <= 7; ++lcd_counter)
        {
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/* 
 * @Brief              : Initialize the assigned pin to be OUTPUT and turn the 8-Bit Character LCD OFF or ON.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_intialize(const chr_8bit_lcd_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INT; l_data_pins_counter < 8; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    return ret;
}

/* 
 * @Brief              : To send commands to 8-Bit Character LCD command register.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param command
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_command(const chr_8bit_lcd_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
       
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (command >> l_pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/* 
 * @Brief              : To send data to 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param data         : The data that we need to send to the Character LCD.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_8bit_lcd_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(l_pin_counter=0; l_pin_counter<8; ++l_pin_counter)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (data >> l_pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_8bit_lcd_t *lcd,uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

/*
 * @Brief              : To print a string on 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD configurations.
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType lcd_8bit_send_string(const chr_8bit_lcd_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_string_pos(const chr_8bit_lcd_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_string(lcd, str);
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_custom_char(const chr_8bit_lcd_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = 0; lcd_counter <= 7; ++lcd_counter)
        {
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/*
 * @Brief              : To convert value of 8-Bits to string. 
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/*
 * @Brief              : To convert value of 16-Bits to string.
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
}

/*
 * @Brief              : To convert value of 32-Bits to string.
 * @Param value
 * @Param str
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}

/*
 * @Brief              :  Used to send commands for 4-Bits Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param _data_command.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_send_4bits(const chr_4bit_lcd_t *lcd, uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
    return ret;
}

/*
 * @Brief              : To send enable signal for 4-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_4bit_lcd_t *lcd)
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    return ret;
}

/*
 * @Brief              : To send enable signal for 8-Bit Character LCD.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_8bit_lcd_t *lcd)
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    return ret;
}

/*
 * @Brief              : To set cursor of 8-Bit Character LCD in specific column and row.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_8bit_lcd_t *lcd, uint8 row, uint8 coulmn)
{
    Std_ReturnType ret = E_OK;
    coulmn--;
    switch(row)
    {    
        case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80 + coulmn)); break; 
        
        case ROW2 : ret = lcd_8bit_send_command(lcd, (0xc0 + coulmn)); break; 
        
        case ROW3 : ret = lcd_8bit_send_command(lcd, (0x94 + coulmn)); break; 
        
        case ROW4 : ret = lcd_8bit_send_command(lcd, (0xd4 + coulmn)); break; 
        
        default : ;
    }
    return ret;
}

/*
 * @Brief              : To set cursor of 4-Bit Character LCD in specific column and row.
 * @Param lcd          : Pointer to the Character LCD module configurations.
 * @Param row          : To select which row you need to print your character.
 * @Param coulmn       : To select which column you need to print your character.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_4bit_lcd_t *lcd, uint8 row, uint8 coulmn)
{
    Std_ReturnType ret = E_OK;
    coulmn--;
    switch(row)
    {
        case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
        
        case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0 + coulmn)); break;
        
        case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
        
        case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + coulmn));  break;
        
        default : ;
    }
    return ret;
}
/***********************************************************************/