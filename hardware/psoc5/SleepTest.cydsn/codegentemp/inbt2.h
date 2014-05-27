/*******************************************************************************
* File Name: inbt2.h  
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

#if !defined(CY_PINS_inbt2_H) /* Pins inbt2_H */
#define CY_PINS_inbt2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "inbt2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 inbt2__PORT == 15 && ((inbt2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    inbt2_Write(uint8 value) ;
void    inbt2_SetDriveMode(uint8 mode) ;
uint8   inbt2_ReadDataReg(void) ;
uint8   inbt2_Read(void) ;
uint8   inbt2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define inbt2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define inbt2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define inbt2_DM_RES_UP          PIN_DM_RES_UP
#define inbt2_DM_RES_DWN         PIN_DM_RES_DWN
#define inbt2_DM_OD_LO           PIN_DM_OD_LO
#define inbt2_DM_OD_HI           PIN_DM_OD_HI
#define inbt2_DM_STRONG          PIN_DM_STRONG
#define inbt2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define inbt2_MASK               inbt2__MASK
#define inbt2_SHIFT              inbt2__SHIFT
#define inbt2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define inbt2_PS                     (* (reg8 *) inbt2__PS)
/* Data Register */
#define inbt2_DR                     (* (reg8 *) inbt2__DR)
/* Port Number */
#define inbt2_PRT_NUM                (* (reg8 *) inbt2__PRT) 
/* Connect to Analog Globals */                                                  
#define inbt2_AG                     (* (reg8 *) inbt2__AG)                       
/* Analog MUX bux enable */
#define inbt2_AMUX                   (* (reg8 *) inbt2__AMUX) 
/* Bidirectional Enable */                                                        
#define inbt2_BIE                    (* (reg8 *) inbt2__BIE)
/* Bit-mask for Aliased Register Access */
#define inbt2_BIT_MASK               (* (reg8 *) inbt2__BIT_MASK)
/* Bypass Enable */
#define inbt2_BYP                    (* (reg8 *) inbt2__BYP)
/* Port wide control signals */                                                   
#define inbt2_CTL                    (* (reg8 *) inbt2__CTL)
/* Drive Modes */
#define inbt2_DM0                    (* (reg8 *) inbt2__DM0) 
#define inbt2_DM1                    (* (reg8 *) inbt2__DM1)
#define inbt2_DM2                    (* (reg8 *) inbt2__DM2) 
/* Input Buffer Disable Override */
#define inbt2_INP_DIS                (* (reg8 *) inbt2__INP_DIS)
/* LCD Common or Segment Drive */
#define inbt2_LCD_COM_SEG            (* (reg8 *) inbt2__LCD_COM_SEG)
/* Enable Segment LCD */
#define inbt2_LCD_EN                 (* (reg8 *) inbt2__LCD_EN)
/* Slew Rate Control */
#define inbt2_SLW                    (* (reg8 *) inbt2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define inbt2_PRTDSI__CAPS_SEL       (* (reg8 *) inbt2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define inbt2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) inbt2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define inbt2_PRTDSI__OE_SEL0        (* (reg8 *) inbt2__PRTDSI__OE_SEL0) 
#define inbt2_PRTDSI__OE_SEL1        (* (reg8 *) inbt2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define inbt2_PRTDSI__OUT_SEL0       (* (reg8 *) inbt2__PRTDSI__OUT_SEL0) 
#define inbt2_PRTDSI__OUT_SEL1       (* (reg8 *) inbt2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define inbt2_PRTDSI__SYNC_OUT       (* (reg8 *) inbt2__PRTDSI__SYNC_OUT) 


#if defined(inbt2__INTSTAT)  /* Interrupt Registers */

    #define inbt2_INTSTAT                (* (reg8 *) inbt2__INTSTAT)
    #define inbt2_SNAP                   (* (reg8 *) inbt2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_inbt2_H */


/* [] END OF FILE */
