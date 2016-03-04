/*******************************************************************************
* File Name: Cond_out.h  
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

#if !defined(CY_PINS_Cond_out_H) /* Pins Cond_out_H */
#define CY_PINS_Cond_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Cond_out_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Cond_out__PORT == 15 && ((Cond_out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Cond_out_Write(uint8 value) ;
void    Cond_out_SetDriveMode(uint8 mode) ;
uint8   Cond_out_ReadDataReg(void) ;
uint8   Cond_out_Read(void) ;
uint8   Cond_out_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Cond_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Cond_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Cond_out_DM_RES_UP          PIN_DM_RES_UP
#define Cond_out_DM_RES_DWN         PIN_DM_RES_DWN
#define Cond_out_DM_OD_LO           PIN_DM_OD_LO
#define Cond_out_DM_OD_HI           PIN_DM_OD_HI
#define Cond_out_DM_STRONG          PIN_DM_STRONG
#define Cond_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Cond_out_MASK               Cond_out__MASK
#define Cond_out_SHIFT              Cond_out__SHIFT
#define Cond_out_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Cond_out_PS                     (* (reg8 *) Cond_out__PS)
/* Data Register */
#define Cond_out_DR                     (* (reg8 *) Cond_out__DR)
/* Port Number */
#define Cond_out_PRT_NUM                (* (reg8 *) Cond_out__PRT) 
/* Connect to Analog Globals */                                                  
#define Cond_out_AG                     (* (reg8 *) Cond_out__AG)                       
/* Analog MUX bux enable */
#define Cond_out_AMUX                   (* (reg8 *) Cond_out__AMUX) 
/* Bidirectional Enable */                                                        
#define Cond_out_BIE                    (* (reg8 *) Cond_out__BIE)
/* Bit-mask for Aliased Register Access */
#define Cond_out_BIT_MASK               (* (reg8 *) Cond_out__BIT_MASK)
/* Bypass Enable */
#define Cond_out_BYP                    (* (reg8 *) Cond_out__BYP)
/* Port wide control signals */                                                   
#define Cond_out_CTL                    (* (reg8 *) Cond_out__CTL)
/* Drive Modes */
#define Cond_out_DM0                    (* (reg8 *) Cond_out__DM0) 
#define Cond_out_DM1                    (* (reg8 *) Cond_out__DM1)
#define Cond_out_DM2                    (* (reg8 *) Cond_out__DM2) 
/* Input Buffer Disable Override */
#define Cond_out_INP_DIS                (* (reg8 *) Cond_out__INP_DIS)
/* LCD Common or Segment Drive */
#define Cond_out_LCD_COM_SEG            (* (reg8 *) Cond_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Cond_out_LCD_EN                 (* (reg8 *) Cond_out__LCD_EN)
/* Slew Rate Control */
#define Cond_out_SLW                    (* (reg8 *) Cond_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Cond_out_PRTDSI__CAPS_SEL       (* (reg8 *) Cond_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Cond_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Cond_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Cond_out_PRTDSI__OE_SEL0        (* (reg8 *) Cond_out__PRTDSI__OE_SEL0) 
#define Cond_out_PRTDSI__OE_SEL1        (* (reg8 *) Cond_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Cond_out_PRTDSI__OUT_SEL0       (* (reg8 *) Cond_out__PRTDSI__OUT_SEL0) 
#define Cond_out_PRTDSI__OUT_SEL1       (* (reg8 *) Cond_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Cond_out_PRTDSI__SYNC_OUT       (* (reg8 *) Cond_out__PRTDSI__SYNC_OUT) 


#if defined(Cond_out__INTSTAT)  /* Interrupt Registers */

    #define Cond_out_INTSTAT                (* (reg8 *) Cond_out__INTSTAT)
    #define Cond_out_SNAP                   (* (reg8 *) Cond_out__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Cond_out_H */


/* [] END OF FILE */
