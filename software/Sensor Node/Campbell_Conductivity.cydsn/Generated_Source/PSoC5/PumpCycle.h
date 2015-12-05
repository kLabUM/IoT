/*******************************************************************************
* File Name: PumpCycle.c
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMP_PumpCycle_H) 
#define CY_COMP_PumpCycle_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h" 


#define PumpCycle_RECALMODE (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Comp_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
   /* uint8 compCRReg; */
}PumpCycle_backupStruct;

#if (CY_PSOC5A)
    /* Stop API changes for PSoC5A */
    typedef struct
    {
        uint8 compCRReg;
    }   PumpCycle_LOWPOWER_BACKUP_STRUCT;
#endif /* CY_PSOC5A */

/* component init state */
extern uint8 PumpCycle_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void    PumpCycle_Start(void)                  ;
void    PumpCycle_Stop(void)                   ;
void    PumpCycle_SetSpeed(uint8 speed)        ;
uint8   PumpCycle_GetCompare(void)             ;
uint16  PumpCycle_ZeroCal(void)                ;
void    PumpCycle_LoadTrim(uint16 trimVal)     ;
void PumpCycle_Init(void)                      ; 
void PumpCycle_Enable(void)                    ;
void PumpCycle_SaveConfig(void)                ;
void PumpCycle_RestoreConfig(void)             ;
void PumpCycle_Sleep(void)                     ;
void PumpCycle_Wakeup(void)                    ;
/* Below APIs are valid only for PSoC3, PSoC5LP silicons.*/
#if (CY_PSOC3 || CY_PSOC5LP) 
    void PumpCycle_PwrDwnOverrideEnable(void)  ;
    void PumpCycle_PwrDwnOverrideDisable(void) ;
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           API Constants        
**************************************/

/* Power constants for SetSpeed() function */
#define PumpCycle_SLOWSPEED   (0x00u)
#define PumpCycle_HIGHSPEED   (0x01u)
#define PumpCycle_LOWPOWER    (0x02u)


/**************************************
*           Parameter Defaults        
**************************************/

#define PumpCycle_DEFAULT_SPEED       (1u) 
#define PumpCycle_DEFAULT_HYSTERESIS  (0u)
#define PumpCycle_DEFAULT_POLARITY    (0u)
#define PumpCycle_DEFAULT_BYPASS_SYNC (1u)
#define PumpCycle_DEFAULT_PWRDWN_OVRD (0u)


/**************************************
*             Registers        
**************************************/
#define PumpCycle_CR_REG            (* (reg8 *) PumpCycle_ctComp__CR )               /* Config register */
#define PumpCycle_CR_PTR            (  (reg8 *) PumpCycle_ctComp__CR )
#define PumpCycle_CLK_REG           (* (reg8 *) PumpCycle_ctComp__CLK )  /* Comp clock control register */
#define PumpCycle_CLK_PTR           (  (reg8 *) PumpCycle_ctComp__CLK )
#define PumpCycle_SW0_REG           (* (reg8 *) PumpCycle_ctComp__SW0 )            /* Routing registers */
#define PumpCycle_SW0_PTR           (  (reg8 *) PumpCycle_ctComp__SW0 )
#define PumpCycle_SW2_REG           (* (reg8 *) PumpCycle_ctComp__SW2 )
#define PumpCycle_SW2_PTR           (  (reg8 *) PumpCycle_ctComp__SW2 )
#define PumpCycle_SW3_REG           (* (reg8 *) PumpCycle_ctComp__SW3 )
#define PumpCycle_SW3_PTR           (  (reg8 *) PumpCycle_ctComp__SW3 )
#define PumpCycle_SW4_REG           (* (reg8 *) PumpCycle_ctComp__SW4 )
#define PumpCycle_SW4_PTR           (  (reg8 *) PumpCycle_ctComp__SW4 )
#define PumpCycle_SW6_REG           (* (reg8 *) PumpCycle_ctComp__SW6 )
#define PumpCycle_SW6_PTR           (  (reg8 *) PumpCycle_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define PumpCycle_TR_REG        (* (reg8 *) PumpCycle_ctComp__TR )                /* Trim registers */
    #define PumpCycle_TR_PTR        (  (reg8 *) PumpCycle_ctComp__TR )
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define PumpCycle_TR0_REG       (* (reg8 *) PumpCycle_ctComp__TR0 )/* Trim register for P-type load */
    #define PumpCycle_TR0_PTR       (  (reg8 *) PumpCycle_ctComp__TR0 ) 
    #define PumpCycle_TR1_REG       (* (reg8 *) PumpCycle_ctComp__TR1 )/* Trim register for N-type load */
    #define PumpCycle_TR1_PTR       (  (reg8 *) PumpCycle_ctComp__TR1 ) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define PumpCycle_WRK_REG           (* (reg8 *) PumpCycle_ctComp__WRK )    /* Working register - output */
