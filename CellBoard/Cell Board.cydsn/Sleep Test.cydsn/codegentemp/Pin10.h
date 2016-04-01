/*******************************************************************************
* File Name: Pin10.h  
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

#if !defined(CY_PINS_Pin10_H) /* Pins Pin10_H */
#define CY_PINS_Pin10_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin10_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin10__PORT == 15 && ((Pin10__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin10_Write(uint8 value) ;
void    Pin10_SetDriveMode(uint8 mode) ;
uint8   Pin10_ReadDataReg(void) ;
uint8   Pin10_Read(void) ;
uint8   Pin10_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin10_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin10_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin10_DM_RES_UP          PIN_DM_RES_UP
#define Pin10_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin10_DM_OD_LO           PIN_DM_OD_LO
#define Pin10_DM_OD_HI           PIN_DM_OD_HI
#define Pin10_DM_STRONG          PIN_DM_STRONG
#define Pin10_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin10_MASK               Pin10__MASK
#define Pin10_SHIFT              Pin10__SHIFT
#define Pin10_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin10_PS                     (* (reg8 *) Pin10__PS)
/* Data Register */
#define Pin10_DR                     (* (reg8 *) Pin10__DR)
/* Port Number */
#define Pin10_PRT_NUM                (* (reg8 *) Pin10__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin10_AG                     (* (reg8 *) Pin10__AG)                       
/* Analog MUX bux enable */
#define Pin10_AMUX                   (* (reg8 *) Pin10__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin10_BIE                    (* (reg8 *) Pin10__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin10_BIT_MASK               (* (reg8 *) Pin10__BIT_MASK)
/* Bypass Enable */
#define Pin10_BYP                    (* (reg8 *) Pin10__BYP)
/* Port wide control signals */                                                   
#define Pin10_CTL                    (* (reg8 *) Pin10__CTL)
/* Drive Modes */
#define Pin10_DM0                    (* (reg8 *) Pin10__DM0) 
#define Pin10_DM1                    (* (reg8 *) Pin10__DM1)
#define Pin10_DM2                    (* (reg8 *) Pin10__DM2) 
/* Input Buffer Disable Override */
#define Pin10_INP_DIS                (* (reg8 *) Pin10__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin10_LCD_COM_SEG            (* (reg8 *) Pin10__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin10_LCD_EN                 (* (reg8 *) Pin10__LCD_EN)
/* Slew Rate Control */
#define Pin10_SLW                    (* (reg8 *) Pin10__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin10_PRTDSI__CAPS_SEL       (* (reg8 *) Pin10__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin10_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin10__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin10_PRTDSI__OE_SEL0        (* (reg8 *) Pin10__PRTDSI__OE_SEL0) 
#define Pin10_PRTDSI__OE_SEL1        (* (reg8 *) Pin10__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin10_PRTDSI__OUT_SEL0       (* (reg8 *) Pin10__PRTDSI__OUT_SEL0) 
#define Pin10_PRTDSI__OUT_SEL1       (* (reg8 *) Pin10__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin10_PRTDSI__SYNC_OUT       (* (reg8 *) Pin10__PRTDSI__SYNC_OUT) 


#if defined(Pin10__INTSTAT)  /* Interrupt Registers */

    #define Pin10_INTSTAT                (* (reg8 *) Pin10__INTSTAT)
    #define Pin10_SNAP                   (* (reg8 *) Pin10__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin10_H */


/* [] END OF FILE */
