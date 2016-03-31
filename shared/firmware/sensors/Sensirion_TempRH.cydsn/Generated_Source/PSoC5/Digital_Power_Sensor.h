/*******************************************************************************
* File Name: Digital_Power_Sensor.h  
* Version 2.0
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

#if !defined(CY_PINS_Digital_Power_Sensor_H) /* Pins Digital_Power_Sensor_H */
#define CY_PINS_Digital_Power_Sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Digital_Power_Sensor_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Digital_Power_Sensor__PORT == 15 && ((Digital_Power_Sensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Digital_Power_Sensor_Write(uint8 value) ;
void    Digital_Power_Sensor_SetDriveMode(uint8 mode) ;
uint8   Digital_Power_Sensor_ReadDataReg(void) ;
uint8   Digital_Power_Sensor_Read(void) ;
uint8   Digital_Power_Sensor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Digital_Power_Sensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Digital_Power_Sensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Digital_Power_Sensor_DM_RES_UP          PIN_DM_RES_UP
#define Digital_Power_Sensor_DM_RES_DWN         PIN_DM_RES_DWN
#define Digital_Power_Sensor_DM_OD_LO           PIN_DM_OD_LO
#define Digital_Power_Sensor_DM_OD_HI           PIN_DM_OD_HI
#define Digital_Power_Sensor_DM_STRONG          PIN_DM_STRONG
#define Digital_Power_Sensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Digital_Power_Sensor_MASK               Digital_Power_Sensor__MASK
#define Digital_Power_Sensor_SHIFT              Digital_Power_Sensor__SHIFT
#define Digital_Power_Sensor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Digital_Power_Sensor_PS                     (* (reg8 *) Digital_Power_Sensor__PS)
/* Data Register */
#define Digital_Power_Sensor_DR                     (* (reg8 *) Digital_Power_Sensor__DR)
/* Port Number */
#define Digital_Power_Sensor_PRT_NUM                (* (reg8 *) Digital_Power_Sensor__PRT) 
/* Connect to Analog Globals */                                                  
#define Digital_Power_Sensor_AG                     (* (reg8 *) Digital_Power_Sensor__AG)                       
/* Analog MUX bux enable */
#define Digital_Power_Sensor_AMUX                   (* (reg8 *) Digital_Power_Sensor__AMUX) 
/* Bidirectional Enable */                                                        
#define Digital_Power_Sensor_BIE                    (* (reg8 *) Digital_Power_Sensor__BIE)
/* Bit-mask for Aliased Register Access */
#define Digital_Power_Sensor_BIT_MASK               (* (reg8 *) Digital_Power_Sensor__BIT_MASK)
/* Bypass Enable */
#define Digital_Power_Sensor_BYP                    (* (reg8 *) Digital_Power_Sensor__BYP)
/* Port wide control signals */                                                   
#define Digital_Power_Sensor_CTL                    (* (reg8 *) Digital_Power_Sensor__CTL)
/* Drive Modes */
#define Digital_Power_Sensor_DM0                    (* (reg8 *) Digital_Power_Sensor__DM0) 
#define Digital_Power_Sensor_DM1                    (* (reg8 *) Digital_Power_Sensor__DM1)
#define Digital_Power_Sensor_DM2                    (* (reg8 *) Digital_Power_Sensor__DM2) 
/* Input Buffer Disable Override */
#define Digital_Power_Sensor_INP_DIS                (* (reg8 *) Digital_Power_Sensor__INP_DIS)
/* LCD Common or Segment Drive */
#define Digital_Power_Sensor_LCD_COM_SEG            (* (reg8 *) Digital_Power_Sensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Digital_Power_Sensor_LCD_EN                 (* (reg8 *) Digital_Power_Sensor__LCD_EN)
/* Slew Rate Control */
#define Digital_Power_Sensor_SLW                    (* (reg8 *) Digital_Power_Sensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Digital_Power_Sensor_PRTDSI__CAPS_SEL       (* (reg8 *) Digital_Power_Sensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Digital_Power_Sensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Digital_Power_Sensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Digital_Power_Sensor_PRTDSI__OE_SEL0        (* (reg8 *) Digital_Power_Sensor__PRTDSI__OE_SEL0) 
#define Digital_Power_Sensor_PRTDSI__OE_SEL1        (* (reg8 *) Digital_Power_Sensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Digital_Power_Sensor_PRTDSI__OUT_SEL0       (* (reg8 *) Digital_Power_Sensor__PRTDSI__OUT_SEL0) 
#define Digital_Power_Sensor_PRTDSI__OUT_SEL1       (* (reg8 *) Digital_Power_Sensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Digital_Power_Sensor_PRTDSI__SYNC_OUT       (* (reg8 *) Digital_Power_Sensor__PRTDSI__SYNC_OUT) 


#if defined(Digital_Power_Sensor__INTSTAT)  /* Interrupt Registers */

    #define Digital_Power_Sensor_INTSTAT                (* (reg8 *) Digital_Power_Sensor__INTSTAT)
    #define Digital_Power_Sensor_SNAP                   (* (reg8 *) Digital_Power_Sensor__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Digital_Power_Sensor_H */


/* [] END OF FILE */
