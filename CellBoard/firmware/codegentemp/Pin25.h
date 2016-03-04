/*******************************************************************************
* File Name: Pin25.h  
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

#if !defined(CY_PINS_Pin25_H) /* Pins Pin25_H */
#define CY_PINS_Pin25_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin25_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin25__PORT == 15 && ((Pin25__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin25_Write(uint8 value) ;
void    Pin25_SetDriveMode(uint8 mode) ;
uint8   Pin25_ReadDataReg(void) ;
uint8   Pin25_Read(void) ;
uint8   Pin25_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin25_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin25_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin25_DM_RES_UP          PIN_DM_RES_UP
#define Pin25_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin25_DM_OD_LO           PIN_DM_OD_LO
#define Pin25_DM_OD_HI           PIN_DM_OD_HI
#define Pin25_DM_STRONG          PIN_DM_STRONG
#define Pin25_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin25_MASK               Pin25__MASK
#define Pin25_SHIFT              Pin25__SHIFT
#define Pin25_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin25_PS                     (* (reg8 *) Pin25__PS)
/* Data Register */
#define Pin25_DR                     (* (reg8 *) Pin25__DR)
/* Port Number */
#define Pin25_PRT_NUM                (* (reg8 *) Pin25__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin25_AG                     (* (reg8 *) Pin25__AG)                       
/* Analog MUX bux enable */
#define Pin25_AMUX                   (* (reg8 *) Pin25__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin25_BIE                    (* (reg8 *) Pin25__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin25_BIT_MASK               (* (reg8 *) Pin25__BIT_MASK)
/* Bypass Enable */
#define Pin25_BYP                    (* (reg8 *) Pin25__BYP)
/* Port wide control signals */                                                   
#define Pin25_CTL                    (* (reg8 *) Pin25__CTL)
/* Drive Modes */
#define Pin25_DM0                    (* (reg8 *) Pin25__DM0) 
#define Pin25_DM1                    (* (reg8 *) Pin25__DM1)
#define Pin25_DM2                    (* (reg8 *) Pin25__DM2) 
/* Input Buffer Disable Override */
#define Pin25_INP_DIS                (* (reg8 *) Pin25__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin25_LCD_COM_SEG            (* (reg8 *) Pin25__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin25_LCD_EN                 (* (reg8 *) Pin25__LCD_EN)
/* Slew Rate Control */
#define Pin25_SLW                    (* (reg8 *) Pin25__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin25_PRTDSI__CAPS_SEL       (* (reg8 *) Pin25__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin25_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin25__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin25_PRTDSI__OE_SEL0        (* (reg8 *) Pin25__PRTDSI__OE_SEL0) 
#define Pin25_PRTDSI__OE_SEL1        (* (reg8 *) Pin25__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin25_PRTDSI__OUT_SEL0       (* (reg8 *) Pin25__PRTDSI__OUT_SEL0) 
#define Pin25_PRTDSI__OUT_SEL1       (* (reg8 *) Pin25__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin25_PRTDSI__SYNC_OUT       (* (reg8 *) Pin25__PRTDSI__SYNC_OUT) 


#if defined(Pin25__INTSTAT)  /* Interrupt Registers */

    #define Pin25_INTSTAT                (* (reg8 *) Pin25__INTSTAT)
    #define Pin25_SNAP                   (* (reg8 *) Pin25__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin25_H */


/* [] END OF FILE */
