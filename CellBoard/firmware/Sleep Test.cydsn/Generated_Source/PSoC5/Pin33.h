/*******************************************************************************
* File Name: Pin33.h  
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

#if !defined(CY_PINS_Pin33_H) /* Pins Pin33_H */
#define CY_PINS_Pin33_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin33_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin33__PORT == 15 && ((Pin33__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin33_Write(uint8 value) ;
void    Pin33_SetDriveMode(uint8 mode) ;
uint8   Pin33_ReadDataReg(void) ;
uint8   Pin33_Read(void) ;
uint8   Pin33_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin33_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin33_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin33_DM_RES_UP          PIN_DM_RES_UP
#define Pin33_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin33_DM_OD_LO           PIN_DM_OD_LO
#define Pin33_DM_OD_HI           PIN_DM_OD_HI
#define Pin33_DM_STRONG          PIN_DM_STRONG
#define Pin33_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin33_MASK               Pin33__MASK
#define Pin33_SHIFT              Pin33__SHIFT
#define Pin33_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin33_PS                     (* (reg8 *) Pin33__PS)
/* Data Register */
#define Pin33_DR                     (* (reg8 *) Pin33__DR)
/* Port Number */
#define Pin33_PRT_NUM                (* (reg8 *) Pin33__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin33_AG                     (* (reg8 *) Pin33__AG)                       
/* Analog MUX bux enable */
#define Pin33_AMUX                   (* (reg8 *) Pin33__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin33_BIE                    (* (reg8 *) Pin33__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin33_BIT_MASK               (* (reg8 *) Pin33__BIT_MASK)
/* Bypass Enable */
#define Pin33_BYP                    (* (reg8 *) Pin33__BYP)
/* Port wide control signals */                                                   
#define Pin33_CTL                    (* (reg8 *) Pin33__CTL)
/* Drive Modes */
#define Pin33_DM0                    (* (reg8 *) Pin33__DM0) 
#define Pin33_DM1                    (* (reg8 *) Pin33__DM1)
#define Pin33_DM2                    (* (reg8 *) Pin33__DM2) 
/* Input Buffer Disable Override */
#define Pin33_INP_DIS                (* (reg8 *) Pin33__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin33_LCD_COM_SEG            (* (reg8 *) Pin33__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin33_LCD_EN                 (* (reg8 *) Pin33__LCD_EN)
/* Slew Rate Control */
#define Pin33_SLW                    (* (reg8 *) Pin33__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin33_PRTDSI__CAPS_SEL       (* (reg8 *) Pin33__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin33_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin33__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin33_PRTDSI__OE_SEL0        (* (reg8 *) Pin33__PRTDSI__OE_SEL0) 
#define Pin33_PRTDSI__OE_SEL1        (* (reg8 *) Pin33__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin33_PRTDSI__OUT_SEL0       (* (reg8 *) Pin33__PRTDSI__OUT_SEL0) 
#define Pin33_PRTDSI__OUT_SEL1       (* (reg8 *) Pin33__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin33_PRTDSI__SYNC_OUT       (* (reg8 *) Pin33__PRTDSI__SYNC_OUT) 


#if defined(Pin33__INTSTAT)  /* Interrupt Registers */

    #define Pin33_INTSTAT                (* (reg8 *) Pin33__INTSTAT)
    #define Pin33_SNAP                   (* (reg8 *) Pin33__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin33_H */


/* [] END OF FILE */
