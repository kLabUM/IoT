/*******************************************************************************
* File Name: Pin12.h  
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

#if !defined(CY_PINS_Pin12_H) /* Pins Pin12_H */
#define CY_PINS_Pin12_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin12_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin12__PORT == 15 && ((Pin12__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin12_Write(uint8 value) ;
void    Pin12_SetDriveMode(uint8 mode) ;
uint8   Pin12_ReadDataReg(void) ;
uint8   Pin12_Read(void) ;
uint8   Pin12_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin12_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin12_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin12_DM_RES_UP          PIN_DM_RES_UP
#define Pin12_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin12_DM_OD_LO           PIN_DM_OD_LO
#define Pin12_DM_OD_HI           PIN_DM_OD_HI
#define Pin12_DM_STRONG          PIN_DM_STRONG
#define Pin12_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin12_MASK               Pin12__MASK
#define Pin12_SHIFT              Pin12__SHIFT
#define Pin12_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin12_PS                     (* (reg8 *) Pin12__PS)
/* Data Register */
#define Pin12_DR                     (* (reg8 *) Pin12__DR)
/* Port Number */
#define Pin12_PRT_NUM                (* (reg8 *) Pin12__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin12_AG                     (* (reg8 *) Pin12__AG)                       
/* Analog MUX bux enable */
#define Pin12_AMUX                   (* (reg8 *) Pin12__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin12_BIE                    (* (reg8 *) Pin12__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin12_BIT_MASK               (* (reg8 *) Pin12__BIT_MASK)
/* Bypass Enable */
#define Pin12_BYP                    (* (reg8 *) Pin12__BYP)
/* Port wide control signals */                                                   
#define Pin12_CTL                    (* (reg8 *) Pin12__CTL)
/* Drive Modes */
#define Pin12_DM0                    (* (reg8 *) Pin12__DM0) 
#define Pin12_DM1                    (* (reg8 *) Pin12__DM1)
#define Pin12_DM2                    (* (reg8 *) Pin12__DM2) 
/* Input Buffer Disable Override */
#define Pin12_INP_DIS                (* (reg8 *) Pin12__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin12_LCD_COM_SEG            (* (reg8 *) Pin12__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin12_LCD_EN                 (* (reg8 *) Pin12__LCD_EN)
/* Slew Rate Control */
#define Pin12_SLW                    (* (reg8 *) Pin12__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin12_PRTDSI__CAPS_SEL       (* (reg8 *) Pin12__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin12_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin12__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin12_PRTDSI__OE_SEL0        (* (reg8 *) Pin12__PRTDSI__OE_SEL0) 
#define Pin12_PRTDSI__OE_SEL1        (* (reg8 *) Pin12__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin12_PRTDSI__OUT_SEL0       (* (reg8 *) Pin12__PRTDSI__OUT_SEL0) 
#define Pin12_PRTDSI__OUT_SEL1       (* (reg8 *) Pin12__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin12_PRTDSI__SYNC_OUT       (* (reg8 *) Pin12__PRTDSI__SYNC_OUT) 


#if defined(Pin12__INTSTAT)  /* Interrupt Registers */

    #define Pin12_INTSTAT                (* (reg8 *) Pin12__INTSTAT)
    #define Pin12_SNAP                   (* (reg8 *) Pin12__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin12_H */


/* [] END OF FILE */
