/*******************************************************************************
* File Name: timer.h
* Version 2.50
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_30_timer_H)
#define CY_Timer_v2_30_timer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 timer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define timer_Resolution                 32u
#define timer_UsingFixedFunction         0u
#define timer_UsingHWCaptureCounter      0u
#define timer_SoftwareCaptureMode        0u
#define timer_SoftwareTriggerMode        0u
#define timer_UsingHWEnable              0u
#define timer_EnableTriggerMode          0u
#define timer_InterruptOnCaptureCount    0u
#define timer_RunModeUsed                0u
#define timer_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!timer_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint32 TimerUdb;                 /* Timer internal counter value */
            uint32 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (timer_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in CY_UDB_V0 */

        #if (CY_UDB_V1)
            uint32 TimerUdb;
            uint8 InterruptMaskValue;
            #if (timer_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */
        #endif /* (CY_UDB_V1) */

        #if (!timer_ControlRegRemoved)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}timer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    timer_Start(void) ;
void    timer_Stop(void) ;

void    timer_SetInterruptMode(uint8 interruptMode) ;
uint8   timer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define timer_GetInterruptSource() timer_ReadStatusRegister()

#if(!timer_ControlRegRemoved)
    uint8   timer_ReadControlRegister(void) ;
    void    timer_WriteControlRegister(uint8 control) \
        ;
#endif /* (!timer_ControlRegRemoved) */

uint32  timer_ReadPeriod(void) ;
void    timer_WritePeriod(uint32 period) \
    ;
uint32  timer_ReadCounter(void) ;
void    timer_WriteCounter(uint32 counter) \
    ;
uint32  timer_ReadCapture(void) ;
void    timer_SoftwareCapture(void) ;


#if(!timer_UsingFixedFunction) /* UDB Prototypes */
    #if (timer_SoftwareCaptureMode)
        void    timer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!timer_UsingFixedFunction) */

    #if (timer_SoftwareTriggerMode)
        void    timer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (timer_SoftwareTriggerMode) */
    #if (timer_EnableTriggerMode)
        void    timer_EnableTrigger(void) ;
        void    timer_DisableTrigger(void) ;
    #endif /* (timer_EnableTriggerMode) */

    #if(timer_InterruptOnCaptureCount)
        #if(!timer_ControlRegRemoved)
            void    timer_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!timer_ControlRegRemoved) */
    #endif /* (timer_InterruptOnCaptureCount) */

    #if (timer_UsingHWCaptureCounter)
        void    timer_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   timer_ReadCaptureCount(void) ;
    #endif /* (timer_UsingHWCaptureCounter) */

    void timer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void timer_Init(void)          ;
void timer_Enable(void)        ;
void timer_SaveConfig(void)    ;
void timer_RestoreConfig(void) ;
void timer_Sleep(void)         ;
void timer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define timer__B_TIMER__CM_NONE 0
#define timer__B_TIMER__CM_RISINGEDGE 1
#define timer__B_TIMER__CM_FALLINGEDGE 2
#define timer__B_TIMER__CM_EITHEREDGE 3
#define timer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define timer__B_TIMER__TM_NONE 0x00u
#define timer__B_TIMER__TM_RISINGEDGE 0x04u
#define timer__B_TIMER__TM_FALLINGEDGE 0x08u
#define timer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define timer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define timer_INIT_PERIOD             4294967295u
#define timer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << timer_CTRL_CAP_MODE_SHIFT))
#define timer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << timer_CTRL_TRIG_MODE_SHIFT))
#if (timer_UsingFixedFunction)
    #define timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << timer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << timer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << timer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (timer_UsingFixedFunction) */
