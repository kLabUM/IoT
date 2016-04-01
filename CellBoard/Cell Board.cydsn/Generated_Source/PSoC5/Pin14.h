/*******************************************************************************
* File Name: Pin14.h  
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

#if !defined(CY_PINS_Pin14_H) /* Pins Pin14_H */
#define CY_PINS_Pin14_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin14_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin14__PORT == 15 && ((Pin14__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin14_Write(uint8 value) ;
void    Pin14_SetDriveMode(uint8 mode) ;
uint8   Pin14_ReadDataReg(void) ;
uint8   Pin14_Read(void) ;
uint8   Pin14_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin14_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin14_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin14_DM_RES_UP          PIN_DM_RES_UP
#define Pin14_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin14_DM_OD_LO           PIN_DM_OD_LO
#define Pin14_DM_OD_HI           PIN_DM_OD_HI
#define Pin14_DM_STRONG          PIN_DM_STRONG
#define Pin14_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin14_MASK               Pin14__MASK
#define Pin14_SHIFT              Pin14__SHIFT
#define Pin14_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin14_PS                     (* (reg8 *) Pin14__PS)
/* Data Register */
#define Pin14_DR                     (* (reg8 *) Pin14__DR)
/* Port Number */
#define Pin14_PRT_NUM                (* (reg8 *) Pin14__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin14_AG                     (* (reg8 *) Pin14__AG)                       
/* Analog MUX bux enable */
#define Pin14_AMUX                   (* (reg8 *) Pin14__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin14_BIE                    (* (reg8 *) Pin14__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin14_BIT_MASK               (* (reg8 *) Pin14__BIT_MASK)
/* Bypass Enable */
#define Pin14_BYP                    (* (reg8 *) Pin14__BYP)
/* Port wide control signals */                                                   
#define Pin14_CTL                    (* (reg8 *) Pin14__CTL)
/* Drive Modes */
#define Pin14_DM0                    (* (reg8 *) Pin14__DM0) 
#define Pin14_DM1                    (* (reg8 *) Pin14__DM1)
#define Pin14_DM2                    (* (reg8 *) Pin14__DM2) 
/* Input Buffer Disable Override */
#define Pin14_INP_DIS                (* (reg8 *) Pin14__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin14_LCD_COM_SEG            (* (reg8 *) Pin14__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin14_LCD_EN                 (* (reg8 *) Pin14__LCD_EN)
/* Slew Rate Control */
#define Pin14_SLW                    (* (reg8 *) Pin14__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin14_PRTDSI__CAPS_SEL       (* (reg8 *) Pin14__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin14_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin14__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin14_PRTDSI__OE_SEL0        (* (reg8 *) Pin14__PRTDSI__OE_SEL0) 
#define Pin14_PRTDSI__OE_SEL1        (* (reg8 *) Pin14__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin14_PRTDSI__OUT_SEL0       (* (reg8 *) Pin14__PRTDSI__OUT_SEL0) 
#define Pin14_PRTDSI__OUT_SEL1       (* (reg8 *) Pin14__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin14_PRTDSI__SYNC_OUT       (* (reg8 *) Pin14__PRTDSI__SYNC_OUT) 


#if defined(Pin14__INTSTAT)  /* Interrupt Registers */

    #define Pin14_INTSTAT                (* (reg8 *) Pin14__INTSTAT)
    #define Pin14_SNAP                   (* (reg8 *) Pin14__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin14_H */


/* [] END OF FILE */
