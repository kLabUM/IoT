/*******************************************************************************
* File Name: SlowClock_1.h
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

#if !defined(CY_CLOCK_SlowClock_1_H)
#define CY_CLOCK_SlowClock_1_H

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

void SlowClock_1_Start(void) ;
void SlowClock_1_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SlowClock_1_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SlowClock_1_StandbyPower(uint8 state) ;
void SlowClock_1_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SlowClock_1_GetDividerRegister(void) ;
void SlowClock_1_SetModeRegister(uint8 modeBitMask) ;
void SlowClock_1_ClearModeRegister(uint8 modeBitMask) ;
uint8 SlowClock_1_GetModeRegister(void) ;
void SlowClock_1_SetSourceRegister(uint8 clkSource) ;
uint8 SlowClock_1_GetSourceRegister(void) ;
#if defined(SlowClock_1__CFG3)
void SlowClock_1_SetPhaseRegister(uint8 clkPhase) ;
uint8 SlowClock_1_GetPhaseRegister(void) ;
#endif /* defined(SlowClock_1__CFG3) */

#define SlowClock_1_Enable()                       SlowClock_1_Start()
#define SlowClock_1_Disable()                      SlowClock_1_Stop()
#define SlowClock_1_SetDivider(clkDivider)         SlowClock_1_SetDividerRegister(clkDivider, 1)
#define SlowClock_1_SetDividerValue(clkDivider)    SlowClock_1_SetDividerRegister((clkDivider) - 1, 1)
#define SlowClock_1_SetMode(clkMode)               SlowClock_1_SetModeRegister(clkMode)
#define SlowClock_1_SetSource(clkSource)           SlowClock_1_SetSourceRegister(clkSource)
#if defined(SlowClock_1__CFG3)
#define SlowClock_1_SetPhase(clkPhase)             SlowClock_1_SetPhaseRegister(clkPhase)
#define SlowClock_1_SetPhaseValue(clkPhase)        SlowClock_1_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(SlowClock_1__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SlowClock_1_CLKEN              (* (reg8 *) SlowClock_1__PM_ACT_CFG)
#define SlowClock_1_CLKEN_PTR          ((reg8 *) SlowClock_1__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SlowClock_1_CLKSTBY            (* (reg8 *) SlowClock_1__PM_STBY_CFG)
#define SlowClock_1_CLKSTBY_PTR        ((reg8 *) SlowClock_1__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SlowClock_1_DIV_LSB            (* (reg8 *) SlowClock_1__CFG0)
#define SlowClock_1_DIV_LSB_PTR        ((reg8 *) SlowClock_1__CFG0)
#define SlowClock_1_DIV_PTR            ((reg16 *) SlowClock_1__CFG0)

/* Clock MSB divider configuration register. */
#define SlowClock_1_DIV_MSB            (* (reg8 *) SlowClock_1__CFG1)
#define SlowClock_1_DIV_MSB_PTR        ((reg8 *) SlowClock_1__CFG1)

/* Mode and source configuration register */
#define SlowClock_1_MOD_SRC            (* (reg8 *) SlowClock_1__CFG2)
#define SlowClock_1_MOD_SRC_PTR        ((reg8 *) SlowClock_1__CFG2)

#if defined(SlowClock_1__CFG3)
/* Analog clock phase configuration register */
#define SlowClock_1_PHASE              (* (reg8 *) SlowClock_1__CFG3)
#define SlowClock_1_PHASE_PTR          ((reg8 *) SlowClock_1__CFG3)
#endif /* defined(SlowClock_1__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SlowClock_1_CLKEN_MASK         SlowClock_1__PM_ACT_MSK
#define SlowClock_1_CLKSTBY_MASK       SlowClock_1__PM_STBY_MSK

/* CFG2 field masks */
#define SlowClock_1_SRC_SEL_MSK        SlowClock_1__CFG2_SRC_SEL_MASK
#define SlowClock_1_MODE_MASK          (~(SlowClock_1_SRC_SEL_MSK))

#if defined(SlowClock_1__CFG3)
/* CFG3 phase mask */
#define SlowClock_1_PHASE_MASK         SlowClock_1__CFG3_PHASE_DLY_MASK
#endif /* defined(SlowClock_1__CFG3) */

#endif /* CY_CLOCK_SlowClock_1_H */


/* [] END OF FILE */
