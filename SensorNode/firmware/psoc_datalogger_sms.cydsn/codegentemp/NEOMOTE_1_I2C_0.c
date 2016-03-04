/*******************************************************************************
* File Name: NEOMOTE_1_I2C_0.c
* Version 3.30
*
* Description:
*  This file provides the source code of APIs for the I2C component.
*  Actual protocol and operation code resides in the interrupt service routine
*  file.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NEOMOTE_1_I2C_0_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 NEOMOTE_1_I2C_0_initVar = 0u;    /* Defines if component was initialized */

volatile uint8 NEOMOTE_1_I2C_0_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Init
********************************************************************************
*
* Summary:
*  Initializes I2C registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Init(void) 
{
    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        NEOMOTE_1_I2C_0_CFG_REG  = NEOMOTE_1_I2C_0_DEFAULT_CFG;
        NEOMOTE_1_I2C_0_XCFG_REG = NEOMOTE_1_I2C_0_DEFAULT_XCFG;

        #if(CY_PSOC5A)
            NEOMOTE_1_I2C_0_CLKDIV_REG  = LO8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR);
        #else
            NEOMOTE_1_I2C_0_CLKDIV1_REG = LO8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR);
            NEOMOTE_1_I2C_0_CLKDIV2_REG = HI8(NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR);
        #endif /* (CY_PSOC5A) */

    #else
        uint8 enableInterrupts;

        NEOMOTE_1_I2C_0_CFG_REG      = NEOMOTE_1_I2C_0_DEFAULT_CFG;      /* control  */
        NEOMOTE_1_I2C_0_INT_MASK_REG = NEOMOTE_1_I2C_0_DEFAULT_INT_MASK; /* int_mask */

        /* Enable interrupts from block */
        enableInterrupts = CyEnterCriticalSection();
        NEOMOTE_1_I2C_0_INT_ENABLE_REG |= NEOMOTE_1_I2C_0_INTR_ENABLE; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
            NEOMOTE_1_I2C_0_MCLK_PRD_REG = NEOMOTE_1_I2C_0_DEFAULT_MCLK_PRD;
            NEOMOTE_1_I2C_0_MCLK_CMP_REG = NEOMOTE_1_I2C_0_DEFAULT_MCLK_CMP;
         #endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            NEOMOTE_1_I2C_0_PERIOD_REG = NEOMOTE_1_I2C_0_DEFAULT_PERIOD;
        #endif  /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_TimeoutInit();
    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */

    /* Disable Interrupt and set vector and priority */
    CyIntDisable    (NEOMOTE_1_I2C_0_ISR_NUMBER);
    CyIntSetPriority(NEOMOTE_1_I2C_0_ISR_NUMBER, NEOMOTE_1_I2C_0_ISR_PRIORITY);
    #if(NEOMOTE_1_I2C_0_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(NEOMOTE_1_I2C_0_ISR_NUMBER, &NEOMOTE_1_I2C_0_ISR);
    #endif /* (NEOMOTE_1_I2C_0_INTERN_I2C_INTR_HANDLER) */


    /* Put state machine in idle state */
    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;

    #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
        /* Reset status and buffers index */
        NEOMOTE_1_I2C_0_SlaveClearReadBuf();
        NEOMOTE_1_I2C_0_SlaveClearWriteBuf();
        NEOMOTE_1_I2C_0_slStatus = 0u; /* Reset slave status */

        /* Set default address */
        NEOMOTE_1_I2C_0_SlaveSetAddress(NEOMOTE_1_I2C_0_DEFAULT_ADDR);
    #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

    #if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
        /* Reset status and buffers index */
        NEOMOTE_1_I2C_0_MasterClearReadBuf();
        NEOMOTE_1_I2C_0_MasterClearWriteBuf();
        (void) NEOMOTE_1_I2C_0_MasterClearStatus();
    #endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Enable
