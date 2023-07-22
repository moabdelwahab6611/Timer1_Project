/* 
 * File     : hal_i2c.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 17, 2023, 4:19 PM
 */

/**************************Includes-Section*****************************/
#include "hal_i2c.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @Brief : Callback pointer to function.
 */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_I2C_DefaultInterruptHandler)(void) = NULL;
#endif

/*
 * @Brief : Callback pointer to function.
 */    
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
#endif
    
/*
 * @Brief : Callback pointer to function.
 */
    static void (*MSSP_I2C_Report_Receive_Overflow_InterruptHandler)(void) = NULL;

/*
 * @Brief : MSSP I2C mode GPIO configurations.
 */
static inline void MSSP_I2C_Mode_GPIO_CFG(void);

/*
 * @Brief      : MSSP I2C master mode clock configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *_i2c);

/*
 * @Brief      : MSSP I2C slave mode configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Slave_Mode_Configurations(const mssp_i2c_t *_i2c);

/*
 * @Brief      : MSSP I2C interrupt configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *_i2c);

/*
 * @Brief      : MSSP I2C bus collision interrupt configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Bus_Collision_Interrupt_Configurations(const mssp_i2c_t *_i2c);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the MSSP I2C.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Initialize(const mssp_i2c_t *_i2c)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _i2c)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Disable MSSP I2C. */
        MSSP_I2C_DISABLE_MODULE_CFG();
        /* @Brief : MSSP I2C mode selection. */
        if(MSSP_I2C_MASTER_MODE == _i2c->mssp_i2c_cfg.mssp_i2c_mod)     /* @Brief : MSSP I2C master mode configurations. */
        {
            /* @Brief : MSSP I2C master mode clock configurations. */
            MSSP_I2C_Master_Mode_Clock_Configurations(_i2c);
        }
        else if(MSSP_I2C_SLAVE_MODE == _i2c->mssp_i2c_cfg.mssp_i2c_mod) /* @Brief : MSSP I2C slave mode configurations. */  
        {
            /* @Brief : MSSP I2C slave mode General Call configurations. */
            if(MSSP_I2C_ENABLE_GENERAL_CALL == _i2c->mssp_i2c_cfg.mssp_i2c_general_call)
            {
                MSSP_I2C_ENABLE_GENERAL_CALL_CFG();
            }
            else if(MSSP_I2C_DISABLE_GENERAL_CALL == _i2c->mssp_i2c_cfg.mssp_i2c_general_call)
            {
                MSSP_I2C_DISABLE_GENERAL_CALL_CFG();
            }
            else{/*****Nothing*****/}
            /* @Brief : MSSP I2C slave mode write collision detect. */
            SSPCON1bits.WCOL = 0;       /* @Brief : MSSP I2C slave mode no collision detected. */
            /* @Brief : MSSP I2C slave mode clear the receive overflow indicator. */
            SSPCON1bits.SSPOV = 0;      /* @Brief : MSSP I2C slave mode no overflow indicator. */
            /* @Brief : MSSP I2C slave mode release the clock. */
            SSPCON1bits.CKP = 1;        /* @Brief : MSSP I2C slave mode clock released. */
            /* @Brief : Assign MSSP I2C slave address. */
            SSPADD = _i2c->mssp_i2c_cfg.mssp_i2c_slave_address;
            /* @Brief : MSSP I2C slave mode configurations. */
            MSSP_I2C_Slave_Mode_Configurations(_i2c);
        }
        else{/*****Nothing*****/}
        /* @Brief :  MSSP I2C master mode GPIO configurations. */
        MSSP_I2C_Mode_GPIO_CFG();
        /* @Brief : MSSP I2C Slew Rate configurations. */
        if(MSSP_I2C_ENABLE_SLEW_RATE == _i2c->mssp_i2c_cfg.mssp_i2c_slew_rate)
        {
            MSSP_I2C_ENABLE_SLEW_RATE_CFG();
        }
        else if(MSSP_I2C_DISABLE_SLEW_RATE == _i2c->mssp_i2c_cfg.mssp_i2c_slew_rate)
        {
            MSSP_I2C_DISABLE_SLEW_RATE_CFG();
        }
        else{/*****Nothing*****/}
        /* @Brief : MSSP I2C SMBus control configurations. */
        if(MSSP_I2C_ENABLE_SMBUS == _i2c->mssp_i2c_cfg.mssp_i2c_SMBus_conrol)
        {
            MSSP_I2C_ENABLE_SMBUS_CFG();
        }
        else if(MSSP_I2C_DISABLE_SMBUS == _i2c->mssp_i2c_cfg.mssp_i2c_SMBus_conrol)
        {
            MSSP_I2C_ENABLE_SMBUS_CFG();
        }
        else{/*****Nothing*****/}
        /* @Brief : MSSP I2C Interrupt configuration. */
        MSSP_I2C_Interrupt_Configurations(_i2c);
        /* @Brief : MSSP I2C Bus Collision Interrupt configuration. */
        MSSP_I2C_Bus_Collision_Interrupt_Configurations(_i2c);
        /* @Brief : Enable MSSP I2C. */
        MSSP_I2C_ENABLE_MODULE_CFG();
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To de-initialize the MSSP I2C.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_DeInitialize(const mssp_i2c_t *_i2c)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _i2c)
    {
        ret = E_NOT_OK;
    }
    else
    { 
       /* @Brief : Disable MSSP I2C. */
       MSSP_I2C_DISABLE_MODULE_CFG();
       /* @Brief : MSSP I2C Interrupt configuration. */
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
       MSSP_I2C_InterruptDisable();
#endif
       /* @Brief : MSSP I2C Bus Collision Interrupt configuration. */
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE       
       MSSP_I2C_BUS_COL_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To make master send start bit on MSSP I2C bus for a certain slave.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *_i2c)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _i2c)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Initiate start condition on SDL & SDC pins. */
        SSPCON2bits.SEN = 1; /* @Brief : Initiate start condition on SDL & SDC pins, and automatically cleared by hardware. */
        /* @Brief : Wait for the completion of start condition. */
        while(SSPCON2bits.SEN);
        /* @Brief : Clears the MSSP I2C interrupt flag. */
        PIR1bits.SSPIF = 0;
        /* @Brief : Report the start condition detection. */
        if(MSSP_I2C_START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret = E_OK; /* @Brief : Indicates that start condition has been detected. */
        }
        else
        {
           ret = E_NOT_OK; /* @Brief : Indicates that start condition has not been detected. */
        }
    }
    return ret;
}

