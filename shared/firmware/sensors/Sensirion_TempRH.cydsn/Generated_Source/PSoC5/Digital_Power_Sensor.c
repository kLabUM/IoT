/*******************************************************************************
* File Name: Digital_Power_Sensor.c  
* Version 2.0
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
#include "Digital_Power_Sensor.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Digital_Power_Sensor__PORT == 15 && ((Digital_Power_Sensor__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Digital_Power_Sensor_Write
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
void Digital_Power_Sensor_Write(uint8 value) 
{
    uint8 staticBits = (Digital_Power_Sensor_DR & (uint8)(~Digital_Power_Sensor_MASK));
    Digital_Power_Sensor_DR = staticBits | ((uint8)(value << Digital_Power_Sensor_SHIFT) & Digital_Power_Sensor_MASK);
}


/*******************************************************************************
* Function Name: Digital_Power_Sensor_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Digital_Power_Sensor_DM_STRONG     Strong Drive 
*  Digital_Power_Sensor_DM_OD_HI      Open Drain, Drives High 
*  Digital_Power_Sensor_DM_OD_LO      Open Drain, Drives Low 
*  Digital_Power_Sensor_DM_RES_UP     Resistive Pull Up 
*  Digital_Power_Sensor_DM_RES_DWN    Resistive Pull Down 
*  Digital_Power_Sensor_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Digital_Power_Sensor_DM_DIG_HIZ    High Impedance Digital 
*  Digital_Power_Sensor_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Digital_Power_Sensor_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Digital_Power_Sensor_0, mode);
}


/*******************************************************************************
* Function Name: Digital_Power_Sensor_Read
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
*  Macro Digital_Power_Sensor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Digital_Power_Sensor_Read(void) 
{
    return (Digital_Power_Sensor_PS & Digital_Power_Sensor_MASK) >> Digital_Power_Sensor_SHIFT;
}


/*******************************************************************************
* Function Name: Digital_Power_Sensor_ReadDataReg
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
uint8 Digital_Power_Sensor_ReadDataReg(void) 
{
    return (Digital_Power_Sensor_DR & Digital_Power_Sensor_MASK) >> Digital_Power_Sensor_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Digital_Power_Sensor_INTSTAT) 

    /*******************************************************************************
    * Function Name: Digital_Power_Sensor_ClearInterrupt
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
    uint8 Digital_Power_Sensor_ClearInterrupt(void) 
    {
        return (Digital_Power_Sensor_INTSTAT & Digital_Power_Sensor_MASK) >> Digital_Power_Sensor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
