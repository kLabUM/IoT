/*******************************************************************************
* File Name: Pin6.h  
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

#if !defined(CY_PINS_Pin6_H) /* Pins Pin6_H */
#define CY_PINS_Pin6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin6_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin6__PORT == 15 && ((Pin6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin6_Write(uint8 value) ;
void    Pin6_SetDriveMode(uint8 mode) ;
uint8   Pin6_ReadDataReg(void) ;
uint8   Pin6_Read(void) ;
uint8   Pin6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin6_DM_RES_UP          PIN_DM_RES_UP
#define Pin6_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin6_DM_OD_LO           PIN_DM_OD_LO
#define Pin6_DM_OD_HI           PIN_DM_OD_HI
#define Pin6_DM_STRONG          PIN_DM_STRONG
#define Pin6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin6_MASK               Pin6__MASK
#define Pin6_SHIFT              Pin6__SHIFT
#define Pin6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin6_PS                     (* (reg8 *) Pin6__PS)
/* Data Register */
#define Pin6_DR                     (* (reg8 *) Pin6__DR)
/* Port Number */
#define Pin6_PRT_NUM                (* (reg8 *) Pin6__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin6_AG                     (* (reg8 *) Pin6__AG)                       
/* Analog MUX bux enable */
#define Pin6_AMUX                   (* (reg8 *) Pin6__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin6_BIE                    (* (reg8 *) Pin6__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin6_BIT_MASK               (* (reg8 *) Pin6__BIT_MASK)
/* Bypass Enable */
#define Pin6_BYP                    (* (reg8 *) Pin6__BYP)
/* Port wide control signals */                                                   
#define Pin6_CTL                    (* (reg8 *) Pin6__CTL)
/* Drive Modes */
#define Pin6_DM0                    (* (reg8 *) Pin6__DM0) 
#define Pin6_DM1                    (* (reg8 *) Pin6__DM1)
#define Pin6_DM2                    (* (reg8 *) Pin6__DM2) 
/* Input Buffer Disable Override */
#define Pin6_INP_DIS                (* (reg8 *) Pin6__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin6_LCD_COM_SEG            (* (reg8 *) Pin6__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin6_LCD_EN                 (* (reg8 *) Pin6__LCD_EN)
/* Slew Rate Control */
#define Pin6_SLW                    (* (reg8 *) Pin6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin6_PRTDSI__CAPS_SEL       (* (reg8 *) Pin6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin6_PRTDSI__OE_SEL0        (* (reg8 *) Pin6__PRTDSI__OE_SEL0) 
#define Pin6_PRTDSI__OE_SEL1        (* (reg8 *) Pin6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin6_PRTDSI__OUT_SEL0       (* (reg8 *) Pin6__PRTDSI__OUT_SEL0) 
#define Pin6_PRTDSI__OUT_SEL1       (* (reg8 *) Pin6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin6_PRTDSI__SYNC_OUT       (* (reg8 *) Pin6__PRTDSI__SYNC_OUT) 


#if defined(Pin6__INTSTAT)  /* Interrupt Registers */

    #define Pin6_INTSTAT                (* (reg8 *) Pin6__INTSTAT)
    #define Pin6_SNAP                   (* (reg8 *) Pin6__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin6_H */


/* [] END OF FILE */
