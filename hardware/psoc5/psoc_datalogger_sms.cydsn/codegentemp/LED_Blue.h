/*******************************************************************************
* File Name: LED_Blue.h  
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

#if !defined(CY_PINS_LED_Blue_H) /* Pins LED_Blue_H */
#define CY_PINS_LED_Blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_Blue_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_Blue__PORT == 15 && ((LED_Blue__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Blue_Write(uint8 value) ;
void    LED_Blue_SetDriveMode(uint8 mode) ;
uint8   LED_Blue_ReadDataReg(void) ;
uint8   LED_Blue_Read(void) ;
uint8   LED_Blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_Blue_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_Blue_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_Blue_DM_RES_UP          PIN_DM_RES_UP
#define LED_Blue_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_Blue_DM_OD_LO           PIN_DM_OD_LO
#define LED_Blue_DM_OD_HI           PIN_DM_OD_HI
#define LED_Blue_DM_STRONG          PIN_DM_STRONG
#define LED_Blue_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_Blue_MASK               LED_Blue__MASK
#define LED_Blue_SHIFT              LED_Blue__SHIFT
#define LED_Blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_Blue_PS                     (* (reg8 *) LED_Blue__PS)
/* Data Register */
#define LED_Blue_DR                     (* (reg8 *) LED_Blue__DR)
/* Port Number */
#define LED_Blue_PRT_NUM                (* (reg8 *) LED_Blue__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_Blue_AG                     (* (reg8 *) LED_Blue__AG)                       
/* Analog MUX bux enable */
#define LED_Blue_AMUX                   (* (reg8 *) LED_Blue__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_Blue_BIE                    (* (reg8 *) LED_Blue__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_Blue_BIT_MASK               (* (reg8 *) LED_Blue__BIT_MASK)
/* Bypass Enable */
#define LED_Blue_BYP                    (* (reg8 *) LED_Blue__BYP)
/* Port wide control signals */                                                   
#define LED_Blue_CTL                    (* (reg8 *) LED_Blue__CTL)
/* Drive Modes */
#define LED_Blue_DM0                    (* (reg8 *) LED_Blue__DM0) 
#define LED_Blue_DM1                    (* (reg8 *) LED_Blue__DM1)
#define LED_Blue_DM2                    (* (reg8 *) LED_Blue__DM2) 
/* Input Buffer Disable Override */
#define LED_Blue_INP_DIS                (* (reg8 *) LED_Blue__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_Blue_LCD_COM_SEG            (* (reg8 *) LED_Blue__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_Blue_LCD_EN                 (* (reg8 *) LED_Blue__LCD_EN)
/* Slew Rate Control */
#define LED_Blue_SLW                    (* (reg8 *) LED_Blue__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_Blue_PRTDSI__CAPS_SEL       (* (reg8 *) LED_Blue__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_Blue_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_Blue__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_Blue_PRTDSI__OE_SEL0        (* (reg8 *) LED_Blue__PRTDSI__OE_SEL0) 
#define LED_Blue_PRTDSI__OE_SEL1        (* (reg8 *) LED_Blue__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_Blue_PRTDSI__OUT_SEL0       (* (reg8 *) LED_Blue__PRTDSI__OUT_SEL0) 
#define LED_Blue_PRTDSI__OUT_SEL1       (* (reg8 *) LED_Blue__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_Blue_PRTDSI__SYNC_OUT       (* (reg8 *) LED_Blue__PRTDSI__SYNC_OUT) 


#if defined(LED_Blue__INTSTAT)  /* Interrupt Registers */

    #define LED_Blue_INTSTAT                (* (reg8 *) LED_Blue__INTSTAT)
    #define LED_Blue_SNAP                   (* (reg8 *) LED_Blue__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_Blue_H */


/* [] END OF FILE */
