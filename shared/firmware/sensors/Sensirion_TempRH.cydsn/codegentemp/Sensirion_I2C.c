/*******************************************************************************
* File Name: Sensirion_I2C.c
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

#include "Sensirion_I2C_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 Sensirion_I2C_initVar = 0u;    /* Defines if component was initialized */

volatile uint8 Sensirion_I2C_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: Sensirion_I2C_Init
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
void Sensirion_I2C_Init(void) 
{
    #if(Sensirion_I2C_FF_IMPLEMENTED)
        Sensirion_I2C_CFG_REG  = Sensirion_I2C_DEFAULT_CFG;
        Sensirion_I2C_XCFG_REG = Sensirion_I2C_DEFAULT_XCFG;

        #if(CY_PSOC5A)
            Sensirion_I2C_CLKDIV_REG  = LO8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR);
        #else
            Sensirion_I2C_CLKDIV1_REG = LO8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR);
            Sensirion_I2C_CLKDIV2_REG = HI8(Sensirion_I2C_DEFAULT_DIVIDE_FACTOR);
        #endif /* (CY_PSOC5A) */

    #else
        uint8 enableInterrupts;

        Sensirion_I2C_CFG_REG      = Sensirion_I2C_DEFAULT_CFG;      /* control  */
        Sensirion_I2C_INT_MASK_REG = Sensirion_I2C_DEFAULT_INT_MASK; /* int_mask */

        /* Enable interrupts from block */
        enableInterrupts = CyEnterCriticalSection();
        Sensirion_I2C_INT_ENABLE_REG |= Sensirion_I2C_INTR_ENABLE; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(Sensirion_I2C_MODE_MASTER_ENABLED)
            Sensirion_I2C_MCLK_PRD_REG = Sensirion_I2C_DEFAULT_MCLK_PRD;
            Sensirion_I2C_MCLK_CMP_REG = Sensirion_I2C_DEFAULT_MCLK_CMP;
         #endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            Sensirion_I2C_PERIOD_REG = Sensirion_I2C_DEFAULT_PERIOD;
        #endif  /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_TimeoutInit();
    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */

    /* Disable Interrupt and set vector and priority */
    CyIntDisable    (Sensirion_I2C_ISR_NUMBER);
    CyIntSetPriority(Sensirion_I2C_ISR_NUMBER, Sensirion_I2C_ISR_PRIORITY);
    #if(Sensirion_I2C_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(Sensirion_I2C_ISR_NUMBER, &Sensirion_I2C_ISR);
    #endif /* (Sensirion_I2C_INTERN_I2C_INTR_HANDLER) */


    /* Put state machine in idle state */
    Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;

    #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
        /* Reset status and buffers index */
        Sensirion_I2C_SlaveClearReadBuf();
        Sensirion_I2C_SlaveClearWriteBuf();
        Sensirion_I2C_slStatus = 0u; /* Reset slave status */

        /* Set default address */
        Sensirion_I2C_SlaveSetAddress(Sensirion_I2C_DEFAULT_ADDR);
    #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

    #if(Sensirion_I2C_MODE_MASTER_ENABLED)
        /* Reset status and buffers index */
        Sensirion_I2C_MasterClearReadBuf();
        Sensirion_I2C_MasterClearWriteBuf();
        (void) Sensirion_I2C_MasterClearStatus();
    #endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: Sensirion_I2C_Enable
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
void Sensirion_I2C_Enable(void) 
{
    #if(Sensirion_I2C_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        /* Enable power to I2C FF block */
        enableInterrupts = CyEnterCriticalSection();
        Sensirion_I2C_ACT_PWRMGR_REG  |= Sensirion_I2C_ACT_PWR_EN;
        Sensirion_I2C_STBY_PWRMGR_REG |= Sensirion_I2C_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            uint8 enableInterrupts;
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            /* Enable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            Sensirion_I2C_COUNTER_AUX_CTL_REG |= Sensirion_I2C_CNT7_ENABLE;   /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        Sensirion_I2C_CFG_REG |= Sensirion_I2C_ENABLE_MS;

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_TimeoutEnable();
    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Sensirion_I2C_Start
********************************************************************************
*
* Summary:
*  Starts the I2C hardware. Enables Active mode power template bits or clock
*  gating as appropriate. It is required to be executed before I2C bus
*  operation.
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
*  Sensirion_I2C_initVar - used to check initial configuration, modified
*  on first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Sensirion_I2C_Start(void) 
{
    /* Initialize I2C registers, reset I2C buffer index and clears status */
    if(0u == Sensirion_I2C_initVar)
    {
        Sensirion_I2C_Init();
        Sensirion_I2C_initVar = 1u; /* Component initialized */
    }

    Sensirion_I2C_Enable();
    Sensirion_I2C_EnableInt();
}


