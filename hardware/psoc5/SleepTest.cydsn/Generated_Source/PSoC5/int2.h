/*******************************************************************************
* File Name: int2.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_int2_H) /* Pins int2_H */
#define CY_PINS_int2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "int2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 int2__PORT == 15 && ((int2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    int2_Write(uint8 value) ;
void    int2_SetDriveMode(uint8 mode) ;
uint8   int2_ReadDataReg(void) ;
uint8   int2_Read(void) ;
uint8   int2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define int2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define int2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define int2_DM_RES_UP          PIN_DM_RES_UP
#define int2_DM_RES_DWN         PIN_DM_RES_DWN
#define int2_DM_OD_LO           PIN_DM_OD_LO
#define int2_DM_OD_HI           PIN_DM_OD_HI
#define int2_DM_STRONG          PIN_DM_STRONG
#define int2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define int2_MASK               int2__MASK
#define int2_SHIFT              int2__SHIFT
#define int2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define int2_PS                     (* (reg8 *) int2__PS)
/* Data Register */
#define int2_DR                     (* (reg8 *) int2__DR)
/* Port Number */
#define int2_PRT_NUM                (* (reg8 *) int2__PRT) 
/* Connect to Analog Globals */                                                  
#define int2_AG                     (* (reg8 *) int2__AG)                       
/* Analog MUX bux enable */
#define int2_AMUX                   (* (reg8 *) int2__AMUX) 
/* Bidirectional Enable */                                                        
#define int2_BIE                    (* (reg8 *) int2__BIE)
/* Bit-mask for Aliased Register Access */
#define int2_BIT_MASK               (* (reg8 *) int2__BIT_MASK)
/* Bypass Enable */
#define int2_BYP                    (* (reg8 *) int2__BYP)
/* Port wide control signals */                                                   
#define int2_CTL                    (* (reg8 *) int2__CTL)
/* Drive Modes */
#define int2_DM0                    (* (reg8 *) int2__DM0) 
#define int2_DM1                    (* (reg8 *) int2__DM1)
#define int2_DM2                    (* (reg8 *) int2__DM2) 
/* Input Buffer Disable Override */
#define int2_INP_DIS                (* (reg8 *) int2__INP_DIS)
/* LCD Common or Segment Drive */
#define int2_LCD_COM_SEG            (* (reg8 *) int2__LCD_COM_SEG)
/* Enable Segment LCD */
#define int2_LCD_EN                 (* (reg8 *) int2__LCD_EN)
/* Slew Rate Control */
#define int2_SLW                    (* (reg8 *) int2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define int2_PRTDSI__CAPS_SEL       (* (reg8 *) int2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define int2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) int2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define int2_PRTDSI__OE_SEL0        (* (reg8 *) int2__PRTDSI__OE_SEL0) 
#define int2_PRTDSI__OE_SEL1        (* (reg8 *) int2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define int2_PRTDSI__OUT_SEL0       (* (reg8 *) int2__PRTDSI__OUT_SEL0) 
#define int2_PRTDSI__OUT_SEL1       (* (reg8 *) int2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define int2_PRTDSI__SYNC_OUT       (* (reg8 *) int2__PRTDSI__SYNC_OUT) 


#if defined(int2__INTSTAT)  /* Interrupt Registers */

    #define int2_INTSTAT                (* (reg8 *) int2__INTSTAT)
    #define int2_SNAP                   (* (reg8 *) int2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_int2_H */


/* [] END OF FILE */
