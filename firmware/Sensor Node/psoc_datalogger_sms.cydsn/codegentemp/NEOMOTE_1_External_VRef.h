/*******************************************************************************
* File Name: NEOMOTE_1_External_VRef.h  
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

#if !defined(CY_PINS_NEOMOTE_1_External_VRef_H) /* Pins NEOMOTE_1_External_VRef_H */
#define CY_PINS_NEOMOTE_1_External_VRef_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NEOMOTE_1_External_VRef_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NEOMOTE_1_External_VRef__PORT == 15 && ((NEOMOTE_1_External_VRef__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    NEOMOTE_1_External_VRef_Write(uint8 value) ;
void    NEOMOTE_1_External_VRef_SetDriveMode(uint8 mode) ;
uint8   NEOMOTE_1_External_VRef_ReadDataReg(void) ;
uint8   NEOMOTE_1_External_VRef_Read(void) ;
uint8   NEOMOTE_1_External_VRef_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NEOMOTE_1_External_VRef_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define NEOMOTE_1_External_VRef_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define NEOMOTE_1_External_VRef_DM_RES_UP          PIN_DM_RES_UP
#define NEOMOTE_1_External_VRef_DM_RES_DWN         PIN_DM_RES_DWN
#define NEOMOTE_1_External_VRef_DM_OD_LO           PIN_DM_OD_LO
#define NEOMOTE_1_External_VRef_DM_OD_HI           PIN_DM_OD_HI
#define NEOMOTE_1_External_VRef_DM_STRONG          PIN_DM_STRONG
#define NEOMOTE_1_External_VRef_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define NEOMOTE_1_External_VRef_MASK               NEOMOTE_1_External_VRef__MASK
#define NEOMOTE_1_External_VRef_SHIFT              NEOMOTE_1_External_VRef__SHIFT
#define NEOMOTE_1_External_VRef_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NEOMOTE_1_External_VRef_PS                     (* (reg8 *) NEOMOTE_1_External_VRef__PS)
/* Data Register */
#define NEOMOTE_1_External_VRef_DR                     (* (reg8 *) NEOMOTE_1_External_VRef__DR)
/* Port Number */
#define NEOMOTE_1_External_VRef_PRT_NUM                (* (reg8 *) NEOMOTE_1_External_VRef__PRT) 
/* Connect to Analog Globals */                                                  
#define NEOMOTE_1_External_VRef_AG                     (* (reg8 *) NEOMOTE_1_External_VRef__AG)                       
/* Analog MUX bux enable */
#define NEOMOTE_1_External_VRef_AMUX                   (* (reg8 *) NEOMOTE_1_External_VRef__AMUX) 
/* Bidirectional Enable */                                                        
#define NEOMOTE_1_External_VRef_BIE                    (* (reg8 *) NEOMOTE_1_External_VRef__BIE)
/* Bit-mask for Aliased Register Access */
#define NEOMOTE_1_External_VRef_BIT_MASK               (* (reg8 *) NEOMOTE_1_External_VRef__BIT_MASK)
/* Bypass Enable */
#define NEOMOTE_1_External_VRef_BYP                    (* (reg8 *) NEOMOTE_1_External_VRef__BYP)
/* Port wide control signals */                                                   
#define NEOMOTE_1_External_VRef_CTL                    (* (reg8 *) NEOMOTE_1_External_VRef__CTL)
/* Drive Modes */
#define NEOMOTE_1_External_VRef_DM0                    (* (reg8 *) NEOMOTE_1_External_VRef__DM0) 
#define NEOMOTE_1_External_VRef_DM1                    (* (reg8 *) NEOMOTE_1_External_VRef__DM1)
#define NEOMOTE_1_External_VRef_DM2                    (* (reg8 *) NEOMOTE_1_External_VRef__DM2) 
/* Input Buffer Disable Override */
#define NEOMOTE_1_External_VRef_INP_DIS                (* (reg8 *) NEOMOTE_1_External_VRef__INP_DIS)
/* LCD Common or Segment Drive */
#define NEOMOTE_1_External_VRef_LCD_COM_SEG            (* (reg8 *) NEOMOTE_1_External_VRef__LCD_COM_SEG)
/* Enable Segment LCD */
#define NEOMOTE_1_External_VRef_LCD_EN                 (* (reg8 *) NEOMOTE_1_External_VRef__LCD_EN)
/* Slew Rate Control */
#define NEOMOTE_1_External_VRef_SLW                    (* (reg8 *) NEOMOTE_1_External_VRef__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NEOMOTE_1_External_VRef_PRTDSI__CAPS_SEL       (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NEOMOTE_1_External_VRef_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NEOMOTE_1_External_VRef_PRTDSI__OE_SEL0        (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__OE_SEL0) 
#define NEOMOTE_1_External_VRef_PRTDSI__OE_SEL1        (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NEOMOTE_1_External_VRef_PRTDSI__OUT_SEL0       (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__OUT_SEL0) 
#define NEOMOTE_1_External_VRef_PRTDSI__OUT_SEL1       (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NEOMOTE_1_External_VRef_PRTDSI__SYNC_OUT       (* (reg8 *) NEOMOTE_1_External_VRef__PRTDSI__SYNC_OUT) 


#if defined(NEOMOTE_1_External_VRef__INTSTAT)  /* Interrupt Registers */

    #define NEOMOTE_1_External_VRef_INTSTAT                (* (reg8 *) NEOMOTE_1_External_VRef__INTSTAT)
    #define NEOMOTE_1_External_VRef_SNAP                   (* (reg8 *) NEOMOTE_1_External_VRef__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NEOMOTE_1_External_VRef_H */


/* [] END OF FILE */
