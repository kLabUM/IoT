/*******************************************************************************
* File Name: Telit_tx.h  
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

#if !defined(CY_PINS_Telit_tx_H) /* Pins Telit_tx_H */
#define CY_PINS_Telit_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Telit_tx_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Telit_tx__PORT == 15 && ((Telit_tx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Telit_tx_Write(uint8 value) ;
void    Telit_tx_SetDriveMode(uint8 mode) ;
uint8   Telit_tx_ReadDataReg(void) ;
uint8   Telit_tx_Read(void) ;
uint8   Telit_tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Telit_tx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Telit_tx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Telit_tx_DM_RES_UP          PIN_DM_RES_UP
#define Telit_tx_DM_RES_DWN         PIN_DM_RES_DWN
#define Telit_tx_DM_OD_LO           PIN_DM_OD_LO
#define Telit_tx_DM_OD_HI           PIN_DM_OD_HI
#define Telit_tx_DM_STRONG          PIN_DM_STRONG
#define Telit_tx_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Telit_tx_MASK               Telit_tx__MASK
#define Telit_tx_SHIFT              Telit_tx__SHIFT
#define Telit_tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Telit_tx_PS                     (* (reg8 *) Telit_tx__PS)
/* Data Register */
#define Telit_tx_DR                     (* (reg8 *) Telit_tx__DR)
/* Port Number */
#define Telit_tx_PRT_NUM                (* (reg8 *) Telit_tx__PRT) 
/* Connect to Analog Globals */                                                  
#define Telit_tx_AG                     (* (reg8 *) Telit_tx__AG)                       
/* Analog MUX bux enable */
#define Telit_tx_AMUX                   (* (reg8 *) Telit_tx__AMUX) 
/* Bidirectional Enable */                                                        
#define Telit_tx_BIE                    (* (reg8 *) Telit_tx__BIE)
/* Bit-mask for Aliased Register Access */
#define Telit_tx_BIT_MASK               (* (reg8 *) Telit_tx__BIT_MASK)
/* Bypass Enable */
#define Telit_tx_BYP                    (* (reg8 *) Telit_tx__BYP)
/* Port wide control signals */                                                   
#define Telit_tx_CTL                    (* (reg8 *) Telit_tx__CTL)
/* Drive Modes */
#define Telit_tx_DM0                    (* (reg8 *) Telit_tx__DM0) 
#define Telit_tx_DM1                    (* (reg8 *) Telit_tx__DM1)
#define Telit_tx_DM2                    (* (reg8 *) Telit_tx__DM2) 
/* Input Buffer Disable Override */
#define Telit_tx_INP_DIS                (* (reg8 *) Telit_tx__INP_DIS)
/* LCD Common or Segment Drive */
#define Telit_tx_LCD_COM_SEG            (* (reg8 *) Telit_tx__LCD_COM_SEG)
/* Enable Segment LCD */
#define Telit_tx_LCD_EN                 (* (reg8 *) Telit_tx__LCD_EN)
/* Slew Rate Control */
#define Telit_tx_SLW                    (* (reg8 *) Telit_tx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Telit_tx_PRTDSI__CAPS_SEL       (* (reg8 *) Telit_tx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Telit_tx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Telit_tx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Telit_tx_PRTDSI__OE_SEL0        (* (reg8 *) Telit_tx__PRTDSI__OE_SEL0) 
#define Telit_tx_PRTDSI__OE_SEL1        (* (reg8 *) Telit_tx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Telit_tx_PRTDSI__OUT_SEL0       (* (reg8 *) Telit_tx__PRTDSI__OUT_SEL0) 
#define Telit_tx_PRTDSI__OUT_SEL1       (* (reg8 *) Telit_tx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Telit_tx_PRTDSI__SYNC_OUT       (* (reg8 *) Telit_tx__PRTDSI__SYNC_OUT) 


#if defined(Telit_tx__INTSTAT)  /* Interrupt Registers */

    #define Telit_tx_INTSTAT                (* (reg8 *) Telit_tx__INTSTAT)
    #define Telit_tx_SNAP                   (* (reg8 *) Telit_tx__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Telit_tx_H */


/* [] END OF FILE */
