/*******************************************************************************
* File Name: Maxbotix_Power.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Maxbotix_Power_H) /* Pins Maxbotix_Power_H */
#define CY_PINS_Maxbotix_Power_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Maxbotix_Power_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Maxbotix_Power__PORT == 15 && ((Maxbotix_Power__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Maxbotix_Power_Write(uint8 value);
void    Maxbotix_Power_SetDriveMode(uint8 mode);
uint8   Maxbotix_Power_ReadDataReg(void);
uint8   Maxbotix_Power_Read(void);
void    Maxbotix_Power_SetInterruptMode(uint16 position, uint16 mode);
uint8   Maxbotix_Power_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Maxbotix_Power_SetDriveMode() function.
     *  @{
     */
        #define Maxbotix_Power_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Maxbotix_Power_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Maxbotix_Power_DM_RES_UP          PIN_DM_RES_UP
        #define Maxbotix_Power_DM_RES_DWN         PIN_DM_RES_DWN
        #define Maxbotix_Power_DM_OD_LO           PIN_DM_OD_LO
        #define Maxbotix_Power_DM_OD_HI           PIN_DM_OD_HI
        #define Maxbotix_Power_DM_STRONG          PIN_DM_STRONG
        #define Maxbotix_Power_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Maxbotix_Power_MASK               Maxbotix_Power__MASK
#define Maxbotix_Power_SHIFT              Maxbotix_Power__SHIFT
#define Maxbotix_Power_WIDTH              1u

/* Interrupt constants */
#if defined(Maxbotix_Power__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Maxbotix_Power_SetInterruptMode() function.
     *  @{
     */
        #define Maxbotix_Power_INTR_NONE      (uint16)(0x0000u)
        #define Maxbotix_Power_INTR_RISING    (uint16)(0x0001u)
        #define Maxbotix_Power_INTR_FALLING   (uint16)(0x0002u)
        #define Maxbotix_Power_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Maxbotix_Power_INTR_MASK      (0x01u) 
#endif /* (Maxbotix_Power__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Maxbotix_Power_PS                     (* (reg8 *) Maxbotix_Power__PS)
/* Data Register */
#define Maxbotix_Power_DR                     (* (reg8 *) Maxbotix_Power__DR)
/* Port Number */
#define Maxbotix_Power_PRT_NUM                (* (reg8 *) Maxbotix_Power__PRT) 
/* Connect to Analog Globals */                                                  
#define Maxbotix_Power_AG                     (* (reg8 *) Maxbotix_Power__AG)                       
/* Analog MUX bux enable */
#define Maxbotix_Power_AMUX                   (* (reg8 *) Maxbotix_Power__AMUX) 
/* Bidirectional Enable */                                                        
#define Maxbotix_Power_BIE                    (* (reg8 *) Maxbotix_Power__BIE)
/* Bit-mask for Aliased Register Access */
#define Maxbotix_Power_BIT_MASK               (* (reg8 *) Maxbotix_Power__BIT_MASK)
/* Bypass Enable */
#define Maxbotix_Power_BYP                    (* (reg8 *) Maxbotix_Power__BYP)
/* Port wide control signals */                                                   
#define Maxbotix_Power_CTL                    (* (reg8 *) Maxbotix_Power__CTL)
/* Drive Modes */
#define Maxbotix_Power_DM0                    (* (reg8 *) Maxbotix_Power__DM0) 
#define Maxbotix_Power_DM1                    (* (reg8 *) Maxbotix_Power__DM1)
#define Maxbotix_Power_DM2                    (* (reg8 *) Maxbotix_Power__DM2) 
/* Input Buffer Disable Override */
#define Maxbotix_Power_INP_DIS                (* (reg8 *) Maxbotix_Power__INP_DIS)
/* LCD Common or Segment Drive */
#define Maxbotix_Power_LCD_COM_SEG            (* (reg8 *) Maxbotix_Power__LCD_COM_SEG)
/* Enable Segment LCD */
#define Maxbotix_Power_LCD_EN                 (* (reg8 *) Maxbotix_Power__LCD_EN)
/* Slew Rate Control */
#define Maxbotix_Power_SLW                    (* (reg8 *) Maxbotix_Power__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Maxbotix_Power_PRTDSI__CAPS_SEL       (* (reg8 *) Maxbotix_Power__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Maxbotix_Power_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Maxbotix_Power__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Maxbotix_Power_PRTDSI__OE_SEL0        (* (reg8 *) Maxbotix_Power__PRTDSI__OE_SEL0) 
#define Maxbotix_Power_PRTDSI__OE_SEL1        (* (reg8 *) Maxbotix_Power__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Maxbotix_Power_PRTDSI__OUT_SEL0       (* (reg8 *) Maxbotix_Power__PRTDSI__OUT_SEL0) 
#define Maxbotix_Power_PRTDSI__OUT_SEL1       (* (reg8 *) Maxbotix_Power__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Maxbotix_Power_PRTDSI__SYNC_OUT       (* (reg8 *) Maxbotix_Power__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Maxbotix_Power__SIO_CFG)
    #define Maxbotix_Power_SIO_HYST_EN        (* (reg8 *) Maxbotix_Power__SIO_HYST_EN)
    #define Maxbotix_Power_SIO_REG_HIFREQ     (* (reg8 *) Maxbotix_Power__SIO_REG_HIFREQ)
    #define Maxbotix_Power_SIO_CFG            (* (reg8 *) Maxbotix_Power__SIO_CFG)
    #define Maxbotix_Power_SIO_DIFF           (* (reg8 *) Maxbotix_Power__SIO_DIFF)
#endif /* (Maxbotix_Power__SIO_CFG) */

/* Interrupt Registers */
#if defined(Maxbotix_Power__INTSTAT)
    #define Maxbotix_Power_INTSTAT            (* (reg8 *) Maxbotix_Power__INTSTAT)
    #define Maxbotix_Power_SNAP               (* (reg8 *) Maxbotix_Power__SNAP)
    
	#define Maxbotix_Power_0_INTTYPE_REG 		(* (reg8 *) Maxbotix_Power__0__INTTYPE)
#endif /* (Maxbotix_Power__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Maxbotix_Power_H */


/* [] END OF FILE */
