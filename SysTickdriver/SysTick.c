 /******************************************************************************
 *
 * Module: SysTick Timer
 *
 * File Name: SysTick.c
 *
 * Description: Source file for the TM4C123GH6PM SysTick Timer driver
 *
 * Author: Abdelrahman Hussien
 *
 *******************************************************************************/
#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"


extern volatile void (*g_CallBackPtr)(void) = NULL_PTR;      /*Global Variable for Call Back Pointer = NULL*/

/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enable the SystTick Timer to run using the System Clock with Frequency 16Mhz and generate interrupt based on milliseconds input
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){

    SYSTICK_CTRL_REG    = 0;     /* Disable the SysTick Timer by Clear the ENABLE Bit */

    uint32 reloadValue  = (16000000 / 1000) * a_TimeInMilliSeconds; /*the reload value based on how many milliseconds that i want with 16MHz clock*/

    SYSTICK_RELOAD_REG  = reloadValue - 1 ;  /*Set the register reload value based on reload value - 1 */

    SYSTICK_CURRENT_REG = 0 ;     /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;

}
/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Start and wait for the SysTick tha has counted to zero
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){

    SysTick_Init(a_TimeInMilliSeconds); /* Initialize the SysTick timer with the specified time in milliseconds*/

    while(!(SYSTICK_CTRL_REG & ( 1 << SYSTICK_CTRL_COUNT))){} /*while loop to wait for the flag bit is set to 1 when systick has counted to 0*/

    SYSTICK_CTRL_REG    = 0;     /* Disable the SysTick Timer by Clear the ENABLE Bit */
}
/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to handle ISR for SysTick
**********************************************************************/
void SysTick_Handler(void){

    if(g_CallBackPtr != NULL_PTR){

        /*Call the function using using call-back function*/
        (*g_CallBackPtr)();
    }
}
/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pointer to Function
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the call back function
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){

    g_CallBackPtr = Ptr2Func;

}
/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Stop the SysTick timer
**********************************************************************/
void SysTick_Stop(void){

    SYSTICK_CTRL_REG   &=~(1<< SYSTICK_CTRL_ENABLE);    /* Disable the SysTick Timer by Clear the ENABLE Bit */

}
/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Start The SysTick Timer
**********************************************************************/
void SysTick_Start(void){

    SYSTICK_CTRL_REG   |=  (1<< SYSTICK_CTRL_ENABLE);    /*Enable the SysTick Timer by Set the ENABLE Bit*/

}
/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to DeInit the SysTick Timer
**********************************************************************/
void SysTick_DeInit(void){

    SYSTICK_CTRL_REG    = 0;     /* Disable the SysTick Timer by Clear the ENABLE Bit */

}
