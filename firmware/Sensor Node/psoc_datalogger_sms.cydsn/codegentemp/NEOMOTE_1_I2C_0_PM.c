/*******************************************************************************
* File Name: NEOMOTE_1_I2C_0_PM.c
* Version 3.30
*
* Description:
*  This file provides Low power mode APIs for I2C component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NEOMOTE_1_I2C_0_PVT.h"

NEOMOTE_1_I2C_0_BACKUP_STRUCT NEOMOTE_1_I2C_0_backup =
{
    NEOMOTE_1_I2C_0_DISABLE, /* enableState */

    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        NEOMOTE_1_I2C_0_DEFAULT_XCFG,  /* xcfg */
        NEOMOTE_1_I2C_0_DEFAULT_CFG,   /* cfg  */

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            NEOMOTE_1_I2C_0_DEFAULT_ADDR, /* addr */
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            LO8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR),  /* div */
        #else
            LO8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR), /* div1 */
            HI8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR), /* div2 */
        #endif /* (CY_PSOC5A) */

    #else  /* (NEOMOTE_1_I2C_0_UDB_IMPLEMENTED) */
        NEOMOTE_1_I2C_0_DEFAULT_CFG,    /* control */

        #if(CY_UDB_V0)
            NEOMOTE_1_I2C_0_INT_ENABLE_MASK, /* aux_ctl */

            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                NEOMOTE_1_I2C_0_DEFAULT_ADDR, /* addr_d0 */
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */
        #endif /* (CY_UDB_V0) */
    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_DEFAULT_TMOUT_PERIOD,
        NEOMOTE_1_I2C_0_DEFAULT_TMOUT_INTR_MASK,

        #if(NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            NEOMOTE_1_I2C_0_DEFAULT_TMOUT_PRESCALER_PRD,
        #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLED) */

    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
};

#if((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) && (NEOMOTE_1_I2C_0_WAKEUP_ENABLED))
    volatile uint8 NEOMOTE_1_I2C_0_wakeupSource;
