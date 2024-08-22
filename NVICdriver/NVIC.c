/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: Source file for the TM4C123GH6PM NVIC driver
 *
 * Author: Abdelrahman Hussien
 *
 *******************************************************************************/
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"


/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){

    uint8 bit;
    bit = IRQ_Num % 32;    /*to know which bit i will enable it*/

    if(IRQ_Num < 32){

        NVIC_EN0_REG  |= (1<<bit);
    }
    else if(IRQ_Num < 64){

        NVIC_EN1_REG  |= (1<<bit);
    }
    else if(IRQ_Num < 96){

        NVIC_EN2_REG  |= (1<<bit);
    }
    else if (IRQ_Num < 128) {

        NVIC_EN3_REG  |= (1<<bit);
    }
    else{

        NVIC_EN4_REG  |=(1<<bit);
    }


}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){

    uint8 bitNum;
    bitNum = IRQ_Num % 32;      /*to know which bit i will disable it*/

    if(IRQ_Num < 32){

        NVIC_DIS0_REG  |= (1<<bitNum);
    }
    else if(IRQ_Num < 64){

        NVIC_DIS1_REG  |= (1<<bitNum);
    }
    else if(IRQ_Num < 96){

        NVIC_DIS2_REG  |= (1<<bitNum);
    }
    else if (IRQ_Num < 128) {

        NVIC_DIS3_REG  |= (1<<bitNum);
    }
    else{

        NVIC_DIS4_REG  |= (1<<bitNum);
    }
}
/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table / IRQ_priority
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority value for specific IRQ.
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,NVIC_IRQPriorityType IRQ_Priority){

    uint8 offset = IRQ_Num / 4 ;         /*Calculate the offset to know PRIn*/
    uint8 bit  = ((IRQ_Num % 4)*8) + 5;  /*Calculate the bit number to set the priority*/

    volatile uint32 *interruptAddress = (NVIC_PRI0_REG + offset);

    *interruptAddress |= (IRQ_Priority<<bit);

}

/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception Number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Enable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num){

    Enable_Exceptions();                /*This Macro disable IRQ interrupts*/
    Enable_Faults();                    /*This Macro disable Faults*/

    if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE){

        /*Enable Bus Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL |= (BUS_FAULT_ENABLE_MASK);

    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE){

        /*Enable Usage Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL |= (USAGE_FAULT_ENABLE_MASK);

    }
    else if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE){

        /*Enable Mem Mange Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL |= (MEM_FAULT_ENABLE_MASK);

    }
    else {
            //do nothing
    }
}
/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){

    Disable_Exceptions();             /*This Macro disable IRQ interrupts*/
    Disable_Faults();                 /*This Macro disable Faults*/


    if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE){

        /*Disable Bus Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL &=~ (BUS_FAULT_ENABLE_MASK);

    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE){

        /*Disable USAGE Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL &=~ (USAGE_FAULT_ENABLE_MASK);

    }
    else if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE){

        /*Disable Bus Fault in System Handler Ctrl Register*/
        NVIC_SYSTEM_SYSHNDCTRL &=~ (MEM_FAULT_ENABLE_MASK);

    }
    else {
           //do nothing
    }
}
/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception number - Exception priority
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to set the priority value for specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){

       if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE){

           /* Assign priority to memory management fault */
           NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);

       }
       else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE){

           /* Assign priority to BUS fault */
           NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);

       }
       else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE){

           /* Assign priority to USAGE fault */
           NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);

       }
       else if (Exception_Num == EXCEPTION_SVC_TYPE){

           /* Assign priority to SVC */
           NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);

       }
       else if (Exception_Num == EXCEPTION_PEND_SV_TYPE){

           /* Assign priority to PENDSV */
           NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);

       }
       else if (Exception_Num == EXCEPTION_SYSTICK_TYPE){

           /* Assign priority to SysTick timer */
           NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS );

       }
       else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE) {

           /* Assign priority to Debug Monitor */
           NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
    }

}