/*******************************************************************************
* Function Name: Sensirion_I2C_Stop
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
void Sensirion_I2C_Stop(void) 
{
    #if((Sensirion_I2C_FF_IMPLEMENTED)  || \
        (Sensirion_I2C_UDB_IMPLEMENTED && Sensirion_I2C_MODE_SLAVE_ENABLED))
        uint8 enableInterrupts;
    #endif /* ((Sensirion_I2C_FF_IMPLEMENTED)  || \
               (Sensirion_I2C_UDB_IMPLEMENTED && Sensirion_I2C_MODE_SLAVE_ENABLED)) */

    Sensirion_I2C_DisableInt();

    Sensirion_I2C_DISABLE_INT_ON_STOP;   /* Interrupt on Stop can be enabled by write */
    (void) Sensirion_I2C_CSR_REG;        /* Clear CSR reg */
    
    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        Sensirion_I2C_TimeoutStop();
    #endif  /* End (Sensirion_I2C_TIMEOUT_ENABLED) */

    #if(Sensirion_I2C_FF_IMPLEMENTED)
        #if(CY_PSOC3 || CY_PSOC5LP)
            /* Store registers which are held in reset when Master and Slave bits are cleared */
            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                Sensirion_I2C_backup.addr = Sensirion_I2C_ADDR_REG;
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

            Sensirion_I2C_backup.clkDiv1  = Sensirion_I2C_CLKDIV1_REG;
            Sensirion_I2C_backup.clkDiv2  = Sensirion_I2C_CLKDIV2_REG;


            /* Reset FF block */
            Sensirion_I2C_CFG_REG &= ((uint8) ~Sensirion_I2C_ENABLE_MS);
            CyDelayUs(Sensirion_I2C_FF_RESET_DELAY);
            Sensirion_I2C_CFG_REG |= ((uint8)  Sensirion_I2C_ENABLE_MS);


            /* Restore registers */
            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                Sensirion_I2C_ADDR_REG = Sensirion_I2C_backup.addr;
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

            Sensirion_I2C_CLKDIV1_REG = Sensirion_I2C_backup.clkDiv1;
            Sensirion_I2C_CLKDIV2_REG = Sensirion_I2C_backup.clkDiv2;

        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        /* Disable power to I2C block */
        enableInterrupts = CyEnterCriticalSection();
        Sensirion_I2C_ACT_PWRMGR_REG  &= ((uint8) ~Sensirion_I2C_ACT_PWR_EN);
        Sensirion_I2C_STBY_PWRMGR_REG &= ((uint8) ~Sensirion_I2C_STBY_PWR_EN);
        CyExitCriticalSection(enableInterrupts);

    #else

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            /* Disable slave bit counter */
            enableInterrupts = CyEnterCriticalSection();
            Sensirion_I2C_COUNTER_AUX_CTL_REG &= ((uint8) ~Sensirion_I2C_CNT7_ENABLE);
            CyExitCriticalSection(enableInterrupts);
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        Sensirion_I2C_CFG_REG &= ((uint8) ~Sensirion_I2C_ENABLE_MS);

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    Sensirion_I2C_ClearPendingInt();  /* Clear interrupt triggers on reset */

    Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;  /* Reset software FSM */
}


/* [] END OF FILE */
