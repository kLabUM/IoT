/*******************************************************************************
* File Name: SCCT_Comp_1_SCCMPCLK.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SCCT_Comp_1_SCCMPCLK_H)
#define CY_CLOCK_SCCT_Comp_1_SCCMPCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SCCT_Comp_1_SCCMPCLK_Start(void) ;
void SCCT_Comp_1_SCCMPCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SCCT_Comp_1_SCCMPCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SCCT_Comp_1_SCCMPCLK_StandbyPower(uint8 state) ;
void SCCT_Comp_1_SCCMPCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SCCT_Comp_1_SCCMPCLK_GetDividerRegister(void) ;
void SCCT_Comp_1_SCCMPCLK_SetModeRegister(uint8 modeBitMask) ;
void SCCT_Comp_1_SCCMPCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 SCCT_Comp_1_SCCMPCLK_GetModeRegister(void) ;
void SCCT_Comp_1_SCCMPCLK_SetSourceRegister(uint8 clkSource) ;
uint8 SCCT_Comp_1_SCCMPCLK_GetSourceRegister(void) ;
#if defined(SCCT_Comp_1_SCCMPCLK__CFG3)
void SCCT_Comp_1_SCCMPCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 SCCT_Comp_1_SCCMPCLK_GetPhaseRegister(void) ;
#endif /* defined(SCCT_Comp_1_SCCMPCLK__CFG3) */

#define SCCT_Comp_1_SCCMPCLK_Enable()                       SCCT_Comp_1_SCCMPCLK_Start()
#define SCCT_Comp_1_SCCMPCLK_Disable()                      SCCT_Comp_1_SCCMPCLK_Stop()
#define SCCT_Comp_1_SCCMPCLK_SetDivider(clkDivider)         SCCT_Comp_1_SCCMPCLK_SetDividerRegister(clkDivider, 1)
#define SCCT_Comp_1_SCCMPCLK_SetDividerValue(clkDivider)    SCCT_Comp_1_SCCMPCLK_SetDividerRegister((clkDivider) - 1, 1)
#define SCCT_Comp_1_SCCMPCLK_SetMode(clkMode)               SCCT_Comp_1_SCCMPCLK_SetModeRegister(clkMode)
#define SCCT_Comp_1_SCCMPCLK_SetSource(clkSource)           SCCT_Comp_1_SCCMPCLK_SetSourceRegister(clkSource)
#if defined(SCCT_Comp_1_SCCMPCLK__CFG3)
#define SCCT_Comp_1_SCCMPCLK_SetPhase(clkPhase)             SCCT_Comp_1_SCCMPCLK_SetPhaseRegister(clkPhase)
#define SCCT_Comp_1_SCCMPCLK_SetPhaseValue(clkPhase)        SCCT_Comp_1_SCCMPCLK_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(SCCT_Comp_1_SCCMPCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SCCT_Comp_1_SCCMPCLK_CLKEN              (* (reg8 *) SCCT_Comp_1_SCCMPCLK__PM_ACT_CFG)
#define SCCT_Comp_1_SCCMPCLK_CLKEN_PTR          ((reg8 *) SCCT_Comp_1_SCCMPCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SCCT_Comp_1_SCCMPCLK_CLKSTBY            (* (reg8 *) SCCT_Comp_1_SCCMPCLK__PM_STBY_CFG)
#define SCCT_Comp_1_SCCMPCLK_CLKSTBY_PTR        ((reg8 *) SCCT_Comp_1_SCCMPCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SCCT_Comp_1_SCCMPCLK_DIV_LSB            (* (reg8 *) SCCT_Comp_1_SCCMPCLK__CFG0)
#define SCCT_Comp_1_SCCMPCLK_DIV_LSB_PTR        ((reg8 *) SCCT_Comp_1_SCCMPCLK__CFG0)
#define SCCT_Comp_1_SCCMPCLK_DIV_PTR            ((reg16 *) SCCT_Comp_1_SCCMPCLK__CFG0)

/* Clock MSB divider configuration register. */
#define SCCT_Comp_1_SCCMPCLK_DIV_MSB            (* (reg8 *) SCCT_Comp_1_SCCMPCLK__CFG1)
#define SCCT_Comp_1_SCCMPCLK_DIV_MSB_PTR        ((reg8 *) SCCT_Comp_1_SCCMPCLK__CFG1)

/* Mode and source configuration register */
#define SCCT_Comp_1_SCCMPCLK_MOD_SRC            (* (reg8 *) SCCT_Comp_1_SCCMPCLK__CFG2)
#define SCCT_Comp_1_SCCMPCLK_MOD_SRC_PTR        ((reg8 *) SCCT_Comp_1_SCCMPCLK__CFG2)

#if defined(SCCT_Comp_1_SCCMPCLK__CFG3)
/* Analog clock phase configuration register */
#define SCCT_Comp_1_SCCMPCLK_PHASE              (* (reg8 *) SCCT_Comp_1_SCCMPCLK__CFG3)
#define SCCT_Comp_1_SCCMPCLK_PHASE_PTR          ((reg8 *) SCCT_Comp_1_SCCMPCLK__CFG3)
#endif /* defined(SCCT_Comp_1_SCCMPCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SCCT_Comp_1_SCCMPCLK_CLKEN_MASK         SCCT_Comp_1_SCCMPCLK__PM_ACT_MSK
#define SCCT_Comp_1_SCCMPCLK_CLKSTBY_MASK       SCCT_Comp_1_SCCMPCLK__PM_STBY_MSK

/* CFG2 field masks */
#define SCCT_Comp_1_SCCMPCLK_SRC_SEL_MSK        SCCT_Comp_1_SCCMPCLK__CFG2_SRC_SEL_MASK
#define SCCT_Comp_1_SCCMPCLK_MODE_MASK          (~(SCCT_Comp_1_SCCMPCLK_SRC_SEL_MSK))

#if defined(SCCT_Comp_1_SCCMPCLK__CFG3)
/* CFG3 phase mask */
#define SCCT_Comp_1_SCCMPCLK_PHASE_MASK         SCCT_Comp_1_SCCMPCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(SCCT_Comp_1_SCCMPCLK__CFG3) */

#endif /* CY_CLOCK_SCCT_Comp_1_SCCMPCLK_H */


/* [] END OF FILE */
