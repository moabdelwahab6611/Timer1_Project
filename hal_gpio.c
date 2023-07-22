/* 
 * File     : hal_gpio.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 5:38 PM
 */

/**************************Includes-Section*****************************/
#include "hal_gpio.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/***********Reference to the Data Direction Control Registers***********/
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/**Reference to the Data Latch Register (Read and Write to Data Latch)**/
volatile uint8 *lat_registers[]  = {&LATA , &LATB , &LATC , &LATD , &LATE};
/*****************Reference to the Port Status Register*****************/
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the direction of a specific pin @Ref : direction_t.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/*
 * @Brief                  : To get direction status of a pin.
 * @Param _pin_config      : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param direction_status : Pointer to the pin direction status configurations. 
 * @Return Status of the function.
 *          (E_OK)         : The function done successfully.
 *          (E_NOT_OK)     : The function has issue to perform this action. 
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/* 
 * @Brief              : To write logic 1 or 0 on a pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param logic
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/* 
 * @Brief              : To read logic on a pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param logic        : Pointer to the pin logic status configurations. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/*
 * @Brief              : To toggle the pin logic.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/* 
 * @Brief              : To initialize certain pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

/*
 * @Brief              : To initialize the direction of the whole port.
 * @Param port
 * @Param direction
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

/* 
 * @Brief                  : To get the whole port direction status.
 * @Param port
 * @Param direction_status : Pointer to get whole port direction status configurations. 
 * @Return Status of the function.
 *          (E_OK)         : The function done successfully.
 *          (E_NOT_OK)     : The function has issue to perform this action.
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    if((NULL == direction_status) && (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}
#endif

/* 
 * @Brief              : To write logic 1 or 0 on the whole port.
 * @Param port
 * @Param logic
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif

/* 
 * @Brief              : To read the logic on the whole port.
 * @Param port
 * @Param logic        : Pointer to the read whole port logic configurations. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    Std_ReturnType ret = E_OK;
    if((NULL == logic) && (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *lat_registers[port];
    }
    return ret;
}
#endif

/* 
 * @Brief              : To toggle port logic. 
 * @Param port         
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif
/***********************************************************************/