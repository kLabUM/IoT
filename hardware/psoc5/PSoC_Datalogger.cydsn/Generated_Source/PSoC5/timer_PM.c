/*******************************************************************************
* File Name: timer_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "timer.h"
static timer_backupStruct timer_backup;


/*******************************************************************************
* Function Name: timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void timer_SaveConfig(void) 
{
    #if (!timer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            timer_backup.TimerUdb = timer_ReadCounter();
            timer_backup.TimerPeriod = timer_ReadPeriod();
            timer_backup.InterruptMaskValue = timer_STATUS_MASK;
            #if (timer_UsingHWCaptureCounter)
                timer_backup.TimerCaptureCounter = timer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            timer_backup.TimerUdb = timer_ReadCounter();
            timer_backup.InterruptMaskValue = timer_STATUS_MASK;
            #if (timer_UsingHWCaptureCounter)
                timer_backup.TimerCaptureCounter = timer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!timer_ControlRegRemoved)
            timer_backup.TimerControlRegister = timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: timer_RestoreConfig
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
* Global variables:
*  timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void timer_RestoreConfig(void) 
{   
    #if (!timer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 timer_interruptState;

            timer_WriteCounter(timer_backup.TimerUdb);
            timer_WritePeriod(timer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            timer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            timer_STATUS_AUX_CTRL |= timer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(timer_interruptState);
            timer_STATUS_MASK =timer_backup.InterruptMaskValue;
            #if (timer_UsingHWCaptureCounter)
                timer_SetCaptureCount(timer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            timer_WriteCounter(timer_backup.TimerUdb);
            timer_STATUS_MASK =timer_backup.InterruptMaskValue;
            #if (timer_UsingHWCaptureCounter)
                timer_SetCaptureCount(timer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!timer_ControlRegRemoved)
            timer_WriteControlRegister(timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void timer_Sleep(void) 
{
    #if(!timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(timer_CTRL_ENABLE == (timer_CONTROL & timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    timer_Stop();
    timer_SaveConfig();
}


/*******************************************************************************
* Function Name: timer_Wakeup
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
*  timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void timer_Wakeup(void) 
{
    timer_RestoreConfig();
    #if(!timer_ControlRegRemoved)
        if(timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
