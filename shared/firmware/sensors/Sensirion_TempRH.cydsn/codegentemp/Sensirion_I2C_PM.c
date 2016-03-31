/*******************************************************************************
* File Name: Sensirion_I2C_PM.c
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

#include "Sensirion_I2C_PVT.h"

Sensirion_I2C_BACKUP_STRUCT Sensirion_I2C_backup =
{
    Sensirion_I2C_DISABLE, /* enableState */

    #if(Sensirion_I2C_FF_IMPLEMENTED)
        Sensirion_I2C_DEFAULT_XCFG,  /* xcfg */
        Sensirion_I2C_DEFAULT_CFG,   /* cfg  */

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            Sensirion_I2C_DEFAULT_ADDR, /* addr */
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            LO8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR),  /* div */
        #else
            LO8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR), /* div1 */
            HI8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR), /* div2 */
        #endif /* (CY_PSOC5A) */

    #else  /* (Sensirion_I2C_UDB_IMPLEMENTED) */
        Sensirion_I2C_DEFAULT_CFG,    /* control */

        #if(CY_UDB_V0)
            Sensirion_I2C_INT_ENABLE_MASK, /* aux_ctl */

            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                Sensirion_I2C_DEFAULT_ADDR, /* addr_d0 */
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */
        #endif /* (CY_UDB_V0) */
    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_DEFAULT_TMOUT_PERIOD,
        Sensirion_I2C_DEFAULT_TMOUT_INTR_MASK,

        #if(Sensirion_I2C_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            Sensirion_I2C_DEFAULT_TMOUT_PRESCALER_PRD,
        #endif /* (Sensirion_I2C_TIMEOUT_PRESCALER_ENABLED) */

    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
};

#if((Sensirion_I2C_FF_IMPLEMENTED) && (Sensirion_I2C_WAKEUP_ENABLED))
    volatile uint8 Sensirion_I2C_wakeupSource;
