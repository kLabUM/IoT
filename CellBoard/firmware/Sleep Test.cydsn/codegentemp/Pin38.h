/*******************************************************************************
* File Name: Pin38.h  
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

#if !defined(CY_PINS_Pin38_H) /* Pins Pin38_H */
#define CY_PINS_Pin38_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin38_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin38__PORT == 15 && ((Pin38__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin38_Write(uint8 value) ;
void    Pin38_SetDriveMode(uint8 mode) ;
uint8   Pin38_ReadDataReg(void) ;
uint8   Pin38_Read(void) ;
uint8   Pin38_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin38_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin38_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin38_DM_RES_UP          PIN_DM_RES_UP
#define Pin38_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin38_DM_OD_LO           PIN_DM_OD_LO
#define Pin38_DM_OD_HI           PIN_DM_OD_HI
#define Pin38_DM_STRONG          PIN_DM_STRONG
#define Pin38_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin38_MASK               Pin38__MASK
#define Pin38_SHIFT              Pin38__SHIFT
#define Pin38_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin38_PS                     (* (reg8 *) Pin38__PS)
/* Data Register */
#define Pin38_DR                     (* (reg8 *) Pin38__DR)
/* Port Number */
#define Pin38_PRT_NUM                (* (reg8 *) Pin38__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin38_AG                     (* (reg8 *) Pin38__AG)                       
/* Analog MUX bux enable */
#define Pin38_AMUX                   (* (reg8 *) Pin38__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin38_BIE                    (* (reg8 *) Pin38__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin38_BIT_MASK               (* (reg8 *) Pin38__BIT_MASK)
/* Bypass Enable */
#define Pin38_BYP                    (* (reg8 *) Pin38__BYP)
/* Port wide control signals */                                                   
#define Pin38_CTL                    (* (reg8 *) Pin38__CTL)
/* Drive Modes */
#define Pin38_DM0                    (* (reg8 *) Pin38__DM0) 
#define Pin38_DM1                    (* (reg8 *) Pin38__DM1)
#define Pin38_DM2                    (* (reg8 *) Pin38__DM2) 
/* Input Buffer Disable Override */
#define Pin38_INP_DIS                (* (reg8 *) Pin38__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin38_LCD_COM_SEG            (* (reg8 *) Pin38__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin38_LCD_EN                 (* (reg8 *) Pin38__LCD_EN)
/* Slew Rate Control */
#define Pin38_SLW                    (* (reg8 *) Pin38__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin38_PRTDSI__CAPS_SEL       (* (reg8 *) Pin38__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin38_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin38__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin38_PRTDSI__OE_SEL0        (* (reg8 *) Pin38__PRTDSI__OE_SEL0) 
#define Pin38_PRTDSI__OE_SEL1        (* (reg8 *) Pin38__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin38_PRTDSI__OUT_SEL0       (* (reg8 *) Pin38__PRTDSI__OUT_SEL0) 
#define Pin38_PRTDSI__OUT_SEL1       (* (reg8 *) Pin38__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin38_PRTDSI__SYNC_OUT       (* (reg8 *) Pin38__PRTDSI__SYNC_OUT) 


#if defined(Pin38__INTSTAT)  /* Interrupt Registers */

    #define Pin38_INTSTAT                (* (reg8 *) Pin38__INTSTAT)
    #define Pin38_SNAP                   (* (reg8 *) Pin38__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin38_H */


/* [] END OF FILE */
