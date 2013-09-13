/*******************************************************************************
* File Name: ultrasonic_uart_PM.c
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

#include "ultrasonic_uart.h"


/***************************************
* Local data allocation
***************************************/

static ultrasonic_uart_BACKUP_STRUCT  ultrasonic_uart_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: ultrasonic_uart_SaveConfig
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
*  ultrasonic_uart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ultrasonic_uart_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(ultrasonic_uart_CONTROL_REG_REMOVED == 0u)
            ultrasonic_uart_backup.cr = ultrasonic_uart_CONTROL_REG;
        #endif /* End ultrasonic_uart_CONTROL_REG_REMOVED */

        #if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
            ultrasonic_uart_backup.rx_period = ultrasonic_uart_RXBITCTR_PERIOD_REG;
            ultrasonic_uart_backup.rx_mask = ultrasonic_uart_RXSTATUS_MASK_REG;
            #if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
                ultrasonic_uart_backup.rx_addr1 = ultrasonic_uart_RXADDRESS1_REG;
                ultrasonic_uart_backup.rx_addr2 = ultrasonic_uart_RXADDRESS2_REG;
            #endif /* End ultrasonic_uart_RXHW_ADDRESS_ENABLED */
        #endif /* End ultrasonic_uart_RX_ENABLED | ultrasonic_uart_HD_ENABLED*/

        #if(ultrasonic_uart_TX_ENABLED)
            #if(ultrasonic_uart_TXCLKGEN_DP)
                ultrasonic_uart_backup.tx_clk_ctr = ultrasonic_uart_TXBITCLKGEN_CTR_REG;
                ultrasonic_uart_backup.tx_clk_compl = ultrasonic_uart_TXBITCLKTX_COMPLETE_REG;
            #else
                ultrasonic_uart_backup.tx_period = ultrasonic_uart_TXBITCTR_PERIOD_REG;
            #endif /*End ultrasonic_uart_TXCLKGEN_DP */
            ultrasonic_uart_backup.tx_mask = ultrasonic_uart_TXSTATUS_MASK_REG;
        #endif /*End ultrasonic_uart_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(ultrasonic_uart_CONTROL_REG_REMOVED == 0u)
            ultrasonic_uart_backup.cr = ultrasonic_uart_CONTROL_REG;
        #endif /* End ultrasonic_uart_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ultrasonic_uart_RestoreConfig
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
*  ultrasonic_uart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ultrasonic_uart_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(ultrasonic_uart_CONTROL_REG_REMOVED == 0u)
            ultrasonic_uart_CONTROL_REG = ultrasonic_uart_backup.cr;
        #endif /* End ultrasonic_uart_CONTROL_REG_REMOVED */

        #if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
            ultrasonic_uart_RXBITCTR_PERIOD_REG = ultrasonic_uart_backup.rx_period;
            ultrasonic_uart_RXSTATUS_MASK_REG = ultrasonic_uart_backup.rx_mask;
            #if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
                ultrasonic_uart_RXADDRESS1_REG = ultrasonic_uart_backup.rx_addr1;
                ultrasonic_uart_RXADDRESS2_REG = ultrasonic_uart_backup.rx_addr2;
            #endif /* End ultrasonic_uart_RXHW_ADDRESS_ENABLED */
        #endif  /* End (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */

        #if(ultrasonic_uart_TX_ENABLED)
            #if(ultrasonic_uart_TXCLKGEN_DP)
                ultrasonic_uart_TXBITCLKGEN_CTR_REG = ultrasonic_uart_backup.tx_clk_ctr;
                ultrasonic_uart_TXBITCLKTX_COMPLETE_REG = ultrasonic_uart_backup.tx_clk_compl;
            #else
                ultrasonic_uart_TXBITCTR_PERIOD_REG = ultrasonic_uart_backup.tx_period;
            #endif /*End ultrasonic_uart_TXCLKGEN_DP */
            ultrasonic_uart_TXSTATUS_MASK_REG = ultrasonic_uart_backup.tx_mask;
        #endif /*End ultrasonic_uart_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(ultrasonic_uart_CONTROL_REG_REMOVED == 0u)
            ultrasonic_uart_CONTROL_REG = ultrasonic_uart_backup.cr;
        #endif /* End ultrasonic_uart_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ultrasonic_uart_Sleep
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
*  ultrasonic_uart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ultrasonic_uart_Sleep(void)
{

    #if(ultrasonic_uart_RX_ENABLED || ultrasonic_uart_HD_ENABLED)
        if((ultrasonic_uart_RXSTATUS_ACTL_REG  & ultrasonic_uart_INT_ENABLE) != 0u)
        {
            ultrasonic_uart_backup.enableState = 1u;
        }
        else
        {
            ultrasonic_uart_backup.enableState = 0u;
        }
    #else
        if((ultrasonic_uart_TXSTATUS_ACTL_REG  & ultrasonic_uart_INT_ENABLE) !=0u)
        {
            ultrasonic_uart_backup.enableState = 1u;
        }
        else
        {
            ultrasonic_uart_backup.enableState = 0u;
        }
    #endif /* End ultrasonic_uart_RX_ENABLED || ultrasonic_uart_HD_ENABLED*/

    ultrasonic_uart_Stop();
    ultrasonic_uart_SaveConfig();
}


/*******************************************************************************
* Function Name: ultrasonic_uart_Wakeup
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
*  ultrasonic_uart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ultrasonic_uart_Wakeup(void)
{
    ultrasonic_uart_RestoreConfig();
    #if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
        ultrasonic_uart_ClearRxBuffer();
    #endif /* End (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */
    #if(ultrasonic_uart_TX_ENABLED || ultrasonic_uart_HD_ENABLED)
        ultrasonic_uart_ClearTxBuffer();
    #endif /* End ultrasonic_uart_TX_ENABLED || ultrasonic_uart_HD_ENABLED */

    if(ultrasonic_uart_backup.enableState != 0u)
    {
        ultrasonic_uart_Enable();
    }
}


/* [] END OF FILE */
