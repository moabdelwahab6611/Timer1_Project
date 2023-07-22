/* 
 * File     : hal_usart.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 13, 2023, 9:22 PM
 */

/**************************Includes-Section*****************************/
#include "hal_usart.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*USART_TxDefaultInterruptHandler)(void) = NULL;            /* @Brief : USART Transmit Interrupt Handler. */  
#endif
    
/*
 * @Brief : Callback pointer to function.
 */
#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*USART_RxDefaultInterruptHandler)(void) = NULL;            /* @Brief : USART Receive Interrupt Handler. */  
    static void (*USART_FramingErrorHandler)(void) = NULL;                  /* @Brief : USART Framing Error Interrupt Handler. */
    static void (*USART_OverrunErrorHandler)(void) = NULL;                  /* @Brief : USART Overrun Error Interrupt Handler. */ 
#endif    
    
/*
 * @Brief        : To calculate baud rate.
 * @Param _usart : Pointer to the USART module configurations.        
 */
static void USART_Baud_Rate_Calculation(const usart_t *_usart);

/*
 * @Brief        : To initialize USART Transmit pin in asynchronous mode.
 * @Param _usart : Pointer to the USART module configurations.         
 */
static void USART_ASYNCRONOUS_TX_Init(const usart_t *_usart);

/*
 * @Brief        : To initialize USART Receive pin in asynchronous mode.
 * @Param _usart : Pointer to the USART module configurations.         
 */
static void USART_ASYNCRONOUS_RX_Init(const usart_t *_usart);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : Initialization of USART communication peripheral.
 * @Param _usart       : Pointer to the USART module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType USART_Asynchronous_Initialize(const usart_t *_usart)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _usart)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable USART. */
        RCSTAbits.SPEN = USART_DISABLE_MODULE;
         /* @Brief : TX and RX pins configuration. */
        TRISCbits.RC7 = 1;                      /* RX : Input Configuration if needed */
        TRISCbits.RC6 = 1;                      /* TX : Input Configuration if needed */
        /* @Brief : Baud rate calculation. */
        USART_Baud_Rate_Calculation(_usart);
        /* @Brief : To initialize USART Transmit pin in asynchronous mode. */
        USART_ASYNCRONOUS_TX_Init(_usart);
        /* @Brief : To initialize USART Receive pin in asynchronous mode. */
        USART_ASYNCRONOUS_RX_Init(_usart);
        /* @Brief : Enable USART. */
        RCSTAbits.SPEN = USART_ENABLE_MODULE;
        ret = E_OK;
    }  
    return ret; 
}

/*
 * @Brief              : De-initialization of USART communication peripheral.
 * @Param _usart       : Pointer to the USART module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_ReturnType USART_Asynchronous_DeInitialize(const usart_t *_usart)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _usart)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable USART. */
        RCSTAbits.SPEN = USART_DISABLE_MODULE;
        ret = E_OK;
    }  
    return ret;
}

/*
 * @Brief              : To read byte from a Receive data register.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_ReadByte_Blocking(uint8 *_data)
{
    Std_ReturnType ret = E_NOT_OK;
    while(!PIR1bits.RCIF);
    *_data = RCREG;
    return ret;
}

/*
 * @Brief              : To read byte from a Receive data register.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_ReadByte_NonBlocking(uint8 *_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF)
    {
        *_data = RCREG;
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

/*
 * @Brief              : To restart Receiver in USART asynchronous mode.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_Restart_RX(void)
{
    Std_ReturnType ret = E_OK;
    /* @Brief : To disable Receiver in USART asynchronous mode.*/
    RCSTAbits.CREN = 0;
    /* @Brief : To enable Receiver in USART asynchronous mode.*/
    RCSTAbits.CREN = 1;
    return ret;
}

/*
 * @Brief              : To write byte in a Transmit data register.
 * @Param _data        
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteByte_Blocking(uint8 _data)
{
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* @Brief : Enable the interrupt. */
    USART_TX_InterruptEnable();
#endif
    TXREG = _data;
    return ret; 
}

/*
 * @Brief              : To write byte in a Transmit data register. 
 * @Param _data        
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteByte_NonBlocking(uint8 _data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter = ZERO_INT;
    if(1 == TXSTAbits.TRMT)
    {
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* @Brief : Enable the interrupt. */
    USART_TX_InterruptEnable();
#endif
    TXREG = _data;
    ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

/*
 * @Brief              : To write a string.
 * @Param _data        : Pointer to the _data stored in a receive data register.
 * @Param str_length
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue to perform this action. 
 */
Std_ReturnType USART_Asynchronous_WriteString_Blocking(uint8 *_data, uint16 str_length)
{
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter = ZERO_INT;
    for(char_counter = ZERO_INT; char_counter < str_length; char_counter++)
    {
        ret = USART_Asynchronous_WriteByte_Blocking(_data[char_counter]);
    }   
    return ret;
}

/*
 * @Brief        : To calculate baud rate.
 * @Param _usart : Pointer to the USART module configurations.        
 */
static void USART_Baud_Rate_Calculation(const usart_t *_usart)
{
    float Baud_Rate_Temp_Value = 0;
    switch(_usart->baudrate_config)
    {
        case BAUDRATE_ASYNCHRONOUS_MODE_8BIT_LOW_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE; 
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_MODE_LOW_SPEED;
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 64) - 1;
        break;
        
        case BAUDRATE_ASYNCHRONOUS_MODE_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE; 
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_MODE_HIGH_SPEED;
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 16) - 1;
        break;
        
        case BAUDRATE_ASYNCHRONOUS_MODE_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE; 
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_MODE_LOW_SPEED;
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 16) - 1;
        break;
        
        case BAUDRATE_ASYNCHRONOUS_MODE_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE; 
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_MODE_HIGH_SPEED;
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 4) - 1;
        break;
        
        case BAUDRATE_SYNCHRONOUS_MODE_8BIT :
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE; 
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 4) - 1;
        break;
        
        case BAUDRATE_SYNCHRONOUS_MODE_16BIT :
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE; 
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_GEN;
            Baud_Rate_Temp_Value = ((_XTAL_FREQ / (float)_usart->baudrate) / 4) - 1;
        break;
        
        default : ;
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp_Value); 
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp_Value) >> 8);
}

