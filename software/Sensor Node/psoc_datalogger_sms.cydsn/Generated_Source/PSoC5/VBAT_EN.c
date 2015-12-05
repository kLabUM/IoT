/*******************************************************************************
* File Name: VBAT_EN.c  
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
#include "VBAT_EN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VBAT_EN__PORT == 15 && ((VBAT_EN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VBAT_EN_Write
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
void VBAT_EN_Write(uint8 value) 
{
    uint8 staticBits = (VBAT_EN_DR & (uint8)(~VBAT_EN_MASK));
    VBAT_EN_DR = staticBits | ((uint8)(value << VBAT_EN_SHIFT) & VBAT_EN_MASK);
}


/*******************************************************************************
* Function Name: VBAT_EN_SetDriveMode
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
void VBAT_EN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VBAT_EN_0, mode);
}


/*******************************************************************************
* Function Name: VBAT_EN_Read
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
*  Macro VBAT_EN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VBAT_EN_Read(void) 
{
    return (VBAT_EN_PS & VBAT_EN_MASK) >> VBAT_EN_SHIFT;
}


/*******************************************************************************
* Function Name: VBAT_EN_ReadDataReg
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
uint8 VBAT_EN_ReadDataReg(void) 
{
    return (VBAT_EN_DR & VBAT_EN_MASK) >> VBAT_EN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VBAT_EN_INTSTAT) 

    /*******************************************************************************
    * Function Name: VBAT_EN_ClearInterrupt
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
    uint8 VBAT_EN_ClearInterrupt(void) 
    {
        return (VBAT_EN_INTSTAT & VBAT_EN_MASK) >> VBAT_EN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
