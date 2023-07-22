/* 
 * File     : mcal_interrupt_manager.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on June 2, 2023, 9:36 PM
 */

/**************************Includes-Section*****************************/
#include "mcal_interrupt_manager.h"
/***********************************************************************/

/********************Data Types Declarations-Section********************/
static volatile uint8 RB4_Flag = 1;
static volatile uint8 RB5_Flag = 1;
static volatile uint8 RB6_Flag = 1;
static volatile uint8 RB7_Flag = 1;
/***********************************************************************/

/*****************Software Interfaces Functions-Section*****************/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
void __interrupt() InterruptManagerHigh(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*****Nothing*****/}
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else{/*****Nothing*****/}
}

#else
void __interrupt() InterruptManager(void)
{
    /****************INTx external on change interrupt start****************/
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR(); 
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F))
    {
        INT1_ISR(); 
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /****************PortB external on change interrupt start***************/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1))
    {
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0))
    {
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1))
    {
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0))
    {
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1))
    {
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0))
    {
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1))
    {
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0))
    {
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /************************ADC modules interrupt**************************/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /**********************Timers modules interrupt*************************/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TMR0_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TMR2_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /***********************USART module interrupt**************************/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        USART_TX_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        USART_RX_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /**********************MSSP I2C module interrupt************************/
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        MSSP_I2C_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        MSSP_I2C_BC_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
    
    /*******************CCP1 and CCP2 modules interrupt*********************/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{/*****Nothing*****/}
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{/*****Nothing*****/}
    /***********************************************************************/
}
#endif
/***********************************************************************/