/*
 * @Brief        : To initialize USART Transmit pin in asynchronous mode.
 * @Param _usart : Pointer to the USART module configurations.         
 */
static void USART_ASYNCRONOUS_TX_Init(const usart_t *_usart)
{
    if(USART_ENABLE_ASYNCHRONOUS_MODE_TX == _usart->usart_tx_cfg.usart_enable_tx)
    {
        /* @Brief : USART Transmit enable or disable configuration. */
        TXSTAbits.TXEN = USART_ENABLE_ASYNCHRONOUS_MODE_TX;
        
        /* @Brief : USART Transmit interrupt configuration. */
        USART_TxDefaultInterruptHandler = _usart->USART_TxDefaultInterruptHandler;
        
        /* @Brief : USART Transmit interrupt configuration. */
        if(USART_ENABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT == _usart->usart_tx_cfg.usart_enable_tx_interrupt)
        {
            PIE1bits.TXIE = USART_ENABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT;
            /* @Brief : USART Interrupt configuration. */ 
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            USART_TX_InterruptEnable();
            /* @Brief : USART Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _usart->usart_tx_cfg.usart_tx_interrupt_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            USART_TX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _usart->usart_tx_cfg.usart_tx_interrupt_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            USART_TX_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif            
#endif 
        }
        else if(USART_DISABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT == _usart->usart_tx_cfg.usart_enable_tx_interrupt)
        {
            PIE1bits.TXIE = USART_DISABLE_ASYNCHRONOUS_MODE_TX_INTERRUPT;
        }
        else{/*****Nothing*****/}
    
        /* @Brief : USART 9-Bit Transmit configuration. */
        if(USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_TX == _usart->usart_tx_cfg.usart_enable_9bit_tx)
        {
            TXSTAbits.TX9 = USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_TX;
        }
        else if(USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_TX == _usart->usart_tx_cfg.usart_enable_9bit_tx)
        {
            TXSTAbits.TX9 = USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_TX;
        }
        else{/*****Nothing*****/}
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief        : To initialize USART Receive pin in asynchronous mode.
 * @Param _usart : Pointer to the USART module configurations.         
 */
static void USART_ASYNCRONOUS_RX_Init(const usart_t *_usart)
{
    if(USART_ENABLE_ASYNCHRONOUS_MODE_RX == _usart->usart_rx_cfg.usart_enable_rx)
    {
        /* @Brief : USART Receive enable or disable configuration. */
        RCSTAbits.CREN = USART_ENABLE_ASYNCHRONOUS_MODE_RX;
        
        /* @Brief : USART Receive interrupt configuration. */
        USART_RxDefaultInterruptHandler = _usart->USART_RxDefaultInterruptHandler;
        
        /* @Brief : USART Receive error status configuration. */
        USART_FramingErrorHandler = _usart->USART_FramingErrorHandler;
        USART_OverrunErrorHandler = _usart->USART_OverrunErrorHandler;
                
        /* @Brief : USART Receive interrupt configuration. */
        if(USART_ENABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT == _usart->usart_rx_cfg.usart_enable_rx_interrupt)
        {
            PIE1bits.RCIE = USART_ENABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT;
            /* @Brief : USART Interrupt configuration. */ 
#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            USART_RX_InterruptEnable();
            /* @Brief : USART Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _usart->usart_rx_cfg.usart_rx_interrupt_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            USART_RX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _usart->usart_rx_cfg.usart_rx_interrupt_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            USART_RX_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif            
#endif 
        }
        else if(USART_DISABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT == _usart->usart_rx_cfg.usart_enable_rx_interrupt)
        {
            PIE1bits.RCIE = USART_DISABLE_ASYNCHRONOUS_MODE_RX_INTERRUPT;
        }
        else{/*****Nothing*****/}
    
        /* @Brief : USART 9-Bit Receive configuration. */
        if(USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_RX == _usart->usart_rx_cfg.usart_enable_9bit_rx)
        {
            RCSTAbits.RX9 = USART_ENABLE_ASYNCHRONOUS_MODE_9BIT_RX;
        }
        else if(USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_RX == _usart->usart_rx_cfg.usart_enable_9bit_rx)
        {
            RCSTAbits.RX9 = USART_DISABLE_ASYNCHRONOUS_MODE_9BIT_RX;
        }
        else{/*****Nothing*****/}
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief : Callback pointer to function to USART Transmit interrupt service routine.
 */
void USART_TX_ISR(void)
{
    /* @Brief : Disable the interrupt. */
    USART_TX_InterruptDisable();
    if(USART_TxDefaultInterruptHandler)
    {
        USART_TxDefaultInterruptHandler();
    }
    else{/*****Nothing*****/}
}

/*
 * @Brief : Callback pointer to function to USART Receive interrupt service routine.
 */
void USART_RX_ISR(void)
{
  if(USART_RxDefaultInterruptHandler)
    {
        USART_RxDefaultInterruptHandler();
    }
    else{/*****Nothing*****/} 
  
  if(USART_FramingErrorHandler)
    {
        USART_FramingErrorHandler();
    }
    else{/*****Nothing*****/}
  
  if(USART_OverrunErrorHandler)
    {
        USART_OverrunErrorHandler();
    }
    else{/*****Nothing*****/}
}
/***********************************************************************/