/*******************************************************************************
* File Name: Pin27.h  
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

#if !defined(CY_PINS_Pin27_H) /* Pins Pin27_H */
#define CY_PINS_Pin27_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin27_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin27__PORT == 15 && ((Pin27__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin27_Write(uint8 value) ;
void    Pin27_SetDriveMode(uint8 mode) ;
uint8   Pin27_ReadDataReg(void) ;
uint8   Pin27_Read(void) ;
uint8   Pin27_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin27_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin27_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin27_DM_RES_UP          PIN_DM_RES_UP
#define Pin27_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin27_DM_OD_LO           PIN_DM_OD_LO
#define Pin27_DM_OD_HI           PIN_DM_OD_HI
#define Pin27_DM_STRONG          PIN_DM_STRONG
#define Pin27_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin27_MASK               Pin27__MASK
#define Pin27_SHIFT              Pin27__SHIFT
#define Pin27_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin27_PS                     (* (reg8 *) Pin27__PS)
/* Data Register */
#define Pin27_DR                     (* (reg8 *) Pin27__DR)
/* Port Number */
#define Pin27_PRT_NUM                (* (reg8 *) Pin27__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin27_AG                     (* (reg8 *) Pin27__AG)                       
/* Analog MUX bux enable */
#define Pin27_AMUX                   (* (reg8 *) Pin27__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin27_BIE                    (* (reg8 *) Pin27__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin27_BIT_MASK               (* (reg8 *) Pin27__BIT_MASK)
/* Bypass Enable */
#define Pin27_BYP                    (* (reg8 *) Pin27__BYP)
/* Port wide control signals */                                                   
#define Pin27_CTL                    (* (reg8 *) Pin27__CTL)
/* Drive Modes */
#define Pin27_DM0                    (* (reg8 *) Pin27__DM0) 
#define Pin27_DM1                    (* (reg8 *) Pin27__DM1)
#define Pin27_DM2                    (* (reg8 *) Pin27__DM2) 
/* Input Buffer Disable Override */
#define Pin27_INP_DIS                (* (reg8 *) Pin27__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin27_LCD_COM_SEG            (* (reg8 *) Pin27__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin27_LCD_EN                 (* (reg8 *) Pin27__LCD_EN)
/* Slew Rate Control */
#define Pin27_SLW                    (* (reg8 *) Pin27__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin27_PRTDSI__CAPS_SEL       (* (reg8 *) Pin27__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin27_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin27__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin27_PRTDSI__OE_SEL0        (* (reg8 *) Pin27__PRTDSI__OE_SEL0) 
#define Pin27_PRTDSI__OE_SEL1        (* (reg8 *) Pin27__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin27_PRTDSI__OUT_SEL0       (* (reg8 *) Pin27__PRTDSI__OUT_SEL0) 
#define Pin27_PRTDSI__OUT_SEL1       (* (reg8 *) Pin27__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin27_PRTDSI__SYNC_OUT       (* (reg8 *) Pin27__PRTDSI__SYNC_OUT) 


#if defined(Pin27__INTSTAT)  /* Interrupt Registers */

    #define Pin27_INTSTAT                (* (reg8 *) Pin27__INTSTAT)
    #define Pin27_SNAP                   (* (reg8 *) Pin27__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin27_H */


/* [] END OF FILE */
