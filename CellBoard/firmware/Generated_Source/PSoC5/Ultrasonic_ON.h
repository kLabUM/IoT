/*******************************************************************************
* File Name: Ultrasonic_ON.h  
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

#if !defined(CY_PINS_Ultrasonic_ON_H) /* Pins Ultrasonic_ON_H */
#define CY_PINS_Ultrasonic_ON_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ultrasonic_ON_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ultrasonic_ON__PORT == 15 && ((Ultrasonic_ON__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Ultrasonic_ON_Write(uint8 value) ;
void    Ultrasonic_ON_SetDriveMode(uint8 mode) ;
uint8   Ultrasonic_ON_ReadDataReg(void) ;
uint8   Ultrasonic_ON_Read(void) ;
uint8   Ultrasonic_ON_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Ultrasonic_ON_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Ultrasonic_ON_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Ultrasonic_ON_DM_RES_UP          PIN_DM_RES_UP
#define Ultrasonic_ON_DM_RES_DWN         PIN_DM_RES_DWN
#define Ultrasonic_ON_DM_OD_LO           PIN_DM_OD_LO
#define Ultrasonic_ON_DM_OD_HI           PIN_DM_OD_HI
#define Ultrasonic_ON_DM_STRONG          PIN_DM_STRONG
#define Ultrasonic_ON_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Ultrasonic_ON_MASK               Ultrasonic_ON__MASK
#define Ultrasonic_ON_SHIFT              Ultrasonic_ON__SHIFT
#define Ultrasonic_ON_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ultrasonic_ON_PS                     (* (reg8 *) Ultrasonic_ON__PS)
/* Data Register */
#define Ultrasonic_ON_DR                     (* (reg8 *) Ultrasonic_ON__DR)
/* Port Number */
#define Ultrasonic_ON_PRT_NUM                (* (reg8 *) Ultrasonic_ON__PRT) 
/* Connect to Analog Globals */                                                  
#define Ultrasonic_ON_AG                     (* (reg8 *) Ultrasonic_ON__AG)                       
/* Analog MUX bux enable */
#define Ultrasonic_ON_AMUX                   (* (reg8 *) Ultrasonic_ON__AMUX) 
/* Bidirectional Enable */                                                        
#define Ultrasonic_ON_BIE                    (* (reg8 *) Ultrasonic_ON__BIE)
/* Bit-mask for Aliased Register Access */
#define Ultrasonic_ON_BIT_MASK               (* (reg8 *) Ultrasonic_ON__BIT_MASK)
/* Bypass Enable */
#define Ultrasonic_ON_BYP                    (* (reg8 *) Ultrasonic_ON__BYP)
/* Port wide control signals */                                                   
#define Ultrasonic_ON_CTL                    (* (reg8 *) Ultrasonic_ON__CTL)
/* Drive Modes */
#define Ultrasonic_ON_DM0                    (* (reg8 *) Ultrasonic_ON__DM0) 
#define Ultrasonic_ON_DM1                    (* (reg8 *) Ultrasonic_ON__DM1)
#define Ultrasonic_ON_DM2                    (* (reg8 *) Ultrasonic_ON__DM2) 
/* Input Buffer Disable Override */
#define Ultrasonic_ON_INP_DIS                (* (reg8 *) Ultrasonic_ON__INP_DIS)
/* LCD Common or Segment Drive */
#define Ultrasonic_ON_LCD_COM_SEG            (* (reg8 *) Ultrasonic_ON__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ultrasonic_ON_LCD_EN                 (* (reg8 *) Ultrasonic_ON__LCD_EN)
/* Slew Rate Control */
#define Ultrasonic_ON_SLW                    (* (reg8 *) Ultrasonic_ON__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ultrasonic_ON_PRTDSI__CAPS_SEL       (* (reg8 *) Ultrasonic_ON__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ultrasonic_ON_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ultrasonic_ON__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ultrasonic_ON_PRTDSI__OE_SEL0        (* (reg8 *) Ultrasonic_ON__PRTDSI__OE_SEL0) 
#define Ultrasonic_ON_PRTDSI__OE_SEL1        (* (reg8 *) Ultrasonic_ON__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ultrasonic_ON_PRTDSI__OUT_SEL0       (* (reg8 *) Ultrasonic_ON__PRTDSI__OUT_SEL0) 
#define Ultrasonic_ON_PRTDSI__OUT_SEL1       (* (reg8 *) Ultrasonic_ON__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ultrasonic_ON_PRTDSI__SYNC_OUT       (* (reg8 *) Ultrasonic_ON__PRTDSI__SYNC_OUT) 


#if defined(Ultrasonic_ON__INTSTAT)  /* Interrupt Registers */

    #define Ultrasonic_ON_INTSTAT                (* (reg8 *) Ultrasonic_ON__INTSTAT)
    #define Ultrasonic_ON_SNAP                   (* (reg8 *) Ultrasonic_ON__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ultrasonic_ON_H */


/* [] END OF FILE */