#define timer_INIT_CAPTURE_COUNT      (2u)
#define timer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << timer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (timer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define timer_STATUS         (*(reg8 *) timer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define timer_STATUS_MASK    (*(reg8 *) timer_TimerHW__SR0 )
    #define timer_CONTROL        (*(reg8 *) timer_TimerHW__CFG0)
    #define timer_CONTROL2       (*(reg8 *) timer_TimerHW__CFG1)
    #define timer_CONTROL2_PTR   ( (reg8 *) timer_TimerHW__CFG1)
    #define timer_RT1            (*(reg8 *) timer_TimerHW__RT1)
    #define timer_RT1_PTR        ( (reg8 *) timer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define timer_CONTROL3       (*(reg8 *) timer_TimerHW__CFG2)
        #define timer_CONTROL3_PTR   ( (reg8 *) timer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define timer_GLOBAL_ENABLE  (*(reg8 *) timer_TimerHW__PM_ACT_CFG)
    #define timer_GLOBAL_STBY_ENABLE  (*(reg8 *) timer_TimerHW__PM_STBY_CFG)

    #define timer_CAPTURE_LSB         (* (reg16 *) timer_TimerHW__CAP0 )
    #define timer_CAPTURE_LSB_PTR       ((reg16 *) timer_TimerHW__CAP0 )
    #define timer_PERIOD_LSB          (* (reg16 *) timer_TimerHW__PER0 )
    #define timer_PERIOD_LSB_PTR        ((reg16 *) timer_TimerHW__PER0 )
    #define timer_COUNTER_LSB         (* (reg16 *) timer_TimerHW__CNT_CMP0 )
    #define timer_COUNTER_LSB_PTR       ((reg16 *) timer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define timer_BLOCK_EN_MASK                     timer_TimerHW__PM_ACT_MSK
    #define timer_BLOCK_STBY_EN_MASK                timer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define timer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define timer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define timer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define timer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define timer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define timer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << timer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define timer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define timer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << timer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define timer_CTRL_MODE_SHIFT                     0x01u
        #define timer_CTRL_MODE_MASK                     ((uint8)((uint8)0x07u << timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define timer_CTRL_RCOD_SHIFT        0x02u
        #define timer_CTRL_ENBL_SHIFT        0x00u
        #define timer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define timer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << timer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define timer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << timer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define timer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << timer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define timer_CTRL_RCOD       ((uint8)((uint8)0x03u << timer_CTRL_RCOD_SHIFT))
        #define timer_CTRL_ENBL       ((uint8)((uint8)0x80u << timer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define timer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define timer_RT1_MASK                        ((uint8)((uint8)0x03u << timer_RT1_SHIFT))
    #define timer_SYNC                            ((uint8)((uint8)0x03u << timer_RT1_SHIFT))
    #define timer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define timer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << timer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define timer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << timer_SYNCDSI_SHIFT))

    #define timer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << timer_CTRL_MODE_SHIFT))
    #define timer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << timer_CTRL_MODE_SHIFT))
    #define timer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << timer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define timer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define timer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define timer_STATUS_TC_INT_MASK_SHIFT        (timer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define timer_STATUS_CAPTURE_INT_MASK_SHIFT   (timer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define timer_STATUS_TC                       ((uint8)((uint8)0x01u << timer_STATUS_TC_SHIFT))
    #define timer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define timer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << timer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define timer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << timer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define timer_STATUS              (* (reg8 *) timer_TimerUDB_nrstSts_stsreg__STATUS_REG )
    #define timer_STATUS_MASK         (* (reg8 *) timer_TimerUDB_nrstSts_stsreg__MASK_REG)
    #define timer_STATUS_AUX_CTRL     (* (reg8 *) timer_TimerUDB_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define timer_CONTROL             (* (reg8 *) timer_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG )
    
    #if(timer_Resolution <= 8u) /* 8-bit Timer */
        #define timer_CAPTURE_LSB         (* (reg8 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define timer_CAPTURE_LSB_PTR       ((reg8 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define timer_PERIOD_LSB          (* (reg8 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define timer_PERIOD_LSB_PTR        ((reg8 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define timer_COUNTER_LSB         (* (reg8 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define timer_COUNTER_LSB_PTR       ((reg8 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(timer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define timer_CAPTURE_LSB         (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define timer_CAPTURE_LSB_PTR       ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define timer_PERIOD_LSB          (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define timer_PERIOD_LSB_PTR        ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define timer_COUNTER_LSB         (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define timer_COUNTER_LSB_PTR       ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define timer_CAPTURE_LSB         (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define timer_CAPTURE_LSB_PTR       ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define timer_PERIOD_LSB          (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define timer_PERIOD_LSB_PTR        ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define timer_COUNTER_LSB         (* (reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define timer_COUNTER_LSB_PTR       ((reg16 *) timer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(timer_Resolution <= 24u)/* 24-bit Timer */
        #define timer_CAPTURE_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define timer_CAPTURE_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define timer_PERIOD_LSB          (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define timer_PERIOD_LSB_PTR        ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define timer_COUNTER_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define timer_COUNTER_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define timer_CAPTURE_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define timer_CAPTURE_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define timer_PERIOD_LSB          (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define timer_PERIOD_LSB_PTR        ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define timer_COUNTER_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define timer_COUNTER_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define timer_CAPTURE_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define timer_CAPTURE_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define timer_PERIOD_LSB          (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define timer_PERIOD_LSB_PTR        ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define timer_COUNTER_LSB         (* (reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define timer_COUNTER_LSB_PTR       ((reg32 *) timer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #if (timer_UsingHWCaptureCounter)
        #define timer_CAP_COUNT              (*(reg8 *) timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define timer_CAP_COUNT_PTR          ( (reg8 *) timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define timer_CAPTURE_COUNT_CTRL     (*(reg8 *) timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define timer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (timer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define timer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define timer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define timer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define timer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define timer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define timer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << timer_CTRL_INTCNT_SHIFT))
    #define timer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << timer_CTRL_TRIG_MODE_SHIFT))
    #define timer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << timer_CTRL_TRIG_EN_SHIFT))
    #define timer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << timer_CTRL_CAP_MODE_SHIFT))
    #define timer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << timer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define timer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define timer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define timer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define timer_STATUS_TC_INT_MASK_SHIFT       timer_STATUS_TC_SHIFT
    #define timer_STATUS_CAPTURE_INT_MASK_SHIFT  timer_STATUS_CAPTURE_SHIFT
    #define timer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define timer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define timer_STATUS_FIFOFULL_INT_MASK_SHIFT timer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define timer_STATUS_TC                      ((uint8)((uint8)0x01u << timer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define timer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define timer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << timer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define timer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << timer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define timer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << timer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define timer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << timer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define timer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << timer_STATUS_FIFOFULL_SHIFT))

    #define timer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define timer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define timer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define timer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define timer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define timer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_timer_H */


/* [] END OF FILE */
