/*******************************************************************************
* File Name: int1.h  
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

#if !defined(CY_PINS_int1_H) /* Pins int1_H */
#define CY_PINS_int1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "int1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 int1__PORT == 15 && ((int1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    int1_Write(uint8 value) ;
void    int1_SetDriveMode(uint8 mode) ;
uint8   int1_ReadDataReg(void) ;
uint8   int1_Read(void) ;
uint8   int1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define int1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define int1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define int1_DM_RES_UP          PIN_DM_RES_UP
#define int1_DM_RES_DWN         PIN_DM_RES_DWN
#define int1_DM_OD_LO           PIN_DM_OD_LO
#define int1_DM_OD_HI           PIN_DM_OD_HI
#define int1_DM_STRONG          PIN_DM_STRONG
#define int1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define int1_MASK               int1__MASK
#define int1_SHIFT              int1__SHIFT
#define int1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define int1_PS                     (* (reg8 *) int1__PS)
/* Data Register */
#define int1_DR                     (* (reg8 *) int1__DR)
/* Port Number */
#define int1_PRT_NUM                (* (reg8 *) int1__PRT) 
/* Connect to Analog Globals */                                                  
#define int1_AG                     (* (reg8 *) int1__AG)                       
/* Analog MUX bux enable */
#define int1_AMUX                   (* (reg8 *) int1__AMUX) 
/* Bidirectional Enable */                                                        
#define int1_BIE                    (* (reg8 *) int1__BIE)
/* Bit-mask for Aliased Register Access */
#define int1_BIT_MASK               (* (reg8 *) int1__BIT_MASK)
/* Bypass Enable */
#define int1_BYP                    (* (reg8 *) int1__BYP)
/* Port wide control signals */                                                   
#define int1_CTL                    (* (reg8 *) int1__CTL)
/* Drive Modes */
#define int1_DM0                    (* (reg8 *) int1__DM0) 
#define int1_DM1                    (* (reg8 *) int1__DM1)
#define int1_DM2                    (* (reg8 *) int1__DM2) 
/* Input Buffer Disable Override */
#define int1_INP_DIS                (* (reg8 *) int1__INP_DIS)
/* LCD Common or Segment Drive */
#define int1_LCD_COM_SEG            (* (reg8 *) int1__LCD_COM_SEG)
/* Enable Segment LCD */
#define int1_LCD_EN                 (* (reg8 *) int1__LCD_EN)
/* Slew Rate Control */
#define int1_SLW                    (* (reg8 *) int1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define int1_PRTDSI__CAPS_SEL       (* (reg8 *) int1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define int1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) int1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define int1_PRTDSI__OE_SEL0        (* (reg8 *) int1__PRTDSI__OE_SEL0) 
#define int1_PRTDSI__OE_SEL1        (* (reg8 *) int1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define int1_PRTDSI__OUT_SEL0       (* (reg8 *) int1__PRTDSI__OUT_SEL0) 
#define int1_PRTDSI__OUT_SEL1       (* (reg8 *) int1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define int1_PRTDSI__SYNC_OUT       (* (reg8 *) int1__PRTDSI__SYNC_OUT) 


#if defined(int1__INTSTAT)  /* Interrupt Registers */

    #define int1_INTSTAT                (* (reg8 *) int1__INTSTAT)
    #define int1_SNAP                   (* (reg8 *) int1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_int1_H */


/* [] END OF FILE */
