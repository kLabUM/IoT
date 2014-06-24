/*******************************************************************************
* File Name: Temp_Vs.h  
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

#if !defined(CY_PINS_Temp_Vs_H) /* Pins Temp_Vs_H */
#define CY_PINS_Temp_Vs_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp_Vs_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp_Vs__PORT == 15 && ((Temp_Vs__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Temp_Vs_Write(uint8 value) ;
void    Temp_Vs_SetDriveMode(uint8 mode) ;
uint8   Temp_Vs_ReadDataReg(void) ;
uint8   Temp_Vs_Read(void) ;
uint8   Temp_Vs_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Temp_Vs_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Temp_Vs_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Temp_Vs_DM_RES_UP          PIN_DM_RES_UP
#define Temp_Vs_DM_RES_DWN         PIN_DM_RES_DWN
#define Temp_Vs_DM_OD_LO           PIN_DM_OD_LO
#define Temp_Vs_DM_OD_HI           PIN_DM_OD_HI
#define Temp_Vs_DM_STRONG          PIN_DM_STRONG
#define Temp_Vs_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Temp_Vs_MASK               Temp_Vs__MASK
#define Temp_Vs_SHIFT              Temp_Vs__SHIFT
#define Temp_Vs_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp_Vs_PS                     (* (reg8 *) Temp_Vs__PS)
/* Data Register */
#define Temp_Vs_DR                     (* (reg8 *) Temp_Vs__DR)
/* Port Number */
#define Temp_Vs_PRT_NUM                (* (reg8 *) Temp_Vs__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp_Vs_AG                     (* (reg8 *) Temp_Vs__AG)                       
/* Analog MUX bux enable */
#define Temp_Vs_AMUX                   (* (reg8 *) Temp_Vs__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp_Vs_BIE                    (* (reg8 *) Temp_Vs__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp_Vs_BIT_MASK               (* (reg8 *) Temp_Vs__BIT_MASK)
/* Bypass Enable */
#define Temp_Vs_BYP                    (* (reg8 *) Temp_Vs__BYP)
/* Port wide control signals */                                                   
#define Temp_Vs_CTL                    (* (reg8 *) Temp_Vs__CTL)
/* Drive Modes */
#define Temp_Vs_DM0                    (* (reg8 *) Temp_Vs__DM0) 
#define Temp_Vs_DM1                    (* (reg8 *) Temp_Vs__DM1)
#define Temp_Vs_DM2                    (* (reg8 *) Temp_Vs__DM2) 
/* Input Buffer Disable Override */
#define Temp_Vs_INP_DIS                (* (reg8 *) Temp_Vs__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp_Vs_LCD_COM_SEG            (* (reg8 *) Temp_Vs__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp_Vs_LCD_EN                 (* (reg8 *) Temp_Vs__LCD_EN)
/* Slew Rate Control */
#define Temp_Vs_SLW                    (* (reg8 *) Temp_Vs__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp_Vs_PRTDSI__CAPS_SEL       (* (reg8 *) Temp_Vs__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp_Vs_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp_Vs__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp_Vs_PRTDSI__OE_SEL0        (* (reg8 *) Temp_Vs__PRTDSI__OE_SEL0) 
#define Temp_Vs_PRTDSI__OE_SEL1        (* (reg8 *) Temp_Vs__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp_Vs_PRTDSI__OUT_SEL0       (* (reg8 *) Temp_Vs__PRTDSI__OUT_SEL0) 
#define Temp_Vs_PRTDSI__OUT_SEL1       (* (reg8 *) Temp_Vs__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp_Vs_PRTDSI__SYNC_OUT       (* (reg8 *) Temp_Vs__PRTDSI__SYNC_OUT) 


#if defined(Temp_Vs__INTSTAT)  /* Interrupt Registers */

    #define Temp_Vs_INTSTAT                (* (reg8 *) Temp_Vs__INTSTAT)
    #define Temp_Vs_SNAP                   (* (reg8 *) Temp_Vs__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp_Vs_H */


/* [] END OF FILE */