/*
 * @Brief              : To make master send repeated start bit on MSSP I2C bus for a certain slave to keep control on the bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *_i2c)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _i2c)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        /* @Brief : Initiate repeated start condition on SDL & SDC pins. */
        SSPCON2bits.RSEN = 1; /* @Brief : Initiate repeated start condition on SDL & SDC pins, and automatically cleared by hardware. */
        /* @Brief : Wait for the completion of repeated start condition. */
        while(SSPCON2bits.RSEN);
        /* @Brief : Clears the MSSP I2C interrupt flag. */
        PIR1bits.SSPIF = 0;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To make master send stop bit on MSSP I2C bus for a certain slave.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *_i2c)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _i2c)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Initiate stop condition on SDL & SDC pins. */
        SSPCON2bits.PEN = 1; /* @Brief : Initiate stop condition on SDL & SDC pins, and automatically cleared by hardware. */
        /* @Brief : Wait for the completion of stop condition. */
        while(SSPCON2bits.PEN);
        /* @Brief : Clears the MSSP I2C interrupt flag. */
        PIR1bits.SSPIF = 0;
        /* @Brief : Report the stop condition detection. */
        if(MSSP_I2C_STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            ret = E_OK;    /* @Brief : Indicates that stop condition has been detected. */
        }
        else
        {
           ret = E_NOT_OK; /* @Brief : Indicates that stop condition has not been detected. */
        }
    }
    return ret;
}

