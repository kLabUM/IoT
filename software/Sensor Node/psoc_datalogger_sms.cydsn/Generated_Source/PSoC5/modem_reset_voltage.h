/*******************************************************************************
* File Name: modem_reset_voltage.h  
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

#if !defined(CY_PINS_modem_reset_voltage_H) /* Pins modem_reset_voltage_H */
#define CY_PINS_modem_reset_voltage_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "modem_reset_voltage_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 modem_reset_voltage__PORT == 15 && ((modem_reset_voltage__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    modem_reset_voltage_Write(uint8 value) ;
void    modem_reset_voltage_SetDriveMode(uint8 mode) ;
uint8   modem_reset_voltage_ReadDataReg(void) ;
uint8   modem_reset_voltage_Read(void) ;
uint8   modem_reset_voltage_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define modem_reset_voltage_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define modem_reset_voltage_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define modem_reset_voltage_DM_RES_UP          PIN_DM_RES_UP
#define modem_reset_voltage_DM_RES_DWN         PIN_DM_RES_DWN
#define modem_reset_voltage_DM_OD_LO           PIN_DM_OD_LO
#define modem_reset_voltage_DM_OD_HI           PIN_DM_OD_HI
#define modem_reset_voltage_DM_STRONG          PIN_DM_STRONG
#define modem_reset_voltage_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define modem_reset_voltage_MASK               modem_reset_voltage__MASK
#define modem_reset_voltage_SHIFT              modem_reset_voltage__SHIFT
#define modem_reset_voltage_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define modem_reset_voltage_PS                     (* (reg8 *) modem_reset_voltage__PS)
/* Data Register */
#define modem_reset_voltage_DR                     (* (reg8 *) modem_reset_voltage__DR)
/* Port Number */
#define modem_reset_voltage_PRT_NUM                (* (reg8 *) modem_reset_voltage__PRT) 
/* Connect to Analog Globals */                                                  
#define modem_reset_voltage_AG                     (* (reg8 *) modem_reset_voltage__AG)                       
/* Analog MUX bux enable */
#define modem_reset_voltage_AMUX                   (* (reg8 *) modem_reset_voltage__AMUX) 
/* Bidirectional Enable */                                                        
#define modem_reset_voltage_BIE                    (* (reg8 *) modem_reset_voltage__BIE)
/* Bit-mask for Aliased Register Access */
#define modem_reset_voltage_BIT_MASK               (* (reg8 *) modem_reset_voltage__BIT_MASK)
/* Bypass Enable */
#define modem_reset_voltage_BYP                    (* (reg8 *) modem_reset_voltage__BYP)
/* Port wide control signals */                                                   
#define modem_reset_voltage_CTL                    (* (reg8 *) modem_reset_voltage__CTL)
/* Drive Modes */
#define modem_reset_voltage_DM0                    (* (reg8 *) modem_reset_voltage__DM0) 
#define modem_reset_voltage_DM1                    (* (reg8 *) modem_reset_voltage__DM1)
#define modem_reset_voltage_DM2                    (* (reg8 *) modem_reset_voltage__DM2) 
/* Input Buffer Disable Override */
#define modem_reset_voltage_INP_DIS                (* (reg8 *) modem_reset_voltage__INP_DIS)
/* LCD Common or Segment Drive */
#define modem_reset_voltage_LCD_COM_SEG            (* (reg8 *) modem_reset_voltage__LCD_COM_SEG)
/* Enable Segment LCD */
#define modem_reset_voltage_LCD_EN                 (* (reg8 *) modem_reset_voltage__LCD_EN)
/* Slew Rate Control */
#define modem_reset_voltage_SLW                    (* (reg8 *) modem_reset_voltage__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define modem_reset_voltage_PRTDSI__CAPS_SEL       (* (reg8 *) modem_reset_voltage__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define modem_reset_voltage_PRTDSI__DBL_SYNC_IN    (* (reg8 *) modem_reset_voltage__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define modem_reset_voltage_PRTDSI__OE_SEL0        (* (reg8 *) modem_reset_voltage__PRTDSI__OE_SEL0) 
#define modem_reset_voltage_PRTDSI__OE_SEL1        (* (reg8 *) modem_reset_voltage__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define modem_reset_voltage_PRTDSI__OUT_SEL0       (* (reg8 *) modem_reset_voltage__PRTDSI__OUT_SEL0) 
#define modem_reset_voltage_PRTDSI__OUT_SEL1       (* (reg8 *) modem_reset_voltage__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define modem_reset_voltage_PRTDSI__SYNC_OUT       (* (reg8 *) modem_reset_voltage__PRTDSI__SYNC_OUT) 


#if defined(modem_reset_voltage__INTSTAT)  /* Interrupt Registers */

    #define modem_reset_voltage_INTSTAT                (* (reg8 *) modem_reset_voltage__INTSTAT)
    #define modem_reset_voltage_SNAP                   (* (reg8 *) modem_reset_voltage__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_modem_reset_voltage_H */


/* [] END OF FILE */
