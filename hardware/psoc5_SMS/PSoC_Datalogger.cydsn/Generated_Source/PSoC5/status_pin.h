/*******************************************************************************
* File Name: status_pin.h  
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

#if !defined(CY_PINS_status_pin_H) /* Pins status_pin_H */
#define CY_PINS_status_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "status_pin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 status_pin__PORT == 15 && ((status_pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    status_pin_Write(uint8 value) ;
void    status_pin_SetDriveMode(uint8 mode) ;
uint8   status_pin_ReadDataReg(void) ;
uint8   status_pin_Read(void) ;
uint8   status_pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define status_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define status_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define status_pin_DM_RES_UP          PIN_DM_RES_UP
#define status_pin_DM_RES_DWN         PIN_DM_RES_DWN
#define status_pin_DM_OD_LO           PIN_DM_OD_LO
#define status_pin_DM_OD_HI           PIN_DM_OD_HI
#define status_pin_DM_STRONG          PIN_DM_STRONG
#define status_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define status_pin_MASK               status_pin__MASK
#define status_pin_SHIFT              status_pin__SHIFT
#define status_pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define status_pin_PS                     (* (reg8 *) status_pin__PS)
/* Data Register */
#define status_pin_DR                     (* (reg8 *) status_pin__DR)
/* Port Number */
#define status_pin_PRT_NUM                (* (reg8 *) status_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define status_pin_AG                     (* (reg8 *) status_pin__AG)                       
/* Analog MUX bux enable */
#define status_pin_AMUX                   (* (reg8 *) status_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define status_pin_BIE                    (* (reg8 *) status_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define status_pin_BIT_MASK               (* (reg8 *) status_pin__BIT_MASK)
/* Bypass Enable */
#define status_pin_BYP                    (* (reg8 *) status_pin__BYP)
/* Port wide control signals */                                                   
#define status_pin_CTL                    (* (reg8 *) status_pin__CTL)
/* Drive Modes */
#define status_pin_DM0                    (* (reg8 *) status_pin__DM0) 
#define status_pin_DM1                    (* (reg8 *) status_pin__DM1)
#define status_pin_DM2                    (* (reg8 *) status_pin__DM2) 
/* Input Buffer Disable Override */
#define status_pin_INP_DIS                (* (reg8 *) status_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define status_pin_LCD_COM_SEG            (* (reg8 *) status_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define status_pin_LCD_EN                 (* (reg8 *) status_pin__LCD_EN)
/* Slew Rate Control */
#define status_pin_SLW                    (* (reg8 *) status_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define status_pin_PRTDSI__CAPS_SEL       (* (reg8 *) status_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define status_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) status_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define status_pin_PRTDSI__OE_SEL0        (* (reg8 *) status_pin__PRTDSI__OE_SEL0) 
#define status_pin_PRTDSI__OE_SEL1        (* (reg8 *) status_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define status_pin_PRTDSI__OUT_SEL0       (* (reg8 *) status_pin__PRTDSI__OUT_SEL0) 
#define status_pin_PRTDSI__OUT_SEL1       (* (reg8 *) status_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define status_pin_PRTDSI__SYNC_OUT       (* (reg8 *) status_pin__PRTDSI__SYNC_OUT) 


#if defined(status_pin__INTSTAT)  /* Interrupt Registers */

    #define status_pin_INTSTAT                (* (reg8 *) status_pin__INTSTAT)
    #define status_pin_SNAP                   (* (reg8 *) status_pin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_status_pin_H */


/* [] END OF FILE */
