/*******************************************************************************
* File Name: Ultrasonic_ON.c  
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
#include "Ultrasonic_ON.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Ultrasonic_ON__PORT == 15 && ((Ultrasonic_ON__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Ultrasonic_ON_Write
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
void Ultrasonic_ON_Write(uint8 value) 
{
    uint8 staticBits = (Ultrasonic_ON_DR & (uint8)(~Ultrasonic_ON_MASK));
    Ultrasonic_ON_DR = staticBits | ((uint8)(value << Ultrasonic_ON_SHIFT) & Ultrasonic_ON_MASK);
}


/*******************************************************************************
* Function Name: Ultrasonic_ON_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Ultrasonic_ON_DM_STRONG     Strong Drive 
*  Ultrasonic_ON_DM_OD_HI      Open Drain, Drives High 
*  Ultrasonic_ON_DM_OD_LO      Open Drain, Drives Low 
*  Ultrasonic_ON_DM_RES_UP     Resistive Pull Up 
*  Ultrasonic_ON_DM_RES_DWN    Resistive Pull Down 
*  Ultrasonic_ON_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Ultrasonic_ON_DM_DIG_HIZ    High Impedance Digital 
*  Ultrasonic_ON_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Ultrasonic_ON_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Ultrasonic_ON_0, mode);
}


/*******************************************************************************
* Function Name: Ultrasonic_ON_Read
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
*  Macro Ultrasonic_ON_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Ultrasonic_ON_Read(void) 
{
    return (Ultrasonic_ON_PS & Ultrasonic_ON_MASK) >> Ultrasonic_ON_SHIFT;
}


/*******************************************************************************
* Function Name: Ultrasonic_ON_ReadDataReg
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
uint8 Ultrasonic_ON_ReadDataReg(void) 
{
    return (Ultrasonic_ON_DR & Ultrasonic_ON_MASK) >> Ultrasonic_ON_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Ultrasonic_ON_INTSTAT) 

    /*******************************************************************************
    * Function Name: Ultrasonic_ON_ClearInterrupt
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
    uint8 Ultrasonic_ON_ClearInterrupt(void) 
    {
        return (Ultrasonic_ON_INTSTAT & Ultrasonic_ON_MASK) >> Ultrasonic_ON_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
