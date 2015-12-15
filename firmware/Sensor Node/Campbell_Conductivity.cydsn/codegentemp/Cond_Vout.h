/*******************************************************************************
* File Name: Cond_Vout.h  
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

#if !defined(CY_PINS_Cond_Vout_H) /* Pins Cond_Vout_H */
#define CY_PINS_Cond_Vout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Cond_Vout_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Cond_Vout__PORT == 15 && ((Cond_Vout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Cond_Vout_Write(uint8 value) ;
void    Cond_Vout_SetDriveMode(uint8 mode) ;
uint8   Cond_Vout_ReadDataReg(void) ;
uint8   Cond_Vout_Read(void) ;
uint8   Cond_Vout_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Cond_Vout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Cond_Vout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Cond_Vout_DM_RES_UP          PIN_DM_RES_UP
#define Cond_Vout_DM_RES_DWN         PIN_DM_RES_DWN
#define Cond_Vout_DM_OD_LO           PIN_DM_OD_LO
#define Cond_Vout_DM_OD_HI           PIN_DM_OD_HI
#define Cond_Vout_DM_STRONG          PIN_DM_STRONG
#define Cond_Vout_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Cond_Vout_MASK               Cond_Vout__MASK
#define Cond_Vout_SHIFT              Cond_Vout__SHIFT
#define Cond_Vout_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Cond_Vout_PS                     (* (reg8 *) Cond_Vout__PS)
/* Data Register */
#define Cond_Vout_DR                     (* (reg8 *) Cond_Vout__DR)
/* Port Number */
#define Cond_Vout_PRT_NUM                (* (reg8 *) Cond_Vout__PRT) 
/* Connect to Analog Globals */                                                  
#define Cond_Vout_AG                     (* (reg8 *) Cond_Vout__AG)                       
/* Analog MUX bux enable */
#define Cond_Vout_AMUX                   (* (reg8 *) Cond_Vout__AMUX) 
/* Bidirectional Enable */                                                        
#define Cond_Vout_BIE                    (* (reg8 *) Cond_Vout__BIE)
/* Bit-mask for Aliased Register Access */
#define Cond_Vout_BIT_MASK               (* (reg8 *) Cond_Vout__BIT_MASK)
/* Bypass Enable */
#define Cond_Vout_BYP                    (* (reg8 *) Cond_Vout__BYP)
/* Port wide control signals */                                                   
#define Cond_Vout_CTL                    (* (reg8 *) Cond_Vout__CTL)
/* Drive Modes */
#define Cond_Vout_DM0                    (* (reg8 *) Cond_Vout__DM0) 
#define Cond_Vout_DM1                    (* (reg8 *) Cond_Vout__DM1)
#define Cond_Vout_DM2                    (* (reg8 *) Cond_Vout__DM2) 
/* Input Buffer Disable Override */
#define Cond_Vout_INP_DIS                (* (reg8 *) Cond_Vout__INP_DIS)
/* LCD Common or Segment Drive */
#define Cond_Vout_LCD_COM_SEG            (* (reg8 *) Cond_Vout__LCD_COM_SEG)
/* Enable Segment LCD */
#define Cond_Vout_LCD_EN                 (* (reg8 *) Cond_Vout__LCD_EN)
/* Slew Rate Control */
#define Cond_Vout_SLW                    (* (reg8 *) Cond_Vout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Cond_Vout_PRTDSI__CAPS_SEL       (* (reg8 *) Cond_Vout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Cond_Vout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Cond_Vout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Cond_Vout_PRTDSI__OE_SEL0        (* (reg8 *) Cond_Vout__PRTDSI__OE_SEL0) 
#define Cond_Vout_PRTDSI__OE_SEL1        (* (reg8 *) Cond_Vout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Cond_Vout_PRTDSI__OUT_SEL0       (* (reg8 *) Cond_Vout__PRTDSI__OUT_SEL0) 
#define Cond_Vout_PRTDSI__OUT_SEL1       (* (reg8 *) Cond_Vout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Cond_Vout_PRTDSI__SYNC_OUT       (* (reg8 *) Cond_Vout__PRTDSI__SYNC_OUT) 


#if defined(Cond_Vout__INTSTAT)  /* Interrupt Registers */

    #define Cond_Vout_INTSTAT                (* (reg8 *) Cond_Vout__INTSTAT)
    #define Cond_Vout_SNAP                   (* (reg8 *) Cond_Vout__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Cond_Vout_H */


/* [] END OF FILE */
