/*******************************************************************************
* File Name: Pin7.h  
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

#if !defined(CY_PINS_Pin7_H) /* Pins Pin7_H */
#define CY_PINS_Pin7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin7_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin7__PORT == 15 && ((Pin7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin7_Write(uint8 value) ;
void    Pin7_SetDriveMode(uint8 mode) ;
uint8   Pin7_ReadDataReg(void) ;
uint8   Pin7_Read(void) ;
uint8   Pin7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin7_DM_RES_UP          PIN_DM_RES_UP
#define Pin7_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin7_DM_OD_LO           PIN_DM_OD_LO
#define Pin7_DM_OD_HI           PIN_DM_OD_HI
#define Pin7_DM_STRONG          PIN_DM_STRONG
#define Pin7_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin7_MASK               Pin7__MASK
#define Pin7_SHIFT              Pin7__SHIFT
#define Pin7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin7_PS                     (* (reg8 *) Pin7__PS)
/* Data Register */
#define Pin7_DR                     (* (reg8 *) Pin7__DR)
/* Port Number */
#define Pin7_PRT_NUM                (* (reg8 *) Pin7__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin7_AG                     (* (reg8 *) Pin7__AG)                       
/* Analog MUX bux enable */
#define Pin7_AMUX                   (* (reg8 *) Pin7__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin7_BIE                    (* (reg8 *) Pin7__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin7_BIT_MASK               (* (reg8 *) Pin7__BIT_MASK)
/* Bypass Enable */
#define Pin7_BYP                    (* (reg8 *) Pin7__BYP)
/* Port wide control signals */                                                   
#define Pin7_CTL                    (* (reg8 *) Pin7__CTL)
/* Drive Modes */
#define Pin7_DM0                    (* (reg8 *) Pin7__DM0) 
#define Pin7_DM1                    (* (reg8 *) Pin7__DM1)
#define Pin7_DM2                    (* (reg8 *) Pin7__DM2) 
/* Input Buffer Disable Override */
#define Pin7_INP_DIS                (* (reg8 *) Pin7__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin7_LCD_COM_SEG            (* (reg8 *) Pin7__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin7_LCD_EN                 (* (reg8 *) Pin7__LCD_EN)
/* Slew Rate Control */
#define Pin7_SLW                    (* (reg8 *) Pin7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin7_PRTDSI__CAPS_SEL       (* (reg8 *) Pin7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin7_PRTDSI__OE_SEL0        (* (reg8 *) Pin7__PRTDSI__OE_SEL0) 
#define Pin7_PRTDSI__OE_SEL1        (* (reg8 *) Pin7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin7_PRTDSI__OUT_SEL0       (* (reg8 *) Pin7__PRTDSI__OUT_SEL0) 
#define Pin7_PRTDSI__OUT_SEL1       (* (reg8 *) Pin7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin7_PRTDSI__SYNC_OUT       (* (reg8 *) Pin7__PRTDSI__SYNC_OUT) 


#if defined(Pin7__INTSTAT)  /* Interrupt Registers */

    #define Pin7_INTSTAT                (* (reg8 *) Pin7__INTSTAT)
    #define Pin7_SNAP                   (* (reg8 *) Pin7__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin7_H */


/* [] END OF FILE */
