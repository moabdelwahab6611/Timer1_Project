/* 
 * File     : hal_usart.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 13, 2023, 9:22 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/**************************Includes-Section*****************************/
#include "proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
/* @Brief : Macro to enable USART module. */
#define USART_ENABLE_MODULE                1
/* @Brief : Macro to disable USART module. */
#define USART_DISABLE_MODULE               0

/* @Brief : Macro for USART to work in Synchronous mode. */
#define USART_SYNCHRONOUS_MODE              1
/* @Brief : Macro for USART to work in Asynchronous mode. */
#define USART_ASYNCHRONOUS_MODE             0

/* @Brief : Macro for USART to work in Asynchronous mode High baud generated speed. */
#define USART_ASYNCHRONOUS_MODE_HIGH_SPEED  1
/* @Brief : Macro for USART to work in Asynchronous mode Low baud generated speed. */
#define USART_ASYNCHRONOUS_MODE_LOW_SPEED   0

/* @Brief : Macrosfor selection USART 16-Bit baud rate generator register size. */
#define USART_16BIT_BAUD_GEN                1
/* @Brief : Macro for selection USART 8-Bit baud rate generator register size. */
#define USART_8BIT_BAUD_GEN                 0

/* @Brief : Macro to enable USART Transmit in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_TX   1
/* @Brief : Macro to disable USART Transmit in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_TX  0

/* @Brief : Macro to enable USART Transmit interrupt in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT   1
/* @Brief : Macro to disable USART Transmit interrupt in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT  0

/* @Brief : Macro to enable USART Transmit in 9-Bit in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_TX        1
/* @Brief : Macro to disable USART Transmit in 9-Bit in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_TX       0

/* @Brief : Macro to enable USART Receiving in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_RX   1
/* @Brief : Macro to disable USART Receiving in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_RX  0

/* @Brief : Macro to enable USART Receiving interrupt in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT   1
/* @Brief : Macro to disable USART Receiving interrupt in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT  0

/* @Brief : Macro to enable USART Receiving in 9-Bit in Asynchronous mode. */
#define USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_RX        1
/* @Brief : Macros to disable USART Receiving in 9-Bit in Asynchronous mode. */
#define USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_RX       0

/* @Brief : Macros to USART for framing error indication configurations. */
#define USART_FRAMING_ERROR_DETECTED       1
#define USART_FRAMING_ERROR_CLEARED        0

/* @Brief : Macros to USART for overrun error indication configurations. */
#define USART_OVERRUN_ERROR_DETECTED       1
#define USART_OVERRUN_ERROR_CLEARED        0
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/********************Data Types Declarations-Section********************/
/* @Brief : Baud rate speed configuration for USART. */
typedef enum
{
    BAUDRATE_ASYNCHRONOUS_MODE_8BIT_LOW_SPEED,           /* @Brief : Low Baud rate speed with 8-Bit Register in Asynchronous mod configuration for USART. */
    BAUDRATE_ASYNCHRONOUS_MODE_8BIT_HIGH_SPEED,          /* @Brief : High Baud rate speed with 8-Bit Register in Asynchronous mod configuration for USART. */
    BAUDRATE_ASYNCHRONOUS_MODE_16BIT_LOW_SPEED,          /* @Brief : Low Baud rate speed with 16-Bit Register in Asynchronous mod configuration for USART. */
    BAUDRATE_ASYNCHRONOUS_MODE_16BIT_HIGH_SPEED,         /* @Brief : High Baud rate speed with 16-Bit Register in Asynchronous mod configuration for USART. */
    BAUDRATE_SYNCHRONOUS_MODE_8BIT,                      /* @Brief : Baud rate speed with 8-Bit Register in Synchronous mod configuration for USART. */
    BAUDRATE_SYNCHRONOUS_MODE_16BIT                      /* @Brief : Baud rate speed with 16-Bit Register in Synchronous mod configuration for USART. */
}baudrate_gen_t;

