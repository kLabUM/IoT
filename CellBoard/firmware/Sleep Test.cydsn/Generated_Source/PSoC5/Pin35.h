/*******************************************************************************
* File Name: Pin35.h  
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

#if !defined(CY_PINS_Pin35_H) /* Pins Pin35_H */
#define CY_PINS_Pin35_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin35_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin35__PORT == 15 && ((Pin35__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin35_Write(uint8 value) ;
void    Pin35_SetDriveMode(uint8 mode) ;
uint8   Pin35_ReadDataReg(void) ;
uint8   Pin35_Read(void) ;
uint8   Pin35_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin35_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin35_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin35_DM_RES_UP          PIN_DM_RES_UP
#define Pin35_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin35_DM_OD_LO           PIN_DM_OD_LO
#define Pin35_DM_OD_HI           PIN_DM_OD_HI
#define Pin35_DM_STRONG          PIN_DM_STRONG
#define Pin35_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin35_MASK               Pin35__MASK
#define Pin35_SHIFT              Pin35__SHIFT
#define Pin35_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin35_PS                     (* (reg8 *) Pin35__PS)
/* Data Register */
#define Pin35_DR                     (* (reg8 *) Pin35__DR)
/* Port Number */
#define Pin35_PRT_NUM                (* (reg8 *) Pin35__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin35_AG                     (* (reg8 *) Pin35__AG)                       
/* Analog MUX bux enable */
#define Pin35_AMUX                   (* (reg8 *) Pin35__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin35_BIE                    (* (reg8 *) Pin35__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin35_BIT_MASK               (* (reg8 *) Pin35__BIT_MASK)
/* Bypass Enable */
#define Pin35_BYP                    (* (reg8 *) Pin35__BYP)
/* Port wide control signals */                                                   
#define Pin35_CTL                    (* (reg8 *) Pin35__CTL)
/* Drive Modes */
#define Pin35_DM0                    (* (reg8 *) Pin35__DM0) 
#define Pin35_DM1                    (* (reg8 *) Pin35__DM1)
#define Pin35_DM2                    (* (reg8 *) Pin35__DM2) 
/* Input Buffer Disable Override */
#define Pin35_INP_DIS                (* (reg8 *) Pin35__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin35_LCD_COM_SEG            (* (reg8 *) Pin35__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin35_LCD_EN                 (* (reg8 *) Pin35__LCD_EN)
/* Slew Rate Control */
#define Pin35_SLW                    (* (reg8 *) Pin35__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin35_PRTDSI__CAPS_SEL       (* (reg8 *) Pin35__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin35_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin35__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin35_PRTDSI__OE_SEL0        (* (reg8 *) Pin35__PRTDSI__OE_SEL0) 
#define Pin35_PRTDSI__OE_SEL1        (* (reg8 *) Pin35__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin35_PRTDSI__OUT_SEL0       (* (reg8 *) Pin35__PRTDSI__OUT_SEL0) 
#define Pin35_PRTDSI__OUT_SEL1       (* (reg8 *) Pin35__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin35_PRTDSI__SYNC_OUT       (* (reg8 *) Pin35__PRTDSI__SYNC_OUT) 


#if defined(Pin35__INTSTAT)  /* Interrupt Registers */

    #define Pin35_INTSTAT                (* (reg8 *) Pin35__INTSTAT)
    #define Pin35_SNAP                   (* (reg8 *) Pin35__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin35_H */


/* [] END OF FILE */
