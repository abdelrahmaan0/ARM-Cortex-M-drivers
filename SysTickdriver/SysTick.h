 /******************************************************************************
 *
 * Module: SysTick Timer
 *
 * File Name: SysTick.h
 *
 * Description: Header file for the TM4C123GH6PM SysTick Timer driver
 *
 * Author: Abdelrahman Hussien
 *
 *******************************************************************************/
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/
#define SYSTICK_CTRL_COUNT    16
#define SYSTICK_CTRL_ENABLE   0

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/


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

void SysTick_Init(uint16 a_TimeInMilliSeconds);

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

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

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

void SysTick_Handler(void);

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

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

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

void SysTick_Stop(void);

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

void SysTick_Start(void);

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

void SysTick_DeInit(void);



#endif
