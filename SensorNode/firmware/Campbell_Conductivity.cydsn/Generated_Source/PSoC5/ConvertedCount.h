/*******************************************************************************
* File Name: ConvertedCount.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_ConvertedCount_H) /* CY_STATUS_REG_ConvertedCount_H */
#define CY_STATUS_REG_ConvertedCount_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 ConvertedCount_Read(void) ;
void ConvertedCount_InterruptEnable(void) ;
void ConvertedCount_InterruptDisable(void) ;
void ConvertedCount_WriteMask(uint8 mask) ;
uint8 ConvertedCount_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define ConvertedCount_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define ConvertedCount_INPUTS              8


/***************************************
*             Registers
***************************************/

/* Status Register */
#define ConvertedCount_Status             (* (reg8 *) ConvertedCount_sts_sts_reg__STATUS_REG )
#define ConvertedCount_Status_PTR         (  (reg8 *) ConvertedCount_sts_sts_reg__STATUS_REG )
#define ConvertedCount_Status_Mask        (* (reg8 *) ConvertedCount_sts_sts_reg__MASK_REG )
#define ConvertedCount_Status_Aux_Ctrl    (* (reg8 *) ConvertedCount_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_ConvertedCount_H */


/* [] END OF FILE */
