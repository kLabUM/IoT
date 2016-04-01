/*******************************************************************************
* File Name: Pin5.h  
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

#if !defined(CY_PINS_Pin5_H) /* Pins Pin5_H */
#define CY_PINS_Pin5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin5_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin5__PORT == 15 && ((Pin5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin5_Write(uint8 value) ;
void    Pin5_SetDriveMode(uint8 mode) ;
uint8   Pin5_ReadDataReg(void) ;
uint8   Pin5_Read(void) ;
uint8   Pin5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin5_DM_RES_UP          PIN_DM_RES_UP
#define Pin5_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin5_DM_OD_LO           PIN_DM_OD_LO
#define Pin5_DM_OD_HI           PIN_DM_OD_HI
#define Pin5_DM_STRONG          PIN_DM_STRONG
#define Pin5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin5_MASK               Pin5__MASK
#define Pin5_SHIFT              Pin5__SHIFT
#define Pin5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin5_PS                     (* (reg8 *) Pin5__PS)
/* Data Register */
#define Pin5_DR                     (* (reg8 *) Pin5__DR)
/* Port Number */
#define Pin5_PRT_NUM                (* (reg8 *) Pin5__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin5_AG                     (* (reg8 *) Pin5__AG)                       
/* Analog MUX bux enable */
#define Pin5_AMUX                   (* (reg8 *) Pin5__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin5_BIE                    (* (reg8 *) Pin5__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin5_BIT_MASK               (* (reg8 *) Pin5__BIT_MASK)
/* Bypass Enable */
#define Pin5_BYP                    (* (reg8 *) Pin5__BYP)
/* Port wide control signals */                                                   
#define Pin5_CTL                    (* (reg8 *) Pin5__CTL)
/* Drive Modes */
#define Pin5_DM0                    (* (reg8 *) Pin5__DM0) 
#define Pin5_DM1                    (* (reg8 *) Pin5__DM1)
#define Pin5_DM2                    (* (reg8 *) Pin5__DM2) 
/* Input Buffer Disable Override */
#define Pin5_INP_DIS                (* (reg8 *) Pin5__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin5_LCD_COM_SEG            (* (reg8 *) Pin5__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin5_LCD_EN                 (* (reg8 *) Pin5__LCD_EN)
/* Slew Rate Control */
#define Pin5_SLW                    (* (reg8 *) Pin5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin5_PRTDSI__CAPS_SEL       (* (reg8 *) Pin5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin5_PRTDSI__OE_SEL0        (* (reg8 *) Pin5__PRTDSI__OE_SEL0) 
#define Pin5_PRTDSI__OE_SEL1        (* (reg8 *) Pin5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin5_PRTDSI__OUT_SEL0       (* (reg8 *) Pin5__PRTDSI__OUT_SEL0) 
#define Pin5_PRTDSI__OUT_SEL1       (* (reg8 *) Pin5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin5_PRTDSI__SYNC_OUT       (* (reg8 *) Pin5__PRTDSI__SYNC_OUT) 


#if defined(Pin5__INTSTAT)  /* Interrupt Registers */

    #define Pin5_INTSTAT                (* (reg8 *) Pin5__INTSTAT)
    #define Pin5_SNAP                   (* (reg8 *) Pin5__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin5_H */


/* [] END OF FILE */
