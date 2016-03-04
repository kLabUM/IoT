/*******************************************************************************
* File Name: pump_active.c  
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
#include "pump_active.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 pump_active__PORT == 15 && ((pump_active__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: pump_active_Write
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
void pump_active_Write(uint8 value) 
{
    uint8 staticBits = (pump_active_DR & (uint8)(~pump_active_MASK));
    pump_active_DR = staticBits | ((uint8)(value << pump_active_SHIFT) & pump_active_MASK);
}


/*******************************************************************************
* Function Name: pump_active_SetDriveMode
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
void pump_active_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pump_active_0, mode);
}


/*******************************************************************************
* Function Name: pump_active_Read
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
*  Macro pump_active_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pump_active_Read(void) 
{
    return (pump_active_PS & pump_active_MASK) >> pump_active_SHIFT;
}


/*******************************************************************************
* Function Name: pump_active_ReadDataReg
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
uint8 pump_active_ReadDataReg(void) 
{
    return (pump_active_DR & pump_active_MASK) >> pump_active_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pump_active_INTSTAT) 

    /*******************************************************************************
    * Function Name: pump_active_ClearInterrupt
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
    uint8 pump_active_ClearInterrupt(void) 
    {
        return (pump_active_INTSTAT & pump_active_MASK) >> pump_active_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
