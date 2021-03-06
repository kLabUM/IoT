/*******************************************************************************
* File Name: voltage_pin.h  
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

#if !defined(CY_PINS_voltage_pin_H) /* Pins voltage_pin_H */
#define CY_PINS_voltage_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "voltage_pin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 voltage_pin__PORT == 15 && ((voltage_pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    voltage_pin_Write(uint8 value) ;
void    voltage_pin_SetDriveMode(uint8 mode) ;
uint8   voltage_pin_ReadDataReg(void) ;
uint8   voltage_pin_Read(void) ;
uint8   voltage_pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define voltage_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define voltage_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define voltage_pin_DM_RES_UP          PIN_DM_RES_UP
#define voltage_pin_DM_RES_DWN         PIN_DM_RES_DWN
#define voltage_pin_DM_OD_LO           PIN_DM_OD_LO
#define voltage_pin_DM_OD_HI           PIN_DM_OD_HI
#define voltage_pin_DM_STRONG          PIN_DM_STRONG
#define voltage_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define voltage_pin_MASK               voltage_pin__MASK
#define voltage_pin_SHIFT              voltage_pin__SHIFT
#define voltage_pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define voltage_pin_PS                     (* (reg8 *) voltage_pin__PS)
/* Data Register */
#define voltage_pin_DR                     (* (reg8 *) voltage_pin__DR)
/* Port Number */
#define voltage_pin_PRT_NUM                (* (reg8 *) voltage_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define voltage_pin_AG                     (* (reg8 *) voltage_pin__AG)                       
/* Analog MUX bux enable */
#define voltage_pin_AMUX                   (* (reg8 *) voltage_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define voltage_pin_BIE                    (* (reg8 *) voltage_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define voltage_pin_BIT_MASK               (* (reg8 *) voltage_pin__BIT_MASK)
/* Bypass Enable */
#define voltage_pin_BYP                    (* (reg8 *) voltage_pin__BYP)
/* Port wide control signals */                                                   
#define voltage_pin_CTL                    (* (reg8 *) voltage_pin__CTL)
/* Drive Modes */
#define voltage_pin_DM0                    (* (reg8 *) voltage_pin__DM0) 
#define voltage_pin_DM1                    (* (reg8 *) voltage_pin__DM1)
#define voltage_pin_DM2                    (* (reg8 *) voltage_pin__DM2) 
/* Input Buffer Disable Override */
#define voltage_pin_INP_DIS                (* (reg8 *) voltage_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define voltage_pin_LCD_COM_SEG            (* (reg8 *) voltage_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define voltage_pin_LCD_EN                 (* (reg8 *) voltage_pin__LCD_EN)
/* Slew Rate Control */
#define voltage_pin_SLW                    (* (reg8 *) voltage_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define voltage_pin_PRTDSI__CAPS_SEL       (* (reg8 *) voltage_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define voltage_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) voltage_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define voltage_pin_PRTDSI__OE_SEL0        (* (reg8 *) voltage_pin__PRTDSI__OE_SEL0) 
#define voltage_pin_PRTDSI__OE_SEL1        (* (reg8 *) voltage_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define voltage_pin_PRTDSI__OUT_SEL0       (* (reg8 *) voltage_pin__PRTDSI__OUT_SEL0) 
#define voltage_pin_PRTDSI__OUT_SEL1       (* (reg8 *) voltage_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define voltage_pin_PRTDSI__SYNC_OUT       (* (reg8 *) voltage_pin__PRTDSI__SYNC_OUT) 


#if defined(voltage_pin__INTSTAT)  /* Interrupt Registers */

    #define voltage_pin_INTSTAT                (* (reg8 *) voltage_pin__INTSTAT)
    #define voltage_pin_SNAP                   (* (reg8 *) voltage_pin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_voltage_pin_H */


/* [] END OF FILE */