#define PumpCycle_WRK_PTR           (  (reg8 *) PumpCycle_ctComp__WRK )
#define PumpCycle_PWRMGR_REG        (* (reg8 *) PumpCycle_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define PumpCycle_PWRMGR_PTR        (  (reg8 *) PumpCycle_ctComp__PM_ACT_CFG )
#define PumpCycle_STBY_PWRMGR_REG   (* (reg8 *) PumpCycle_ctComp__PM_STBY_CFG )/* Standby Power manager */
#define PumpCycle_STBY_PWRMGR_PTR   (  (reg8 *) PumpCycle_ctComp__PM_STBY_CFG )

/*      Trim Locations      */
#define PumpCycle_ctComp__TRIM__TR0_HS_PTR     ((void CYFAR *) PumpCycle_ctComp__TRIM__TR0_HS)
#define PumpCycle_ctComp__TRIM__TR0_HS_REG     CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define PumpCycle_ctComp__TRIM__TR1_HS_PTR ((void CYFAR *) PumpCycle_ctComp__TRIM__TR1_HS)
    #define PumpCycle_ctComp__TRIM__TR1_HS_REG CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define PumpCycle_ctComp__TRIM__TR0_LS_PTR     ((void CYFAR *) ((uint32)PumpCycle_ctComp__TRIM__TR0 + 1u))
#define PumpCycle_ctComp__TRIM__TR0_LS_REG     CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define PumpCycle_ctComp__TRIM__TR1_LS_PTR ((void CYFAR *) ((uint32)PumpCycle_ctComp__TRIM__TR1 + 1u))
    #define PumpCycle_ctComp__TRIM__TR1_LS_REG CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define PumpCycle_CR                (* (reg8 *) PumpCycle_ctComp__CR )               /* Config register */
#define PumpCycle_CLK               (* (reg8 *) PumpCycle_ctComp__CLK )  /* Comp clock control register */
#define PumpCycle_SW0               (* (reg8 *) PumpCycle_ctComp__SW0 )            /* Routing registers */
#define PumpCycle_SW2               (* (reg8 *) PumpCycle_ctComp__SW2 )
#define PumpCycle_SW3               (* (reg8 *) PumpCycle_ctComp__SW3 )
#define PumpCycle_SW4               (* (reg8 *) PumpCycle_ctComp__SW4 )
#define PumpCycle_SW6               (* (reg8 *) PumpCycle_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define PumpCycle_TR            (* (reg8 *) PumpCycle_ctComp__TR )                /* Trim registers */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define PumpCycle_TR0           (* (reg8 *) PumpCycle_ctComp__TR0 )/* Trim register for P-type load */
    #define PumpCycle_TR1           (* (reg8 *) PumpCycle_ctComp__TR1 )/* Trim register for N-type load */
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define PumpCycle_WRK               (* (reg8 *) PumpCycle_ctComp__WRK )    /* Working register - output */
#define PumpCycle_PWRMGR            (* (reg8 *) PumpCycle_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define PumpCycle_STBY_PWRMGR       (* (reg8 *) PumpCycle_ctComp__PM_STBY_CFG )/* Standby Power manager */