#endif /* ((Sensirion_I2C_FF_IMPLEMENTED) && (Sensirion_I2C_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: Sensirion_I2C_SaveConfig
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
*  Sensirion_I2C_backup - used to save component configuration and
*       none-retention registers before enter sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Sensirion_I2C_SaveConfig(void) 
{
    #if(Sensirion_I2C_FF_IMPLEMENTED)
        #if(Sensirion_I2C_WAKEUP_ENABLED)
            uint8 enableInterrupts;
        #endif /* (Sensirion_I2C_WAKEUP_ENABLED) */

        /* Store regiters in either Sleep mode */
        Sensirion_I2C_backup.cfg  = Sensirion_I2C_CFG_REG;
        Sensirion_I2C_backup.xcfg = Sensirion_I2C_XCFG_REG;

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            Sensirion_I2C_backup.addr = Sensirion_I2C_ADDR_REG;
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            Sensirion_I2C_backup.clkDiv   = Sensirion_I2C_CLKDIV_REG;
        #else
            Sensirion_I2C_backup.clkDiv1  = Sensirion_I2C_CLKDIV1_REG;
            Sensirion_I2C_backup.clkDiv2  = Sensirion_I2C_CLKDIV2_REG;
        #endif /* (CY_PSOC5A) */

        #if(Sensirion_I2C_WAKEUP_ENABLED)
            /* Need to disable Master */
            Sensirion_I2C_CFG_REG &= ((uint8) ~Sensirion_I2C_ENABLE_MASTER);

            /* Enable the I2C regulator backup */
            enableInterrupts = CyEnterCriticalSection();
            Sensirion_I2C_PWRSYS_CR1_REG |= Sensirion_I2C_PWRSYS_CR1_I2C_REG_BACKUP;
            CyExitCriticalSection(enableInterrupts);

            /* 1) Set force NACK to ignore I2C transactions
               2) Wait while I2C will be ready go to Sleep
               3) These bits are cleared on wake up */
            Sensirion_I2C_XCFG_REG |= Sensirion_I2C_XCFG_FORCE_NACK;
            while(0u == (Sensirion_I2C_XCFG_REG & Sensirion_I2C_XCFG_RDY_TO_SLEEP))
            {
                ; /* Wait when block is ready to Sleep */
            }

            /* Setup wakeup interrupt */
            Sensirion_I2C_DisableInt();
            (void) CyIntSetVector(Sensirion_I2C_ISR_NUMBER, &Sensirion_I2C_WAKEUP_ISR);
            Sensirion_I2C_wakeupSource = 0u;
            Sensirion_I2C_EnableInt();

        #endif /* (Sensirion_I2C_WAKEUP_ENABLED) */

    #else
        /* Store only address match bit */
        Sensirion_I2C_backup.control = (Sensirion_I2C_CFG_REG & Sensirion_I2C_CTRL_ANY_ADDRESS_MASK);

        #if(CY_UDB_V0)
            /* Store interrupt mask bits */
            Sensirion_I2C_backup.intMask = Sensirion_I2C_INT_MASK_REG;

            #if(Sensirion_I2C_MODE & Sensirion_I2C_MODE_SLAVE)
                Sensirion_I2C_backup.addr = Sensirion_I2C_ADDR_REG;
            #endif /* (Sensirion_I2C_MODE & Sensirion_I2C_MODE_SLAVE) */

        #endif /* (CY_UDB_V0) */

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_TimeoutSaveConfig();   /* Save Timeout config */
    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Sensirion_I2C_Sleep
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
void Sensirion_I2C_Sleep(void) 
{
    #if(Sensirion_I2C_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        Sensirion_I2C_backup.enableState = Sensirion_I2C_DISABLE;

        #if(Sensirion_I2C_TIMEOUT_ENABLED)
            Sensirion_I2C_TimeoutStop();
        #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */

    #else

        Sensirion_I2C_backup.enableState = ((uint8) Sensirion_I2C_IS_ENABLED);

        if(Sensirion_I2C_IS_ENABLED)
        {
            Sensirion_I2C_Stop();
        }
    #endif /* (Sensirion_I2C_WAKEUP_ENABLED) */

    Sensirion_I2C_SaveConfig();
}


/*******************************************************************************
* Function Name: Sensirion_I2C_RestoreConfig
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
*  Sensirion_I2C_backup - used to save component configuration and
*  none-retention registers before exit sleep mode.
*
*******************************************************************************/
void Sensirion_I2C_RestoreConfig(void) 
{
    #if(Sensirion_I2C_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        if(Sensirion_I2C_CHECK_PWRSYS_I2C_BACKUP)    /* Enabled if was in Sleep */
        {
            /* Disable back-up regulator */
            enableInterrupts = CyEnterCriticalSection();
            Sensirion_I2C_PWRSYS_CR1_REG &= ((uint8) ~Sensirion_I2C_PWRSYS_CR1_I2C_REG_BACKUP);
            CyExitCriticalSection(enableInterrupts);

            /* Re-enable Master */
            Sensirion_I2C_CFG_REG = Sensirion_I2C_backup.cfg;
        }
        else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
        {
            #if(Sensirion_I2C_WAKEUP_ENABLED)
                /* Disable power to I2C block before register restore */
                enableInterrupts = CyEnterCriticalSection();
                Sensirion_I2C_ACT_PWRMGR_REG  &= ((uint8) ~Sensirion_I2C_ACT_PWR_EN);
                Sensirion_I2C_STBY_PWRMGR_REG &= ((uint8) ~Sensirion_I2C_STBY_PWR_EN);
                CyExitCriticalSection(enableInterrupts);

                /* Enable component after restore complete */
                Sensirion_I2C_backup.enableState = Sensirion_I2C_ENABLE;
            #endif /* (Sensirion_I2C_WAKEUP_ENABLED) */

            /* Restore component registers: Hibernate disable power */
            Sensirion_I2C_XCFG_REG = Sensirion_I2C_backup.xcfg;
            Sensirion_I2C_CFG_REG  = Sensirion_I2C_backup.cfg;

            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                Sensirion_I2C_ADDR_REG = Sensirion_I2C_backup.addr;
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

            #if(CY_PSOC5A)
                Sensirion_I2C_CLKDIV_REG  = Sensirion_I2C_backup.clkDiv;
            #else
                Sensirion_I2C_CLKDIV1_REG = Sensirion_I2C_backup.clkDiv1;
                Sensirion_I2C_CLKDIV2_REG = Sensirion_I2C_backup.clkDiv2;
            #endif /* (CY_PSOC5A) */
        }

        #if(Sensirion_I2C_WAKEUP_ENABLED)
            Sensirion_I2C_DisableInt();
            (void) CyIntSetVector(Sensirion_I2C_ISR_NUMBER, &Sensirion_I2C_ISR);
            if(0u != Sensirion_I2C_wakeupSource)
            {
                Sensirion_I2C_SetPendingInt();   /* Generate interrupt to process incomming transcation */
            }
            Sensirion_I2C_EnableInt();
        #endif /* (Sensirion_I2C_WAKEUP_ENABLED) */

    #else

        #if(CY_UDB_V0)
            uint8 enableInterrupts;

            Sensirion_I2C_INT_MASK_REG |= Sensirion_I2C_backup.intMask;

            enableInterrupts = CyEnterCriticalSection();
            Sensirion_I2C_INT_ENABLE_REG |= Sensirion_I2C_INT_ENABLE_MASK;
            CyExitCriticalSection(enableInterrupts);

            #if(Sensirion_I2C_MODE_MASTER_ENABLED)
                /* Restore Master Clock generator */
                Sensirion_I2C_MCLK_PRD_REG = Sensirion_I2C_DEFAULT_MCLK_PRD;
                Sensirion_I2C_MCLK_CMP_REG = Sensirion_I2C_DEFAULT_MCLK_CMP;
            #endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */

            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                Sensirion_I2C_ADDR_REG = Sensirion_I2C_backup.addr;

                /* Restore slave bit counter period */
                Sensirion_I2C_PERIOD_REG = Sensirion_I2C_DEFAULT_PERIOD;
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        #endif /* (CY_UDB_V0) */

        Sensirion_I2C_CFG_REG = Sensirion_I2C_backup.control;

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_TimeoutRestoreConfig();
    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Sensirion_I2C_Wakeup
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
void Sensirion_I2C_Wakeup(void) 
{
    Sensirion_I2C_RestoreConfig();   /* Restore I2C register settings */

    /* Restore component enable state */
    if(0u != Sensirion_I2C_backup.enableState)
    {
        Sensirion_I2C_Enable();
        Sensirion_I2C_EnableInt();
    }
    else
    {
        #if(Sensirion_I2C_TIMEOUT_ENABLED)
            Sensirion_I2C_TimeoutEnable();
        #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
