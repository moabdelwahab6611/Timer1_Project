/* 
 * File     : ecu_button.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 27, 2023, 1:49 AM
 */

/**************************Includes-Section*****************************/
#include "ecu_button.h"
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialize the assigned pin to be Input.
 * @Param btn          : Pointer to the Push Button configurations.
 * @Return  Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType button_initialize(const button_t *btn)
{
    Std_ReturnType ret = E_OK;
    if(NULL == btn)
	{
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(btn->button_pin)); /* @Brief : Initialize the button pin direction configuration. */
    }
    return ret;
}

/*
 * @Brief              : Read the state of the Push Button.
 * @Param btn          : Pointer to the Push Button configurations.
 * @Param btn_state    : Pointer to the Push Button status configurations (@Ref button_state_t). 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state)
{
    Std_ReturnType ret = E_NOT_OK;
    logic_t Pin_Logic_Status = GPIO_LOW;
    if((NULL == btn) || (NULL == btn_state))
	{
        ret = E_NOT_OK;
    }
    else
	{
        gpio_pin_read_logic(&(btn->button_pin), &Pin_Logic_Status); /* @Brief : To read pin logic. */
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
		{
            /* @Brief : Button Active High configuration. */
            if(GPIO_HIGH == Pin_Logic_Status) 
			{
                *btn_state = BUTTON_PRESSED;   /* @Brief : Button pressed status. */
            }
            else
			{
                *btn_state = BUTTON_RELEASED;  /* @Brief : Button released status. */
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
		{
            /* @Brief : Button Active Low configuration. */
            if(GPIO_HIGH == Pin_Logic_Status)
			{
                *btn_state = BUTTON_RELEASED;  /* @Brief : Button pressed status. */
            }
            else
			{
                *btn_state = BUTTON_PRESSED;   /* @Brief : Button released status. */
            }
        }
        else {/*****Nothing*****/}
        ret = E_OK;
    }
    return ret;
}
/***********************************************************************/