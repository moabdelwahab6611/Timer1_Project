/* 
 * File     : hal_i2c.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 17, 2023, 4:19 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to enable MSSP I2C module. */
#define MSSP_I2C_ENABLE_MODULE       1
/* @Brief : Macro to disable MSSP I2C module. */
#define MSSP_I2C_DISABLE_MODULE      0

/* @Brief : Macro to enable Slew Rate for MSSP I2C. */
#define MSSP_I2C_ENABLE_SLEW_RATE    1
/* @Brief : Macro to disable Slew Rate for MSSP I2C. */
#define MSSP_I2C_DISABLE_SLEW_RATE   0

/* @Brief : Macro to enable SMBus for MSSP I2C. */
#define MSSP_I2C_ENABLE_SMBUS        1
/* @Brief : Macro to disable SMBus for MSSP I2C. */
#define MSSP_I2C_DISABLE_SMBUS       0

/* @Brief : Macro to slave data indication to MSSP I2C. */
#define MSSP_I2C_LAST_BYTE_DATA      1
/* @Brief : Macro to slave address indication to MSSP I2C. */
#define MSSP_I2C_LAST_BYTE_ADDRESS   0

/* @Brief : Macro for stop bit indication on MSSP I2C bus for a certain slave. */
#define MSSP_I2C_STOP_BIT_DETECTED           1
/* @Brief : Macro for stop bit indication on MSSP I2C bus for a certain slave. */
#define MSSP_I2C_STOP_BIT_NOT_DETECTED       0

/* @Brief : Macro for start bit indication on MSSP I2C bus for a certain slave. */
#define MSSP_I2C_START_BIT_DETECTED           1
/* @Brief : Macro for start bit indication on MSSP I2C bus for a certain slave. */
#define MSSP_I2C_START_BIT_NOT_DETECTED       0

/* @Brief : Macro for MSSP I2C to be in master mode. */
#define MSSP_I2C_MASTER_MODE  1
/* @Brief : Macro for MSSP I2C to be in slave mode. */
#define MSSP_I2C_SLAVE_MODE   0

/* @Brief : Macro for MSSP I2C master synchronous serial port mod selection. */
#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS                        0x06U
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS                       0x07U
#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS_SS_ENABLE_INTERRUPT    0x0EU
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS_SS_ENABLE_INTERRUPT   0x0FU
#define MSSP_I2C_MASTER_MODE_DEFINED_CLOCK                      0x08U
#define MSSP_I2C_MASTER_MODE_FIRMWARE_CONTROLLED                0x09U

/* @Brief : Macro to enable General Call for MSSP I2C. */
#define MSSP_I2C_ENABLE_GENERAL_CALL  1
/* @Brief : Macro to disable General Call for MSSP I2C. */
#define MSSP_I2C_DISABLE_GENERAL_CALL 0

/* @Brief : Macro to enable master mode receive for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_ENABLE_RECEIVE   1
/* @Brief : Macro to disable master mode receive for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_DISABLE_RECEIVE  0

/* @Brief : Macro that defines master mode receive acknowledge status bit for MSSP I2C. */
#define MSSP_I2C_ACK_RECEIVED_FROM_SLAVE      0
/* @Brief : Macro that defines master mode receive acknowledge status bit for MSSP I2C. */
#define MSSP_I2C_ACK_NOT_RECEIVED_FROM_SLAVE  1

/* @Brief : Macro that defines master mode receive acknowledge data bit for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_SEND_ACK         0
/* @Brief : Macro that defines master mode receive acknowledge data bit for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_SEND_NACK        1
/***********************************************************************/

/******************Macro Function Declarations-Section******************/
/* @Brief : Macro function to enable MSSP I2C module. */
#define MSSP_I2C_ENABLE_MODULE_CFG()               (SSPCON1bits.SSPEN = 1)
/* @Brief : Macro function to disable MSSP I2C module. */
#define MSSP_I2C_DISABLE_MODULE_CFG()              (SSPCON1bits.SSPEN = 0)

/* @Brief : Macro function to enable Slew Rate for MSSP I2C. */
#define MSSP_I2C_ENABLE_SLEW_RATE_CFG()            (SSPSTATbits.SMP = 1)
/* @Brief : Macro function to disable Slew Rate for MSSP I2C. */
#define MSSP_I2C_DISABLE_SLEW_RATE_CFG()           (SSPSTATbits.SMP = 0)

