/*******************************************************************************
* File Name: Pin9.h  
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

#if !defined(CY_PINS_Pin9_H) /* Pins Pin9_H */
#define CY_PINS_Pin9_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin9_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin9__PORT == 15 && ((Pin9__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin9_Write(uint8 value) ;
void    Pin9_SetDriveMode(uint8 mode) ;
uint8   Pin9_ReadDataReg(void) ;
uint8   Pin9_Read(void) ;
uint8   Pin9_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin9_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin9_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin9_DM_RES_UP          PIN_DM_RES_UP
#define Pin9_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin9_DM_OD_LO           PIN_DM_OD_LO
#define Pin9_DM_OD_HI           PIN_DM_OD_HI
#define Pin9_DM_STRONG          PIN_DM_STRONG
#define Pin9_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin9_MASK               Pin9__MASK
#define Pin9_SHIFT              Pin9__SHIFT
#define Pin9_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin9_PS                     (* (reg8 *) Pin9__PS)
/* Data Register */
#define Pin9_DR                     (* (reg8 *) Pin9__DR)
/* Port Number */
#define Pin9_PRT_NUM                (* (reg8 *) Pin9__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin9_AG                     (* (reg8 *) Pin9__AG)                       
/* Analog MUX bux enable */
#define Pin9_AMUX                   (* (reg8 *) Pin9__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin9_BIE                    (* (reg8 *) Pin9__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin9_BIT_MASK               (* (reg8 *) Pin9__BIT_MASK)
/* Bypass Enable */
#define Pin9_BYP                    (* (reg8 *) Pin9__BYP)
/* Port wide control signals */                                                   
#define Pin9_CTL                    (* (reg8 *) Pin9__CTL)
/* Drive Modes */
#define Pin9_DM0                    (* (reg8 *) Pin9__DM0) 
#define Pin9_DM1                    (* (reg8 *) Pin9__DM1)
#define Pin9_DM2                    (* (reg8 *) Pin9__DM2) 
/* Input Buffer Disable Override */
#define Pin9_INP_DIS                (* (reg8 *) Pin9__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin9_LCD_COM_SEG            (* (reg8 *) Pin9__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin9_LCD_EN                 (* (reg8 *) Pin9__LCD_EN)
/* Slew Rate Control */
#define Pin9_SLW                    (* (reg8 *) Pin9__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin9_PRTDSI__CAPS_SEL       (* (reg8 *) Pin9__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin9_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin9__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin9_PRTDSI__OE_SEL0        (* (reg8 *) Pin9__PRTDSI__OE_SEL0) 
#define Pin9_PRTDSI__OE_SEL1        (* (reg8 *) Pin9__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin9_PRTDSI__OUT_SEL0       (* (reg8 *) Pin9__PRTDSI__OUT_SEL0) 
#define Pin9_PRTDSI__OUT_SEL1       (* (reg8 *) Pin9__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin9_PRTDSI__SYNC_OUT       (* (reg8 *) Pin9__PRTDSI__SYNC_OUT) 


#if defined(Pin9__INTSTAT)  /* Interrupt Registers */

    #define Pin9_INTSTAT                (* (reg8 *) Pin9__INTSTAT)
    #define Pin9_SNAP                   (* (reg8 *) Pin9__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin9_H */


/* [] END OF FILE */