/*
 * @Brief              : To send data to a certain slave on MSSP I2C bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Param i2c_data
 * @Param _ack         : Pointer to the MSSP I2C acknowledge bit configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Mode_Write_Blocking(const mssp_i2c_t *_i2c, uint8 i2c_data, uint8 *_ack)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _i2c) || (NULL == _ack))
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Write data to data register. */
        SSPBUF = i2c_data;
        /* @Brief : Wait for the completion of transmission. */
        while(!PIR1bits.SSPIF);
        /* @Brief : Clears the MSSP I2C interrupt flag. */
        PIR1bits.SSPIF = 0;
        /* @Brief : Report the acknowledge receive from the slave. */
        if(MSSP_I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *_ack = MSSP_I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else
        {
            *_ack = MSSP_I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To send data to a certain slave on MSSP I2C bus.
 * @Param _i2c         : Pointer to the MSSP I2C module configurations.
 * @Param ack
 * @Param i2c_data     : Pointer to the MSSP I2C data configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType MSSP_I2C_Master_Mode_Read_Blocking(const mssp_i2c_t *_i2c, uint8 ack, uint8 *i2c_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _i2c) || (NULL == i2c_data))
    {
        ret = E_NOT_OK;
    }
    else
    { 
        /* @Brief : Master Mode enable receive. */
        MSSP_I2C_MASTER_MODE_ENABLE_RECEIVE_CFG();
        /* @Brief : Wait for the buffer register full flag. */
        while(!SSPSTATbits.BF);
        /* @Brief : Copy the data register to buffer variable. */
        *i2c_data = SSPBUF;
        /* @Brief : Report the acknowledge or not acknowledge after receive. */
        if(MSSP_I2C_MASTER_MODE_SEND_ACK == ack)
        {
            SSPCON2bits.ACKDT = 0;  /* @Brief : Acknowledge. */
            /* @Brief : initiate the Acknowledge sequence on SCL & SDL pins and transmit ACKDT data pin. */
            SSPCON2bits.ACKEN = 1;
        }
        else if(MSSP_I2C_MASTER_MODE_SEND_NACK == ack)
        {
            SSPCON2bits.ACKDT = 1;  /* @Brief : Not Acknowledge. */
            /* @Brief : initiate the Acknowledge sequence on SCL & SDL pins and transmit ACKDT data pin. */
            SSPCON2bits.ACKEN = 1;
        }
        else{/*****Nothing*****/}
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief : Callback pointer to function to MSSP I2C interrupt service routine.
 */
void MSSP_I2C_ISR(void)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_InterruptFlagClear();          /* @Brief : Clear flag of MSSP I2C interrupt. */
    if(MSSP_I2C_DefaultInterruptHandler)
    {
        MSSP_I2C_DefaultInterruptHandler();
    }
    else{/*****Nothing*****/}
#endif
}

/*
 * @Brief : Callback pointer to function to MSSP I2C Bus Collision interrupt service routine.
 */
void MSSP_I2C_BC_ISR(void)
{
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_BUS_COL_InterruptFlagClear();  /* @Brief : Clear flag of MSSP I2C bus collision interrupt. */
    if(MSSP_I2C_Report_Write_Collision_InterruptHandler)
    {
        MSSP_I2C_Report_Write_Collision_InterruptHandler();
    }
    else{/*****Nothing*****/}
#endif   
}

/*
 * @Brief : MSSP I2C mode GPIO configurations.
 */
static inline void MSSP_I2C_Mode_GPIO_CFG(void)
{
    TRISCbits.TRISC3 = 1; /* @Brief : Serial Clock Line (SCL) is input. */
    TRISCbits.TRISC4 = 1; /* @Brief : Serial Data Line (SDL) is input. */
}

/*
 * @Brief      : MSSP I2C master mode clock configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *_i2c)
{
    SSPCON1bits.SSPM = _i2c->mssp_i2c_cfg.mssp_i2c_mod_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / _i2c->mssp_i2c_master_clock) - 1);
}

/*
 * @Brief      : MSSP I2C slave mode configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Slave_Mode_Configurations(const mssp_i2c_t *_i2c)
{
    SSPCON1bits.SSPM = _i2c->mssp_i2c_cfg.mssp_i2c_mod_cfg;
}

/*
 * @Brief      : MSSP I2C interrupt configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *_i2c)
{
    /* @Brief : Receive overflow Interrupt configuration. */
    MSSP_I2C_Report_Receive_Overflow_InterruptHandler = _i2c->MSSP_I2C_Report_Receive_Overflow;
    /* @Brief : MSSP I2C Interrupt configuration. */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        MSSP_I2C_DefaultInterruptHandler = _i2c->MSSP_I2C_DefaultInterruptHandler;       
    /* Brief : Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _i2c->mssp_i2c_cfg.mssp_i2c_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _i2c->mssp_i2c_cfg.mssp_i2c_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();        
#endif
#endif
}

/*
 * @Brief      : MSSP I2C bus collision interrupt configurations.
 * @Param _i2c : Pointer to the MSSP I2C module configurations.
 */
static inline void MSSP_I2C_Bus_Collision_Interrupt_Configurations(const mssp_i2c_t *_i2c)
{
    /* @Brief : MSSP I2C Bus Collision Interrupt configuration. */
#if MSSP_I2C_BUS_COLL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_BUS_COL_InterruptEnable();
        MSSP_I2C_BUS_COL_InterruptFlagClear();
        MSSP_I2C_Report_Write_Collision_InterruptHandler = _i2c->MSSP_I2C_Report_Write_Collision;
    /* Brief : Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable(); 
        if(INTERRUPT_HIGH_PRIORITY == _i2c->mssp_i2c_cfg.mssp_i2c_bc_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_BUS_COL_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _i2c->mssp_i2c_cfg.mssp_i2c_bc_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_BUS_COL_LowPrioritySet();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();        
#endif
#endif
}
/***********************************************************************/