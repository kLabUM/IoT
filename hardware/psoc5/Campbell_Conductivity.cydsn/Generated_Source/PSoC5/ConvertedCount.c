/*******************************************************************************
* File Name: ConvertedCount.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ConvertedCount.h"

#if !defined(ConvertedCount_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: ConvertedCount_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 ConvertedCount_Read(void) 
{ 
    return ConvertedCount_Status;
}


/*******************************************************************************
* Function Name: ConvertedCount_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConvertedCount_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ConvertedCount_Status_Aux_Ctrl |= ConvertedCount_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConvertedCount_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConvertedCount_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ConvertedCount_Status_Aux_Ctrl &= (uint8)(~ConvertedCount_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConvertedCount_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void ConvertedCount_WriteMask(uint8 mask) 
{
    #if(ConvertedCount_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << ConvertedCount_INPUTS) - 1u);
	#endif /* End ConvertedCount_INPUTS < 8u */
    ConvertedCount_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: ConvertedCount_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 ConvertedCount_ReadMask(void) 
{
    return ConvertedCount_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
