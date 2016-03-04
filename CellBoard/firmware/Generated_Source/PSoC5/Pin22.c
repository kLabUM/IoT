/*******************************************************************************
* File Name: Pin22.c  
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
#include "Pin22.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pin22__PORT == 15 && ((Pin22__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pin22_Write
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
void Pin22_Write(uint8 value) 
{
    uint8 staticBits = (Pin22_DR & (uint8)(~Pin22_MASK));
    Pin22_DR = staticBits | ((uint8)(value << Pin22_SHIFT) & Pin22_MASK);
}


/*******************************************************************************
* Function Name: Pin22_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin22_DM_STRONG     Strong Drive 
*  Pin22_DM_OD_HI      Open Drain, Drives High 
*  Pin22_DM_OD_LO      Open Drain, Drives Low 
*  Pin22_DM_RES_UP     Resistive Pull Up 
*  Pin22_DM_RES_DWN    Resistive Pull Down 
*  Pin22_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin22_DM_DIG_HIZ    High Impedance Digital 
*  Pin22_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin22_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin22_0, mode);
}


/*******************************************************************************
* Function Name: Pin22_Read
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
*  Macro Pin22_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin22_Read(void) 
{
    return (Pin22_PS & Pin22_MASK) >> Pin22_SHIFT;
}


/*******************************************************************************
* Function Name: Pin22_ReadDataReg
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
uint8 Pin22_ReadDataReg(void) 
{
    return (Pin22_DR & Pin22_MASK) >> Pin22_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin22_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin22_ClearInterrupt
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
    uint8 Pin22_ClearInterrupt(void) 
    {
        return (Pin22_INTSTAT & Pin22_MASK) >> Pin22_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
