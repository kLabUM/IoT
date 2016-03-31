/*******************************************************************************
* File Name: Decagon_Power.c  
* Version 2.5
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
#include "Decagon_Power.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Decagon_Power__PORT == 15 && ((Decagon_Power__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Decagon_Power_Write
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
void Decagon_Power_Write(uint8 value) 
{
    uint8 staticBits = (Decagon_Power_DR & (uint8)(~Decagon_Power_MASK));
    Decagon_Power_DR = staticBits | ((uint8)(value << Decagon_Power_SHIFT) & Decagon_Power_MASK);
}


/*******************************************************************************
* Function Name: Decagon_Power_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Decagon_Power_DM_STRONG     Strong Drive 
*  Decagon_Power_DM_OD_HI      Open Drain, Drives High 
*  Decagon_Power_DM_OD_LO      Open Drain, Drives Low 
*  Decagon_Power_DM_RES_UP     Resistive Pull Up 
*  Decagon_Power_DM_RES_DWN    Resistive Pull Down 
*  Decagon_Power_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Decagon_Power_DM_DIG_HIZ    High Impedance Digital 
*  Decagon_Power_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Decagon_Power_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Decagon_Power_0, mode);
}


/*******************************************************************************
* Function Name: Decagon_Power_Read
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
*  Macro Decagon_Power_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Decagon_Power_Read(void) 
{
    return (Decagon_Power_PS & Decagon_Power_MASK) >> Decagon_Power_SHIFT;
}


/*******************************************************************************
* Function Name: Decagon_Power_ReadDataReg
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
uint8 Decagon_Power_ReadDataReg(void) 
{
    return (Decagon_Power_DR & Decagon_Power_MASK) >> Decagon_Power_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Decagon_Power_INTSTAT) 

    /*******************************************************************************
    * Function Name: Decagon_Power_ClearInterrupt
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
    uint8 Decagon_Power_ClearInterrupt(void) 
    {
        return (Decagon_Power_INTSTAT & Decagon_Power_MASK) >> Decagon_Power_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
