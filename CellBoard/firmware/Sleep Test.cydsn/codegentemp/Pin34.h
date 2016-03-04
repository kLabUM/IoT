/*******************************************************************************
* File Name: Pin34.h  
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

#if !defined(CY_PINS_Pin34_H) /* Pins Pin34_H */
#define CY_PINS_Pin34_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin34_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin34__PORT == 15 && ((Pin34__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin34_Write(uint8 value) ;
void    Pin34_SetDriveMode(uint8 mode) ;
uint8   Pin34_ReadDataReg(void) ;
uint8   Pin34_Read(void) ;
uint8   Pin34_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin34_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin34_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin34_DM_RES_UP          PIN_DM_RES_UP
#define Pin34_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin34_DM_OD_LO           PIN_DM_OD_LO
#define Pin34_DM_OD_HI           PIN_DM_OD_HI
#define Pin34_DM_STRONG          PIN_DM_STRONG
#define Pin34_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin34_MASK               Pin34__MASK
#define Pin34_SHIFT              Pin34__SHIFT
#define Pin34_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin34_PS                     (* (reg8 *) Pin34__PS)
/* Data Register */
#define Pin34_DR                     (* (reg8 *) Pin34__DR)
/* Port Number */
#define Pin34_PRT_NUM                (* (reg8 *) Pin34__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin34_AG                     (* (reg8 *) Pin34__AG)                       
/* Analog MUX bux enable */
#define Pin34_AMUX                   (* (reg8 *) Pin34__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin34_BIE                    (* (reg8 *) Pin34__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin34_BIT_MASK               (* (reg8 *) Pin34__BIT_MASK)
/* Bypass Enable */
#define Pin34_BYP                    (* (reg8 *) Pin34__BYP)
/* Port wide control signals */                                                   
#define Pin34_CTL                    (* (reg8 *) Pin34__CTL)
/* Drive Modes */
#define Pin34_DM0                    (* (reg8 *) Pin34__DM0) 
#define Pin34_DM1                    (* (reg8 *) Pin34__DM1)
#define Pin34_DM2                    (* (reg8 *) Pin34__DM2) 
/* Input Buffer Disable Override */
#define Pin34_INP_DIS                (* (reg8 *) Pin34__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin34_LCD_COM_SEG            (* (reg8 *) Pin34__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin34_LCD_EN                 (* (reg8 *) Pin34__LCD_EN)
/* Slew Rate Control */
#define Pin34_SLW                    (* (reg8 *) Pin34__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin34_PRTDSI__CAPS_SEL       (* (reg8 *) Pin34__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin34_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin34__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin34_PRTDSI__OE_SEL0        (* (reg8 *) Pin34__PRTDSI__OE_SEL0) 
#define Pin34_PRTDSI__OE_SEL1        (* (reg8 *) Pin34__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin34_PRTDSI__OUT_SEL0       (* (reg8 *) Pin34__PRTDSI__OUT_SEL0) 
#define Pin34_PRTDSI__OUT_SEL1       (* (reg8 *) Pin34__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin34_PRTDSI__SYNC_OUT       (* (reg8 *) Pin34__PRTDSI__SYNC_OUT) 


#if defined(Pin34__INTSTAT)  /* Interrupt Registers */

    #define Pin34_INTSTAT                (* (reg8 *) Pin34__INTSTAT)
    #define Pin34_SNAP                   (* (reg8 *) Pin34__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin34_H */


/* [] END OF FILE */
