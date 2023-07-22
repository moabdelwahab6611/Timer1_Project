/* 
 * File     : application.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 5:38 PM
 */

/**************************Includes-Section*****************************/
#include "application.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
/***********************************************************************/

/***********************************************************************/
volatile uint32 timer1_on;
volatile uint16 timer1_counter_val;

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

timer1_t counter_obj;

void Timer1_DefaultInterruptHandler(void)
{
    timer1_on++;
    led_turn_toggle(&led1);
}

void timer1_timer_init(void)
{
    timer1_t timer_obj;
    timer_obj.TMR1_InterruptHandler = Timer1_DefaultInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_8;
    timer_obj.timer1_preload_value = 15536;
    timer_obj.timer1_reg_rw_mode = TIMER1_RW_16BIT_REGISTER_MODE;
    Timer1_Init(&timer_obj);
}
/***********************************************************************/

/***********************Main Function-Section***************************/
int main() 
{ 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    //timer1_timer_init();
    counter_obj.TMR1_InterruptHandler = NULL;
    counter_obj.priority = INTERRUPT_LOW_PRIORITY;
    counter_obj.timer1_mode = TIMER1_COUNTER_MODE;
    counter_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
    counter_obj.timer1_preload_value = 0;
    counter_obj.timer1_reg_rw_mode = TIMER1_RW_16BIT_REGISTER_MODE;
    counter_obj.timer1_counter_mode = TIMER1_SYNCHRONOUS_COUNTER_MODE;
    ret = Timer1_Init(&counter_obj);
    ret = led_initialize(&led1);
    while(1)
    {   
       ret = Timer1_Read_Value(&counter_obj, &timer1_counter_val);
    }
    return (EXIT_SUCCESS);
}
/***********************************************************************/

/*************************Functions-Section*****************************/
void application_intialize(void)
{
    Std_ReturnType ret = E_NOT_OK;   
    ecu_layer_intialize();
}
/***********************************************************************/