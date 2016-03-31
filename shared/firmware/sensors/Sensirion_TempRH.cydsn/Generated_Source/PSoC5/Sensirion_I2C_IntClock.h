/*******************************************************************************
* File Name: Sensirion_I2C_IntClock.h
* Version 2.20
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

#if !defined(CY_CLOCK_Sensirion_I2C_IntClock_H)
#define CY_CLOCK_Sensirion_I2C_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Sensirion_I2C_IntClock_Start(void) ;
void Sensirion_I2C_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Sensirion_I2C_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Sensirion_I2C_IntClock_StandbyPower(uint8 state) ;
void Sensirion_I2C_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Sensirion_I2C_IntClock_GetDividerRegister(void) ;
void Sensirion_I2C_IntClock_SetModeRegister(uint8 modeBitMask) ;
void Sensirion_I2C_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Sensirion_I2C_IntClock_GetModeRegister(void) ;
void Sensirion_I2C_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 Sensirion_I2C_IntClock_GetSourceRegister(void) ;
#if defined(Sensirion_I2C_IntClock__CFG3)
void Sensirion_I2C_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Sensirion_I2C_IntClock_GetPhaseRegister(void) ;
#endif /* defined(Sensirion_I2C_IntClock__CFG3) */

#define Sensirion_I2C_IntClock_Enable()                       Sensirion_I2C_IntClock_Start()
#define Sensirion_I2C_IntClock_Disable()                      Sensirion_I2C_IntClock_Stop()
#define Sensirion_I2C_IntClock_SetDivider(clkDivider)         Sensirion_I2C_IntClock_SetDividerRegister(clkDivider, 1u)
#define Sensirion_I2C_IntClock_SetDividerValue(clkDivider)    Sensirion_I2C_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Sensirion_I2C_IntClock_SetMode(clkMode)               Sensirion_I2C_IntClock_SetModeRegister(clkMode)
#define Sensirion_I2C_IntClock_SetSource(clkSource)           Sensirion_I2C_IntClock_SetSourceRegister(clkSource)
#if defined(Sensirion_I2C_IntClock__CFG3)
#define Sensirion_I2C_IntClock_SetPhase(clkPhase)             Sensirion_I2C_IntClock_SetPhaseRegister(clkPhase)
#define Sensirion_I2C_IntClock_SetPhaseValue(clkPhase)        Sensirion_I2C_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Sensirion_I2C_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Sensirion_I2C_IntClock_CLKEN              (* (reg8 *) Sensirion_I2C_IntClock__PM_ACT_CFG)
#define Sensirion_I2C_IntClock_CLKEN_PTR          ((reg8 *) Sensirion_I2C_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Sensirion_I2C_IntClock_CLKSTBY            (* (reg8 *) Sensirion_I2C_IntClock__PM_STBY_CFG)
#define Sensirion_I2C_IntClock_CLKSTBY_PTR        ((reg8 *) Sensirion_I2C_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Sensirion_I2C_IntClock_DIV_LSB            (* (reg8 *) Sensirion_I2C_IntClock__CFG0)
#define Sensirion_I2C_IntClock_DIV_LSB_PTR        ((reg8 *) Sensirion_I2C_IntClock__CFG0)
#define Sensirion_I2C_IntClock_DIV_PTR            ((reg16 *) Sensirion_I2C_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define Sensirion_I2C_IntClock_DIV_MSB            (* (reg8 *) Sensirion_I2C_IntClock__CFG1)
#define Sensirion_I2C_IntClock_DIV_MSB_PTR        ((reg8 *) Sensirion_I2C_IntClock__CFG1)

/* Mode and source configuration register */
#define Sensirion_I2C_IntClock_MOD_SRC            (* (reg8 *) Sensirion_I2C_IntClock__CFG2)
#define Sensirion_I2C_IntClock_MOD_SRC_PTR        ((reg8 *) Sensirion_I2C_IntClock__CFG2)

#if defined(Sensirion_I2C_IntClock__CFG3)
/* Analog clock phase configuration register */
#define Sensirion_I2C_IntClock_PHASE              (* (reg8 *) Sensirion_I2C_IntClock__CFG3)
#define Sensirion_I2C_IntClock_PHASE_PTR          ((reg8 *) Sensirion_I2C_IntClock__CFG3)
#endif /* defined(Sensirion_I2C_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Sensirion_I2C_IntClock_CLKEN_MASK         Sensirion_I2C_IntClock__PM_ACT_MSK
#define Sensirion_I2C_IntClock_CLKSTBY_MASK       Sensirion_I2C_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define Sensirion_I2C_IntClock_SRC_SEL_MSK        Sensirion_I2C_IntClock__CFG2_SRC_SEL_MASK
#define Sensirion_I2C_IntClock_MODE_MASK          (~(Sensirion_I2C_IntClock_SRC_SEL_MSK))

#if defined(Sensirion_I2C_IntClock__CFG3)
/* CFG3 phase mask */
#define Sensirion_I2C_IntClock_PHASE_MASK         Sensirion_I2C_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(Sensirion_I2C_IntClock__CFG3) */

#endif /* CY_CLOCK_Sensirion_I2C_IntClock_H */


/* [] END OF FILE */
