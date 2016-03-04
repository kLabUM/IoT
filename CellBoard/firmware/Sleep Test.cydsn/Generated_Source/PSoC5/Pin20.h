/*******************************************************************************
* File Name: Pin20.h  
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

#if !defined(CY_PINS_Pin20_H) /* Pins Pin20_H */
#define CY_PINS_Pin20_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin20_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin20__PORT == 15 && ((Pin20__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin20_Write(uint8 value) ;
void    Pin20_SetDriveMode(uint8 mode) ;
uint8   Pin20_ReadDataReg(void) ;
uint8   Pin20_Read(void) ;
uint8   Pin20_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin20_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin20_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin20_DM_RES_UP          PIN_DM_RES_UP
#define Pin20_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin20_DM_OD_LO           PIN_DM_OD_LO
#define Pin20_DM_OD_HI           PIN_DM_OD_HI
#define Pin20_DM_STRONG          PIN_DM_STRONG
#define Pin20_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin20_MASK               Pin20__MASK
#define Pin20_SHIFT              Pin20__SHIFT
#define Pin20_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin20_PS                     (* (reg8 *) Pin20__PS)
/* Data Register */
#define Pin20_DR                     (* (reg8 *) Pin20__DR)
/* Port Number */
#define Pin20_PRT_NUM                (* (reg8 *) Pin20__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin20_AG                     (* (reg8 *) Pin20__AG)                       
/* Analog MUX bux enable */
#define Pin20_AMUX                   (* (reg8 *) Pin20__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin20_BIE                    (* (reg8 *) Pin20__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin20_BIT_MASK               (* (reg8 *) Pin20__BIT_MASK)
/* Bypass Enable */
#define Pin20_BYP                    (* (reg8 *) Pin20__BYP)
/* Port wide control signals */                                                   
#define Pin20_CTL                    (* (reg8 *) Pin20__CTL)
/* Drive Modes */
#define Pin20_DM0                    (* (reg8 *) Pin20__DM0) 
#define Pin20_DM1                    (* (reg8 *) Pin20__DM1)
#define Pin20_DM2                    (* (reg8 *) Pin20__DM2) 
/* Input Buffer Disable Override */
#define Pin20_INP_DIS                (* (reg8 *) Pin20__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin20_LCD_COM_SEG            (* (reg8 *) Pin20__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin20_LCD_EN                 (* (reg8 *) Pin20__LCD_EN)
/* Slew Rate Control */
#define Pin20_SLW                    (* (reg8 *) Pin20__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin20_PRTDSI__CAPS_SEL       (* (reg8 *) Pin20__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin20_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin20__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin20_PRTDSI__OE_SEL0        (* (reg8 *) Pin20__PRTDSI__OE_SEL0) 
#define Pin20_PRTDSI__OE_SEL1        (* (reg8 *) Pin20__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin20_PRTDSI__OUT_SEL0       (* (reg8 *) Pin20__PRTDSI__OUT_SEL0) 
#define Pin20_PRTDSI__OUT_SEL1       (* (reg8 *) Pin20__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin20_PRTDSI__SYNC_OUT       (* (reg8 *) Pin20__PRTDSI__SYNC_OUT) 


#if defined(Pin20__INTSTAT)  /* Interrupt Registers */

    #define Pin20_INTSTAT                (* (reg8 *) Pin20__INTSTAT)
    #define Pin20_SNAP                   (* (reg8 *) Pin20__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin20_H */


/* [] END OF FILE */
