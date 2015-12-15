/*******************************************************************************
* File Name: crustal.c  
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
#include "crustal.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 crustal__PORT == 15 && ((crustal__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: crustal_Write
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
void crustal_Write(uint8 value) 
{
    uint8 staticBits = (crustal_DR & (uint8)(~crustal_MASK));
    crustal_DR = staticBits | ((uint8)(value << crustal_SHIFT) & crustal_MASK);
}


/*******************************************************************************
* Function Name: crustal_SetDriveMode
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
void crustal_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(crustal_0, mode);
}


/*******************************************************************************
* Function Name: crustal_Read
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
*  Macro crustal_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 crustal_Read(void) 
{
    return (crustal_PS & crustal_MASK) >> crustal_SHIFT;
}


/*******************************************************************************
* Function Name: crustal_ReadDataReg
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
uint8 crustal_ReadDataReg(void) 
{
    return (crustal_DR & crustal_MASK) >> crustal_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(crustal_INTSTAT) 

    /*******************************************************************************
    * Function Name: crustal_ClearInterrupt
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
    uint8 crustal_ClearInterrupt(void) 
    {
        return (crustal_INTSTAT & crustal_MASK) >> crustal_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
