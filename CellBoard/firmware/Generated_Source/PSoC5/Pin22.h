/*******************************************************************************
* File Name: Pin22.h  
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

#if !defined(CY_PINS_Pin22_H) /* Pins Pin22_H */
#define CY_PINS_Pin22_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin22_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin22__PORT == 15 && ((Pin22__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin22_Write(uint8 value) ;
void    Pin22_SetDriveMode(uint8 mode) ;
uint8   Pin22_ReadDataReg(void) ;
uint8   Pin22_Read(void) ;
uint8   Pin22_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin22_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin22_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin22_DM_RES_UP          PIN_DM_RES_UP
#define Pin22_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin22_DM_OD_LO           PIN_DM_OD_LO
#define Pin22_DM_OD_HI           PIN_DM_OD_HI
#define Pin22_DM_STRONG          PIN_DM_STRONG
#define Pin22_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin22_MASK               Pin22__MASK
#define Pin22_SHIFT              Pin22__SHIFT
#define Pin22_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin22_PS                     (* (reg8 *) Pin22__PS)
/* Data Register */
#define Pin22_DR                     (* (reg8 *) Pin22__DR)
/* Port Number */
#define Pin22_PRT_NUM                (* (reg8 *) Pin22__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin22_AG                     (* (reg8 *) Pin22__AG)                       
/* Analog MUX bux enable */
#define Pin22_AMUX                   (* (reg8 *) Pin22__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin22_BIE                    (* (reg8 *) Pin22__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin22_BIT_MASK               (* (reg8 *) Pin22__BIT_MASK)
/* Bypass Enable */
#define Pin22_BYP                    (* (reg8 *) Pin22__BYP)
/* Port wide control signals */                                                   
#define Pin22_CTL                    (* (reg8 *) Pin22__CTL)
/* Drive Modes */
#define Pin22_DM0                    (* (reg8 *) Pin22__DM0) 
#define Pin22_DM1                    (* (reg8 *) Pin22__DM1)
#define Pin22_DM2                    (* (reg8 *) Pin22__DM2) 
/* Input Buffer Disable Override */
#define Pin22_INP_DIS                (* (reg8 *) Pin22__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin22_LCD_COM_SEG            (* (reg8 *) Pin22__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin22_LCD_EN                 (* (reg8 *) Pin22__LCD_EN)
/* Slew Rate Control */
#define Pin22_SLW                    (* (reg8 *) Pin22__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin22_PRTDSI__CAPS_SEL       (* (reg8 *) Pin22__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin22_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin22__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin22_PRTDSI__OE_SEL0        (* (reg8 *) Pin22__PRTDSI__OE_SEL0) 
#define Pin22_PRTDSI__OE_SEL1        (* (reg8 *) Pin22__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin22_PRTDSI__OUT_SEL0       (* (reg8 *) Pin22__PRTDSI__OUT_SEL0) 
#define Pin22_PRTDSI__OUT_SEL1       (* (reg8 *) Pin22__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin22_PRTDSI__SYNC_OUT       (* (reg8 *) Pin22__PRTDSI__SYNC_OUT) 


#if defined(Pin22__INTSTAT)  /* Interrupt Registers */

    #define Pin22_INTSTAT                (* (reg8 *) Pin22__INTSTAT)
    #define Pin22_SNAP                   (* (reg8 *) Pin22__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin22_H */


/* [] END OF FILE */
