/*******************************************************************************
* File Name: Pin34.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Pin34.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pin34__PORT == 15 && ((Pin34__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pin34_Write
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
void Pin34_Write(uint8 value) 
{
    uint8 staticBits = (Pin34_DR & (uint8)(~Pin34_MASK));
    Pin34_DR = staticBits | ((uint8)(value << Pin34_SHIFT) & Pin34_MASK);
}


/*******************************************************************************
* Function Name: Pin34_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin34_DM_STRONG     Strong Drive 
*  Pin34_DM_OD_HI      Open Drain, Drives High 
*  Pin34_DM_OD_LO      Open Drain, Drives Low 
*  Pin34_DM_RES_UP     Resistive Pull Up 
*  Pin34_DM_RES_DWN    Resistive Pull Down 
*  Pin34_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin34_DM_DIG_HIZ    High Impedance Digital 
*  Pin34_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin34_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin34_0, mode);
}


/*******************************************************************************
* Function Name: Pin34_Read
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
*  Macro Pin34_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin34_Read(void) 
{
    return (Pin34_PS & Pin34_MASK) >> Pin34_SHIFT;
}


/*******************************************************************************
* Function Name: Pin34_ReadDataReg
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
uint8 Pin34_ReadDataReg(void) 
{
    return (Pin34_DR & Pin34_MASK) >> Pin34_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin34_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin34_ClearInterrupt
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
    uint8 Pin34_ClearInterrupt(void) 
    {
        return (Pin34_INTSTAT & Pin34_MASK) >> Pin34_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
