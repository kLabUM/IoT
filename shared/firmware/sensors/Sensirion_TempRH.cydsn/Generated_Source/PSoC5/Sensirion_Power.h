/*******************************************************************************
* File Name: Sensirion_Power.h  
* Version 2.0
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

#if !defined(CY_PINS_Sensirion_Power_H) /* Pins Sensirion_Power_H */
#define CY_PINS_Sensirion_Power_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sensirion_Power_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Sensirion_Power__PORT == 15 && ((Sensirion_Power__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Sensirion_Power_Write(uint8 value) ;
void    Sensirion_Power_SetDriveMode(uint8 mode) ;
uint8   Sensirion_Power_ReadDataReg(void) ;
uint8   Sensirion_Power_Read(void) ;
uint8   Sensirion_Power_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sensirion_Power_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Sensirion_Power_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Sensirion_Power_DM_RES_UP          PIN_DM_RES_UP
#define Sensirion_Power_DM_RES_DWN         PIN_DM_RES_DWN
#define Sensirion_Power_DM_OD_LO           PIN_DM_OD_LO
#define Sensirion_Power_DM_OD_HI           PIN_DM_OD_HI
#define Sensirion_Power_DM_STRONG          PIN_DM_STRONG
#define Sensirion_Power_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Sensirion_Power_MASK               Sensirion_Power__MASK
#define Sensirion_Power_SHIFT              Sensirion_Power__SHIFT
#define Sensirion_Power_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sensirion_Power_PS                     (* (reg8 *) Sensirion_Power__PS)
/* Data Register */
#define Sensirion_Power_DR                     (* (reg8 *) Sensirion_Power__DR)
/* Port Number */
#define Sensirion_Power_PRT_NUM                (* (reg8 *) Sensirion_Power__PRT) 
/* Connect to Analog Globals */                                                  
#define Sensirion_Power_AG                     (* (reg8 *) Sensirion_Power__AG)                       
/* Analog MUX bux enable */
#define Sensirion_Power_AMUX                   (* (reg8 *) Sensirion_Power__AMUX) 
/* Bidirectional Enable */                                                        
#define Sensirion_Power_BIE                    (* (reg8 *) Sensirion_Power__BIE)
/* Bit-mask for Aliased Register Access */
#define Sensirion_Power_BIT_MASK               (* (reg8 *) Sensirion_Power__BIT_MASK)
/* Bypass Enable */
#define Sensirion_Power_BYP                    (* (reg8 *) Sensirion_Power__BYP)
/* Port wide control signals */                                                   
#define Sensirion_Power_CTL                    (* (reg8 *) Sensirion_Power__CTL)
/* Drive Modes */
#define Sensirion_Power_DM0                    (* (reg8 *) Sensirion_Power__DM0) 
#define Sensirion_Power_DM1                    (* (reg8 *) Sensirion_Power__DM1)
#define Sensirion_Power_DM2                    (* (reg8 *) Sensirion_Power__DM2) 
/* Input Buffer Disable Override */
#define Sensirion_Power_INP_DIS                (* (reg8 *) Sensirion_Power__INP_DIS)
/* LCD Common or Segment Drive */
#define Sensirion_Power_LCD_COM_SEG            (* (reg8 *) Sensirion_Power__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sensirion_Power_LCD_EN                 (* (reg8 *) Sensirion_Power__LCD_EN)
/* Slew Rate Control */
#define Sensirion_Power_SLW                    (* (reg8 *) Sensirion_Power__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sensirion_Power_PRTDSI__CAPS_SEL       (* (reg8 *) Sensirion_Power__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sensirion_Power_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sensirion_Power__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sensirion_Power_PRTDSI__OE_SEL0        (* (reg8 *) Sensirion_Power__PRTDSI__OE_SEL0) 
#define Sensirion_Power_PRTDSI__OE_SEL1        (* (reg8 *) Sensirion_Power__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sensirion_Power_PRTDSI__OUT_SEL0       (* (reg8 *) Sensirion_Power__PRTDSI__OUT_SEL0) 
#define Sensirion_Power_PRTDSI__OUT_SEL1       (* (reg8 *) Sensirion_Power__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sensirion_Power_PRTDSI__SYNC_OUT       (* (reg8 *) Sensirion_Power__PRTDSI__SYNC_OUT) 


#if defined(Sensirion_Power__INTSTAT)  /* Interrupt Registers */

    #define Sensirion_Power_INTSTAT                (* (reg8 *) Sensirion_Power__INTSTAT)
    #define Sensirion_Power_SNAP                   (* (reg8 *) Sensirion_Power__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Sensirion_Power_H */


/* [] END OF FILE */