/* @Brief : Macro function to enable SMBus for MSSP I2C. */
#define MSSP_I2C_ENABLE_SMBUS_CFG()                (SSPSTATbits.CKE = 1)
/* @Brief : Macro function to disable SMBus for MSSP I2C. */
#define MSSP_I2C_DISABLE_SMBUS_CFG()               (SSPSTATbits.CKE = 0)

/* @Brief : Macro function to enable General Call for MSSP I2C. */
#define MSSP_I2C_ENABLE_GENERAL_CALL_CFG()         (SSPCON2bits.GCEN = 1)
/* @Brief : Macro function to disable General Call for MSSP I2C. */
#define MSSP_I2C_DISABLE_GENERAL_CALL_CFG()        (SSPCON2bits.GCEN = 0)

/* @Brief : Macro function to enable master mode receive for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_ENABLE_RECEIVE_CFG()  (SSPCON2bits.RCEN = 1)
/* @Brief : Macro function to disable master mode receive for MSSP I2C. */
#define MSSP_I2C_MASTER_MODE_DISABLE_RECEIVE_CFG() (SSPCON2bits.RCEN = 0)

/* @Brief : Macro function to enable clock stretch for MSSP I2C. */
#define MSSP_I2C_CLOCK_STRETCH()                   (SSPCON1bits.CKP = 0)
/* @Brief : Macro function to release clock for MSSP I2C. */
#define MSSP_I2C_RELEASE_CLOCK()                   (SSPCON1bits.CKP = 1)
/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : MSSP I2C configuration. */
typedef struct
{
    uint8 mssp_i2c_mod_cfg;                  /* @Brief : MSSP I2C master synchronous serial port mod selection. */
    uint8 mssp_i2c_slave_address;            /* @Brief : MSSP I2C slave address selection. */
    uint8 mssp_i2c_mod : 1;                  /* @Brief : MSSP I2C master or slave mod selection. */
    uint8 mssp_i2c_slew_rate : 1;            /* @Brief : To enable or disable Slew Rate for MSSP I2C. */
    uint8 mssp_i2c_SMBus_conrol : 1;         /* @Brief : To enable or disable SMBus for MSSP I2C. */
    uint8 mssp_i2c_general_call : 1;         /* @Brief : To enable or disable General Call for MSSP I2C. */
    uint8 mssp_i2c_master_receive_mode : 1;  /* @Brief : To enable or disable Master Receive for MSSP I2C. */
    uint8 mssp_i2c_reversed : 3;             /* @Brief : Reserved bits for MSSP I2C. */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority;
#endif  
}mssp_i2c_config_t;

/* @Brief : MSSP I2C configuration. */
typedef struct
{
    uint32 mssp_i2c_master_clock;                   /* @Brief : MSSP I2C master clock frequency. */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*MSSP_I2C_DefaultInterruptHandler)(void); /* @Brief : MSSP I2C default interrupt handler. */
#endif    
    /* @Brief : MSSP I2C Bus Collision Interrupt configuration. */
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*MSSP_I2C_Report_Write_Collision)(void);  /* @Brief : MSSP I2C write collision indicator. */
#endif    
    void (*MSSP_I2C_Report_Receive_Overflow)(void); /* @Brief : MSSP I2C receive overflow indicator. */
    mssp_i2c_config_t mssp_i2c_cfg;                 /* @Brief : MSSP I2C configuration. */
}mssp_i2c_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : To initialize the MSSP I2C.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Initialize(const mssp_i2c_t *_i2c);

/*
 * @Brief              : To de-initialize the MSSP I2C.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_DeInitialize(const mssp_i2c_t *_i2c);

/*
 * @Brief              : To make master send start bit on MSSP I2C bus for a certain slave.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *_i2c);

/*
 * @Brief              : To make master send repeated start bit on MSSP I2C bus for a certain slave to keep control on the bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *_i2c);

/*
 * @Brief              : To make master send stop bit on MSSP I2C bus for a certain slave.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *_i2c);

/*
 * @Brief              : To send data to a certain slave on MSSP I2C bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Param i2c_data
 * @Param _ack         : Pointer to the MSSP I2C acknowledge bit configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Mode_Write_Blocking(const mssp_i2c_t *_i2c, uint8 i2c_data, uint8 *_ack);

/*
 * @Brief              : To send data to a certain slave on MSSP I2C bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Param ack
 * @Param i2c_data     : Pointer to the MSSP I2C data configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Mode_Read_Blocking(const mssp_i2c_t *_i2c, uint8 ack, uint8 *i2c_data);
/***********************************************************************/
#endif	/* HAL_I2C_H */

