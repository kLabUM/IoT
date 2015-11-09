/*******************************************************************************
* File Name: SCCT_Comp_1.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the SCCT Comparator
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

#if !defined(CY_SCCT_COMP_SCCT_Comp_1_H)
#define CY_SCCT_COMP_SCCT_Comp_1_H

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*       Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
}   SCCT_Comp_1_BACKUP_STRUCT;


/* Variable describes init state of the SCCT_Comp_1 */
extern uint8 SCCT_Comp_1_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SCCT_Comp_1_POLARITY                 (0u)
#define SCCT_Comp_1_SYNC                     (1u)


/***************************************
*        Function Prototypes
***************************************/

void SCCT_Comp_1_Start(void)                 ;
void SCCT_Comp_1_Stop(void)                  ;
void SCCT_Comp_1_Init(void)                  ;
void SCCT_Comp_1_Enable(void)                ;
void SCCT_Comp_1_Sleep(void)                 ;
void SCCT_Comp_1_Wakeup(void)                ;


/***************************************
*             Registers
***************************************/

#define SCCT_Comp_1_CR0_REG                  (* (reg8 *) SCCT_Comp_1_SC__CR0 )
#define SCCT_Comp_1_CR0_PTR                  (  (reg8 *) SCCT_Comp_1_SC__CR0 )
#define SCCT_Comp_1_CR1_REG                  (* (reg8 *) SCCT_Comp_1_SC__CR1 )
#define SCCT_Comp_1_CR1_PTR                  (  (reg8 *) SCCT_Comp_1_SC__CR1 )
#define SCCT_Comp_1_CR2_REG                  (* (reg8 *) SCCT_Comp_1_SC__CR2 )
#define SCCT_Comp_1_CR2_PTR                  (  (reg8 *) SCCT_Comp_1_SC__CR2 )
#define SCCT_Comp_1_SC_CLK_REG               (* (reg8 *) SCCT_Comp_1_SC__CLK )
#define SCCT_Comp_1_SC_CLK_PTR               (  (reg8 *) SCCT_Comp_1_SC__CLK )

/* Power manager */
#define SCCT_Comp_1_PM_ACT_CFG_REG           (* (reg8 *) SCCT_Comp_1_SC__PM_ACT_CFG )
#define SCCT_Comp_1_PM_ACT_CFG_PTR           (  (reg8 *) SCCT_Comp_1_SC__PM_ACT_CFG )
#define SCCT_Comp_1_PM_STBY_CFG_REG          (* (reg8 *) SCCT_Comp_1_SC__PM_STBY_CFG )
#define SCCT_Comp_1_PM_STBY_CFG_PTR          (  (reg8 *) SCCT_Comp_1_SC__PM_STBY_CFG )
#define SCCT_Comp_1_BSTCLK_REG               (* (reg8 *) SCCT_Comp_1_SC__BST )
#define SCCT_Comp_1_BSTCLK_PTR               (  (reg8 *) SCCT_Comp_1_SC__BST )

/* Pump clock selection register */
#define SCCT_Comp_1_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1 )
#define SCCT_Comp_1_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1 )

/* Pump Register for SC block */
#define SCCT_Comp_1_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define SCCT_Comp_1_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */
#define SCCT_Comp_1_ACT_PWR_EN               (SCCT_Comp_1_SC__PM_ACT_MSK)

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register) mask */
#define SCCT_Comp_1_STBY_PWR_EN              (SCCT_Comp_1_SC__PM_STBY_MSK)


/***************************************
*        Register Constants
***************************************/

/* CR0 SC/CT Control Register 0 definitions */
#define SCCT_Comp_1_MODE_COMPARATOR          (0x20u)

/* CR2 SC/CT Control Register 2 definitions */
#define SCCT_Comp_1_BIAS                     (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define SCCT_Comp_1_PUMP_CR1_SC_CLKSEL       (0x80u)

/* ANIF.PUMP.CR1 Constants */
#define SCCT_Comp_1_CLK_EN                   (0x08u)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */
#define SCCT_Comp_1_PM_ACT_CFG_MASK          (0x0Fu)

/* SC_BST Boost Clock Selection Register Constants */
#define SCCT_Comp_1_BST_CLK_EN               (0x08u)
#define SCCT_Comp_1_BST_CLK_INDEX_MASK       (0x07u)

/* SC_MISC Control Register Constants */
#define SCCT_Comp_1_PUMP_FORCE               (0x20u)

#endif /* CY_SCCT_COMP_SCCT_Comp_1_H */


/* [] END OF FILE */
