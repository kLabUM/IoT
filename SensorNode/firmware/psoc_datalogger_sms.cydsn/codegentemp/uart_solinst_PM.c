/*******************************************************************************
* File Name: uart_solinst_PM.c
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

#include "uart_solinst.h"


/***************************************
* Local data allocation
***************************************/

static uart_solinst_BACKUP_STRUCT  uart_solinst_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: uart_solinst_SaveConfig
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
*  uart_solinst_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_solinst_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(uart_solinst_CONTROL_REG_REMOVED == 0u)
            uart_solinst_backup.cr = uart_solinst_CONTROL_REG;
        #endif /* End uart_solinst_CONTROL_REG_REMOVED */

        #if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
            uart_solinst_backup.rx_period = uart_solinst_RXBITCTR_PERIOD_REG;
            uart_solinst_backup.rx_mask = uart_solinst_RXSTATUS_MASK_REG;
            #if (uart_solinst_RXHW_ADDRESS_ENABLED)
                uart_solinst_backup.rx_addr1 = uart_solinst_RXADDRESS1_REG;
                uart_solinst_backup.rx_addr2 = uart_solinst_RXADDRESS2_REG;
            #endif /* End uart_solinst_RXHW_ADDRESS_ENABLED */
        #endif /* End uart_solinst_RX_ENABLED | uart_solinst_HD_ENABLED*/

        #if(uart_solinst_TX_ENABLED)
            #if(uart_solinst_TXCLKGEN_DP)
                uart_solinst_backup.tx_clk_ctr = uart_solinst_TXBITCLKGEN_CTR_REG;
                uart_solinst_backup.tx_clk_compl = uart_solinst_TXBITCLKTX_COMPLETE_REG;
            #else
                uart_solinst_backup.tx_period = uart_solinst_TXBITCTR_PERIOD_REG;
            #endif /*End uart_solinst_TXCLKGEN_DP */
            uart_solinst_backup.tx_mask = uart_solinst_TXSTATUS_MASK_REG;
        #endif /*End uart_solinst_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(uart_solinst_CONTROL_REG_REMOVED == 0u)
            uart_solinst_backup.cr = uart_solinst_CONTROL_REG;
        #endif /* End uart_solinst_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_solinst_RestoreConfig
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
*  uart_solinst_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_solinst_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(uart_solinst_CONTROL_REG_REMOVED == 0u)
            uart_solinst_CONTROL_REG = uart_solinst_backup.cr;
        #endif /* End uart_solinst_CONTROL_REG_REMOVED */

        #if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
            uart_solinst_RXBITCTR_PERIOD_REG = uart_solinst_backup.rx_period;
            uart_solinst_RXSTATUS_MASK_REG = uart_solinst_backup.rx_mask;
            #if (uart_solinst_RXHW_ADDRESS_ENABLED)
                uart_solinst_RXADDRESS1_REG = uart_solinst_backup.rx_addr1;
                uart_solinst_RXADDRESS2_REG = uart_solinst_backup.rx_addr2;
            #endif /* End uart_solinst_RXHW_ADDRESS_ENABLED */
        #endif  /* End (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */

        #if(uart_solinst_TX_ENABLED)
            #if(uart_solinst_TXCLKGEN_DP)
                uart_solinst_TXBITCLKGEN_CTR_REG = uart_solinst_backup.tx_clk_ctr;
                uart_solinst_TXBITCLKTX_COMPLETE_REG = uart_solinst_backup.tx_clk_compl;
            #else
                uart_solinst_TXBITCTR_PERIOD_REG = uart_solinst_backup.tx_period;
            #endif /*End uart_solinst_TXCLKGEN_DP */
            uart_solinst_TXSTATUS_MASK_REG = uart_solinst_backup.tx_mask;
        #endif /*End uart_solinst_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(uart_solinst_CONTROL_REG_REMOVED == 0u)
            uart_solinst_CONTROL_REG = uart_solinst_backup.cr;
        #endif /* End uart_solinst_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_solinst_Sleep
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
*  uart_solinst_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_solinst_Sleep(void)
{

    #if(uart_solinst_RX_ENABLED || uart_solinst_HD_ENABLED)
        if((uart_solinst_RXSTATUS_ACTL_REG  & uart_solinst_INT_ENABLE) != 0u)
        {
            uart_solinst_backup.enableState = 1u;
        }
        else
        {
            uart_solinst_backup.enableState = 0u;
        }
    #else
        if((uart_solinst_TXSTATUS_ACTL_REG  & uart_solinst_INT_ENABLE) !=0u)
        {
            uart_solinst_backup.enableState = 1u;
        }
        else
        {
            uart_solinst_backup.enableState = 0u;
        }
    #endif /* End uart_solinst_RX_ENABLED || uart_solinst_HD_ENABLED*/

    uart_solinst_Stop();
    uart_solinst_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_solinst_Wakeup
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
*  uart_solinst_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_solinst_Wakeup(void)
{
    uart_solinst_RestoreConfig();
    #if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
        uart_solinst_ClearRxBuffer();
    #endif /* End (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */
    #if(uart_solinst_TX_ENABLED || uart_solinst_HD_ENABLED)
        uart_solinst_ClearTxBuffer();
    #endif /* End uart_solinst_TX_ENABLED || uart_solinst_HD_ENABLED */

    if(uart_solinst_backup.enableState != 0u)
    {
        uart_solinst_Enable();
    }
}


/* [] END OF FILE */
