/*******************************************************************************
* File Name: Pin24.h  
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

#if !defined(CY_PINS_Pin24_H) /* Pins Pin24_H */
#define CY_PINS_Pin24_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin24_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin24__PORT == 15 && ((Pin24__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin24_Write(uint8 value) ;
void    Pin24_SetDriveMode(uint8 mode) ;
uint8   Pin24_ReadDataReg(void) ;
uint8   Pin24_Read(void) ;
uint8   Pin24_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin24_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin24_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin24_DM_RES_UP          PIN_DM_RES_UP
#define Pin24_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin24_DM_OD_LO           PIN_DM_OD_LO
#define Pin24_DM_OD_HI           PIN_DM_OD_HI
#define Pin24_DM_STRONG          PIN_DM_STRONG
#define Pin24_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin24_MASK               Pin24__MASK
#define Pin24_SHIFT              Pin24__SHIFT
#define Pin24_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin24_PS                     (* (reg8 *) Pin24__PS)
/* Data Register */
#define Pin24_DR                     (* (reg8 *) Pin24__DR)
/* Port Number */
#define Pin24_PRT_NUM                (* (reg8 *) Pin24__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin24_AG                     (* (reg8 *) Pin24__AG)                       
/* Analog MUX bux enable */
#define Pin24_AMUX                   (* (reg8 *) Pin24__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin24_BIE                    (* (reg8 *) Pin24__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin24_BIT_MASK               (* (reg8 *) Pin24__BIT_MASK)
/* Bypass Enable */
#define Pin24_BYP                    (* (reg8 *) Pin24__BYP)
/* Port wide control signals */                                                   
#define Pin24_CTL                    (* (reg8 *) Pin24__CTL)
/* Drive Modes */
#define Pin24_DM0                    (* (reg8 *) Pin24__DM0) 
#define Pin24_DM1                    (* (reg8 *) Pin24__DM1)
#define Pin24_DM2                    (* (reg8 *) Pin24__DM2) 
/* Input Buffer Disable Override */
#define Pin24_INP_DIS                (* (reg8 *) Pin24__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin24_LCD_COM_SEG            (* (reg8 *) Pin24__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin24_LCD_EN                 (* (reg8 *) Pin24__LCD_EN)
/* Slew Rate Control */
#define Pin24_SLW                    (* (reg8 *) Pin24__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin24_PRTDSI__CAPS_SEL       (* (reg8 *) Pin24__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin24_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin24__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin24_PRTDSI__OE_SEL0        (* (reg8 *) Pin24__PRTDSI__OE_SEL0) 
#define Pin24_PRTDSI__OE_SEL1        (* (reg8 *) Pin24__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin24_PRTDSI__OUT_SEL0       (* (reg8 *) Pin24__PRTDSI__OUT_SEL0) 
#define Pin24_PRTDSI__OUT_SEL1       (* (reg8 *) Pin24__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin24_PRTDSI__SYNC_OUT       (* (reg8 *) Pin24__PRTDSI__SYNC_OUT) 


#if defined(Pin24__INTSTAT)  /* Interrupt Registers */

    #define Pin24_INTSTAT                (* (reg8 *) Pin24__INTSTAT)
    #define Pin24_SNAP                   (* (reg8 *) Pin24__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin24_H */


/* [] END OF FILE */
