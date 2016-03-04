/*******************************************************************************
* File Name: pump_active.h  
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

#if !defined(CY_PINS_pump_active_H) /* Pins pump_active_H */
#define CY_PINS_pump_active_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pump_active_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pump_active__PORT == 15 && ((pump_active__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pump_active_Write(uint8 value) ;
void    pump_active_SetDriveMode(uint8 mode) ;
uint8   pump_active_ReadDataReg(void) ;
uint8   pump_active_Read(void) ;
uint8   pump_active_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pump_active_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pump_active_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pump_active_DM_RES_UP          PIN_DM_RES_UP
#define pump_active_DM_RES_DWN         PIN_DM_RES_DWN
#define pump_active_DM_OD_LO           PIN_DM_OD_LO
#define pump_active_DM_OD_HI           PIN_DM_OD_HI
#define pump_active_DM_STRONG          PIN_DM_STRONG
#define pump_active_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pump_active_MASK               pump_active__MASK
#define pump_active_SHIFT              pump_active__SHIFT
#define pump_active_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pump_active_PS                     (* (reg8 *) pump_active__PS)
/* Data Register */
#define pump_active_DR                     (* (reg8 *) pump_active__DR)
/* Port Number */
#define pump_active_PRT_NUM                (* (reg8 *) pump_active__PRT) 
/* Connect to Analog Globals */                                                  
#define pump_active_AG                     (* (reg8 *) pump_active__AG)                       
/* Analog MUX bux enable */
#define pump_active_AMUX                   (* (reg8 *) pump_active__AMUX) 
/* Bidirectional Enable */                                                        
#define pump_active_BIE                    (* (reg8 *) pump_active__BIE)
/* Bit-mask for Aliased Register Access */
#define pump_active_BIT_MASK               (* (reg8 *) pump_active__BIT_MASK)
/* Bypass Enable */
#define pump_active_BYP                    (* (reg8 *) pump_active__BYP)
/* Port wide control signals */                                                   
#define pump_active_CTL                    (* (reg8 *) pump_active__CTL)
/* Drive Modes */
#define pump_active_DM0                    (* (reg8 *) pump_active__DM0) 
#define pump_active_DM1                    (* (reg8 *) pump_active__DM1)
#define pump_active_DM2                    (* (reg8 *) pump_active__DM2) 
/* Input Buffer Disable Override */
#define pump_active_INP_DIS                (* (reg8 *) pump_active__INP_DIS)
/* LCD Common or Segment Drive */
#define pump_active_LCD_COM_SEG            (* (reg8 *) pump_active__LCD_COM_SEG)
/* Enable Segment LCD */
#define pump_active_LCD_EN                 (* (reg8 *) pump_active__LCD_EN)
/* Slew Rate Control */
#define pump_active_SLW                    (* (reg8 *) pump_active__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pump_active_PRTDSI__CAPS_SEL       (* (reg8 *) pump_active__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pump_active_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pump_active__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pump_active_PRTDSI__OE_SEL0        (* (reg8 *) pump_active__PRTDSI__OE_SEL0) 
#define pump_active_PRTDSI__OE_SEL1        (* (reg8 *) pump_active__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pump_active_PRTDSI__OUT_SEL0       (* (reg8 *) pump_active__PRTDSI__OUT_SEL0) 
#define pump_active_PRTDSI__OUT_SEL1       (* (reg8 *) pump_active__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pump_active_PRTDSI__SYNC_OUT       (* (reg8 *) pump_active__PRTDSI__SYNC_OUT) 


#if defined(pump_active__INTSTAT)  /* Interrupt Registers */

    #define pump_active_INTSTAT                (* (reg8 *) pump_active__INTSTAT)
    #define pump_active_SNAP                   (* (reg8 *) pump_active__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pump_active_H */


/* [] END OF FILE */
