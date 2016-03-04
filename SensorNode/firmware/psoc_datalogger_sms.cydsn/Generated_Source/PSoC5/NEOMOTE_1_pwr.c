/*******************************************************************************
* File Name: NEOMOTE_1_pwr.c  
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
#include "NEOMOTE_1_pwr.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 NEOMOTE_1_pwr__PORT == 15 && ((NEOMOTE_1_pwr__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: NEOMOTE_1_pwr_Write
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
void NEOMOTE_1_pwr_Write(uint8 value) 
{
    uint8 staticBits = (NEOMOTE_1_pwr_DR & (uint8)(~NEOMOTE_1_pwr_MASK));
    NEOMOTE_1_pwr_DR = staticBits | ((uint8)(value << NEOMOTE_1_pwr_SHIFT) & NEOMOTE_1_pwr_MASK);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_pwr_SetDriveMode
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
void NEOMOTE_1_pwr_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(NEOMOTE_1_pwr_0, mode);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_pwr_Read
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
*  Macro NEOMOTE_1_pwr_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 NEOMOTE_1_pwr_Read(void) 
{
    return (NEOMOTE_1_pwr_PS & NEOMOTE_1_pwr_MASK) >> NEOMOTE_1_pwr_SHIFT;
}


/*******************************************************************************
* Function Name: NEOMOTE_1_pwr_ReadDataReg
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
uint8 NEOMOTE_1_pwr_ReadDataReg(void) 
{
    return (NEOMOTE_1_pwr_DR & NEOMOTE_1_pwr_MASK) >> NEOMOTE_1_pwr_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(NEOMOTE_1_pwr_INTSTAT) 

    /*******************************************************************************
    * Function Name: NEOMOTE_1_pwr_ClearInterrupt
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
    uint8 NEOMOTE_1_pwr_ClearInterrupt(void) 
    {
        return (NEOMOTE_1_pwr_INTSTAT & NEOMOTE_1_pwr_MASK) >> NEOMOTE_1_pwr_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
