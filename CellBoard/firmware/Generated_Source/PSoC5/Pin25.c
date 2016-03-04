/*******************************************************************************
* File Name: Pin25.c  
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
#include "Pin25.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pin25__PORT == 15 && ((Pin25__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pin25_Write
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
void Pin25_Write(uint8 value) 
{
    uint8 staticBits = (Pin25_DR & (uint8)(~Pin25_MASK));
    Pin25_DR = staticBits | ((uint8)(value << Pin25_SHIFT) & Pin25_MASK);
}


/*******************************************************************************
* Function Name: Pin25_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin25_DM_STRONG     Strong Drive 
*  Pin25_DM_OD_HI      Open Drain, Drives High 
*  Pin25_DM_OD_LO      Open Drain, Drives Low 
*  Pin25_DM_RES_UP     Resistive Pull Up 
*  Pin25_DM_RES_DWN    Resistive Pull Down 
*  Pin25_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin25_DM_DIG_HIZ    High Impedance Digital 
*  Pin25_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin25_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin25_0, mode);
}


/*******************************************************************************
* Function Name: Pin25_Read
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
*  Macro Pin25_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin25_Read(void) 
{
    return (Pin25_PS & Pin25_MASK) >> Pin25_SHIFT;
}


/*******************************************************************************
* Function Name: Pin25_ReadDataReg
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
uint8 Pin25_ReadDataReg(void) 
{
    return (Pin25_DR & Pin25_MASK) >> Pin25_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin25_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin25_ClearInterrupt
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
    uint8 Pin25_ClearInterrupt(void) 
    {
        return (Pin25_INTSTAT & Pin25_MASK) >> Pin25_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
