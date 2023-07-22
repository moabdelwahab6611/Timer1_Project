/* 
 * File     : hal_gpio.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 6:03 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/**************************Includes-Section*****************************/
#include "./pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro that defines Bit-Mask for GPIO. */
#define BIT_MASK  (uint8)1

/* @Brief : Macro that defines Pin Max Number for GPIO. */
#define PORT_PIN_MAX_NUMBER  8
/* @Brief : Macro that defines Port Max Number for GPIO. */
#define PORT_MAX_NUMBER      5

/* @Brief : Macro that defines PortC-Mask for GPIO. */
#define PORTC_MASK           0xFF
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to HWREG configurations for GPIO. */
#define HWREG8(_X)     (*((volatile uint8 *)(_X)))

/* @Brief : Macro function to Set Bit for GPIO. */
#define SET_BIT(REG, BIT_POSN)     (REG |= (BIT_MASK << BIT_POSN))
/* @Brief : Macro function to Clear Bit for GPIO. */
#define CLEAR_BIT(REG, BIT_POSN)   (REG &= ~(BIT_MASK << BIT_POSN))
/* @Brief : Macro function to Toggle Bit for GPIO. */
#define TOGGLE_BIT(REG, BIT_POSN)  (REG ^= (BIT_MASK << BIT_POSN))
/* @Brief : Macro function to Read Bit for GPIO. */
#define READ_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : GPIO pins logic configurations. */
typedef enum
{
    GPIO_LOW = 0,           /* @Brief : GPIO Low Pin Logic configurations. */
    GPIO_HIGH               /* @Brief : GPIO High Pin Logic configurations. */
}logic_t;

/* @Brief : GPIO pins direction configurations. */
typedef enum
{
    GPIO_DIRECTION_OUTPUT = 0,                   /* @Brief : GPIO Output Pin Direction configurations. */
    GPIO_DIRECTION_INPUT                         /* @Brief : GPIO Input Pin Direction configurations. */
}direction_t;

/* @Brief : GPIO pins configurations. */
typedef enum
{
    GPIO_PIN0 = 0,              /* @Brief : GPIO Pin0 Selection. */
    GPIO_PIN1,                  /* @Brief : GPIO Pin1 Selection. */
    GPIO_PIN2,                  /* @Brief : GPIO Pin2 Selection. */
    GPIO_PIN3,                  /* @Brief : GPIO Pin3 Selection. */
    GPIO_PIN4,                  /* @Brief : GPIO Pin4 Selection. */
    GPIO_PIN5,                  /* @Brief : GPIO Pin5 Selection. */
    GPIO_PIN6,                  /* @Brief : GPIO Pin6 Selection. */
    GPIO_PIN7                   /* @Brief : GPIO Pin7 Selection. */
}pin_index_t;

/* @Brief : GPIO ports configurations. */
typedef enum
{
    PORTA_INDEX = 0,            /* @Brief : GPIO PortA Selection. */
    PORTB_INDEX,                /* @Brief : GPIO PortB Selection. */
    PORTC_INDEX,                /* @Brief : GPIO PortC Selection. */
    PORTD_INDEX,                /* @Brief : GPIO PortD Selection. */
    PORTE_INDEX                 /* @Brief : GPIO PortE Selection. */
}port_index_t;

/* @Brief : GPIO configurations. */
typedef struct
{
    uint8 port : 3;      /* @Ref : port_index_t */
    uint8 pin : 3;       /* @Ref : pin_index_t */
    uint8 direction : 1; /* @Ref : direction_t */
    uint8 logic : 1;     /* @Ref : logic_t */
}pin_config_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the direction of a specific pin @Ref : direction_t.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);

/*
 * @Brief                  : To get direction status of a pin.
 * @Param _pin_config      : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param direction_status : Pointer to the pin direction status configurations. 
 * @Return Status of the function.
 *          (E_OK)         : The function done successfully.
 *          (E_NOT_OK)     : The function has issue to perform this action. 
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);

/* 
 * @Brief              : To write logic 1 or 0 on a pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param logic
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);

/* 
 * @Brief              : To read logic on a pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Param logic        : Pointer to the pin logic status configurations. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);

/*
 * @Brief              : To toggle the pin logic.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);

/* 
 * @Brief              : To initialize certain pin.
 * @Param _pin_config  : Pointer to the GPIO module configurations @Ref : pin_config_t. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

/*
 * @Brief              : To initialize the direction of the whole port.
 * @Param port
 * @Param direction
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);

/* 
 * @Brief                  : To get the whole port direction status.
 * @Param port
 * @Param direction_status : Pointer to get whole port direction status configurations. 
 * @Return Status of the function.
 *          (E_OK)         : The function done successfully.
 *          (E_NOT_OK)     : The function has issue to perform this action.
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);

/* 
 * @Brief              : To write logic 1 or 0 on the whole port.
 * @Param port
 * @Param logic
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);

/* 
 * @Brief              : To read the logic on the whole port.
 * @Param port
 * @Param logic        : Pointer to the read whole port logic configurations. 
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);

/* 
 * @Brief              : To toggle port logic. 
 * @Param port         
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
/***********************************************************************/
#endif	/* HAL_GPIO_H */
