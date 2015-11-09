/*******************************************************************************
* File Name: pwr_pin.c  
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
#include "pwr_pin.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 pwr_pin__PORT == 15 && ((pwr_pin__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: pwr_pin_Write
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
void pwr_pin_Write(uint8 value) 
{
    uint8 staticBits = (pwr_pin_DR & (uint8)(~pwr_pin_MASK));
    pwr_pin_DR = staticBits | ((uint8)(value << pwr_pin_SHIFT) & pwr_pin_MASK);
}


/*******************************************************************************
* Function Name: pwr_pin_SetDriveMode
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
void pwr_pin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pwr_pin_0, mode);
}


/*******************************************************************************
* Function Name: pwr_pin_Read
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
*  Macro pwr_pin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pwr_pin_Read(void) 
{
    return (pwr_pin_PS & pwr_pin_MASK) >> pwr_pin_SHIFT;
}


/*******************************************************************************
* Function Name: pwr_pin_ReadDataReg
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
uint8 pwr_pin_ReadDataReg(void) 
{
    return (pwr_pin_DR & pwr_pin_MASK) >> pwr_pin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pwr_pin_INTSTAT) 

    /*******************************************************************************
    * Function Name: pwr_pin_ClearInterrupt
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
    uint8 pwr_pin_ClearInterrupt(void) 
    {
        return (pwr_pin_INTSTAT & pwr_pin_MASK) >> pwr_pin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
