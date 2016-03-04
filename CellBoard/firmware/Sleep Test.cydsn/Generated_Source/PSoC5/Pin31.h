/*******************************************************************************
* File Name: Pin31.h  
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

#if !defined(CY_PINS_Pin31_H) /* Pins Pin31_H */
#define CY_PINS_Pin31_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin31_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin31__PORT == 15 && ((Pin31__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin31_Write(uint8 value) ;
void    Pin31_SetDriveMode(uint8 mode) ;
uint8   Pin31_ReadDataReg(void) ;
uint8   Pin31_Read(void) ;
uint8   Pin31_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin31_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin31_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin31_DM_RES_UP          PIN_DM_RES_UP
#define Pin31_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin31_DM_OD_LO           PIN_DM_OD_LO
#define Pin31_DM_OD_HI           PIN_DM_OD_HI
#define Pin31_DM_STRONG          PIN_DM_STRONG
#define Pin31_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin31_MASK               Pin31__MASK
#define Pin31_SHIFT              Pin31__SHIFT
#define Pin31_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin31_PS                     (* (reg8 *) Pin31__PS)
/* Data Register */
#define Pin31_DR                     (* (reg8 *) Pin31__DR)
/* Port Number */
#define Pin31_PRT_NUM                (* (reg8 *) Pin31__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin31_AG                     (* (reg8 *) Pin31__AG)                       
/* Analog MUX bux enable */
#define Pin31_AMUX                   (* (reg8 *) Pin31__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin31_BIE                    (* (reg8 *) Pin31__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin31_BIT_MASK               (* (reg8 *) Pin31__BIT_MASK)
/* Bypass Enable */
#define Pin31_BYP                    (* (reg8 *) Pin31__BYP)
/* Port wide control signals */                                                   
#define Pin31_CTL                    (* (reg8 *) Pin31__CTL)
/* Drive Modes */
#define Pin31_DM0                    (* (reg8 *) Pin31__DM0) 
#define Pin31_DM1                    (* (reg8 *) Pin31__DM1)
#define Pin31_DM2                    (* (reg8 *) Pin31__DM2) 
/* Input Buffer Disable Override */
#define Pin31_INP_DIS                (* (reg8 *) Pin31__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin31_LCD_COM_SEG            (* (reg8 *) Pin31__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin31_LCD_EN                 (* (reg8 *) Pin31__LCD_EN)
/* Slew Rate Control */
#define Pin31_SLW                    (* (reg8 *) Pin31__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin31_PRTDSI__CAPS_SEL       (* (reg8 *) Pin31__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin31_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin31__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin31_PRTDSI__OE_SEL0        (* (reg8 *) Pin31__PRTDSI__OE_SEL0) 
#define Pin31_PRTDSI__OE_SEL1        (* (reg8 *) Pin31__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin31_PRTDSI__OUT_SEL0       (* (reg8 *) Pin31__PRTDSI__OUT_SEL0) 
#define Pin31_PRTDSI__OUT_SEL1       (* (reg8 *) Pin31__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin31_PRTDSI__SYNC_OUT       (* (reg8 *) Pin31__PRTDSI__SYNC_OUT) 


#if defined(Pin31__INTSTAT)  /* Interrupt Registers */

    #define Pin31_INTSTAT                (* (reg8 *) Pin31__INTSTAT)
    #define Pin31_SNAP                   (* (reg8 *) Pin31__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin31_H */


/* [] END OF FILE */