/*      Trim Locations      */
#define PumpCycle_HS_TRIM_TR0        CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define PumpCycle_HS_TRIM_TR1    CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define PumpCycle_LS_TRIM_TR0        CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define PumpCycle_LS_TRIM_TR1    CY_GET_XTND_REG8(PumpCycle_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*       Register Constants        
**************************************/

/* CR (Comp Control Register)             */
#define PumpCycle_CFG_MODE_MASK      (0x78u)
#define PumpCycle_FILTER_ON          (0x40u)
#define PumpCycle_HYST_OFF           (0x20u)
#define PumpCycle_CAL_ON             (0x10u)
#define PumpCycle_MX_AO              (0x08u)
#define PumpCycle_PWRDWN_OVRD        (0x04u)

#define PumpCycle_PWR_MODE_SHIFT     (0x00u)
#define PumpCycle_PWR_MODE_MASK      ((uint8)(0x03u << PumpCycle_PWR_MODE_SHIFT))
#define PumpCycle_PWR_MODE_SLOW      ((uint8)(0x00u << PumpCycle_PWR_MODE_SHIFT))
#define PumpCycle_PWR_MODE_FAST      ((uint8)(0x01u << PumpCycle_PWR_MODE_SHIFT))
#define PumpCycle_PWR_MODE_ULOW      ((uint8)(0x02u << PumpCycle_PWR_MODE_SHIFT))

/* CLK (Comp Clock Control Register)      */
#define PumpCycle_BYPASS_SYNC        (0x10u)
#define PumpCycle_SYNC_CLK_EN        (0x08u)
#define PumpCycle_SYNCCLK_MASK       (PumpCycle_BYPASS_SYNC | PumpCycle_SYNC_CLK_EN)

/* SW3 Routing Register definitions */
#define PumpCycle_CMP_SW3_INPCTL_MASK (0x09u)   /* SW3 bits for inP routing control */

/* TR (Comp Trim Register)     */
#define PumpCycle_DEFAULT_CMP_TRIM    (0x00u)

/* PSoC5A */
#if (CY_PSOC5A)
    #define PumpCycle_CMP_TRIM1_DIR   (0x08u)   /* Trim direction for N-type load for offset calibration */
    #define PumpCycle_CMP_TRIM1_MASK  (0x07u)   /* Trim for N-type load for offset calibration */
    #define PumpCycle_CMP_TRIM2_DIR   (0x80u)   /* Trim direction for P-type load for offset calibration */
    #define PumpCycle_CMP_TRIM2_MASK  (0x70u)   /* Trim for P-type load for offset calibration */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP)
    #define PumpCycle_CMP_TR0_DIR     (0x10u)   /* Trim direction for N-type load for offset calibration */
    #define PumpCycle_CMP_TR0_MASK    (0x0Fu)   /* Trim for N-type load for offset calibration */
    #define PumpCycle_CMP_TR1_DIR     (0x10u)   /* Trim direction for P-type load for offset calibration */
    #define PumpCycle_CMP_TR1_MASK    (0x07u)   /* Trim for P-type load for offset calibration */ 
#endif /* CY_PSOC3 || CY_PSOC5LP */


/* WRK (Comp output working register)     */ 
#define PumpCycle_CMP_OUT_MASK       PumpCycle_ctComp__WRK_MASK /* Specific comparator out mask */

/* PM_ACT_CFG7 (Active Power Mode CFG Register)     */ 
#define PumpCycle_ACT_PWR_EN         PumpCycle_ctComp__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG7 (Standby Power Mode CFG Register)     */ 
#define PumpCycle_STBY_PWR_EN        PumpCycle_ctComp__PM_STBY_MSK /* Standby Power enable mask */

#if (CY_PSOC5A)
    /* For stop API changes mask to make the COMP register CR to 0X00  */
    #define PumpCycle_COMP_REG_CLR   (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_COMP_PumpCycle_H */


/* [] END OF FILE */
