/*******************************************************************************
* File Name: Pin19.h  
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

#if !defined(CY_PINS_Pin19_H) /* Pins Pin19_H */
#define CY_PINS_Pin19_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin19_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin19__PORT == 15 && ((Pin19__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin19_Write(uint8 value) ;
void    Pin19_SetDriveMode(uint8 mode) ;
uint8   Pin19_ReadDataReg(void) ;
uint8   Pin19_Read(void) ;
uint8   Pin19_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin19_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin19_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin19_DM_RES_UP          PIN_DM_RES_UP
#define Pin19_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin19_DM_OD_LO           PIN_DM_OD_LO
#define Pin19_DM_OD_HI           PIN_DM_OD_HI
#define Pin19_DM_STRONG          PIN_DM_STRONG
#define Pin19_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin19_MASK               Pin19__MASK
#define Pin19_SHIFT              Pin19__SHIFT
#define Pin19_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin19_PS                     (* (reg8 *) Pin19__PS)
/* Data Register */
#define Pin19_DR                     (* (reg8 *) Pin19__DR)
/* Port Number */
#define Pin19_PRT_NUM                (* (reg8 *) Pin19__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin19_AG                     (* (reg8 *) Pin19__AG)                       
/* Analog MUX bux enable */
#define Pin19_AMUX                   (* (reg8 *) Pin19__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin19_BIE                    (* (reg8 *) Pin19__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin19_BIT_MASK               (* (reg8 *) Pin19__BIT_MASK)
/* Bypass Enable */
#define Pin19_BYP                    (* (reg8 *) Pin19__BYP)
/* Port wide control signals */                                                   
#define Pin19_CTL                    (* (reg8 *) Pin19__CTL)
/* Drive Modes */
#define Pin19_DM0                    (* (reg8 *) Pin19__DM0) 
#define Pin19_DM1                    (* (reg8 *) Pin19__DM1)
#define Pin19_DM2                    (* (reg8 *) Pin19__DM2) 
/* Input Buffer Disable Override */
#define Pin19_INP_DIS                (* (reg8 *) Pin19__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin19_LCD_COM_SEG            (* (reg8 *) Pin19__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin19_LCD_EN                 (* (reg8 *) Pin19__LCD_EN)
/* Slew Rate Control */
#define Pin19_SLW                    (* (reg8 *) Pin19__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin19_PRTDSI__CAPS_SEL       (* (reg8 *) Pin19__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin19_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin19__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin19_PRTDSI__OE_SEL0        (* (reg8 *) Pin19__PRTDSI__OE_SEL0) 
#define Pin19_PRTDSI__OE_SEL1        (* (reg8 *) Pin19__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin19_PRTDSI__OUT_SEL0       (* (reg8 *) Pin19__PRTDSI__OUT_SEL0) 
#define Pin19_PRTDSI__OUT_SEL1       (* (reg8 *) Pin19__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin19_PRTDSI__SYNC_OUT       (* (reg8 *) Pin19__PRTDSI__SYNC_OUT) 


#if defined(Pin19__INTSTAT)  /* Interrupt Registers */

    #define Pin19_INTSTAT                (* (reg8 *) Pin19__INTSTAT)
    #define Pin19_SNAP                   (* (reg8 *) Pin19__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin19_H */


/* [] END OF FILE */
