/*******************************************************************************
* File Name: SleepTimer.h
* Version 3.20
*
* Description:
*  This file provides constants and parameter values for the Sleep Timer
*  Component.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SLEEPTIMER_SleepTimer_H)
#define CY_SLEEPTIMER_SleepTimer_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cyPm.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component SleepTimer_v3_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

extern uint8 SleepTimer_initVar;


/**************************************
*  Function Prototypes
**************************************/

void  SleepTimer_Start(void) ;
void  SleepTimer_Stop(void) ;
void  SleepTimer_Init(void) ;
void  SleepTimer_Enable(void) ;
void  SleepTimer_EnableInt(void) ;
void  SleepTimer_DisableInt(void) ;
void  SleepTimer_SetInterval(uint8 interval) ;
uint8 SleepTimer_GetStatus(void) ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

#if(!CY_PSOC5A)
    #define SleepTimer__CTW_2_MS      (1u)
#endif  /* (!CY_PSOC5A) */

#define SleepTimer__CTW_4_MS          (2u)
#define SleepTimer__CTW_8_MS          (3u)
#define SleepTimer__CTW_16_MS         (4u)
#define SleepTimer__CTW_32_MS         (5u)
#define SleepTimer__CTW_64_MS         (6u)
#define SleepTimer__CTW_128_MS        (7u)
#define SleepTimer__CTW_256_MS        (8u)

#if(!CY_PSOC5A)
    #define SleepTimer__CTW_512_MS    (9u)
    #define SleepTimer__CTW_1024_MS   (10u)
    #define SleepTimer__CTW_2048_MS   (11u)
    #define SleepTimer__CTW_4096_MS   (12u)
#endif  /* (!CY_PSOC5A) */


/***************************************
*   API Constants
***************************************/


/***************************************
*   Initialization Values
***************************************/

#define SleepTimer_ENABLE_INTERRUPT   (1u)
#define SleepTimer_INTERVAL           (2u)


/**************************************
*   Registers
**************************************/

#define SleepTimer_CTW_INTERVAL_REG   (* (reg8 *) CYREG_PM_TW_CFG1 )
#define SleepTimer_CTW_INTERVAL_PTR   (  (reg8 *) CYREG_PM_TW_CFG1 )

#define SleepTimer_TW_CFG_REG         (* (reg8 *) CYREG_PM_TW_CFG2 )
#define SleepTimer_TW_CFG_PTR         (  (reg8 *) CYREG_PM_TW_CFG2 )

#define SleepTimer_ILO_CFG_REG        (* (reg8 *) CYDEV_SLOWCLK_BASE )
#define SleepTimer_ILO_CFG_PTR        (  (reg8 *) CYDEV_SLOWCLK_BASE )

#define SleepTimer_INT_SR_REG         (* (reg8 *) CYREG_PM_INT_SR )
#define SleepTimer_INT_SR_PTR         (  (reg8 *) CYREG_PM_INT_SR )


/**************************************
*   Register Constants
**************************************/

/* Issue interrupt when CTW enabled */
#define SleepTimer_CTW_IE             (0x08u)

/* CTW enable */
#define SleepTimer_CTW_EN             (0x04u)

/* 1 kHz ILO enable */
#define SleepTimer_ILO_1KHZ_EN        (0x02u)

/* CTW interval mask  */
#define SleepTimer_INTERVAL_MASK      (0x0Fu)

/* A onepps event has occured */
#define SleepTimer_PM_INT_SR_ONEPPSP  (0x04u)

/* A central timewheel event has occured */
#define SleepTimer_PM_INT_SR_CTW      (0x02u)

/* A fast timewheel event has occured */
#define SleepTimer_PM_INT_SR_FTW      (0x01u)

#endif  /* End of CY_SLEEPTIMER_SleepTimer_H */


/* [] END OF FILE */
