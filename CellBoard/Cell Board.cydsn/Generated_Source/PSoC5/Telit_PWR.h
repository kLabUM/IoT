/*******************************************************************************
* File Name: Telit_PWR.h  
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

#if !defined(CY_PINS_Telit_PWR_H) /* Pins Telit_PWR_H */
#define CY_PINS_Telit_PWR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Telit_PWR_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Telit_PWR__PORT == 15 && ((Telit_PWR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Telit_PWR_Write(uint8 value) ;
void    Telit_PWR_SetDriveMode(uint8 mode) ;
uint8   Telit_PWR_ReadDataReg(void) ;
uint8   Telit_PWR_Read(void) ;
uint8   Telit_PWR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Telit_PWR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Telit_PWR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Telit_PWR_DM_RES_UP          PIN_DM_RES_UP
#define Telit_PWR_DM_RES_DWN         PIN_DM_RES_DWN
#define Telit_PWR_DM_OD_LO           PIN_DM_OD_LO
#define Telit_PWR_DM_OD_HI           PIN_DM_OD_HI
#define Telit_PWR_DM_STRONG          PIN_DM_STRONG
#define Telit_PWR_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Telit_PWR_MASK               Telit_PWR__MASK
#define Telit_PWR_SHIFT              Telit_PWR__SHIFT
#define Telit_PWR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Telit_PWR_PS                     (* (reg8 *) Telit_PWR__PS)
/* Data Register */
#define Telit_PWR_DR                     (* (reg8 *) Telit_PWR__DR)
/* Port Number */
#define Telit_PWR_PRT_NUM                (* (reg8 *) Telit_PWR__PRT) 
/* Connect to Analog Globals */                                                  
#define Telit_PWR_AG                     (* (reg8 *) Telit_PWR__AG)                       
/* Analog MUX bux enable */
#define Telit_PWR_AMUX                   (* (reg8 *) Telit_PWR__AMUX) 
/* Bidirectional Enable */                                                        
#define Telit_PWR_BIE                    (* (reg8 *) Telit_PWR__BIE)
/* Bit-mask for Aliased Register Access */
#define Telit_PWR_BIT_MASK               (* (reg8 *) Telit_PWR__BIT_MASK)
/* Bypass Enable */
#define Telit_PWR_BYP                    (* (reg8 *) Telit_PWR__BYP)
/* Port wide control signals */                                                   
#define Telit_PWR_CTL                    (* (reg8 *) Telit_PWR__CTL)
/* Drive Modes */
#define Telit_PWR_DM0                    (* (reg8 *) Telit_PWR__DM0) 
#define Telit_PWR_DM1                    (* (reg8 *) Telit_PWR__DM1)
#define Telit_PWR_DM2                    (* (reg8 *) Telit_PWR__DM2) 
/* Input Buffer Disable Override */
#define Telit_PWR_INP_DIS                (* (reg8 *) Telit_PWR__INP_DIS)
/* LCD Common or Segment Drive */
#define Telit_PWR_LCD_COM_SEG            (* (reg8 *) Telit_PWR__LCD_COM_SEG)
/* Enable Segment LCD */
#define Telit_PWR_LCD_EN                 (* (reg8 *) Telit_PWR__LCD_EN)
/* Slew Rate Control */
#define Telit_PWR_SLW                    (* (reg8 *) Telit_PWR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Telit_PWR_PRTDSI__CAPS_SEL       (* (reg8 *) Telit_PWR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Telit_PWR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Telit_PWR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Telit_PWR_PRTDSI__OE_SEL0        (* (reg8 *) Telit_PWR__PRTDSI__OE_SEL0) 
#define Telit_PWR_PRTDSI__OE_SEL1        (* (reg8 *) Telit_PWR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Telit_PWR_PRTDSI__OUT_SEL0       (* (reg8 *) Telit_PWR__PRTDSI__OUT_SEL0) 
#define Telit_PWR_PRTDSI__OUT_SEL1       (* (reg8 *) Telit_PWR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Telit_PWR_PRTDSI__SYNC_OUT       (* (reg8 *) Telit_PWR__PRTDSI__SYNC_OUT) 


#if defined(Telit_PWR__INTSTAT)  /* Interrupt Registers */

    #define Telit_PWR_INTSTAT                (* (reg8 *) Telit_PWR__INTSTAT)
    #define Telit_PWR_SNAP                   (* (reg8 *) Telit_PWR__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Telit_PWR_H */


/* [] END OF FILE */
