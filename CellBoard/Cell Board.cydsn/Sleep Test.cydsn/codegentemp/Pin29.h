/*******************************************************************************
* File Name: Pin29.h  
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

#if !defined(CY_PINS_Pin29_H) /* Pins Pin29_H */
#define CY_PINS_Pin29_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin29_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin29__PORT == 15 && ((Pin29__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin29_Write(uint8 value) ;
void    Pin29_SetDriveMode(uint8 mode) ;
uint8   Pin29_ReadDataReg(void) ;
uint8   Pin29_Read(void) ;
uint8   Pin29_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin29_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin29_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin29_DM_RES_UP          PIN_DM_RES_UP
#define Pin29_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin29_DM_OD_LO           PIN_DM_OD_LO
#define Pin29_DM_OD_HI           PIN_DM_OD_HI
#define Pin29_DM_STRONG          PIN_DM_STRONG
#define Pin29_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin29_MASK               Pin29__MASK
#define Pin29_SHIFT              Pin29__SHIFT
#define Pin29_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin29_PS                     (* (reg8 *) Pin29__PS)
/* Data Register */
#define Pin29_DR                     (* (reg8 *) Pin29__DR)
/* Port Number */
#define Pin29_PRT_NUM                (* (reg8 *) Pin29__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin29_AG                     (* (reg8 *) Pin29__AG)                       
/* Analog MUX bux enable */
#define Pin29_AMUX                   (* (reg8 *) Pin29__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin29_BIE                    (* (reg8 *) Pin29__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin29_BIT_MASK               (* (reg8 *) Pin29__BIT_MASK)
/* Bypass Enable */
#define Pin29_BYP                    (* (reg8 *) Pin29__BYP)
/* Port wide control signals */                                                   
#define Pin29_CTL                    (* (reg8 *) Pin29__CTL)
/* Drive Modes */
#define Pin29_DM0                    (* (reg8 *) Pin29__DM0) 
#define Pin29_DM1                    (* (reg8 *) Pin29__DM1)
#define Pin29_DM2                    (* (reg8 *) Pin29__DM2) 
/* Input Buffer Disable Override */
#define Pin29_INP_DIS                (* (reg8 *) Pin29__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin29_LCD_COM_SEG            (* (reg8 *) Pin29__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin29_LCD_EN                 (* (reg8 *) Pin29__LCD_EN)
/* Slew Rate Control */
#define Pin29_SLW                    (* (reg8 *) Pin29__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin29_PRTDSI__CAPS_SEL       (* (reg8 *) Pin29__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin29_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin29__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin29_PRTDSI__OE_SEL0        (* (reg8 *) Pin29__PRTDSI__OE_SEL0) 
#define Pin29_PRTDSI__OE_SEL1        (* (reg8 *) Pin29__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin29_PRTDSI__OUT_SEL0       (* (reg8 *) Pin29__PRTDSI__OUT_SEL0) 
#define Pin29_PRTDSI__OUT_SEL1       (* (reg8 *) Pin29__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin29_PRTDSI__SYNC_OUT       (* (reg8 *) Pin29__PRTDSI__SYNC_OUT) 


#if defined(Pin29__INTSTAT)  /* Interrupt Registers */

    #define Pin29_INTSTAT                (* (reg8 *) Pin29__INTSTAT)
    #define Pin29_SNAP                   (* (reg8 *) Pin29__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin29_H */


/* [] END OF FILE */
