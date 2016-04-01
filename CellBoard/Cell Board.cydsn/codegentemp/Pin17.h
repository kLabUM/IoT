/*******************************************************************************
* File Name: Pin17.h  
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

#if !defined(CY_PINS_Pin17_H) /* Pins Pin17_H */
#define CY_PINS_Pin17_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin17_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin17__PORT == 15 && ((Pin17__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin17_Write(uint8 value) ;
void    Pin17_SetDriveMode(uint8 mode) ;
uint8   Pin17_ReadDataReg(void) ;
uint8   Pin17_Read(void) ;
uint8   Pin17_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin17_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin17_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin17_DM_RES_UP          PIN_DM_RES_UP
#define Pin17_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin17_DM_OD_LO           PIN_DM_OD_LO
#define Pin17_DM_OD_HI           PIN_DM_OD_HI
#define Pin17_DM_STRONG          PIN_DM_STRONG
#define Pin17_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin17_MASK               Pin17__MASK
#define Pin17_SHIFT              Pin17__SHIFT
#define Pin17_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin17_PS                     (* (reg8 *) Pin17__PS)
/* Data Register */
#define Pin17_DR                     (* (reg8 *) Pin17__DR)
/* Port Number */
#define Pin17_PRT_NUM                (* (reg8 *) Pin17__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin17_AG                     (* (reg8 *) Pin17__AG)                       
/* Analog MUX bux enable */
#define Pin17_AMUX                   (* (reg8 *) Pin17__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin17_BIE                    (* (reg8 *) Pin17__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin17_BIT_MASK               (* (reg8 *) Pin17__BIT_MASK)
/* Bypass Enable */
#define Pin17_BYP                    (* (reg8 *) Pin17__BYP)
/* Port wide control signals */                                                   
#define Pin17_CTL                    (* (reg8 *) Pin17__CTL)
/* Drive Modes */
#define Pin17_DM0                    (* (reg8 *) Pin17__DM0) 
#define Pin17_DM1                    (* (reg8 *) Pin17__DM1)
#define Pin17_DM2                    (* (reg8 *) Pin17__DM2) 
/* Input Buffer Disable Override */
#define Pin17_INP_DIS                (* (reg8 *) Pin17__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin17_LCD_COM_SEG            (* (reg8 *) Pin17__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin17_LCD_EN                 (* (reg8 *) Pin17__LCD_EN)
/* Slew Rate Control */
#define Pin17_SLW                    (* (reg8 *) Pin17__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin17_PRTDSI__CAPS_SEL       (* (reg8 *) Pin17__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin17_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin17__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin17_PRTDSI__OE_SEL0        (* (reg8 *) Pin17__PRTDSI__OE_SEL0) 
#define Pin17_PRTDSI__OE_SEL1        (* (reg8 *) Pin17__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin17_PRTDSI__OUT_SEL0       (* (reg8 *) Pin17__PRTDSI__OUT_SEL0) 
#define Pin17_PRTDSI__OUT_SEL1       (* (reg8 *) Pin17__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin17_PRTDSI__SYNC_OUT       (* (reg8 *) Pin17__PRTDSI__SYNC_OUT) 


#if defined(Pin17__INTSTAT)  /* Interrupt Registers */

    #define Pin17_INTSTAT                (* (reg8 *) Pin17__INTSTAT)
    #define Pin17_SNAP                   (* (reg8 *) Pin17__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin17_H */


/* [] END OF FILE */
