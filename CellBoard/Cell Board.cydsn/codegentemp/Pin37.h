/*******************************************************************************
* File Name: Pin37.h  
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

#if !defined(CY_PINS_Pin37_H) /* Pins Pin37_H */
#define CY_PINS_Pin37_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin37_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin37__PORT == 15 && ((Pin37__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin37_Write(uint8 value) ;
void    Pin37_SetDriveMode(uint8 mode) ;
uint8   Pin37_ReadDataReg(void) ;
uint8   Pin37_Read(void) ;
uint8   Pin37_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin37_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin37_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin37_DM_RES_UP          PIN_DM_RES_UP
#define Pin37_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin37_DM_OD_LO           PIN_DM_OD_LO
#define Pin37_DM_OD_HI           PIN_DM_OD_HI
#define Pin37_DM_STRONG          PIN_DM_STRONG
#define Pin37_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin37_MASK               Pin37__MASK
#define Pin37_SHIFT              Pin37__SHIFT
#define Pin37_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin37_PS                     (* (reg8 *) Pin37__PS)
/* Data Register */
#define Pin37_DR                     (* (reg8 *) Pin37__DR)
/* Port Number */
#define Pin37_PRT_NUM                (* (reg8 *) Pin37__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin37_AG                     (* (reg8 *) Pin37__AG)                       
/* Analog MUX bux enable */
#define Pin37_AMUX                   (* (reg8 *) Pin37__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin37_BIE                    (* (reg8 *) Pin37__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin37_BIT_MASK               (* (reg8 *) Pin37__BIT_MASK)
/* Bypass Enable */
#define Pin37_BYP                    (* (reg8 *) Pin37__BYP)
/* Port wide control signals */                                                   
#define Pin37_CTL                    (* (reg8 *) Pin37__CTL)
/* Drive Modes */
#define Pin37_DM0                    (* (reg8 *) Pin37__DM0) 
#define Pin37_DM1                    (* (reg8 *) Pin37__DM1)
#define Pin37_DM2                    (* (reg8 *) Pin37__DM2) 
/* Input Buffer Disable Override */
#define Pin37_INP_DIS                (* (reg8 *) Pin37__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin37_LCD_COM_SEG            (* (reg8 *) Pin37__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin37_LCD_EN                 (* (reg8 *) Pin37__LCD_EN)
/* Slew Rate Control */
#define Pin37_SLW                    (* (reg8 *) Pin37__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin37_PRTDSI__CAPS_SEL       (* (reg8 *) Pin37__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin37_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin37__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin37_PRTDSI__OE_SEL0        (* (reg8 *) Pin37__PRTDSI__OE_SEL0) 
#define Pin37_PRTDSI__OE_SEL1        (* (reg8 *) Pin37__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin37_PRTDSI__OUT_SEL0       (* (reg8 *) Pin37__PRTDSI__OUT_SEL0) 
#define Pin37_PRTDSI__OUT_SEL1       (* (reg8 *) Pin37__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin37_PRTDSI__SYNC_OUT       (* (reg8 *) Pin37__PRTDSI__SYNC_OUT) 


#if defined(Pin37__INTSTAT)  /* Interrupt Registers */

    #define Pin37_INTSTAT                (* (reg8 *) Pin37__INTSTAT)
    #define Pin37_SNAP                   (* (reg8 *) Pin37__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin37_H */


/* [] END OF FILE */
