/*******************************************************************************
* File Name: Mixer_2_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for 
*  the MIXER component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Mixer_2.h"

static Mixer_2_backupStruct  Mixer_2_backup;


/*******************************************************************************
* Function Name: Mixer_2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void Mixer_2_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: Mixer_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void Mixer_2_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: Mixer_2_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Mixer_2_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Mixer_2_Sleep(void) 
{
    /* Save Mixer enable state */
    if((Mixer_2_PM_ACT_CFG_REG & Mixer_2_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Mixer_2_backup.enableState = 1u;
        /* Stop the configuration */
        Mixer_2_Stop();
    }
    else
    {
        /* Component is disabled */
        Mixer_2_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    Mixer_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Mixer_2_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  Mixer_2_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Mixer_2_Wakeup(void) 
{
    /* Restore the user configuration */
    Mixer_2_RestoreConfig();
    
    /* Enable's the component operation */
    if(Mixer_2_backup.enableState == 1u)
    {
        Mixer_2_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
