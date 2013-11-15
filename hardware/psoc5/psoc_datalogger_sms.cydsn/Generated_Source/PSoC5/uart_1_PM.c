/*******************************************************************************
* File Name: uart_1_PM.c
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

#include "uart_1.h"


/***************************************
* Local data allocation
***************************************/

static uart_1_BACKUP_STRUCT  uart_1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: uart_1_SaveConfig
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
*  uart_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_1_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(uart_1_CONTROL_REG_REMOVED == 0u)
            uart_1_backup.cr = uart_1_CONTROL_REG;
        #endif /* End uart_1_CONTROL_REG_REMOVED */

        #if( (uart_1_RX_ENABLED) || (uart_1_HD_ENABLED) )
            uart_1_backup.rx_period = uart_1_RXBITCTR_PERIOD_REG;
            uart_1_backup.rx_mask = uart_1_RXSTATUS_MASK_REG;
            #if (uart_1_RXHW_ADDRESS_ENABLED)
                uart_1_backup.rx_addr1 = uart_1_RXADDRESS1_REG;
                uart_1_backup.rx_addr2 = uart_1_RXADDRESS2_REG;
            #endif /* End uart_1_RXHW_ADDRESS_ENABLED */
        #endif /* End uart_1_RX_ENABLED | uart_1_HD_ENABLED*/

        #if(uart_1_TX_ENABLED)
            #if(uart_1_TXCLKGEN_DP)
                uart_1_backup.tx_clk_ctr = uart_1_TXBITCLKGEN_CTR_REG;
                uart_1_backup.tx_clk_compl = uart_1_TXBITCLKTX_COMPLETE_REG;
            #else
                uart_1_backup.tx_period = uart_1_TXBITCTR_PERIOD_REG;
            #endif /*End uart_1_TXCLKGEN_DP */
            uart_1_backup.tx_mask = uart_1_TXSTATUS_MASK_REG;
        #endif /*End uart_1_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(uart_1_CONTROL_REG_REMOVED == 0u)
            uart_1_backup.cr = uart_1_CONTROL_REG;
        #endif /* End uart_1_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_1_RestoreConfig
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
*  uart_1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_1_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(uart_1_CONTROL_REG_REMOVED == 0u)
            uart_1_CONTROL_REG = uart_1_backup.cr;
        #endif /* End uart_1_CONTROL_REG_REMOVED */

        #if( (uart_1_RX_ENABLED) || (uart_1_HD_ENABLED) )
            uart_1_RXBITCTR_PERIOD_REG = uart_1_backup.rx_period;
            uart_1_RXSTATUS_MASK_REG = uart_1_backup.rx_mask;
            #if (uart_1_RXHW_ADDRESS_ENABLED)
                uart_1_RXADDRESS1_REG = uart_1_backup.rx_addr1;
                uart_1_RXADDRESS2_REG = uart_1_backup.rx_addr2;
            #endif /* End uart_1_RXHW_ADDRESS_ENABLED */
        #endif  /* End (uart_1_RX_ENABLED) || (uart_1_HD_ENABLED) */

        #if(uart_1_TX_ENABLED)
            #if(uart_1_TXCLKGEN_DP)
                uart_1_TXBITCLKGEN_CTR_REG = uart_1_backup.tx_clk_ctr;
                uart_1_TXBITCLKTX_COMPLETE_REG = uart_1_backup.tx_clk_compl;
            #else
                uart_1_TXBITCTR_PERIOD_REG = uart_1_backup.tx_period;
            #endif /*End uart_1_TXCLKGEN_DP */
            uart_1_TXSTATUS_MASK_REG = uart_1_backup.tx_mask;
        #endif /*End uart_1_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(uart_1_CONTROL_REG_REMOVED == 0u)
            uart_1_CONTROL_REG = uart_1_backup.cr;
        #endif /* End uart_1_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: uart_1_Sleep
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
*  uart_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_1_Sleep(void)
{

    #if(uart_1_RX_ENABLED || uart_1_HD_ENABLED)
        if((uart_1_RXSTATUS_ACTL_REG  & uart_1_INT_ENABLE) != 0u)
        {
            uart_1_backup.enableState = 1u;
        }
        else
        {
            uart_1_backup.enableState = 0u;
        }
    #else
        if((uart_1_TXSTATUS_ACTL_REG  & uart_1_INT_ENABLE) !=0u)
        {
            uart_1_backup.enableState = 1u;
        }
        else
        {
            uart_1_backup.enableState = 0u;
        }
    #endif /* End uart_1_RX_ENABLED || uart_1_HD_ENABLED*/

    uart_1_Stop();
    uart_1_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_1_Wakeup
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
*  uart_1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_1_Wakeup(void)
{
    uart_1_RestoreConfig();
    #if( (uart_1_RX_ENABLED) || (uart_1_HD_ENABLED) )
        uart_1_ClearRxBuffer();
    #endif /* End (uart_1_RX_ENABLED) || (uart_1_HD_ENABLED) */
    #if(uart_1_TX_ENABLED || uart_1_HD_ENABLED)
        uart_1_ClearTxBuffer();
    #endif /* End uart_1_TX_ENABLED || uart_1_HD_ENABLED */

    if(uart_1_backup.enableState != 0u)
    {
        uart_1_Enable();
    }
}


/* [] END OF FILE */
