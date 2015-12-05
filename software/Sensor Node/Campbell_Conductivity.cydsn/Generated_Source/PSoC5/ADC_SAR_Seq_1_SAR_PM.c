/*******************************************************************************
* File Name: ADC_SAR_Seq_1_SAR_PM.c
* Version 2.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_Seq_1_SAR.h"


/***************************************
* Local data allocation
***************************************/

static ADC_SAR_Seq_1_SAR_BACKUP_STRUCT  ADC_SAR_Seq_1_SAR_backup =
{
    ADC_SAR_Seq_1_SAR_DISABLED
};


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_SAR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_1_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_SAR_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_1_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_SAR_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_1_SAR_backup - modified.
*
*******************************************************************************/
void ADC_SAR_Seq_1_SAR_Sleep(void)
{
    if((ADC_SAR_Seq_1_SAR_PWRMGR_SAR_REG  & ADC_SAR_Seq_1_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_SAR_Seq_1_SAR_SAR_CSR0_REG & ADC_SAR_Seq_1_SAR_SAR_SOF_START_CONV) != 0u)
        {
            ADC_SAR_Seq_1_SAR_backup.enableState = ADC_SAR_Seq_1_SAR_ENABLED | ADC_SAR_Seq_1_SAR_STARTED;
        }
        else
        {
            ADC_SAR_Seq_1_SAR_backup.enableState = ADC_SAR_Seq_1_SAR_ENABLED;
        }
        ADC_SAR_Seq_1_SAR_Stop();
    }
    else
    {
        ADC_SAR_Seq_1_SAR_backup.enableState = ADC_SAR_Seq_1_SAR_DISABLED;
    }
    /*ADC_SAR_Seq_1_SAR_SaveConfig();*/
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_SAR_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_1_SAR_backup - used.
*
*******************************************************************************/
void ADC_SAR_Seq_1_SAR_Wakeup(void)
{
    /*ADC_SAR_Seq_1_SAR_RestoreConfig();*/
    if(ADC_SAR_Seq_1_SAR_backup.enableState != ADC_SAR_Seq_1_SAR_DISABLED)
    {
        ADC_SAR_Seq_1_SAR_Enable();
        #if(ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER)
            if((ADC_SAR_Seq_1_SAR_backup.enableState & ADC_SAR_Seq_1_SAR_STARTED) != 0u)
            {
                ADC_SAR_Seq_1_SAR_StartConvert();
            }
        #endif /* End ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER */
        
    }
}


/* [] END OF FILE */
