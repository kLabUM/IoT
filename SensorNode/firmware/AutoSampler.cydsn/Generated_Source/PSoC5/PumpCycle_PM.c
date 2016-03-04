/*******************************************************************************
* File Name: PumpCycle.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PumpCycle.h"

static PumpCycle_backupStruct PumpCycle_backup;


/*******************************************************************************
* Function Name: PumpCycle_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void PumpCycle_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: PumpCycle_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
********************************************************************************/
void PumpCycle_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: PumpCycle_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  PumpCycle_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void PumpCycle_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(PumpCycle_ACT_PWR_EN == (PumpCycle_PWRMGR & PumpCycle_ACT_PWR_EN))
    {
        /* Comp is enabled */
        PumpCycle_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        PumpCycle_backup.enableState = 0u;
    }    
    
    PumpCycle_Stop();
    PumpCycle_SaveConfig();
}


/*******************************************************************************
* Function Name: PumpCycle_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  PumpCycle_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PumpCycle_Wakeup(void) 
{
    PumpCycle_RestoreConfig();
    
    if(PumpCycle_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        PumpCycle_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
