/*******************************************************************************
* File Name: NEOMOTE_1_UART_MOTE_PM.c
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

#include "NEOMOTE_1_UART_MOTE.h"


/***************************************
* Local data allocation
***************************************/

static NEOMOTE_1_UART_MOTE_BACKUP_STRUCT  NEOMOTE_1_UART_MOTE_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_SaveConfig
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
*  NEOMOTE_1_UART_MOTE_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u)
            NEOMOTE_1_UART_MOTE_backup.cr = NEOMOTE_1_UART_MOTE_CONTROL_REG;
        #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */

        #if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
            NEOMOTE_1_UART_MOTE_backup.rx_period = NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG;
            NEOMOTE_1_UART_MOTE_backup.rx_mask = NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG;
            #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
                NEOMOTE_1_UART_MOTE_backup.rx_addr1 = NEOMOTE_1_UART_MOTE_RXADDRESS1_REG;
                NEOMOTE_1_UART_MOTE_backup.rx_addr2 = NEOMOTE_1_UART_MOTE_RXADDRESS2_REG;
            #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
        #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED | NEOMOTE_1_UART_MOTE_HD_ENABLED*/

        #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
            #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
                NEOMOTE_1_UART_MOTE_backup.tx_clk_ctr = NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_REG;
                NEOMOTE_1_UART_MOTE_backup.tx_clk_compl = NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG;
            #else
                NEOMOTE_1_UART_MOTE_backup.tx_period = NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG;
            #endif /*End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
            NEOMOTE_1_UART_MOTE_backup.tx_mask = NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG;
        #endif /*End NEOMOTE_1_UART_MOTE_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u)
            NEOMOTE_1_UART_MOTE_backup.cr = NEOMOTE_1_UART_MOTE_CONTROL_REG;
        #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_RestoreConfig
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
*  NEOMOTE_1_UART_MOTE_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u)
            NEOMOTE_1_UART_MOTE_CONTROL_REG = NEOMOTE_1_UART_MOTE_backup.cr;
        #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */

        #if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
            NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_backup.rx_period;
            NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG = NEOMOTE_1_UART_MOTE_backup.rx_mask;
            #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
                NEOMOTE_1_UART_MOTE_RXADDRESS1_REG = NEOMOTE_1_UART_MOTE_backup.rx_addr1;
                NEOMOTE_1_UART_MOTE_RXADDRESS2_REG = NEOMOTE_1_UART_MOTE_backup.rx_addr2;
            #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
        #endif  /* End (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */

        #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
            #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
                NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_REG = NEOMOTE_1_UART_MOTE_backup.tx_clk_ctr;
                NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG = NEOMOTE_1_UART_MOTE_backup.tx_clk_compl;
            #else
                NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_backup.tx_period;
            #endif /*End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
            NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG = NEOMOTE_1_UART_MOTE_backup.tx_mask;
        #endif /*End NEOMOTE_1_UART_MOTE_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u)
            NEOMOTE_1_UART_MOTE_CONTROL_REG = NEOMOTE_1_UART_MOTE_backup.cr;
        #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Sleep
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
*  NEOMOTE_1_UART_MOTE_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Sleep(void)
{

    #if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)
        if((NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_REG  & NEOMOTE_1_UART_MOTE_INT_ENABLE) != 0u)
        {
            NEOMOTE_1_UART_MOTE_backup.enableState = 1u;
        }
        else
        {
            NEOMOTE_1_UART_MOTE_backup.enableState = 0u;
        }
    #else
        if((NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG  & NEOMOTE_1_UART_MOTE_INT_ENABLE) !=0u)
        {
            NEOMOTE_1_UART_MOTE_backup.enableState = 1u;
        }
        else
        {
            NEOMOTE_1_UART_MOTE_backup.enableState = 0u;
        }
    #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED*/

    NEOMOTE_1_UART_MOTE_Stop();
    NEOMOTE_1_UART_MOTE_SaveConfig();
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Wakeup
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
*  NEOMOTE_1_UART_MOTE_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Wakeup(void)
{
    NEOMOTE_1_UART_MOTE_RestoreConfig();
    #if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
        NEOMOTE_1_UART_MOTE_ClearRxBuffer();
    #endif /* End (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */
    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)
        NEOMOTE_1_UART_MOTE_ClearTxBuffer();
    #endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED */

    if(NEOMOTE_1_UART_MOTE_backup.enableState != 0u)
    {
        NEOMOTE_1_UART_MOTE_Enable();
    }
}


/* [] END OF FILE */
