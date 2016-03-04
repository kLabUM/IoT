/*******************************************************************************
* File Name: Vbat.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Vbat_H) /* Pins Vbat_H */
#define CY_PINS_Vbat_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vbat_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vbat__PORT == 15 && ((Vbat__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Vbat_Write(uint8 value) ;
void    Vbat_SetDriveMode(uint8 mode) ;
uint8   Vbat_ReadDataReg(void) ;
uint8   Vbat_Read(void) ;
uint8   Vbat_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vbat_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vbat_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vbat_DM_RES_UP          PIN_DM_RES_UP
#define Vbat_DM_RES_DWN         PIN_DM_RES_DWN
#define Vbat_DM_OD_LO           PIN_DM_OD_LO
#define Vbat_DM_OD_HI           PIN_DM_OD_HI
#define Vbat_DM_STRONG          PIN_DM_STRONG
#define Vbat_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vbat_MASK               Vbat__MASK
#define Vbat_SHIFT              Vbat__SHIFT
#define Vbat_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vbat_PS                     (* (reg8 *) Vbat__PS)
/* Data Register */
#define Vbat_DR                     (* (reg8 *) Vbat__DR)
/* Port Number */
#define Vbat_PRT_NUM                (* (reg8 *) Vbat__PRT) 
/* Connect to Analog Globals */                                                  
#define Vbat_AG                     (* (reg8 *) Vbat__AG)                       
/* Analog MUX bux enable */
#define Vbat_AMUX                   (* (reg8 *) Vbat__AMUX) 
/* Bidirectional Enable */                                                        
#define Vbat_BIE                    (* (reg8 *) Vbat__BIE)
/* Bit-mask for Aliased Register Access */
#define Vbat_BIT_MASK               (* (reg8 *) Vbat__BIT_MASK)
/* Bypass Enable */
#define Vbat_BYP                    (* (reg8 *) Vbat__BYP)
/* Port wide control signals */                                                   
#define Vbat_CTL                    (* (reg8 *) Vbat__CTL)
/* Drive Modes */
#define Vbat_DM0                    (* (reg8 *) Vbat__DM0) 
#define Vbat_DM1                    (* (reg8 *) Vbat__DM1)
#define Vbat_DM2                    (* (reg8 *) Vbat__DM2) 
/* Input Buffer Disable Override */
#define Vbat_INP_DIS                (* (reg8 *) Vbat__INP_DIS)
/* LCD Common or Segment Drive */
#define Vbat_LCD_COM_SEG            (* (reg8 *) Vbat__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vbat_LCD_EN                 (* (reg8 *) Vbat__LCD_EN)
/* Slew Rate Control */
#define Vbat_SLW                    (* (reg8 *) Vbat__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vbat_PRTDSI__CAPS_SEL       (* (reg8 *) Vbat__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vbat_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vbat__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vbat_PRTDSI__OE_SEL0        (* (reg8 *) Vbat__PRTDSI__OE_SEL0) 
#define Vbat_PRTDSI__OE_SEL1        (* (reg8 *) Vbat__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vbat_PRTDSI__OUT_SEL0       (* (reg8 *) Vbat__PRTDSI__OUT_SEL0) 
#define Vbat_PRTDSI__OUT_SEL1       (* (reg8 *) Vbat__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vbat_PRTDSI__SYNC_OUT       (* (reg8 *) Vbat__PRTDSI__SYNC_OUT) 


#if defined(Vbat__INTSTAT)  /* Interrupt Registers */

    #define Vbat_INTSTAT                (* (reg8 *) Vbat__INTSTAT)
    #define Vbat_SNAP                   (* (reg8 *) Vbat__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vbat_H */


/* [] END OF FILE */
