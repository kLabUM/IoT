/*******************************************************************************
* File Name: Telit_UART_PM.c
* Version 2.30
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

#include "Telit_UART.h"


/***************************************
* Local data allocation
***************************************/

static Telit_UART_BACKUP_STRUCT  Telit_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Telit_UART_SaveConfig
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
* Global Variables:
*  Telit_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Telit_UART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(Telit_UART_CONTROL_REG_REMOVED == 0u)
            Telit_UART_backup.cr = Telit_UART_CONTROL_REG;
        #endif /* End Telit_UART_CONTROL_REG_REMOVED */

        #if( (Telit_UART_RX_ENABLED) || (Telit_UART_HD_ENABLED) )
            Telit_UART_backup.rx_period = Telit_UART_RXBITCTR_PERIOD_REG;
            Telit_UART_backup.rx_mask = Telit_UART_RXSTATUS_MASK_REG;
            #if (Telit_UART_RXHW_ADDRESS_ENABLED)
                Telit_UART_backup.rx_addr1 = Telit_UART_RXADDRESS1_REG;
                Telit_UART_backup.rx_addr2 = Telit_UART_RXADDRESS2_REG;
            #endif /* End Telit_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End Telit_UART_RX_ENABLED | Telit_UART_HD_ENABLED*/

        #if(Telit_UART_TX_ENABLED)
            #if(Telit_UART_TXCLKGEN_DP)
                Telit_UART_backup.tx_clk_ctr = Telit_UART_TXBITCLKGEN_CTR_REG;
                Telit_UART_backup.tx_clk_compl = Telit_UART_TXBITCLKTX_COMPLETE_REG;
            #else
                Telit_UART_backup.tx_period = Telit_UART_TXBITCTR_PERIOD_REG;
            #endif /*End Telit_UART_TXCLKGEN_DP */
            Telit_UART_backup.tx_mask = Telit_UART_TXSTATUS_MASK_REG;
        #endif /*End Telit_UART_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(Telit_UART_CONTROL_REG_REMOVED == 0u)
            Telit_UART_backup.cr = Telit_UART_CONTROL_REG;
        #endif /* End Telit_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Telit_UART_RestoreConfig
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
* Global Variables:
*  Telit_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Telit_UART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(Telit_UART_CONTROL_REG_REMOVED == 0u)
            Telit_UART_CONTROL_REG = Telit_UART_backup.cr;
        #endif /* End Telit_UART_CONTROL_REG_REMOVED */

        #if( (Telit_UART_RX_ENABLED) || (Telit_UART_HD_ENABLED) )
            Telit_UART_RXBITCTR_PERIOD_REG = Telit_UART_backup.rx_period;
            Telit_UART_RXSTATUS_MASK_REG = Telit_UART_backup.rx_mask;
            #if (Telit_UART_RXHW_ADDRESS_ENABLED)
                Telit_UART_RXADDRESS1_REG = Telit_UART_backup.rx_addr1;
                Telit_UART_RXADDRESS2_REG = Telit_UART_backup.rx_addr2;
            #endif /* End Telit_UART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (Telit_UART_RX_ENABLED) || (Telit_UART_HD_ENABLED) */

        #if(Telit_UART_TX_ENABLED)
            #if(Telit_UART_TXCLKGEN_DP)
                Telit_UART_TXBITCLKGEN_CTR_REG = Telit_UART_backup.tx_clk_ctr;
                Telit_UART_TXBITCLKTX_COMPLETE_REG = Telit_UART_backup.tx_clk_compl;
            #else
                Telit_UART_TXBITCTR_PERIOD_REG = Telit_UART_backup.tx_period;
            #endif /*End Telit_UART_TXCLKGEN_DP */
            Telit_UART_TXSTATUS_MASK_REG = Telit_UART_backup.tx_mask;
        #endif /*End Telit_UART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(Telit_UART_CONTROL_REG_REMOVED == 0u)
            Telit_UART_CONTROL_REG = Telit_UART_backup.cr;
        #endif /* End Telit_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Telit_UART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Telit_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Telit_UART_Sleep(void)
{

    #if(Telit_UART_RX_ENABLED || Telit_UART_HD_ENABLED)
        if((Telit_UART_RXSTATUS_ACTL_REG  & Telit_UART_INT_ENABLE) != 0u)
        {
            Telit_UART_backup.enableState = 1u;
        }
        else
        {
            Telit_UART_backup.enableState = 0u;
        }
    #else
        if((Telit_UART_TXSTATUS_ACTL_REG  & Telit_UART_INT_ENABLE) !=0u)
        {
            Telit_UART_backup.enableState = 1u;
        }
        else
        {
            Telit_UART_backup.enableState = 0u;
        }
    #endif /* End Telit_UART_RX_ENABLED || Telit_UART_HD_ENABLED*/

    Telit_UART_Stop();
    Telit_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: Telit_UART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Telit_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Telit_UART_Wakeup(void)
{
    Telit_UART_RestoreConfig();
    #if( (Telit_UART_RX_ENABLED) || (Telit_UART_HD_ENABLED) )
        Telit_UART_ClearRxBuffer();
    #endif /* End (Telit_UART_RX_ENABLED) || (Telit_UART_HD_ENABLED) */
    #if(Telit_UART_TX_ENABLED || Telit_UART_HD_ENABLED)
        Telit_UART_ClearTxBuffer();
    #endif /* End Telit_UART_TX_ENABLED || Telit_UART_HD_ENABLED */

    if(Telit_UART_backup.enableState != 0u)
    {
        Telit_UART_Enable();
    }
}


/* [] END OF FILE */
