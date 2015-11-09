/*******************************************************************************
* File Name: SCCT_Comp_1_PM.c
* Version 1.0
*
* Description:
*  This file provides the power manager source code to the API for SCCT
*  Comparator Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCCT_Comp_1.h"

static SCCT_Comp_1_BACKUP_STRUCT  SCCT_Comp_1_backup;


/*******************************************************************************
* Function Name: SCCT_Comp_1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the SCCT_Comp_1 for low power mode
*  operation (disable for this case). If the SCCT_Comp_1 is enabled, it
*  configures the SCCT_Comp_1 for low power operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SCCT_Comp_1_backup: The structure field 'enableState' is modified
*  depending on the enable state of the SCCT_Comp_1 before entering to
*  sleep mode.
*
* Reentrant:
*  No.
*
* Side Effect:
*  In the inverting mode of SCCT_Comp_1, the output is implemented using
*  UDB. Hence, the SCCT_Comp_1 output level is high when this sleep API is
*  called and it does not go to sleep.
*
*******************************************************************************/
void SCCT_Comp_1_Sleep(void) 
{
    /* Save SCCT_Comp_1 enable state */
    if (0u != (SCCT_Comp_1_PM_ACT_CFG_REG & SCCT_Comp_1_ACT_PWR_EN))
    {
        /* SCCT_Comp_1 is enabled */
        SCCT_Comp_1_backup.enableState = 1u;

        /* Stop the configuration */
        SCCT_Comp_1_Stop();
    }
    else
    {
        /* SCCT_Comp_1 is disabled */
        SCCT_Comp_1_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: SCCT_Comp_1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the SCCT_Comp_1 to the state when
*  SCCT_Comp_1_Sleep() was called.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  SCCT_Comp_1_backup: The structure field 'enableState' is used to
*  restore the enable state of SCCT_Comp_1 after wakeup from sleep mode.
*
* Side Effect:
*  Calling the SCCT_Comp_1_Wakeup() function without first calling the
*  SCCT_Comp_1_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void SCCT_Comp_1_Wakeup(void) 
{
    /* Enables the SCCT_Comp_1 operation */
    if (1u == SCCT_Comp_1_backup.enableState)
    {
        SCCT_Comp_1_Enable();
    } /* Do nothing if SCCT_Comp_1 was disable before */
}


/* [] END OF FILE */
