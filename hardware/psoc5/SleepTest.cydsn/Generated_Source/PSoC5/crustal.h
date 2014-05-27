/*******************************************************************************
* File Name: crustal.h  
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

#if !defined(CY_PINS_crustal_H) /* Pins crustal_H */
#define CY_PINS_crustal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "crustal_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 crustal__PORT == 15 && ((crustal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    crustal_Write(uint8 value) ;
void    crustal_SetDriveMode(uint8 mode) ;
uint8   crustal_ReadDataReg(void) ;
uint8   crustal_Read(void) ;
uint8   crustal_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define crustal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define crustal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define crustal_DM_RES_UP          PIN_DM_RES_UP
#define crustal_DM_RES_DWN         PIN_DM_RES_DWN
#define crustal_DM_OD_LO           PIN_DM_OD_LO
#define crustal_DM_OD_HI           PIN_DM_OD_HI
#define crustal_DM_STRONG          PIN_DM_STRONG
#define crustal_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define crustal_MASK               crustal__MASK
#define crustal_SHIFT              crustal__SHIFT
#define crustal_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define crustal_PS                     (* (reg8 *) crustal__PS)
/* Data Register */
#define crustal_DR                     (* (reg8 *) crustal__DR)
/* Port Number */
#define crustal_PRT_NUM                (* (reg8 *) crustal__PRT) 
/* Connect to Analog Globals */                                                  
#define crustal_AG                     (* (reg8 *) crustal__AG)                       
/* Analog MUX bux enable */
#define crustal_AMUX                   (* (reg8 *) crustal__AMUX) 
/* Bidirectional Enable */                                                        
#define crustal_BIE                    (* (reg8 *) crustal__BIE)
/* Bit-mask for Aliased Register Access */
#define crustal_BIT_MASK               (* (reg8 *) crustal__BIT_MASK)
/* Bypass Enable */
#define crustal_BYP                    (* (reg8 *) crustal__BYP)
/* Port wide control signals */                                                   
#define crustal_CTL                    (* (reg8 *) crustal__CTL)
/* Drive Modes */
#define crustal_DM0                    (* (reg8 *) crustal__DM0) 
#define crustal_DM1                    (* (reg8 *) crustal__DM1)
#define crustal_DM2                    (* (reg8 *) crustal__DM2) 
/* Input Buffer Disable Override */
#define crustal_INP_DIS                (* (reg8 *) crustal__INP_DIS)
/* LCD Common or Segment Drive */
#define crustal_LCD_COM_SEG            (* (reg8 *) crustal__LCD_COM_SEG)
/* Enable Segment LCD */
#define crustal_LCD_EN                 (* (reg8 *) crustal__LCD_EN)
/* Slew Rate Control */
#define crustal_SLW                    (* (reg8 *) crustal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define crustal_PRTDSI__CAPS_SEL       (* (reg8 *) crustal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define crustal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) crustal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define crustal_PRTDSI__OE_SEL0        (* (reg8 *) crustal__PRTDSI__OE_SEL0) 
#define crustal_PRTDSI__OE_SEL1        (* (reg8 *) crustal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define crustal_PRTDSI__OUT_SEL0       (* (reg8 *) crustal__PRTDSI__OUT_SEL0) 
#define crustal_PRTDSI__OUT_SEL1       (* (reg8 *) crustal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define crustal_PRTDSI__SYNC_OUT       (* (reg8 *) crustal__PRTDSI__SYNC_OUT) 


#if defined(crustal__INTSTAT)  /* Interrupt Registers */

    #define crustal_INTSTAT                (* (reg8 *) crustal__INTSTAT)
    #define crustal_SNAP                   (* (reg8 *) crustal__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_crustal_H */


/* [] END OF FILE */
