/*******************************************************************************
* File Name: NEOMOTE_1_pwr.h  
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

#if !defined(CY_PINS_NEOMOTE_1_pwr_H) /* Pins NEOMOTE_1_pwr_H */
#define CY_PINS_NEOMOTE_1_pwr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NEOMOTE_1_pwr_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NEOMOTE_1_pwr__PORT == 15 && ((NEOMOTE_1_pwr__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    NEOMOTE_1_pwr_Write(uint8 value) ;
void    NEOMOTE_1_pwr_SetDriveMode(uint8 mode) ;
uint8   NEOMOTE_1_pwr_ReadDataReg(void) ;
uint8   NEOMOTE_1_pwr_Read(void) ;
uint8   NEOMOTE_1_pwr_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NEOMOTE_1_pwr_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define NEOMOTE_1_pwr_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define NEOMOTE_1_pwr_DM_RES_UP          PIN_DM_RES_UP
#define NEOMOTE_1_pwr_DM_RES_DWN         PIN_DM_RES_DWN
#define NEOMOTE_1_pwr_DM_OD_LO           PIN_DM_OD_LO
#define NEOMOTE_1_pwr_DM_OD_HI           PIN_DM_OD_HI
#define NEOMOTE_1_pwr_DM_STRONG          PIN_DM_STRONG
#define NEOMOTE_1_pwr_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define NEOMOTE_1_pwr_MASK               NEOMOTE_1_pwr__MASK
#define NEOMOTE_1_pwr_SHIFT              NEOMOTE_1_pwr__SHIFT
#define NEOMOTE_1_pwr_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NEOMOTE_1_pwr_PS                     (* (reg8 *) NEOMOTE_1_pwr__PS)
/* Data Register */
#define NEOMOTE_1_pwr_DR                     (* (reg8 *) NEOMOTE_1_pwr__DR)
/* Port Number */
#define NEOMOTE_1_pwr_PRT_NUM                (* (reg8 *) NEOMOTE_1_pwr__PRT) 
/* Connect to Analog Globals */                                                  
#define NEOMOTE_1_pwr_AG                     (* (reg8 *) NEOMOTE_1_pwr__AG)                       
/* Analog MUX bux enable */
#define NEOMOTE_1_pwr_AMUX                   (* (reg8 *) NEOMOTE_1_pwr__AMUX) 
/* Bidirectional Enable */                                                        
#define NEOMOTE_1_pwr_BIE                    (* (reg8 *) NEOMOTE_1_pwr__BIE)
/* Bit-mask for Aliased Register Access */
#define NEOMOTE_1_pwr_BIT_MASK               (* (reg8 *) NEOMOTE_1_pwr__BIT_MASK)
/* Bypass Enable */
#define NEOMOTE_1_pwr_BYP                    (* (reg8 *) NEOMOTE_1_pwr__BYP)
/* Port wide control signals */                                                   
#define NEOMOTE_1_pwr_CTL                    (* (reg8 *) NEOMOTE_1_pwr__CTL)
/* Drive Modes */
#define NEOMOTE_1_pwr_DM0                    (* (reg8 *) NEOMOTE_1_pwr__DM0) 
#define NEOMOTE_1_pwr_DM1                    (* (reg8 *) NEOMOTE_1_pwr__DM1)
#define NEOMOTE_1_pwr_DM2                    (* (reg8 *) NEOMOTE_1_pwr__DM2) 
/* Input Buffer Disable Override */
#define NEOMOTE_1_pwr_INP_DIS                (* (reg8 *) NEOMOTE_1_pwr__INP_DIS)
/* LCD Common or Segment Drive */
#define NEOMOTE_1_pwr_LCD_COM_SEG            (* (reg8 *) NEOMOTE_1_pwr__LCD_COM_SEG)
/* Enable Segment LCD */
#define NEOMOTE_1_pwr_LCD_EN                 (* (reg8 *) NEOMOTE_1_pwr__LCD_EN)
/* Slew Rate Control */
#define NEOMOTE_1_pwr_SLW                    (* (reg8 *) NEOMOTE_1_pwr__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NEOMOTE_1_pwr_PRTDSI__CAPS_SEL       (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NEOMOTE_1_pwr_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NEOMOTE_1_pwr_PRTDSI__OE_SEL0        (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__OE_SEL0) 
#define NEOMOTE_1_pwr_PRTDSI__OE_SEL1        (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NEOMOTE_1_pwr_PRTDSI__OUT_SEL0       (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__OUT_SEL0) 
#define NEOMOTE_1_pwr_PRTDSI__OUT_SEL1       (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NEOMOTE_1_pwr_PRTDSI__SYNC_OUT       (* (reg8 *) NEOMOTE_1_pwr__PRTDSI__SYNC_OUT) 


#if defined(NEOMOTE_1_pwr__INTSTAT)  /* Interrupt Registers */

    #define NEOMOTE_1_pwr_INTSTAT                (* (reg8 *) NEOMOTE_1_pwr__INTSTAT)
    #define NEOMOTE_1_pwr_SNAP                   (* (reg8 *) NEOMOTE_1_pwr__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NEOMOTE_1_pwr_H */


/* [] END OF FILE */
