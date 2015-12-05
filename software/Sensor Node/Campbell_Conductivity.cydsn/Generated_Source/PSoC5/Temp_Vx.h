/*******************************************************************************
* File Name: Temp_Vx.h  
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

#if !defined(CY_PINS_Temp_Vx_H) /* Pins Temp_Vx_H */
#define CY_PINS_Temp_Vx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp_Vx_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp_Vx__PORT == 15 && ((Temp_Vx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Temp_Vx_Write(uint8 value) ;
void    Temp_Vx_SetDriveMode(uint8 mode) ;
uint8   Temp_Vx_ReadDataReg(void) ;
uint8   Temp_Vx_Read(void) ;
uint8   Temp_Vx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Temp_Vx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Temp_Vx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Temp_Vx_DM_RES_UP          PIN_DM_RES_UP
#define Temp_Vx_DM_RES_DWN         PIN_DM_RES_DWN
#define Temp_Vx_DM_OD_LO           PIN_DM_OD_LO
#define Temp_Vx_DM_OD_HI           PIN_DM_OD_HI
#define Temp_Vx_DM_STRONG          PIN_DM_STRONG
#define Temp_Vx_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Temp_Vx_MASK               Temp_Vx__MASK
#define Temp_Vx_SHIFT              Temp_Vx__SHIFT
#define Temp_Vx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp_Vx_PS                     (* (reg8 *) Temp_Vx__PS)
/* Data Register */
#define Temp_Vx_DR                     (* (reg8 *) Temp_Vx__DR)
/* Port Number */
#define Temp_Vx_PRT_NUM                (* (reg8 *) Temp_Vx__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp_Vx_AG                     (* (reg8 *) Temp_Vx__AG)                       
/* Analog MUX bux enable */
#define Temp_Vx_AMUX                   (* (reg8 *) Temp_Vx__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp_Vx_BIE                    (* (reg8 *) Temp_Vx__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp_Vx_BIT_MASK               (* (reg8 *) Temp_Vx__BIT_MASK)
/* Bypass Enable */
#define Temp_Vx_BYP                    (* (reg8 *) Temp_Vx__BYP)
/* Port wide control signals */                                                   
#define Temp_Vx_CTL                    (* (reg8 *) Temp_Vx__CTL)
/* Drive Modes */
#define Temp_Vx_DM0                    (* (reg8 *) Temp_Vx__DM0) 
#define Temp_Vx_DM1                    (* (reg8 *) Temp_Vx__DM1)
#define Temp_Vx_DM2                    (* (reg8 *) Temp_Vx__DM2) 
/* Input Buffer Disable Override */
#define Temp_Vx_INP_DIS                (* (reg8 *) Temp_Vx__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp_Vx_LCD_COM_SEG            (* (reg8 *) Temp_Vx__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp_Vx_LCD_EN                 (* (reg8 *) Temp_Vx__LCD_EN)
/* Slew Rate Control */
#define Temp_Vx_SLW                    (* (reg8 *) Temp_Vx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp_Vx_PRTDSI__CAPS_SEL       (* (reg8 *) Temp_Vx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp_Vx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp_Vx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp_Vx_PRTDSI__OE_SEL0        (* (reg8 *) Temp_Vx__PRTDSI__OE_SEL0) 
#define Temp_Vx_PRTDSI__OE_SEL1        (* (reg8 *) Temp_Vx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp_Vx_PRTDSI__OUT_SEL0       (* (reg8 *) Temp_Vx__PRTDSI__OUT_SEL0) 
#define Temp_Vx_PRTDSI__OUT_SEL1       (* (reg8 *) Temp_Vx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp_Vx_PRTDSI__SYNC_OUT       (* (reg8 *) Temp_Vx__PRTDSI__SYNC_OUT) 


#if defined(Temp_Vx__INTSTAT)  /* Interrupt Registers */

    #define Temp_Vx_INTSTAT                (* (reg8 *) Temp_Vx__INTSTAT)
    #define Temp_Vx_SNAP                   (* (reg8 *) Temp_Vx__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp_Vx_H */


/* [] END OF FILE */
