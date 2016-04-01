/*******************************************************************************
* File Name: Pin39.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin39_H) /* Pins Pin39_H */
#define CY_PINS_Pin39_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin39_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin39__PORT == 15 && ((Pin39__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin39_Write(uint8 value) ;
void    Pin39_SetDriveMode(uint8 mode) ;
uint8   Pin39_ReadDataReg(void) ;
uint8   Pin39_Read(void) ;
uint8   Pin39_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin39_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin39_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin39_DM_RES_UP          PIN_DM_RES_UP
#define Pin39_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin39_DM_OD_LO           PIN_DM_OD_LO
#define Pin39_DM_OD_HI           PIN_DM_OD_HI
#define Pin39_DM_STRONG          PIN_DM_STRONG
#define Pin39_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin39_MASK               Pin39__MASK
#define Pin39_SHIFT              Pin39__SHIFT
#define Pin39_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin39_PS                     (* (reg8 *) Pin39__PS)
/* Data Register */
#define Pin39_DR                     (* (reg8 *) Pin39__DR)
/* Port Number */
#define Pin39_PRT_NUM                (* (reg8 *) Pin39__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin39_AG                     (* (reg8 *) Pin39__AG)                       
/* Analog MUX bux enable */
#define Pin39_AMUX                   (* (reg8 *) Pin39__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin39_BIE                    (* (reg8 *) Pin39__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin39_BIT_MASK               (* (reg8 *) Pin39__BIT_MASK)
/* Bypass Enable */
#define Pin39_BYP                    (* (reg8 *) Pin39__BYP)
/* Port wide control signals */                                                   
#define Pin39_CTL                    (* (reg8 *) Pin39__CTL)
/* Drive Modes */
#define Pin39_DM0                    (* (reg8 *) Pin39__DM0) 
#define Pin39_DM1                    (* (reg8 *) Pin39__DM1)
#define Pin39_DM2                    (* (reg8 *) Pin39__DM2) 
/* Input Buffer Disable Override */
#define Pin39_INP_DIS                (* (reg8 *) Pin39__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin39_LCD_COM_SEG            (* (reg8 *) Pin39__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin39_LCD_EN                 (* (reg8 *) Pin39__LCD_EN)
/* Slew Rate Control */
#define Pin39_SLW                    (* (reg8 *) Pin39__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin39_PRTDSI__CAPS_SEL       (* (reg8 *) Pin39__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin39_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin39__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin39_PRTDSI__OE_SEL0        (* (reg8 *) Pin39__PRTDSI__OE_SEL0) 
#define Pin39_PRTDSI__OE_SEL1        (* (reg8 *) Pin39__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin39_PRTDSI__OUT_SEL0       (* (reg8 *) Pin39__PRTDSI__OUT_SEL0) 
#define Pin39_PRTDSI__OUT_SEL1       (* (reg8 *) Pin39__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin39_PRTDSI__SYNC_OUT       (* (reg8 *) Pin39__PRTDSI__SYNC_OUT) 


#if defined(Pin39__INTSTAT)  /* Interrupt Registers */

    #define Pin39_INTSTAT                (* (reg8 *) Pin39__INTSTAT)
    #define Pin39_SNAP                   (* (reg8 *) Pin39__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin39_H */


/* [] END OF FILE */
