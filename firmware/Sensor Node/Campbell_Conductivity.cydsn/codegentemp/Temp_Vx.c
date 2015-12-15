/*******************************************************************************
* File Name: Temp_Vx.c  
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
#include "Temp_Vx.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Temp_Vx__PORT == 15 && ((Temp_Vx__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Temp_Vx_Write
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
void Temp_Vx_Write(uint8 value) 
{
    uint8 staticBits = (Temp_Vx_DR & (uint8)(~Temp_Vx_MASK));
    Temp_Vx_DR = staticBits | ((uint8)(value << Temp_Vx_SHIFT) & Temp_Vx_MASK);
}


/*******************************************************************************
* Function Name: Temp_Vx_SetDriveMode
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
void Temp_Vx_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Temp_Vx_0, mode);
}


/*******************************************************************************
* Function Name: Temp_Vx_Read
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
*  Macro Temp_Vx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Temp_Vx_Read(void) 
{
    return (Temp_Vx_PS & Temp_Vx_MASK) >> Temp_Vx_SHIFT;
}


/*******************************************************************************
* Function Name: Temp_Vx_ReadDataReg
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
uint8 Temp_Vx_ReadDataReg(void) 
{
    return (Temp_Vx_DR & Temp_Vx_MASK) >> Temp_Vx_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Temp_Vx_INTSTAT) 

    /*******************************************************************************
    * Function Name: Temp_Vx_ClearInterrupt
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
    uint8 Temp_Vx_ClearInterrupt(void) 
    {
        return (Temp_Vx_INTSTAT & Temp_Vx_MASK) >> Temp_Vx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
