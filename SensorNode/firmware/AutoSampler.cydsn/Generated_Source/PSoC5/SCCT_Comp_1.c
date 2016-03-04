/*******************************************************************************
* File Name: SCCT_Comp_1.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the SCCT Comparator
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCCT_Comp_1.h"
#include "CyLib.h"

#if (1u == CYDEV_VARIABLE_VDDA)
    #include "CyScBoostClk.h"
#endif /* 1u == CYDEV_VARIABLE_VDDA */

uint8 SCCT_Comp_1_initVar = 0u;


/*******************************************************************************
* Function Name: SCCT_Comp_1_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the SCCT_Comp_1 according to the customizer
*  settings. It is not necessary to call SCCT_Comp_1_Init() because the
*  SCCT_Comp_1_Start() API calls this function and is the preferred method
*  to begin SCCT_Comp_1 operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SCCT_Comp_1_Init(void) 
{
    /* Set Naked Op-Amp - Comparator mode */
    SCCT_Comp_1_CR0_REG = SCCT_Comp_1_MODE_COMPARATOR;

    /* Reset SCCT_Comp_1 Control Register 1 to initial value */
    SCCT_Comp_1_CR1_REG = 0u;

    /* Set bias current to normal operation */
    SCCT_Comp_1_CR2_REG = SCCT_Comp_1_BIAS;
}


/*******************************************************************************
* Function Name: SCCT_Comp_1_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins SCCT_Comp_1 operation. It is not
*  necessary to call SCCT_Comp_1_Enable() because the
*  SCCT_Comp_1_Start() API calls this function, which is the preferred
*  method to begin SCCT_Comp_1 operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SCCT_Comp_1_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable power to the SCCT_Comp_1 in Active mode */
    SCCT_Comp_1_PM_ACT_CFG_REG |= SCCT_Comp_1_ACT_PWR_EN;

    /* Enable the power to the SCCT_Comp_1 in Alternative active mode */
    SCCT_Comp_1_PM_STBY_CFG_REG |= SCCT_Comp_1_STBY_PWR_EN;

    /* SCCT_Comp_1 internal Pump Clock Selection */
    SCCT_Comp_1_PUMP_CR1_REG |= SCCT_Comp_1_PUMP_CR1_SC_CLKSEL;

    #if (1u == CYDEV_VARIABLE_VDDA)

        if (1u == CyScPumpEnabled)
        {
            SCCT_Comp_1_BSTCLK_REG &= (uint8)(~SCCT_Comp_1_BST_CLK_INDEX_MASK);
            SCCT_Comp_1_BSTCLK_REG |= (SCCT_Comp_1_BST_CLK_EN | CyScBoostClk__INDEX);
            SCCT_Comp_1_SC_MISC_REG |= SCCT_Comp_1_PUMP_FORCE;
            CyScBoostClk_Start();
        }
        else
        {
            SCCT_Comp_1_BSTCLK_REG &= (uint8)(~SCCT_Comp_1_BST_CLK_EN);
            SCCT_Comp_1_SC_MISC_REG &= (uint8)(~SCCT_Comp_1_PUMP_FORCE);
        }

    #endif /* 1u == CYDEV_VARIABLE_VDDA */

    CyExitCriticalSection(enableInterrupts);

    /* Enable clock (aclk) to the SCCT_Comp_1 and disable dynamic control */
    SCCT_Comp_1_SC_CLK_REG = SCCT_Comp_1_CLK_EN;
}


/*******************************************************************************
* Function Name: SCCT_Comp_1_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the SCCT_Comp_1 and
*  enables power to the SCCT_Comp_1. The first time the routine is
*  executed, the SCCT_Comp_1 is initialized to the configuration from the
*  customizer. When called to restart the SCCT_Comp_1 following a
*  SCCT_Comp_1_Stop() call, the current SCCT_Comp_1 parameter
*  settings are retained.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SCCT_Comp_1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
* Side Effect:
*  If the initVar variable is already set, this function only calls the
*  SCCT_Comp_1_Enable() function.
*
*******************************************************************************/
void SCCT_Comp_1_Start(void) 
{
    if (0u == SCCT_Comp_1_initVar)
    {
        SCCT_Comp_1_Init();
        SCCT_Comp_1_initVar = 1u;
    }

    SCCT_Comp_1_Enable();
}


/*******************************************************************************
* Function Name: SCCT_Comp_1_Stop
********************************************************************************
*
* Summary:
*  Turns off the SCCT_Comp_1. It will disable the related SC/CT block.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SCCT_Comp_1_Stop(void) 
{
    uint8 enableInterrupts;    

    enableInterrupts = CyEnterCriticalSection();

    /* Disble power to the SCCT_Comp_1 in Active mode template */
    SCCT_Comp_1_PM_ACT_CFG_REG &= (uint8)(~SCCT_Comp_1_ACT_PWR_EN);

    /* Disble power to the SCCT_Comp_1 in Alternative Active mode template */
    SCCT_Comp_1_PM_STBY_CFG_REG &= (uint8)(~SCCT_Comp_1_STBY_PWR_EN);

    #if (1u == CYDEV_VARIABLE_VDDA)

        SCCT_Comp_1_BSTCLK_REG &= (uint8)(~SCCT_Comp_1_BST_CLK_EN);

        /* Disable pumps only if there aren't any SC/CT block in use */
        if (0u == (SCCT_Comp_1_PM_ACT_CFG_REG & SCCT_Comp_1_PM_ACT_CFG_MASK))
        {
            SCCT_Comp_1_SC_MISC_REG &= (uint8)(~SCCT_Comp_1_PUMP_FORCE);
            SCCT_Comp_1_PUMP_CR1_REG &= (uint8)(~SCCT_Comp_1_PUMP_CR1_SC_CLKSEL);
            CyScBoostClk_Stop();
        }

    #endif /* 1u == CYDEV_VARIABLE_VDDA */

    CyExitCriticalSection(enableInterrupts);
    
    /* Disable clock (aclk) to SCCT_Comp_1 */
    SCCT_Comp_1_SC_CLK_REG &= (uint8)(~SCCT_Comp_1_CLK_EN);
}


/* [] END OF FILE */
