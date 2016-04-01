/*******************************************************************************
* File Name: Telit_ControlReg.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Telit_ControlReg.h"

#if !defined(Telit_ControlReg_Sync_ctrl_reg__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
* Function Name: Telit_ControlReg_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void Telit_ControlReg_Write(uint8 control) 
{
    Telit_ControlReg_Control = control;
}


/*******************************************************************************
* Function Name: Telit_ControlReg_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 Telit_ControlReg_Read(void) 
{
    return Telit_ControlReg_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
