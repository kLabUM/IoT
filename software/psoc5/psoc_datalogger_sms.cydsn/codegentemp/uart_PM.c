/*******************************************************************************
* File Name: uart_PM.c
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

#include "uart.h"


/***************************************
* Local data allocation
***************************************/

static uart_BACKUP_STRUCT  uart_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: uart_SaveConfig
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
*  uart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(uart_CONTROL_REG_REMOVED == 0u)
            uart_backup.cr = uart_CONTROL_REG;
        #endif /* End uart_CONTROL_REG_REMOVED */

        #if( (uart_RX_ENABLED) || (uart_HD_ENABLED) )
            uart_backup.rx_period = uart_RXBITCTR_PERIOD_REG;
            uart_backup.rx_mask = uart_RXSTATUS_MASK_REG;
            #if (uart_RXHW_ADDRESS_ENABLED)
                uart_backup.rx_addr1 = uart_RXADDRESS1_REG;
                uart_backup.rx_addr2 = uart_RXADDRESS2_REG;
            #endif /* End uart_RXHW_ADDRESS_ENABLED */
        #endif /* End uart_RX_ENABLED | uart_HD_ENABLED*/

        #if(uart_TX_ENABLED)
            #if(uart_TXCLKGEN_DP)
                uart_backup.tx_clk_ctr = uart_TXBITCLKGEN_CTR_REG;
                uart_backup.tx_clk_compl = uart_TXBITCLKTX_COMPLETE_REG;
            #else
                uart_backup.tx_period = uart_TXBITCTR_PERIOD_REG;
            #endif /*End uart_TXCLKGEN_DP */
            uart_backup.tx_mask = uart_TXSTATUS_MASK_REG;
        #endif /*End uart_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(uart_CONTROL_REG_REMOVED == 0u)
            uart_backup.cr = uart_CONTROL_REG;
        #endif /* End uart_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_RestoreConfig
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
*  uart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(uart_CONTROL_REG_REMOVED == 0u)
            uart_CONTROL_REG = uart_backup.cr;
        #endif /* End uart_CONTROL_REG_REMOVED */

        #if( (uart_RX_ENABLED) || (uart_HD_ENABLED) )
            uart_RXBITCTR_PERIOD_REG = uart_backup.rx_period;
            uart_RXSTATUS_MASK_REG = uart_backup.rx_mask;
            #if (uart_RXHW_ADDRESS_ENABLED)
                uart_RXADDRESS1_REG = uart_backup.rx_addr1;
                uart_RXADDRESS2_REG = uart_backup.rx_addr2;
            #endif /* End uart_RXHW_ADDRESS_ENABLED */
        #endif  /* End (uart_RX_ENABLED) || (uart_HD_ENABLED) */

        #if(uart_TX_ENABLED)
            #if(uart_TXCLKGEN_DP)
                uart_TXBITCLKGEN_CTR_REG = uart_backup.tx_clk_ctr;
                uart_TXBITCLKTX_COMPLETE_REG = uart_backup.tx_clk_compl;
            #else
                uart_TXBITCTR_PERIOD_REG = uart_backup.tx_period;
            #endif /*End uart_TXCLKGEN_DP */
            uart_TXSTATUS_MASK_REG = uart_backup.tx_mask;
        #endif /*End uart_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(uart_CONTROL_REG_REMOVED == 0u)
            uart_CONTROL_REG = uart_backup.cr;
        #endif /* End uart_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_Sleep
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
*  uart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_Sleep(void)
{

    #if(uart_RX_ENABLED || uart_HD_ENABLED)
        if((uart_RXSTATUS_ACTL_REG  & uart_INT_ENABLE) != 0u)
        {
            uart_backup.enableState = 1u;
        }
        else
        {
            uart_backup.enableState = 0u;
        }
    #else
        if((uart_TXSTATUS_ACTL_REG  & uart_INT_ENABLE) !=0u)
        {
            uart_backup.enableState = 1u;
        }
        else
        {
            uart_backup.enableState = 0u;
        }
    #endif /* End uart_RX_ENABLED || uart_HD_ENABLED*/

    uart_Stop();
    uart_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_Wakeup
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
*  uart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_Wakeup(void)
{
    uart_RestoreConfig();
    #if( (uart_RX_ENABLED) || (uart_HD_ENABLED) )
        uart_ClearRxBuffer();
    #endif /* End (uart_RX_ENABLED) || (uart_HD_ENABLED) */
    #if(uart_TX_ENABLED || uart_HD_ENABLED)
        uart_ClearTxBuffer();
    #endif /* End uart_TX_ENABLED || uart_HD_ENABLED */

    if(uart_backup.enableState != 0u)
    {
        uart_Enable();
    }
}


/* [] END OF FILE */
