/* 
 * File     : mcal_external_interrupt.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 2, 2023, 9:34 PM
 */

/**************************Includes-Section*****************************/
#include "mcal_external_interrupt.h"
/***********************************************************************/

/*****************Helper Functions Declarations-Section*****************/
/*
 * @brief : Callback pointers for (INTx) external interrupts. 
 */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;
/***********************************************************************/
/*
 * @brief : Callback pointers for (RBx) external interrupts. 
 */
static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW = NULL;
/***********************************************************************/
/*
 * @Brief              : To initialize the External INTx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To disable the INTx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */  
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To enable and initialize priority for the INTx Interrupts.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To enable and select edge type for the INTx Interrupts.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To initialize certain INTx Interrupts pin.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);

/*
 * @Brief              : To clear flag of certain INTx Interrupts pin.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);
/***********************************************************************/
/*
 * @Brief              : Call back notation to INT0 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));

/*
 * @Brief              : Call back notation to INT1 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));

/*
 * @Brief              : Call back notation to INT2 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));

/*
 * @Brief              : To call back one of three the INTx ISR.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
/***********************************************************************/
/*
 * @Brief              : To enable the RBx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);

/*
 * @Brief              : To disable the RBx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */ 
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);

/*
 * @Brief              : To enable and initialize priority for the RBx Interrupts.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);

/*
 * @Brief              : To initialize certain RBx Interrupts pin.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
/*
 * @Brief              : To initialize the External INTx Interrupts and enable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Disable External INTx Interrupt. */
        ret = Interrupt_INTx_Disable(int_obj);
        /* @Brief : Clear External INTx Interrupt Flag. */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /* @Brief : Edge Type selection for External INTx Interrupt. */
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        /* @Brief : Pin Selection for External INTx Interrupt. */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /* @Brief : External INTx Interrupt Handler. */
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* @Brief : Enable External INTx Interrupt. */
        ret |= Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

/*
 * @Brief : Callback pointer to function to External INT0 interrupt service routine.
 */
void INT0_ISR(void)
{
    EXT_INT0_InterruptFlagClear();
    if(INT0_InterruptHandler){INT0_InterruptHandler();}
    else{/*****Nothing*****/}
}

/*
 * @Brief : Callback pointer to function to External INT1 interrupt service routine.
 */
void INT1_ISR(void)
{
    EXT_INT1_InterruptFlagClear();
    if(INT1_InterruptHandler){INT1_InterruptHandler();}
    else{/*****Nothing*****/}
}

/*
 * @Brief : Callback pointer to function to External INT2 interrupt service routine.
 */
void INT2_ISR(void)
{
    EXT_INT2_InterruptFlagClear();
    if(INT2_InterruptHandler){INT2_InterruptHandler();}
    else{/*****Nothing*****/}
}

/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB4_Source
 */
void RB4_ISR(uint8 RB4_Source)
{
    EXT_RBx_InterruptFlagClear();
    if(0 == RB4_Source)
    {
        if(RB4_InterruptHandler_HIGH){RB4_InterruptHandler_HIGH();}
        else{/*****Nothing*****/}
    }
    else if (1 == RB4_Source)
    {
        if(RB4_InterruptHandler_LOW){RB4_InterruptHandler_LOW();}
        else{/*****Nothing*****/}
    }
    else {/*****Nothing*****/}   
}

/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB5_Source
 */
void RB5_ISR(uint8 RB5_Source)
{
    EXT_RBx_InterruptFlagClear();
    if(0 == RB5_Source)
    {
        if(RB5_InterruptHandler_HIGH){RB5_InterruptHandler_HIGH();}
        else{/*****Nothing*****/}
    }
    else if (1 == RB5_Source)
    {
        if(RB5_InterruptHandler_LOW){RB5_InterruptHandler_LOW();}
        else{/*****Nothing*****/}
    }
    else { /* Nothing */ }
}

/*
 * @Brief : External Interrupt RB4 MCAL Helper function. 
 * @Param RB6_Source
 */
