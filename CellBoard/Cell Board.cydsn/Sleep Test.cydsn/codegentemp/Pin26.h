/*******************************************************************************
* File Name: Pin26.h  
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

#if !defined(CY_PINS_Pin26_H) /* Pins Pin26_H */
#define CY_PINS_Pin26_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin26_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin26__PORT == 15 && ((Pin26__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin26_Write(uint8 value) ;
void    Pin26_SetDriveMode(uint8 mode) ;
uint8   Pin26_ReadDataReg(void) ;
uint8   Pin26_Read(void) ;
uint8   Pin26_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin26_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin26_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin26_DM_RES_UP          PIN_DM_RES_UP
#define Pin26_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin26_DM_OD_LO           PIN_DM_OD_LO
#define Pin26_DM_OD_HI           PIN_DM_OD_HI
#define Pin26_DM_STRONG          PIN_DM_STRONG
#define Pin26_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin26_MASK               Pin26__MASK
#define Pin26_SHIFT              Pin26__SHIFT
#define Pin26_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin26_PS                     (* (reg8 *) Pin26__PS)
/* Data Register */
#define Pin26_DR                     (* (reg8 *) Pin26__DR)
/* Port Number */
#define Pin26_PRT_NUM                (* (reg8 *) Pin26__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin26_AG                     (* (reg8 *) Pin26__AG)                       
/* Analog MUX bux enable */
#define Pin26_AMUX                   (* (reg8 *) Pin26__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin26_BIE                    (* (reg8 *) Pin26__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin26_BIT_MASK               (* (reg8 *) Pin26__BIT_MASK)
/* Bypass Enable */
#define Pin26_BYP                    (* (reg8 *) Pin26__BYP)
/* Port wide control signals */                                                   
#define Pin26_CTL                    (* (reg8 *) Pin26__CTL)
/* Drive Modes */
#define Pin26_DM0                    (* (reg8 *) Pin26__DM0) 
#define Pin26_DM1                    (* (reg8 *) Pin26__DM1)
#define Pin26_DM2                    (* (reg8 *) Pin26__DM2) 
/* Input Buffer Disable Override */
#define Pin26_INP_DIS                (* (reg8 *) Pin26__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin26_LCD_COM_SEG            (* (reg8 *) Pin26__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin26_LCD_EN                 (* (reg8 *) Pin26__LCD_EN)
/* Slew Rate Control */
#define Pin26_SLW                    (* (reg8 *) Pin26__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin26_PRTDSI__CAPS_SEL       (* (reg8 *) Pin26__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin26_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin26__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin26_PRTDSI__OE_SEL0        (* (reg8 *) Pin26__PRTDSI__OE_SEL0) 
#define Pin26_PRTDSI__OE_SEL1        (* (reg8 *) Pin26__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin26_PRTDSI__OUT_SEL0       (* (reg8 *) Pin26__PRTDSI__OUT_SEL0) 
#define Pin26_PRTDSI__OUT_SEL1       (* (reg8 *) Pin26__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin26_PRTDSI__SYNC_OUT       (* (reg8 *) Pin26__PRTDSI__SYNC_OUT) 


#if defined(Pin26__INTSTAT)  /* Interrupt Registers */

    #define Pin26_INTSTAT                (* (reg8 *) Pin26__INTSTAT)
    #define Pin26_SNAP                   (* (reg8 *) Pin26__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin26_H */


/* [] END OF FILE */
