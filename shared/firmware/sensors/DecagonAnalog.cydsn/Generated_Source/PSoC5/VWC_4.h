/*******************************************************************************
* File Name: VWC_4.h  
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

#if !defined(CY_PINS_VWC_4_H) /* Pins VWC_4_H */
#define CY_PINS_VWC_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VWC_4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VWC_4__PORT == 15 && ((VWC_4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VWC_4_Write(uint8 value);
void    VWC_4_SetDriveMode(uint8 mode);
uint8   VWC_4_ReadDataReg(void);
uint8   VWC_4_Read(void);
void    VWC_4_SetInterruptMode(uint16 position, uint16 mode);
uint8   VWC_4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VWC_4_SetDriveMode() function.
     *  @{
     */
        #define VWC_4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VWC_4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VWC_4_DM_RES_UP          PIN_DM_RES_UP
        #define VWC_4_DM_RES_DWN         PIN_DM_RES_DWN
        #define VWC_4_DM_OD_LO           PIN_DM_OD_LO
        #define VWC_4_DM_OD_HI           PIN_DM_OD_HI
        #define VWC_4_DM_STRONG          PIN_DM_STRONG
        #define VWC_4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VWC_4_MASK               VWC_4__MASK
#define VWC_4_SHIFT              VWC_4__SHIFT
#define VWC_4_WIDTH              1u

/* Interrupt constants */
#if defined(VWC_4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VWC_4_SetInterruptMode() function.
     *  @{
     */
        #define VWC_4_INTR_NONE      (uint16)(0x0000u)
        #define VWC_4_INTR_RISING    (uint16)(0x0001u)
        #define VWC_4_INTR_FALLING   (uint16)(0x0002u)
        #define VWC_4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VWC_4_INTR_MASK      (0x01u) 
#endif /* (VWC_4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VWC_4_PS                     (* (reg8 *) VWC_4__PS)
/* Data Register */
#define VWC_4_DR                     (* (reg8 *) VWC_4__DR)
/* Port Number */
#define VWC_4_PRT_NUM                (* (reg8 *) VWC_4__PRT) 
/* Connect to Analog Globals */                                                  
#define VWC_4_AG                     (* (reg8 *) VWC_4__AG)                       
/* Analog MUX bux enable */
#define VWC_4_AMUX                   (* (reg8 *) VWC_4__AMUX) 
/* Bidirectional Enable */                                                        
#define VWC_4_BIE                    (* (reg8 *) VWC_4__BIE)
/* Bit-mask for Aliased Register Access */
#define VWC_4_BIT_MASK               (* (reg8 *) VWC_4__BIT_MASK)
/* Bypass Enable */
#define VWC_4_BYP                    (* (reg8 *) VWC_4__BYP)
/* Port wide control signals */                                                   
#define VWC_4_CTL                    (* (reg8 *) VWC_4__CTL)
/* Drive Modes */
#define VWC_4_DM0                    (* (reg8 *) VWC_4__DM0) 
#define VWC_4_DM1                    (* (reg8 *) VWC_4__DM1)
#define VWC_4_DM2                    (* (reg8 *) VWC_4__DM2) 
/* Input Buffer Disable Override */
#define VWC_4_INP_DIS                (* (reg8 *) VWC_4__INP_DIS)
/* LCD Common or Segment Drive */
#define VWC_4_LCD_COM_SEG            (* (reg8 *) VWC_4__LCD_COM_SEG)
/* Enable Segment LCD */
#define VWC_4_LCD_EN                 (* (reg8 *) VWC_4__LCD_EN)
/* Slew Rate Control */
#define VWC_4_SLW                    (* (reg8 *) VWC_4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VWC_4_PRTDSI__CAPS_SEL       (* (reg8 *) VWC_4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VWC_4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VWC_4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VWC_4_PRTDSI__OE_SEL0        (* (reg8 *) VWC_4__PRTDSI__OE_SEL0) 
#define VWC_4_PRTDSI__OE_SEL1        (* (reg8 *) VWC_4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VWC_4_PRTDSI__OUT_SEL0       (* (reg8 *) VWC_4__PRTDSI__OUT_SEL0) 
#define VWC_4_PRTDSI__OUT_SEL1       (* (reg8 *) VWC_4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VWC_4_PRTDSI__SYNC_OUT       (* (reg8 *) VWC_4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VWC_4__SIO_CFG)
    #define VWC_4_SIO_HYST_EN        (* (reg8 *) VWC_4__SIO_HYST_EN)
    #define VWC_4_SIO_REG_HIFREQ     (* (reg8 *) VWC_4__SIO_REG_HIFREQ)
    #define VWC_4_SIO_CFG            (* (reg8 *) VWC_4__SIO_CFG)
    #define VWC_4_SIO_DIFF           (* (reg8 *) VWC_4__SIO_DIFF)
#endif /* (VWC_4__SIO_CFG) */

/* Interrupt Registers */
#if defined(VWC_4__INTSTAT)
    #define VWC_4_INTSTAT            (* (reg8 *) VWC_4__INTSTAT)
    #define VWC_4_SNAP               (* (reg8 *) VWC_4__SNAP)
    
	#define VWC_4_0_INTTYPE_REG 		(* (reg8 *) VWC_4__0__INTTYPE)
#endif /* (VWC_4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VWC_4_H */


/* [] END OF FILE */
