/*******************************************************************************
* File Name: Telit_ON.c  
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
#include "Telit_ON.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Telit_ON__PORT == 15 && ((Telit_ON__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Telit_ON_Write
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
void Telit_ON_Write(uint8 value) 
{
    uint8 staticBits = (Telit_ON_DR & (uint8)(~Telit_ON_MASK));
    Telit_ON_DR = staticBits | ((uint8)(value << Telit_ON_SHIFT) & Telit_ON_MASK);
}


/*******************************************************************************
* Function Name: Telit_ON_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Telit_ON_DM_STRONG     Strong Drive 
*  Telit_ON_DM_OD_HI      Open Drain, Drives High 
*  Telit_ON_DM_OD_LO      Open Drain, Drives Low 
*  Telit_ON_DM_RES_UP     Resistive Pull Up 
*  Telit_ON_DM_RES_DWN    Resistive Pull Down 
*  Telit_ON_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Telit_ON_DM_DIG_HIZ    High Impedance Digital 
*  Telit_ON_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Telit_ON_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Telit_ON_0, mode);
}


/*******************************************************************************
* Function Name: Telit_ON_Read
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
*  Macro Telit_ON_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Telit_ON_Read(void) 
{
    return (Telit_ON_PS & Telit_ON_MASK) >> Telit_ON_SHIFT;
}


/*******************************************************************************
* Function Name: Telit_ON_ReadDataReg
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
uint8 Telit_ON_ReadDataReg(void) 
{
    return (Telit_ON_DR & Telit_ON_MASK) >> Telit_ON_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Telit_ON_INTSTAT) 

    /*******************************************************************************
    * Function Name: Telit_ON_ClearInterrupt
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
    uint8 Telit_ON_ClearInterrupt(void) 
    {
        return (Telit_ON_INTSTAT & Telit_ON_MASK) >> Telit_ON_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
