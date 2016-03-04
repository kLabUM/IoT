/*******************************************************************************
* File Name: Pin35.c  
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
#include "Pin35.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pin35__PORT == 15 && ((Pin35__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pin35_Write
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
void Pin35_Write(uint8 value) 
{
    uint8 staticBits = (Pin35_DR & (uint8)(~Pin35_MASK));
    Pin35_DR = staticBits | ((uint8)(value << Pin35_SHIFT) & Pin35_MASK);
}


/*******************************************************************************
* Function Name: Pin35_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin35_DM_STRONG     Strong Drive 
*  Pin35_DM_OD_HI      Open Drain, Drives High 
*  Pin35_DM_OD_LO      Open Drain, Drives Low 
*  Pin35_DM_RES_UP     Resistive Pull Up 
*  Pin35_DM_RES_DWN    Resistive Pull Down 
*  Pin35_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin35_DM_DIG_HIZ    High Impedance Digital 
*  Pin35_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin35_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin35_0, mode);
}


/*******************************************************************************
* Function Name: Pin35_Read
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
*  Macro Pin35_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin35_Read(void) 
{
    return (Pin35_PS & Pin35_MASK) >> Pin35_SHIFT;
}


/*******************************************************************************
* Function Name: Pin35_ReadDataReg
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
uint8 Pin35_ReadDataReg(void) 
{
    return (Pin35_DR & Pin35_MASK) >> Pin35_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin35_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin35_ClearInterrupt
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
    uint8 Pin35_ClearInterrupt(void) 
    {
        return (Pin35_INTSTAT & Pin35_MASK) >> Pin35_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