void RB6_ISR(uint8 RB6_Source)
{
    EXT_RBx_InterruptFlagClear();
    if(0 == RB6_Source)
    {
        if(RB6_InterruptHandler_HIGH){RB6_InterruptHandler_HIGH();}
        else{/*****Nothing*****/}
    }
    else if (1 == RB6_Source)
    {
        if(RB6_InterruptHandler_LOW){RB6_InterruptHandler_LOW();}
        else{/*****Nothing*****/}
    }
    else {/*****Nothing*****/}   
}

/*
 * @Brief : External Interrupt RB4 MCAL Helper function.
 * @Param RB7_Source
 */
void RB7_ISR(uint8 RB7_Source)
{
    EXT_RBx_InterruptFlagClear();
    if(0 == RB7_Source)
    {
        if(RB7_InterruptHandler_HIGH){RB7_InterruptHandler_HIGH();}
        else{/*****Nothing*****/}
    }
    else if (1 == RB7_Source)
    {
        if(RB7_InterruptHandler_LOW){RB7_InterruptHandler_LOW();}
        else{/*****Nothing*****/}
    }
    else {/*****Nothing*****/}   
}

/*
 * @Brief              : To de-initialize the External INTx Interrupts and disable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{ret = Interrupt_INTx_Disable(int_obj);}    /* @Brief : Disable External INTx Interrupt. */
    return ret;
}

/*
 * @Brief              : To initialize the External RBx Interrupts and enable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Disable External RBx Interrupt. */
        EXT_RBx_InterruptDisable();
        /* @Brief : Clear External RBx Interrupt Flag. */
        EXT_RBx_InterruptFlagClear();
        /* @Brief : External RBx Interrupt Priority configuration. */ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
        { 
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_Priority_Low();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
        { 
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_Priority_High();
        }
        else{/*****Nothing*****/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));  /* @Brief : Pin Direction Initialization for External RBx Interrupt. */
        switch(int_obj->mcu_pin.pin)
        {
            case GPIO_PIN4 : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5 : 
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6 : 
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7 : 
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default:
            ret = E_NOT_OK;
        }
        /* @Brief : Enable External RBx Interrupt. */
        EXT_RBx_InterruptEnable();
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To de-initialize the External RBx Interrupts and disable the interrupt.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* @Brief : Disable External INTx Interrupt. */
        EXT_RBx_InterruptDisable();
        /* @Brief : Clear External INTx Interrupt Flag. */
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}

/*
 * @Brief              : To initialize the External INTx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptLowEnable();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptHighEnable();}
                else{/*****Nothing*****/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptLowEnable();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptHighEnable();}
                else{/*****Nothing*****/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/*
 * @Brief              : To disable the INTx Interrupts source.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */ 
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptDisable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptDisable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/*
 * @Brief              : To enable and initialize priority for the INTx Interrupts.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_SetHighPriority();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_SetHighPriority();}
                else{/******Nothing*****/}
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_SetLowPriority();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_SetHighPriority();}
                else{/******Nothing*****/}
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/*
 * @Brief              : To enable and select edge type for the INTx Interrupts.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT0_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                else{/*****Nothing*****/}
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT1_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                else{/*****Nothing*****/}
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT2_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                else{/*****Nothing*****/}
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/*
 * @Brief              : To initialize certain INTx Interrupts pin.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));}
    return ret;
}

/*
 * @Brief              : To clear flag of certain INTx Interrupts pin.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptFlagClear();
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear();
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/*
 * @Brief              : Call back notation to INT0 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : Call back notation to INT1 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : Call back notation to INT2 ISR.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/*
 * @Brief              : To call back one of three the INTx ISR.
 * @Param int_obj      : Pointer to the Interrupt module configurations.
 * @Return Status of the function.
 *          (E_OK)     : The function done successfully.
 *          (E_NOT_OK) : The function has issue while performing this action.
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
/***********************************************************************/