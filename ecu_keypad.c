/* 
 * File     : ecu_keypad.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 31, 2023, 6:50 PM
 */

/**************************Includes-Section*****************************/
#include "ecu_keypad.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : KeyPad rows and columns assigned values.
 */
static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] =
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be OUTPUT or INPUT.
 * @Param _keypad_obj  : Pointer to the KeyPad module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = ZERO_INT;
    uint8 columns_counter = ZERO_INT;
    if(NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = ZERO_INT; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
           ret = gpio_pin_intialize(&(_keypad_obj->keypad_rows_pins[rows_counter])); 
        }
        for(columns_counter = ZERO_INT; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
        {
           ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

/*
 * @Brief              : To get the value from a certain row or column.
 * @Param _keypad_obj  : Pointer to the KeyPad module configurations.
 * @Param value
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_rows_counter = ZERO_INT;
    uint8 l_columns_counter = ZERO_INT;
    uint8 l_counter = ZERO_INT;
    uint8 column_logic = ZERO_INT;
    if((NULL == _keypad_obj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(l_rows_counter = ZERO_INT; l_rows_counter < ECU_KEYPAD_ROWS; l_rows_counter++)
        {
            for(l_counter = ZERO_INT; l_counter < ECU_KEYPAD_ROWS; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins [l_counter]), GPIO_LOW);
            }
            
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins [l_rows_counter]), GPIO_HIGH);
            __delay_ms(10);
            for(l_columns_counter = ZERO_INT; l_columns_counter < ECU_KEYPAD_COLUMNS; l_columns_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = btn_values[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return ret;
}
/***********************************************************************/