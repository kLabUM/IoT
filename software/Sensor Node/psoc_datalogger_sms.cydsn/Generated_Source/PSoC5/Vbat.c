/*******************************************************************************
* File Name: Vbat.c  
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
#include "Vbat.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Vbat__PORT == 15 && ((Vbat__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Vbat_Write
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
void Vbat_Write(uint8 value) 
{
    uint8 staticBits = (Vbat_DR & (uint8)(~Vbat_MASK));
    Vbat_DR = staticBits | ((uint8)(value << Vbat_SHIFT) & Vbat_MASK);
}


/*******************************************************************************
* Function Name: Vbat_SetDriveMode
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
void Vbat_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Vbat_0, mode);
}


/*******************************************************************************
* Function Name: Vbat_Read
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
*  Macro Vbat_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Vbat_Read(void) 
{
    return (Vbat_PS & Vbat_MASK) >> Vbat_SHIFT;
}


/*******************************************************************************
* Function Name: Vbat_ReadDataReg
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
uint8 Vbat_ReadDataReg(void) 
{
    return (Vbat_DR & Vbat_MASK) >> Vbat_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Vbat_INTSTAT) 

    /*******************************************************************************
    * Function Name: Vbat_ClearInterrupt
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
    uint8 Vbat_ClearInterrupt(void) 
    {
        return (Vbat_INTSTAT & Vbat_MASK) >> Vbat_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
