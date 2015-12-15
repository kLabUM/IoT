/*******************************************************************************
* File Name: led.h  
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

#if !defined(CY_PINS_led_H) /* Pins led_H */
#define CY_PINS_led_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "led_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 led__PORT == 15 && ((led__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    led_Write(uint8 value) ;
void    led_SetDriveMode(uint8 mode) ;
uint8   led_ReadDataReg(void) ;
uint8   led_Read(void) ;
uint8   led_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define led_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define led_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define led_DM_RES_UP          PIN_DM_RES_UP
#define led_DM_RES_DWN         PIN_DM_RES_DWN
#define led_DM_OD_LO           PIN_DM_OD_LO
#define led_DM_OD_HI           PIN_DM_OD_HI
#define led_DM_STRONG          PIN_DM_STRONG
#define led_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define led_MASK               led__MASK
#define led_SHIFT              led__SHIFT
#define led_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define led_PS                     (* (reg8 *) led__PS)
/* Data Register */
#define led_DR                     (* (reg8 *) led__DR)
/* Port Number */
#define led_PRT_NUM                (* (reg8 *) led__PRT) 
/* Connect to Analog Globals */                                                  
#define led_AG                     (* (reg8 *) led__AG)                       
/* Analog MUX bux enable */
#define led_AMUX                   (* (reg8 *) led__AMUX) 
/* Bidirectional Enable */                                                        
#define led_BIE                    (* (reg8 *) led__BIE)
/* Bit-mask for Aliased Register Access */
#define led_BIT_MASK               (* (reg8 *) led__BIT_MASK)
/* Bypass Enable */
#define led_BYP                    (* (reg8 *) led__BYP)
/* Port wide control signals */                                                   
#define led_CTL                    (* (reg8 *) led__CTL)
/* Drive Modes */
#define led_DM0                    (* (reg8 *) led__DM0) 
#define led_DM1                    (* (reg8 *) led__DM1)
#define led_DM2                    (* (reg8 *) led__DM2) 
/* Input Buffer Disable Override */
#define led_INP_DIS                (* (reg8 *) led__INP_DIS)
/* LCD Common or Segment Drive */
#define led_LCD_COM_SEG            (* (reg8 *) led__LCD_COM_SEG)
/* Enable Segment LCD */
#define led_LCD_EN                 (* (reg8 *) led__LCD_EN)
/* Slew Rate Control */
#define led_SLW                    (* (reg8 *) led__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define led_PRTDSI__CAPS_SEL       (* (reg8 *) led__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define led_PRTDSI__DBL_SYNC_IN    (* (reg8 *) led__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define led_PRTDSI__OE_SEL0        (* (reg8 *) led__PRTDSI__OE_SEL0) 
#define led_PRTDSI__OE_SEL1        (* (reg8 *) led__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define led_PRTDSI__OUT_SEL0       (* (reg8 *) led__PRTDSI__OUT_SEL0) 
#define led_PRTDSI__OUT_SEL1       (* (reg8 *) led__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define led_PRTDSI__SYNC_OUT       (* (reg8 *) led__PRTDSI__SYNC_OUT) 


#if defined(led__INTSTAT)  /* Interrupt Registers */

    #define led_INTSTAT                (* (reg8 *) led__INTSTAT)
    #define led_SNAP                   (* (reg8 *) led__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_led_H */


/* [] END OF FILE */
