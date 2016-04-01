/*******************************************************************************
* File Name: Telit_RST.h  
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

#if !defined(CY_PINS_Telit_RST_H) /* Pins Telit_RST_H */
#define CY_PINS_Telit_RST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Telit_RST_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Telit_RST__PORT == 15 && ((Telit_RST__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Telit_RST_Write(uint8 value) ;
void    Telit_RST_SetDriveMode(uint8 mode) ;
uint8   Telit_RST_ReadDataReg(void) ;
uint8   Telit_RST_Read(void) ;
uint8   Telit_RST_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Telit_RST_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Telit_RST_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Telit_RST_DM_RES_UP          PIN_DM_RES_UP
#define Telit_RST_DM_RES_DWN         PIN_DM_RES_DWN
#define Telit_RST_DM_OD_LO           PIN_DM_OD_LO
#define Telit_RST_DM_OD_HI           PIN_DM_OD_HI
#define Telit_RST_DM_STRONG          PIN_DM_STRONG
#define Telit_RST_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Telit_RST_MASK               Telit_RST__MASK
#define Telit_RST_SHIFT              Telit_RST__SHIFT
#define Telit_RST_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Telit_RST_PS                     (* (reg8 *) Telit_RST__PS)
/* Data Register */
#define Telit_RST_DR                     (* (reg8 *) Telit_RST__DR)
/* Port Number */
#define Telit_RST_PRT_NUM                (* (reg8 *) Telit_RST__PRT) 
/* Connect to Analog Globals */                                                  
#define Telit_RST_AG                     (* (reg8 *) Telit_RST__AG)                       
/* Analog MUX bux enable */
#define Telit_RST_AMUX                   (* (reg8 *) Telit_RST__AMUX) 
/* Bidirectional Enable */                                                        
#define Telit_RST_BIE                    (* (reg8 *) Telit_RST__BIE)
/* Bit-mask for Aliased Register Access */
#define Telit_RST_BIT_MASK               (* (reg8 *) Telit_RST__BIT_MASK)
/* Bypass Enable */
#define Telit_RST_BYP                    (* (reg8 *) Telit_RST__BYP)
/* Port wide control signals */                                                   
#define Telit_RST_CTL                    (* (reg8 *) Telit_RST__CTL)
/* Drive Modes */
#define Telit_RST_DM0                    (* (reg8 *) Telit_RST__DM0) 
#define Telit_RST_DM1                    (* (reg8 *) Telit_RST__DM1)
#define Telit_RST_DM2                    (* (reg8 *) Telit_RST__DM2) 
/* Input Buffer Disable Override */
#define Telit_RST_INP_DIS                (* (reg8 *) Telit_RST__INP_DIS)
/* LCD Common or Segment Drive */
#define Telit_RST_LCD_COM_SEG            (* (reg8 *) Telit_RST__LCD_COM_SEG)
/* Enable Segment LCD */
#define Telit_RST_LCD_EN                 (* (reg8 *) Telit_RST__LCD_EN)
/* Slew Rate Control */
#define Telit_RST_SLW                    (* (reg8 *) Telit_RST__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Telit_RST_PRTDSI__CAPS_SEL       (* (reg8 *) Telit_RST__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Telit_RST_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Telit_RST__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Telit_RST_PRTDSI__OE_SEL0        (* (reg8 *) Telit_RST__PRTDSI__OE_SEL0) 
#define Telit_RST_PRTDSI__OE_SEL1        (* (reg8 *) Telit_RST__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Telit_RST_PRTDSI__OUT_SEL0       (* (reg8 *) Telit_RST__PRTDSI__OUT_SEL0) 
#define Telit_RST_PRTDSI__OUT_SEL1       (* (reg8 *) Telit_RST__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Telit_RST_PRTDSI__SYNC_OUT       (* (reg8 *) Telit_RST__PRTDSI__SYNC_OUT) 


#if defined(Telit_RST__INTSTAT)  /* Interrupt Registers */

    #define Telit_RST_INTSTAT                (* (reg8 *) Telit_RST__INTSTAT)
    #define Telit_RST_SNAP                   (* (reg8 *) Telit_RST__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Telit_RST_H */


/* [] END OF FILE */