********************************************************************************
*
* Summary:
*  Enables I2C operations.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Enable(void) 
{
    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        /* Enable power to I2C FF block */
        enableInterrupts = CyEnterCriticalSection();
        NEOMOTE_1_I2C_0_ACT_PWRMGR_REG  |= NEOMOTE_1_I2C_0_ACT_PWR_EN;
        NEOMOTE_1_I2C_0_STBY_PWRMGR_REG |= NEOMOTE_1_I2C_0_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            uint8 enableInterrupts;
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            /* Enable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            NEOMOTE_1_I2C_0_COUNTER_AUX_CTL_REG |= NEOMOTE_1_I2C_0_CNT7_ENABLE;   /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        NEOMOTE_1_I2C_0_CFG_REG |= NEOMOTE_1_I2C_0_ENABLE_MS;

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_TimeoutEnable();
    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Start
********************************************************************************
*
* Summary:
*  Starts the I2C hardware. Enables Active mode power template bits or clock
*  gating as appropriate. It is required to be executed before I2C bus
*  operation.
*  The I2C interrupt remains disabled after this function call.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This component automatically enables it's interrupt.  If I2C is enabled
*  without the interrupt enabled, it could lock up the I2C bus.
*
* Global variables:
*  NEOMOTE_1_I2C_0_initVar - used to check initial configuration, modified
*  on first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Start(void) 
{
    /* Initialize I2C registers, reset I2C buffer index and clears status */
    if(0u == NEOMOTE_1_I2C_0_initVar)
    {
        NEOMOTE_1_I2C_0_Init();
        NEOMOTE_1_I2C_0_initVar = 1u; /* Component initialized */
    }

    NEOMOTE_1_I2C_0_Enable();
    NEOMOTE_1_I2C_0_EnableInt();
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_Stop
********************************************************************************
*
* Summary:
*  Disables I2C hardware and disables I2C interrupt. Disables Active mode power
*  template bits or clock gating as appropriate.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_Stop(void) 
{
    #if((NEOMOTE_1_I2C_0_FF_IMPLEMENTED)  || \
        (NEOMOTE_1_I2C_0_UDB_IMPLEMENTED && NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED))
        uint8 enableInterrupts;
    #endif /* ((NEOMOTE_1_I2C_0_FF_IMPLEMENTED)  || \
               (NEOMOTE_1_I2C_0_UDB_IMPLEMENTED && NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)) */

    NEOMOTE_1_I2C_0_DisableInt();

    NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP;   /* Interrupt on Stop can be enabled by write */
    (void) NEOMOTE_1_I2C_0_CSR_REG;        /* Clear CSR reg */
    
    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        NEOMOTE_1_I2C_0_TimeoutStop();
    #endif  /* End (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */

    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        #if(CY_PSOC3 || CY_PSOC5LP)
            /* Store registers which are held in reset when Master and Slave bits are cleared */
            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                NEOMOTE_1_I2C_0_backup.addr = NEOMOTE_1_I2C_0_ADDR_REG;
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

            NEOMOTE_1_I2C_0_backup.clkDiv1  = NEOMOTE_1_I2C_0_CLKDIV1_REG;
            NEOMOTE_1_I2C_0_backup.clkDiv2  = NEOMOTE_1_I2C_0_CLKDIV2_REG;


            /* Reset FF block */
            NEOMOTE_1_I2C_0_CFG_REG &= ((uint8) ~NEOMOTE_1_I2C_0_ENABLE_MS);
            CyDelayUs(NEOMOTE_1_I2C_0_FF_RESET_DELAY);
            NEOMOTE_1_I2C_0_CFG_REG |= ((uint8)  NEOMOTE_1_I2C_0_ENABLE_MS);


            /* Restore registers */
            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                NEOMOTE_1_I2C_0_ADDR_REG = NEOMOTE_1_I2C_0_backup.addr;
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

            NEOMOTE_1_I2C_0_CLKDIV1_REG = NEOMOTE_1_I2C_0_backup.clkDiv1;
            NEOMOTE_1_I2C_0_CLKDIV2_REG = NEOMOTE_1_I2C_0_backup.clkDiv2;

        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        /* Disable power to I2C block */
        enableInterrupts = CyEnterCriticalSection();
        NEOMOTE_1_I2C_0_ACT_PWRMGR_REG  &= ((uint8) ~NEOMOTE_1_I2C_0_ACT_PWR_EN);
        NEOMOTE_1_I2C_0_STBY_PWRMGR_REG &= ((uint8) ~NEOMOTE_1_I2C_0_STBY_PWR_EN);
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            /* Disable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            NEOMOTE_1_I2C_0_COUNTER_AUX_CTL_REG &= ((uint8) ~NEOMOTE_1_I2C_0_CNT7_ENABLE);
            CyExitCriticalSection(enableInterrupts);
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

        NEOMOTE_1_I2C_0_CFG_REG &= ((uint8) ~NEOMOTE_1_I2C_0_ENABLE_MS);

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    NEOMOTE_1_I2C_0_ClearPendingInt();  /* Clear interrupt triggers on reset */

    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;  /* Reset software FSM */
}


/* [] END OF FILE */
