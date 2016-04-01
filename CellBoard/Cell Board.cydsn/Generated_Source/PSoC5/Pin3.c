/*******************************************************************************
* File Name: Pin3.c  
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
#include "Pin3.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pin3__PORT == 15 && ((Pin3__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pin3_Write
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
void Pin3_Write(uint8 value) 
{
    uint8 staticBits = (Pin3_DR & (uint8)(~Pin3_MASK));
    Pin3_DR = staticBits | ((uint8)(value << Pin3_SHIFT) & Pin3_MASK);
}


/*******************************************************************************
* Function Name: Pin3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin3_DM_STRONG     Strong Drive 
*  Pin3_DM_OD_HI      Open Drain, Drives High 
*  Pin3_DM_OD_LO      Open Drain, Drives Low 
*  Pin3_DM_RES_UP     Resistive Pull Up 
*  Pin3_DM_RES_DWN    Resistive Pull Down 
*  Pin3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin3_DM_DIG_HIZ    High Impedance Digital 
*  Pin3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin3_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin3_0, mode);
}


/*******************************************************************************
* Function Name: Pin3_Read
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
*  Macro Pin3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin3_Read(void) 
{
    return (Pin3_PS & Pin3_MASK) >> Pin3_SHIFT;
}


/*******************************************************************************
* Function Name: Pin3_ReadDataReg
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
uint8 Pin3_ReadDataReg(void) 
{
    return (Pin3_DR & Pin3_MASK) >> Pin3_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin3_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin3_ClearInterrupt
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
    uint8 Pin3_ClearInterrupt(void) 
    {
        return (Pin3_INTSTAT & Pin3_MASK) >> Pin3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
