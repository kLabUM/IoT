/*******************************************************************************
* File Name: Pin15.h  
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

#if !defined(CY_PINS_Pin15_H) /* Pins Pin15_H */
#define CY_PINS_Pin15_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin15_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin15__PORT == 15 && ((Pin15__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin15_Write(uint8 value) ;
void    Pin15_SetDriveMode(uint8 mode) ;
uint8   Pin15_ReadDataReg(void) ;
uint8   Pin15_Read(void) ;
uint8   Pin15_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin15_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin15_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin15_DM_RES_UP          PIN_DM_RES_UP
#define Pin15_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin15_DM_OD_LO           PIN_DM_OD_LO
#define Pin15_DM_OD_HI           PIN_DM_OD_HI
#define Pin15_DM_STRONG          PIN_DM_STRONG
#define Pin15_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin15_MASK               Pin15__MASK
#define Pin15_SHIFT              Pin15__SHIFT
#define Pin15_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin15_PS                     (* (reg8 *) Pin15__PS)
/* Data Register */
#define Pin15_DR                     (* (reg8 *) Pin15__DR)
/* Port Number */
#define Pin15_PRT_NUM                (* (reg8 *) Pin15__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin15_AG                     (* (reg8 *) Pin15__AG)                       
/* Analog MUX bux enable */
#define Pin15_AMUX                   (* (reg8 *) Pin15__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin15_BIE                    (* (reg8 *) Pin15__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin15_BIT_MASK               (* (reg8 *) Pin15__BIT_MASK)
/* Bypass Enable */
#define Pin15_BYP                    (* (reg8 *) Pin15__BYP)
/* Port wide control signals */                                                   
#define Pin15_CTL                    (* (reg8 *) Pin15__CTL)
/* Drive Modes */
#define Pin15_DM0                    (* (reg8 *) Pin15__DM0) 
#define Pin15_DM1                    (* (reg8 *) Pin15__DM1)
#define Pin15_DM2                    (* (reg8 *) Pin15__DM2) 
/* Input Buffer Disable Override */
#define Pin15_INP_DIS                (* (reg8 *) Pin15__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin15_LCD_COM_SEG            (* (reg8 *) Pin15__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin15_LCD_EN                 (* (reg8 *) Pin15__LCD_EN)
/* Slew Rate Control */
#define Pin15_SLW                    (* (reg8 *) Pin15__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin15_PRTDSI__CAPS_SEL       (* (reg8 *) Pin15__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin15_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin15__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin15_PRTDSI__OE_SEL0        (* (reg8 *) Pin15__PRTDSI__OE_SEL0) 
#define Pin15_PRTDSI__OE_SEL1        (* (reg8 *) Pin15__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin15_PRTDSI__OUT_SEL0       (* (reg8 *) Pin15__PRTDSI__OUT_SEL0) 
#define Pin15_PRTDSI__OUT_SEL1       (* (reg8 *) Pin15__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin15_PRTDSI__SYNC_OUT       (* (reg8 *) Pin15__PRTDSI__SYNC_OUT) 


#if defined(Pin15__INTSTAT)  /* Interrupt Registers */

    #define Pin15_INTSTAT                (* (reg8 *) Pin15__INTSTAT)
    #define Pin15_SNAP                   (* (reg8 *) Pin15__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin15_H */


/* [] END OF FILE */