#endif /* ((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) && (NEOMOTE_1_I2C_0_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SaveConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: disables I2C Master(if was enabled before go
*  to sleep), enables I2C backup regulator. Waits while on-going transaction be
*  will completed and I2C will be ready go to sleep. All incoming transaction
*  will be NACKed till power down will be asserted. The address match event
*  wakes up the chip.
*  Wakeup on address match disabled: saves I2C configuration and non-retention
*  register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  NEOMOTE_1_I2C_0_backup - used to save component configuration and
*       none-retention registers before enter sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SaveConfig(void) 
{
    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        #if(NEOMOTE_1_I2C_0_WAKEUP_ENABLED)
            uint8 enableInterrupts;
        #endif /* (NEOMOTE_1_I2C_0_WAKEUP_ENABLED) */

        /* Store regiters in either Sleep mode */
        NEOMOTE_1_I2C_0_backup.cfg  = NEOMOTE_1_I2C_0_CFG_REG;
        NEOMOTE_1_I2C_0_backup.xcfg = NEOMOTE_1_I2C_0_XCFG_REG;

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            NEOMOTE_1_I2C_0_backup.addr = NEOMOTE_1_I2C_0_ADDR_REG;
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            NEOMOTE_1_I2C_0_backup.clkDiv   = NEOMOTE_1_I2C_0_CLKDIV_REG;
        #else
            NEOMOTE_1_I2C_0_backup.clkDiv1  = NEOMOTE_1_I2C_0_CLKDIV1_REG;
            NEOMOTE_1_I2C_0_backup.clkDiv2  = NEOMOTE_1_I2C_0_CLKDIV2_REG;
        #endif /* (CY_PSOC5A) */

        #if(NEOMOTE_1_I2C_0_WAKEUP_ENABLED)
            /* Need to disable Master */
            NEOMOTE_1_I2C_0_CFG_REG &= ((uint8) ~NEOMOTE_1_I2C_0_ENABLE_MASTER);

            /* Enable the I2C regulator backup */
            enableInterrupts = CyEnterCriticalSection();
            NEOMOTE_1_I2C_0_PWRSYS_CR1_REG |= NEOMOTE_1_I2C_0_PWRSYS_CR1_I2C_REG_BACKUP;
            CyExitCriticalSection(enableInterrupts);

            /* 1) Set force NACK to ignore I2C transactions
               2) Wait while I2C will be ready go to Sleep
               3) These bits are cleared on wake up */
            NEOMOTE_1_I2C_0_XCFG_REG |= NEOMOTE_1_I2C_0_XCFG_FORCE_NACK;
            while(0u == (NEOMOTE_1_I2C_0_XCFG_REG & NEOMOTE_1_I2C_0_XCFG_RDY_TO_SLEEP))
            {
                ; /* Wait when block is ready to Sleep */
            }

            /* Setup wakeup interrupt */
            NEOMOTE_1_I2C_0_DisableInt();
            (void) CyIntSetVector(NEOMOTE_1_I2C_0_ISR_NUMBER, &NEOMOTE_1_I2C_0_WAKEUP_ISR);
            NEOMOTE_1_I2C_0_wakeupSource = 0u;
            NEOMOTE_1_I2C_0_EnableInt();

        #endif /* (NEOMOTE_1_I2C_0_WAKEUP_ENABLED) */

    #else
        /* Store only address match bit */
        NEOMOTE_1_I2C_0_backup.control = (NEOMOTE_1_I2C_0_CFG_REG & NEOMOTE_1_I2C_0_CTRL_ANY_ADDRESS_MASK);

        #if(CY_UDB_V0)
            /* Store interrupt mask bits */
            NEOMOTE_1_I2C_0_backup.intMask = NEOMOTE_1_I2C_0_INT_MASK_REG;

            #if(NEOMOTE_1_I2C_0_MODE & NEOMOTE_1_I2C_0_MODE_SLAVE)
                NEOMOTE_1_I2C_0_backup.addr = NEOMOTE_1_I2C_0_ADDR_REG;
            #endif /* (NEOMOTE_1_I2C_0_MODE & NEOMOTE_1_I2C_0_MODE_SLAVE) */

        #endif /* (CY_UDB_V0) */

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_TimeoutSaveConfig();   /* Save Timeout config */
    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Sleep
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: All incoming transaction will be NACKed till
*  power down will be asserted. The address match event wakes up the chip.
*  Wakeup on address match disabled: Disables active mode power template bits or
*  clock gating as appropriate. Saves I2C configuration and non-retention
*  register values.
*  Disables I2C interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Sleep(void) 
{
    #if(NEOMOTE_1_I2C_0_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        NEOMOTE_1_I2C_0_backup.enableState = NEOMOTE_1_I2C_0_DISABLE;

        #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
            NEOMOTE_1_I2C_0_TimeoutStop();
        #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */

    #else

        NEOMOTE_1_I2C_0_backup.enableState = ((uint8) NEOMOTE_1_I2C_0_IS_ENABLED);

        if(NEOMOTE_1_I2C_0_IS_ENABLED)
        {
            NEOMOTE_1_I2C_0_Stop();
        }
    #endif /* (NEOMOTE_1_I2C_0_WAKEUP_ENABLED) */

    NEOMOTE_1_I2C_0_SaveConfig();
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_RestoreConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep), disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  NEOMOTE_1_I2C_0_backup - used to save component configuration and
*  none-retention registers before exit sleep mode.
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_RestoreConfig(void) 
{
    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        if(NEOMOTE_1_I2C_0_CHECK_PWRSYS_I2C_BACKUP)    /* Enabled if was in Sleep */
        {
            /* Disable back-up regulator */
            enableInterrupts = CyEnterCriticalSection();
            NEOMOTE_1_I2C_0_PWRSYS_CR1_REG &= ((uint8) ~NEOMOTE_1_I2C_0_PWRSYS_CR1_I2C_REG_BACKUP);
            CyExitCriticalSection(enableInterrupts);

            /* Re-enable Master */
            NEOMOTE_1_I2C_0_CFG_REG = NEOMOTE_1_I2C_0_backup.cfg;
        }
        else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
        {
            #if(NEOMOTE_1_I2C_0_WAKEUP_ENABLED)
                /* Disable power to I2C block before register restore */
                enableInterrupts = CyEnterCriticalSection();
                NEOMOTE_1_I2C_0_ACT_PWRMGR_REG  &= ((uint8) ~NEOMOTE_1_I2C_0_ACT_PWR_EN);
                NEOMOTE_1_I2C_0_STBY_PWRMGR_REG &= ((uint8) ~NEOMOTE_1_I2C_0_STBY_PWR_EN);
                CyExitCriticalSection(enableInterrupts);

                /* Enable component after restore complete */
                NEOMOTE_1_I2C_0_backup.enableState = NEOMOTE_1_I2C_0_ENABLE;
            #endif /* (NEOMOTE_1_I2C_0_WAKEUP_ENABLED) */

            /* Restore component registers: Hibernate disable power */
            NEOMOTE_1_I2C_0_XCFG_REG = NEOMOTE_1_I2C_0_backup.xcfg;
            NEOMOTE_1_I2C_0_CFG_REG  = NEOMOTE_1_I2C_0_backup.cfg;

            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                NEOMOTE_1_I2C_0_ADDR_REG = NEOMOTE_1_I2C_0_backup.addr;
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

            #if(CY_PSOC5A)
                NEOMOTE_1_I2C_0_CLKDIV_REG  = NEOMOTE_1_I2C_0_backup.clkDiv;
            #else
                NEOMOTE_1_I2C_0_CLKDIV1_REG = NEOMOTE_1_I2C_0_backup.clkDiv1;
                NEOMOTE_1_I2C_0_CLKDIV2_REG = NEOMOTE_1_I2C_0_backup.clkDiv2;
            #endif /* (CY_PSOC5A) */
        }

        #if(NEOMOTE_1_I2C_0_WAKEUP_ENABLED)
            NEOMOTE_1_I2C_0_DisableInt();
            (void) CyIntSetVector(NEOMOTE_1_I2C_0_ISR_NUMBER, &NEOMOTE_1_I2C_0_ISR);
            if(0u != NEOMOTE_1_I2C_0_wakeupSource)
            {
                NEOMOTE_1_I2C_0_SetPendingInt();   /* Generate interrupt to process incomming transcation */
            }
            NEOMOTE_1_I2C_0_EnableInt();
        #endif /* (NEOMOTE_1_I2C_0_WAKEUP_ENABLED) */

    #else

        #if(CY_UDB_V0)
            uint8 enableInterrupts;

            NEOMOTE_1_I2C_0_INT_MASK_REG |= NEOMOTE_1_I2C_0_backup.intMask;

            enableInterrupts = CyEnterCriticalSection();
            NEOMOTE_1_I2C_0_INT_ENABLE_REG |= NEOMOTE_1_I2C_0_INT_ENABLE_MASK;
            CyExitCriticalSection(enableInterrupts);

            #if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
                /* Restore Master Clock generator */
                NEOMOTE_1_I2C_0_MCLK_PRD_REG = NEOMOTE_1_I2C_0_DEFAULT_MCLK_PRD;
                NEOMOTE_1_I2C_0_MCLK_CMP_REG = NEOMOTE_1_I2C_0_DEFAULT_MCLK_CMP;
            #endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */

            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                NEOMOTE_1_I2C_0_ADDR_REG = NEOMOTE_1_I2C_0_backup.addr;

                /* Restore slave bit counter period */
                NEOMOTE_1_I2C_0_PERIOD_REG = NEOMOTE_1_I2C_0_DEFAULT_PERIOD;
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        #endif /* (CY_UDB_V0) */

        NEOMOTE_1_I2C_0_CFG_REG = NEOMOTE_1_I2C_0_backup.control;

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_TimeoutRestoreConfig();
    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Wakeup
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep) and disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values. Restores Active mode power template bits or
*  clock gating as appropriate.
*  The I2C interrupt remains disabled after function call.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Wakeup(void) 
{
    NEOMOTE_1_I2C_0_RestoreConfig();   /* Restore I2C register settings */

    /* Restore component enable state */
    if(0u != NEOMOTE_1_I2C_0_backup.enableState)
    {
        NEOMOTE_1_I2C_0_Enable();
        NEOMOTE_1_I2C_0_EnableInt();
    }
    else
    {
        #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
            NEOMOTE_1_I2C_0_TimeoutEnable();
        #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
