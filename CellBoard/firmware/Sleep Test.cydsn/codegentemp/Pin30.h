/*******************************************************************************
* File Name: Pin30.h  
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

#if !defined(CY_PINS_Pin30_H) /* Pins Pin30_H */
#define CY_PINS_Pin30_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin30_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin30__PORT == 15 && ((Pin30__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin30_Write(uint8 value) ;
void    Pin30_SetDriveMode(uint8 mode) ;
uint8   Pin30_ReadDataReg(void) ;
uint8   Pin30_Read(void) ;
uint8   Pin30_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin30_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin30_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin30_DM_RES_UP          PIN_DM_RES_UP
#define Pin30_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin30_DM_OD_LO           PIN_DM_OD_LO
#define Pin30_DM_OD_HI           PIN_DM_OD_HI
#define Pin30_DM_STRONG          PIN_DM_STRONG
#define Pin30_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin30_MASK               Pin30__MASK
#define Pin30_SHIFT              Pin30__SHIFT
#define Pin30_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin30_PS                     (* (reg8 *) Pin30__PS)
/* Data Register */
#define Pin30_DR                     (* (reg8 *) Pin30__DR)
/* Port Number */
#define Pin30_PRT_NUM                (* (reg8 *) Pin30__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin30_AG                     (* (reg8 *) Pin30__AG)                       
/* Analog MUX bux enable */
#define Pin30_AMUX                   (* (reg8 *) Pin30__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin30_BIE                    (* (reg8 *) Pin30__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin30_BIT_MASK               (* (reg8 *) Pin30__BIT_MASK)
/* Bypass Enable */
#define Pin30_BYP                    (* (reg8 *) Pin30__BYP)
/* Port wide control signals */                                                   
#define Pin30_CTL                    (* (reg8 *) Pin30__CTL)
/* Drive Modes */
#define Pin30_DM0                    (* (reg8 *) Pin30__DM0) 
#define Pin30_DM1                    (* (reg8 *) Pin30__DM1)
#define Pin30_DM2                    (* (reg8 *) Pin30__DM2) 
/* Input Buffer Disable Override */
#define Pin30_INP_DIS                (* (reg8 *) Pin30__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin30_LCD_COM_SEG            (* (reg8 *) Pin30__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin30_LCD_EN                 (* (reg8 *) Pin30__LCD_EN)
/* Slew Rate Control */
#define Pin30_SLW                    (* (reg8 *) Pin30__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin30_PRTDSI__CAPS_SEL       (* (reg8 *) Pin30__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin30_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin30__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin30_PRTDSI__OE_SEL0        (* (reg8 *) Pin30__PRTDSI__OE_SEL0) 
#define Pin30_PRTDSI__OE_SEL1        (* (reg8 *) Pin30__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin30_PRTDSI__OUT_SEL0       (* (reg8 *) Pin30__PRTDSI__OUT_SEL0) 
#define Pin30_PRTDSI__OUT_SEL1       (* (reg8 *) Pin30__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin30_PRTDSI__SYNC_OUT       (* (reg8 *) Pin30__PRTDSI__SYNC_OUT) 


#if defined(Pin30__INTSTAT)  /* Interrupt Registers */

    #define Pin30_INTSTAT                (* (reg8 *) Pin30__INTSTAT)
    #define Pin30_SNAP                   (* (reg8 *) Pin30__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin30_H */


/* [] END OF FILE */
