/*******************************************************************************
* File Name: inbt2.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "inbt2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 inbt2__PORT == 15 && ((inbt2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: inbt2_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void inbt2_Write(uint8 value) 
{
    uint8 staticBits = (inbt2_DR & (uint8)(~inbt2_MASK));
    inbt2_DR = staticBits | ((uint8)(value << inbt2_SHIFT) & inbt2_MASK);
}


/*******************************************************************************
* Function Name: inbt2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void inbt2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(inbt2_0, mode);
}


/*******************************************************************************
* Function Name: inbt2_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro inbt2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 inbt2_Read(void) 
{
    return (inbt2_PS & inbt2_MASK) >> inbt2_SHIFT;
}


/*******************************************************************************
* Function Name: inbt2_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 inbt2_ReadDataReg(void) 
{
    return (inbt2_DR & inbt2_MASK) >> inbt2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(inbt2_INTSTAT) 

    /*******************************************************************************
    * Function Name: inbt2_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 inbt2_ClearInterrupt(void) 
    {
        return (inbt2_INTSTAT & inbt2_MASK) >> inbt2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
