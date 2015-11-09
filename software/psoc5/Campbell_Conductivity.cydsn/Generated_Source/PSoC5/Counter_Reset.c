/*******************************************************************************
* File Name: Counter_Reset.c  
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
#include "Counter_Reset.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Counter_Reset__PORT == 15 && ((Counter_Reset__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Counter_Reset_Write
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
void Counter_Reset_Write(uint8 value) 
{
    uint8 staticBits = (Counter_Reset_DR & (uint8)(~Counter_Reset_MASK));
    Counter_Reset_DR = staticBits | ((uint8)(value << Counter_Reset_SHIFT) & Counter_Reset_MASK);
}


/*******************************************************************************
* Function Name: Counter_Reset_SetDriveMode
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
void Counter_Reset_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Counter_Reset_0, mode);
}


/*******************************************************************************
* Function Name: Counter_Reset_Read
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
*  Macro Counter_Reset_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Counter_Reset_Read(void) 
{
    return (Counter_Reset_PS & Counter_Reset_MASK) >> Counter_Reset_SHIFT;
}


/*******************************************************************************
* Function Name: Counter_Reset_ReadDataReg
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
uint8 Counter_Reset_ReadDataReg(void) 
{
    return (Counter_Reset_DR & Counter_Reset_MASK) >> Counter_Reset_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Counter_Reset_INTSTAT) 

    /*******************************************************************************
    * Function Name: Counter_Reset_ClearInterrupt
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
    uint8 Counter_Reset_ClearInterrupt(void) 
    {
        return (Counter_Reset_INTSTAT & Counter_Reset_MASK) >> Counter_Reset_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
