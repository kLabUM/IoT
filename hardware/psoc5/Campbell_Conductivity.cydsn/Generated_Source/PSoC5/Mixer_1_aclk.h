/*******************************************************************************
* File Name: Mixer_1_aclk.h
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

#if !defined(CY_CLOCK_Mixer_1_aclk_H)
#define CY_CLOCK_Mixer_1_aclk_H

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

void Mixer_1_aclk_Start(void) ;
void Mixer_1_aclk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Mixer_1_aclk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Mixer_1_aclk_StandbyPower(uint8 state) ;
void Mixer_1_aclk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Mixer_1_aclk_GetDividerRegister(void) ;
void Mixer_1_aclk_SetModeRegister(uint8 modeBitMask) ;
void Mixer_1_aclk_ClearModeRegister(uint8 modeBitMask) ;
uint8 Mixer_1_aclk_GetModeRegister(void) ;
void Mixer_1_aclk_SetSourceRegister(uint8 clkSource) ;
uint8 Mixer_1_aclk_GetSourceRegister(void) ;
#if defined(Mixer_1_aclk__CFG3)
void Mixer_1_aclk_SetPhaseRegister(uint8 clkPhase) ;
uint8 Mixer_1_aclk_GetPhaseRegister(void) ;
#endif /* defined(Mixer_1_aclk__CFG3) */

#define Mixer_1_aclk_Enable()                       Mixer_1_aclk_Start()
#define Mixer_1_aclk_Disable()                      Mixer_1_aclk_Stop()
#define Mixer_1_aclk_SetDivider(clkDivider)         Mixer_1_aclk_SetDividerRegister(clkDivider, 1)
#define Mixer_1_aclk_SetDividerValue(clkDivider)    Mixer_1_aclk_SetDividerRegister((clkDivider) - 1, 1)
#define Mixer_1_aclk_SetMode(clkMode)               Mixer_1_aclk_SetModeRegister(clkMode)
#define Mixer_1_aclk_SetSource(clkSource)           Mixer_1_aclk_SetSourceRegister(clkSource)
#if defined(Mixer_1_aclk__CFG3)
#define Mixer_1_aclk_SetPhase(clkPhase)             Mixer_1_aclk_SetPhaseRegister(clkPhase)
#define Mixer_1_aclk_SetPhaseValue(clkPhase)        Mixer_1_aclk_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(Mixer_1_aclk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Mixer_1_aclk_CLKEN              (* (reg8 *) Mixer_1_aclk__PM_ACT_CFG)
#define Mixer_1_aclk_CLKEN_PTR          ((reg8 *) Mixer_1_aclk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Mixer_1_aclk_CLKSTBY            (* (reg8 *) Mixer_1_aclk__PM_STBY_CFG)
#define Mixer_1_aclk_CLKSTBY_PTR        ((reg8 *) Mixer_1_aclk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Mixer_1_aclk_DIV_LSB            (* (reg8 *) Mixer_1_aclk__CFG0)
#define Mixer_1_aclk_DIV_LSB_PTR        ((reg8 *) Mixer_1_aclk__CFG0)
#define Mixer_1_aclk_DIV_PTR            ((reg16 *) Mixer_1_aclk__CFG0)

/* Clock MSB divider configuration register. */
#define Mixer_1_aclk_DIV_MSB            (* (reg8 *) Mixer_1_aclk__CFG1)
#define Mixer_1_aclk_DIV_MSB_PTR        ((reg8 *) Mixer_1_aclk__CFG1)

/* Mode and source configuration register */
#define Mixer_1_aclk_MOD_SRC            (* (reg8 *) Mixer_1_aclk__CFG2)
#define Mixer_1_aclk_MOD_SRC_PTR        ((reg8 *) Mixer_1_aclk__CFG2)

#if defined(Mixer_1_aclk__CFG3)
/* Analog clock phase configuration register */
#define Mixer_1_aclk_PHASE              (* (reg8 *) Mixer_1_aclk__CFG3)
#define Mixer_1_aclk_PHASE_PTR          ((reg8 *) Mixer_1_aclk__CFG3)
#endif /* defined(Mixer_1_aclk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Mixer_1_aclk_CLKEN_MASK         Mixer_1_aclk__PM_ACT_MSK
#define Mixer_1_aclk_CLKSTBY_MASK       Mixer_1_aclk__PM_STBY_MSK

/* CFG2 field masks */
#define Mixer_1_aclk_SRC_SEL_MSK        Mixer_1_aclk__CFG2_SRC_SEL_MASK
#define Mixer_1_aclk_MODE_MASK          (~(Mixer_1_aclk_SRC_SEL_MSK))

#if defined(Mixer_1_aclk__CFG3)
/* CFG3 phase mask */
#define Mixer_1_aclk_PHASE_MASK         Mixer_1_aclk__CFG3_PHASE_DLY_MASK
#endif /* defined(Mixer_1_aclk__CFG3) */

#endif /* CY_CLOCK_Mixer_1_aclk_H */


/* [] END OF FILE */