/* @Brief : Transmit configuration for USART. */
typedef struct
{
    uint8 usart_tx_reserved : 5;                                /* @Brief : USART Transmit Reserved Bits. */
    uint8 usart_enable_tx : 1;                                  /* @Brief : USART Enabling  or Disabling Transmit configuration. */
    uint8 usart_enable_tx_interrupt : 1;                        /* @Brief : USART Transmit Interrupt configuration. */
    uint8 usart_enable_9bit_tx : 1;                             /* @Brief : USART Enabling or Disabling 9-Bit Transmission configuration. */
    interrupt_priority_cfg usart_tx_interrupt_priority;         /* @Brief : USART Transmit Interrupt Priority configuration. */
}usart_tx_cfg_t;

/* @Brief : Receiving configuration for USART. */
typedef struct
{   
    uint8 usart_rx_reserved : 5;                                /* @Brief : USART Receive Reserved Bits. */
    uint8 usart_enable_rx : 1;                                  /* @Brief : USART Enabling  or Disabling Receive configuration. */
    uint8 usart_enable_rx_interrupt : 1;                        /* @Brief : USART Receive Interrupt configuration. */
    uint8 usart_enable_9bit_rx : 1;                             /* @Brief : USART Enabling or Disabling 9-Bit Receiving configuration. */
    interrupt_priority_cfg usart_rx_interrupt_priority;         /* @Brief : USART Receive Interrupt Priority configuration. */
}usart_rx_cfg_t;

/* @Brief : Error status configuration for USART. */
typedef union 
{
    struct
    {
        uint8 usart_tx_reserved : 6;                        /* @Brief : USART Error Status Reserved Bits. */  
        uint8 usart_ferr : 1;                               /* @Brief : USART Framing Error configuration. */
        uint8 usart_oerr : 1;                               /* @Brief : USART Overrun Error configuration. */  
    };
    uint8 status;
}usart_error_status_t;

/* @Brief : USART configurations. */
typedef struct 
{
    uint32 baudrate;                                        /* @Brief : USART Baud Rate configuration. */
    baudrate_gen_t baudrate_config;                         /* @Brief : USART Baud Rate configuration. */
    usart_tx_cfg_t usart_tx_cfg;                            /* @Brief : USART Transmit configuration. */
    usart_rx_cfg_t usart_rx_cfg;                            /* @Brief : USART Receive configuration. */
    usart_error_status_t eusart_error_status;               /* @Brief : USART  Error Status configuration. */           
    void (*USART_TxDefaultInterruptHandler)(void);          /* @Brief : USART Transmit Interrupt Handler. */  
    void (*USART_RxDefaultInterruptHandler)(void);          /* @Brief : USART Receive Interrupt Handler. */  
    void (*USART_FramingErrorHandler)(void);                /* @Brief : USART Framing Error Interrupt Handler. */
    void (*USART_OverrunErrorHandler)(void);                /* @Brief : USART Overrun Error Interrupt Handler. */  
}usart_t;
/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/
/*
 * @Brief              : Initialization of USART communication peripheral.
 * @Param _usart       : Pointer to the USART module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType USART_Asynchronous_Initialize(const usart_t *_usart);

/*
 * @Brief              : De-initialization of USART communication peripheral.
 * @Param _usart       : Pointer to the USART module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType USART_Asynchronous_DeInitialize(const usart_t *_usart);

/*
 * @Brief              : To read byte from a Receive data register.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_ReadByte_Blocking(uint8 *_data);

/*
 * @Brief              : To read byte from a Receive data register.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_ReadByte_NonBlocking(uint8 *_data);

/*
 * @Brief              : To restart Receiver in USART asynchronous mode.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_Restart_RX(void);

/*
 * @Brief              : To write byte in a Transmit data register. 
 * @Param _data        
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteByte_Blocking(uint8 _data);

/*
 * @Brief              : To write byte in a Transmit data register. 
 * @Param _data        
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteByte_NonBlocking(uint8 _data);

/*
 * @Brief              : To write a string.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Param str_length
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteString_Blocking(uint8 *_data, uint16 str_length);
/***********************************************************************/
#endif	/* HAL_USART_H */

