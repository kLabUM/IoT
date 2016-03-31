/*******************************************************************************
* File Name: Sensirion_I2C.h
* Version 3.30
*
* Description:
*  This file provides constants and parameter values for the I2C component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_Sensirion_I2C_H)
#define CY_I2C_Sensirion_I2C_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check if required defines such as CY_PSOC5LP are available in cy_boot */
#if !defined (CY_PSOC5LP)
    #error Component I2C_v3_30 requires cy_boot v3.10 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Sensirion_I2C_IMPLEMENTATION     (0u)
#define Sensirion_I2C_MODE               (2u)
#define Sensirion_I2C_ENABLE_WAKEUP      (0u)
#define Sensirion_I2C_ADDR_DECODE        (1u)
#define Sensirion_I2C_UDB_INTRN_CLOCK    (1u)


/* I2C implementation enum */
#define Sensirion_I2C_UDB    (0x00u)
#define Sensirion_I2C_FF     (0x01u)

#define Sensirion_I2C_FF_IMPLEMENTED     (Sensirion_I2C_FF  == Sensirion_I2C_IMPLEMENTATION)
#define Sensirion_I2C_UDB_IMPLEMENTED    (Sensirion_I2C_UDB == Sensirion_I2C_IMPLEMENTATION)

#define Sensirion_I2C_UDB_INTRN_CLOCK_ENABLED    (Sensirion_I2C_UDB_IMPLEMENTED && \
                                                     (0u != Sensirion_I2C_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define Sensirion_I2C_MODE_SLAVE                 (0x01u)
#define Sensirion_I2C_MODE_MASTER                (0x02u)
#define Sensirion_I2C_MODE_MULTI_MASTER          (0x06u)
#define Sensirion_I2C_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define Sensirion_I2C_MODE_MULTI_MASTER_MASK     (0x04u)

#define Sensirion_I2C_MODE_SLAVE_ENABLED         (0u != (Sensirion_I2C_MODE_SLAVE  & Sensirion_I2C_MODE))
#define Sensirion_I2C_MODE_MASTER_ENABLED        (0u != (Sensirion_I2C_MODE_MASTER & Sensirion_I2C_MODE))
#define Sensirion_I2C_MODE_MULTI_MASTER_ENABLED  (0u != (Sensirion_I2C_MODE_MULTI_MASTER_MASK & \
                                                            Sensirion_I2C_MODE))
#define Sensirion_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED    (Sensirion_I2C_MODE_MULTI_MASTER_SLAVE == \
                                                             Sensirion_I2C_MODE)

/* Address detection enum */
#define Sensirion_I2C_SW_DECODE      (0x00u)
#define Sensirion_I2C_HW_DECODE      (0x01u)

#define Sensirion_I2C_SW_ADRR_DECODE             (Sensirion_I2C_SW_DECODE == Sensirion_I2C_ADDR_DECODE)
#define Sensirion_I2C_HW_ADRR_DECODE             (Sensirion_I2C_HW_DECODE == Sensirion_I2C_ADDR_DECODE)

/* Wakeup enabled */
#define Sensirion_I2C_WAKEUP_ENABLED             (0u != Sensirion_I2C_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define Sensirion_I2C_BOOTLOADER_INTERFACE_ENABLED   (Sensirion_I2C_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Sensirion_I2C) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define Sensirion_I2C_TIMEOUT_ENABLE             (0u)
#define Sensirion_I2C_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define Sensirion_I2C_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define Sensirion_I2C_TIMEOUT_PRESCALER_ENABLE   (0u)
#define Sensirion_I2C_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define Sensirion_I2C_TIMEOUT_ENABLED            (0u != Sensirion_I2C_TIMEOUT_ENABLE)
#define Sensirion_I2C_TIMEOUT_SCL_TMOUT_ENABLED  (0u != Sensirion_I2C_TIMEOUT_SCL_TMOUT_ENABLE)
#define Sensirion_I2C_TIMEOUT_SDA_TMOUT_ENABLED  (0u != Sensirion_I2C_TIMEOUT_SDA_TMOUT_ENABLE)
#define Sensirion_I2C_TIMEOUT_PRESCALER_ENABLED  (0u != Sensirion_I2C_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define Sensirion_I2C_TIMEOUT_UDB    (0x00u)
#define Sensirion_I2C_TIMEOUT_FF     (0x01u)

#define Sensirion_I2C_TIMEOUT_FF_IMPLEMENTED     (Sensirion_I2C_TIMEOUT_FF  == \
                                                        Sensirion_I2C_TIMEOUT_IMPLEMENTATION)
#define Sensirion_I2C_TIMEOUT_UDB_IMPLEMENTED    (Sensirion_I2C_TIMEOUT_UDB == \
                                                        Sensirion_I2C_TIMEOUT_IMPLEMENTATION)

#define Sensirion_I2C_TIMEOUT_FF_ENABLED         (Sensirion_I2C_TIMEOUT_ENABLED && \
                                                     Sensirion_I2C_TIMEOUT_FF_IMPLEMENTED && \
                                                     CY_PSOC5LP)

#define Sensirion_I2C_TIMEOUT_UDB_ENABLED        (Sensirion_I2C_TIMEOUT_ENABLED && \
                                                     Sensirion_I2C_TIMEOUT_UDB_IMPLEMENTED)

#define Sensirion_I2C_EXTERN_I2C_INTR_HANDLER    (0u)
#define Sensirion_I2C_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define Sensirion_I2C_INTERN_I2C_INTR_HANDLER    (0u == Sensirion_I2C_EXTERN_I2C_INTR_HANDLER)
#define Sensirion_I2C_INTERN_TMOUT_INTR_HANDLER  (0u == Sensirion_I2C_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

    #if(Sensirion_I2C_FF_IMPLEMENTED)
        uint8 xcfg;
        uint8 cfg;

        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            uint8 addr;
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            uint8 clkDiv;
        #else
            uint8 clkDiv1;
            uint8 clkDiv2;
        #endif /* (CY_PSOC5A) */

    #else
        uint8 control;

        #if(CY_UDB_V0)
            uint8 intMask;

            #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
                uint8 addr;
            #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */
        #endif     /* (CY_UDB_V0) */

    #endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

    #if(Sensirion_I2C_TIMEOUT_ENABLED)
        uint16 tmoutCfg;
        uint8  tmoutIntr;

        #if(Sensirion_I2C_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            uint8 tmoutPrd;
        #endif /* (Sensirion_I2C_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0) */

    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */

} Sensirion_I2C_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void Sensirion_I2C_Init(void)                            ;
void Sensirion_I2C_Enable(void)                          ;

void Sensirion_I2C_Start(void)                           ;
void Sensirion_I2C_Stop(void)                            ;

#define Sensirion_I2C_EnableInt()        CyIntEnable      (Sensirion_I2C_ISR_NUMBER)
#define Sensirion_I2C_DisableInt()       CyIntDisable     (Sensirion_I2C_ISR_NUMBER)
#define Sensirion_I2C_ClearPendingInt()  CyIntClearPending(Sensirion_I2C_ISR_NUMBER)
#define Sensirion_I2C_SetPendingInt()    CyIntSetPending  (Sensirion_I2C_ISR_NUMBER)

void Sensirion_I2C_SaveConfig(void)                      ;
void Sensirion_I2C_Sleep(void)                           ;
void Sensirion_I2C_RestoreConfig(void)                   ;
void Sensirion_I2C_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if(Sensirion_I2C_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 Sensirion_I2C_MasterStatus(void)                ;
    uint8 Sensirion_I2C_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 Sensirion_I2C_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 Sensirion_I2C_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 Sensirion_I2C_MasterGetReadBufSize(void)       ;
    uint8 Sensirion_I2C_MasterGetWriteBufSize(void)      ;
    void  Sensirion_I2C_MasterClearReadBuf(void)         ;
    void  Sensirion_I2C_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 Sensirion_I2C_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 Sensirion_I2C_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 Sensirion_I2C_MasterSendStop(void)             ;
    uint8 Sensirion_I2C_MasterWriteByte(uint8 theByte)   ;
    uint8 Sensirion_I2C_MasterReadByte(uint8 acknNak)    ;

    /* This fake function use as workaround */
    void  Sensirion_I2C_Workaround(void)                 ;

#endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if(Sensirion_I2C_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 Sensirion_I2C_SlaveStatus(void)                ;
    uint8 Sensirion_I2C_SlaveClearReadStatus(void)       ;
    uint8 Sensirion_I2C_SlaveClearWriteStatus(void)      ;

    void  Sensirion_I2C_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  Sensirion_I2C_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  Sensirion_I2C_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 Sensirion_I2C_SlaveGetReadBufSize(void)        ;
    uint8 Sensirion_I2C_SlaveGetWriteBufSize(void)       ;
    void  Sensirion_I2C_SlaveClearReadBuf(void)          ;
    void  Sensirion_I2C_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (Sensirion_I2C_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     Sensirion_I2C_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     Sensirion_I2C_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     Sensirion_I2C_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus Sensirion_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus Sensirion_I2C_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Sensirion_I2C)
            #define CyBtldrCommStart    Sensirion_I2C_CyBtldrCommStart
            #define CyBtldrCommStop     Sensirion_I2C_CyBtldrCommStop
            #define CyBtldrCommReset    Sensirion_I2C_CyBtldrCommReset
            #define CyBtldrCommWrite    Sensirion_I2C_CyBtldrCommWrite
            #define CyBtldrCommRead     Sensirion_I2C_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Sensirion_I2C) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define Sensirion_I2C_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define Sensirion_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define Sensirion_I2C_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define Sensirion_I2C_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Sensirion_I2C_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

/* I2C interrupt handler */
CY_ISR_PROTO(Sensirion_I2C_ISR);
#if((Sensirion_I2C_FF_IMPLEMENTED) || (Sensirion_I2C_WAKEUP_ENABLED))
    CY_ISR_PROTO(Sensirion_I2C_WAKEUP_ISR);
#endif /* ((Sensirion_I2C_FF_IMPLEMENTED) || (Sensirion_I2C_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 Sensirion_I2C_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define Sensirion_I2C_DATA_RATE          (100u)
#define Sensirion_I2C_DEFAULT_ADDR       (8u)
#define Sensirion_I2C_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define Sensirion_I2C_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define Sensirion_I2C_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define Sensirion_I2C_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define Sensirion_I2C_I2C1_SIO_PAIR  (Sensirion_I2C_I2C_PAIR1 == Sensirion_I2C_I2C_PAIR_SELECTED)
#define Sensirion_I2C_I2C0_SIO_PAIR  (Sensirion_I2C_I2C_PAIR0 == Sensirion_I2C_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define Sensirion_I2C_READ_XFER_MODE     (0x01u) /* Read */
#define Sensirion_I2C_WRITE_XFER_MODE    (0x00u) /* Write */
#define Sensirion_I2C_ACK_DATA           (0x01u) /* Send ACK */
#define Sensirion_I2C_NAK_DATA           (0x00u) /* Send NAK */
#define Sensirion_I2C_OVERFLOW_RETURN    (0xFFu) /* Senf on bus in case of overflow */

#if(Sensirion_I2C_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define Sensirion_I2C_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define Sensirion_I2C_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define Sensirion_I2C_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define Sensirion_I2C_MSTAT_CLEAR            (0x00u) /* Clear (init) status value */

    #define Sensirion_I2C_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define Sensirion_I2C_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define Sensirion_I2C_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define Sensirion_I2C_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define Sensirion_I2C_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define Sensirion_I2C_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define Sensirion_I2C_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define Sensirion_I2C_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define Sensirion_I2C_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define Sensirion_I2C_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define Sensirion_I2C_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define Sensirion_I2C_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define Sensirion_I2C_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define Sensirion_I2C_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define Sensirion_I2C_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */

#if(Sensirion_I2C_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define Sensirion_I2C_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define Sensirion_I2C_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define Sensirion_I2C_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define Sensirion_I2C_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define Sensirion_I2C_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define Sensirion_I2C_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define Sensirion_I2C_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define Sensirion_I2C_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define Sensirion_I2C_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define Sensirion_I2C_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define Sensirion_I2C_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define Sensirion_I2C_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  Sensirion_I2C_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  Sensirion_I2C_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  Sensirion_I2C_SM_SLAVE          (Sensirion_I2C_SM_IDLE) /* Any Slave state */
#define  Sensirion_I2C_SM_SL_WR_DATA     (0x11u) /* Master writes data to slzve  */
#define  Sensirion_I2C_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  Sensirion_I2C_SM_MASTER         (0x40u) /* Any master state */

#define  Sensirion_I2C_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  Sensirion_I2C_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  Sensirion_I2C_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  Sensirion_I2C_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  Sensirion_I2C_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  Sensirion_I2C_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  Sensirion_I2C_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define Sensirion_I2C_CHECK_SM_MASTER    (0u != (Sensirion_I2C_SM_MASTER & Sensirion_I2C_state))
#define Sensirion_I2C_CHECK_SM_SLAVE     (0u != (Sensirion_I2C_SM_SLAVE  & Sensirion_I2C_state))


/***************************************
*              Registers
***************************************/

#if(Sensirion_I2C_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define Sensirion_I2C_XCFG_REG           (* (reg8 *) Sensirion_I2C_I2C_FF__XCFG)
    #define Sensirion_I2C_XCFG_PTR           (  (reg8 *) Sensirion_I2C_I2C_FF__XCFG)

    #define Sensirion_I2C_ADDR_REG           (* (reg8 *) Sensirion_I2C_I2C_FF__ADR)
    #define Sensirion_I2C_ADDR_PTR           (  (reg8 *) Sensirion_I2C_I2C_FF__ADR)

    #define Sensirion_I2C_CFG_REG            (* (reg8 *) Sensirion_I2C_I2C_FF__CFG)
    #define Sensirion_I2C_CFG_PTR            (  (reg8 *) Sensirion_I2C_I2C_FF__CFG)

    #define Sensirion_I2C_CSR_REG            (* (reg8 *) Sensirion_I2C_I2C_FF__CSR)
    #define Sensirion_I2C_CSR_PTR            (  (reg8 *) Sensirion_I2C_I2C_FF__CSR)

    #define Sensirion_I2C_DATA_REG           (* (reg8 *) Sensirion_I2C_I2C_FF__D)
    #define Sensirion_I2C_DATA_PTR           (  (reg8 *) Sensirion_I2C_I2C_FF__D)

    #define Sensirion_I2C_MCSR_REG           (* (reg8 *) Sensirion_I2C_I2C_FF__MCSR)
    #define Sensirion_I2C_MCSR_PTR           (  (reg8 *) Sensirion_I2C_I2C_FF__MCSR)

    #define Sensirion_I2C_ACT_PWRMGR_REG     (* (reg8 *) Sensirion_I2C_I2C_FF__PM_ACT_CFG)
    #define Sensirion_I2C_ACT_PWRMGR_PTR     (  (reg8 *) Sensirion_I2C_I2C_FF__PM_ACT_CFG)
    #define Sensirion_I2C_ACT_PWR_EN         (  (uint8)  Sensirion_I2C_I2C_FF__PM_ACT_MSK)

    #define Sensirion_I2C_STBY_PWRMGR_REG    (* (reg8 *) Sensirion_I2C_I2C_FF__PM_STBY_CFG)
    #define Sensirion_I2C_STBY_PWRMGR_PTR    (  (reg8 *) Sensirion_I2C_I2C_FF__PM_STBY_CFG)
    #define Sensirion_I2C_STBY_PWR_EN        (  (uint8)  Sensirion_I2C_I2C_FF__PM_STBY_MSK)

    #define Sensirion_I2C_PWRSYS_CR1_REG     (* (reg8 *) CYREG_PWRSYS_CR1)
    #define Sensirion_I2C_PWRSYS_CR1_PTR     (  (reg8 *) CYREG_PWRSYS_CR1)

    /* Clock divider register depends on silicon */
    #if(CY_PSOC5A)
        #define Sensirion_I2C_CLKDIV_REG     (* (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV)
        #define Sensirion_I2C_CLKDIV_PTR     (  (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV)

    #else
        #define Sensirion_I2C_CLKDIV1_REG    (* (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV1)
        #define Sensirion_I2C_CLKDIV1_PTR    (  (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV1)

        #define Sensirion_I2C_CLKDIV2_REG    (* (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV2)
        #define Sensirion_I2C_CLKDIV2_PTR    (  (reg8 *) Sensirion_I2C_I2C_FF__CLK_DIV2)

    #endif /* (CY_PSOC5A) */

#else
    /* UDB implementation registers */
    #define Sensirion_I2C_CFG_REG    (* (reg8 *) \
                                           Sensirion_I2C_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)
    #define Sensirion_I2C_CFG_PTR    (  (reg8 *) \
                                           Sensirion_I2C_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)

    #define Sensirion_I2C_CSR_REG        (* (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__STATUS_REG)
    #define Sensirion_I2C_CSR_PTR        (  (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__STATUS_REG)

    #define Sensirion_I2C_INT_MASK_REG   (* (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__MASK_REG)
    #define Sensirion_I2C_INT_MASK_PTR   (  (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__MASK_REG)

    #define Sensirion_I2C_INT_ENABLE_REG (* (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define Sensirion_I2C_INT_ENABLE_PTR (  (reg8 *) Sensirion_I2C_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define Sensirion_I2C_DATA_REG       (* (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__A0_REG)
    #define Sensirion_I2C_DATA_PTR       (  (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__A0_REG)

    #define Sensirion_I2C_GO_REG         (* (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__F1_REG)
    #define Sensirion_I2C_GO_PTR         (  (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__F1_REG)

    #define Sensirion_I2C_MCLK_PRD_REG   (* (reg8 *) Sensirion_I2C_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define Sensirion_I2C_MCLK_PRD_PTR   (  (reg8 *) Sensirion_I2C_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define Sensirion_I2C_MCLK_CMP_REG   (* (reg8 *) Sensirion_I2C_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define Sensirion_I2C_MCLK_CMP_PTR   (  (reg8 *) Sensirion_I2C_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
        #define Sensirion_I2C_ADDR_REG       (* (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__D0_REG)
        #define Sensirion_I2C_ADDR_PTR       (  (reg8 *) Sensirion_I2C_bI2C_UDB_Shifter_u0__D0_REG)

        #define Sensirion_I2C_PERIOD_REG     (* (reg8 *) Sensirion_I2C_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define Sensirion_I2C_PERIOD_PTR     (  (reg8 *) Sensirion_I2C_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define Sensirion_I2C_COUNTER_REG    (* (reg8 *) Sensirion_I2C_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define Sensirion_I2C_COUNTER_PTR    (  (reg8 *) Sensirion_I2C_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define Sensirion_I2C_COUNTER_AUX_CTL_REG  (* (reg8 *) \
                                                        Sensirion_I2C_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define Sensirion_I2C_COUNTER_AUX_CTL_PTR  (  (reg8 *) \
                                                        Sensirion_I2C_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

#endif /* (Sensirion_I2C_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* Sensirion_I2C_I2C_IRQ */
#define Sensirion_I2C_ISR_NUMBER     ((uint8) Sensirion_I2C_I2C_IRQ__INTC_NUMBER)
#define Sensirion_I2C_ISR_PRIORITY   ((uint8) Sensirion_I2C_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define Sensirion_I2C_SLAVE_ADDR_MASK    (0x7Fu)
#define Sensirion_I2C_SLAVE_ADDR_SHIFT   (0x01u)
#define Sensirion_I2C_DATA_MASK          (0xFFu)
#define Sensirion_I2C_READ_FLAG          (0x01u)

#define Sensirion_I2C_FF_RESET_DELAY     (0x02u)

#if(Sensirion_I2C_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define Sensirion_I2C_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define Sensirion_I2C_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define Sensirion_I2C_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define Sensirion_I2C_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incomming transactions */
    #define Sensirion_I2C_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define Sensirion_I2C_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define Sensirion_I2C_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define Sensirion_I2C_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define Sensirion_I2C_CFG_PSELECT        (0x40u) /* Pin Select */
    #define Sensirion_I2C_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define Sensirion_I2C_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define Sensirion_I2C_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select  **CHECK**  */
    #define Sensirion_I2C_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define Sensirion_I2C_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define Sensirion_I2C_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define Sensirion_I2C_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define Sensirion_I2C_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define Sensirion_I2C_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define Sensirion_I2C_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define Sensirion_I2C_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define Sensirion_I2C_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occured */
    #define Sensirion_I2C_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define Sensirion_I2C_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define Sensirion_I2C_CSR_ACK            (0x10u) /* ACK response */
    #define Sensirion_I2C_CSR_NAK            (0x00u) /* NAK response */
    #define Sensirion_I2C_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define Sensirion_I2C_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define Sensirion_I2C_CSR_LRB            (0x02u) /* Last received bit */
    #define Sensirion_I2C_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define Sensirion_I2C_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define Sensirion_I2C_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define Sensirion_I2C_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define Sensirion_I2C_CSR_RDY_TO_RD      (0x00u) /* Set to recieve mode */

    /* MCSR I2C Master Control and Status Register */
    #define Sensirion_I2C_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define Sensirion_I2C_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define Sensirion_I2C_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define Sensirion_I2C_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define Sensirion_I2C_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* CLK_DIV I2C Clock Divide Factor Register */
    #define Sensirion_I2C_CLK_DIV_MSK    (0x07u) /* Status bit, Set at Start and cleared at Stop condition */
    #define Sensirion_I2C_CLK_DIV_1      (0x00u) /* Divide input clock by  1 */
    #define Sensirion_I2C_CLK_DIV_2      (0x01u) /* Divide input clock by  2 */
    #define Sensirion_I2C_CLK_DIV_4      (0x02u) /* Divide input clock by  4 */
    #define Sensirion_I2C_CLK_DIV_8      (0x03u) /* Divide input clock by  8 */
    #define Sensirion_I2C_CLK_DIV_16     (0x04u) /* Divide input clock by 16 */
    #define Sensirion_I2C_CLK_DIV_32     (0x05u) /* Divide input clock by 32 */
    #define Sensirion_I2C_CLK_DIV_64     (0x06u) /* Divide input clock by 64 */

    /* PWRSYS_CR1 to handle Sleep */
    #define Sensirion_I2C_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define Sensirion_I2C_CTRL_START_SHIFT           (7u)
    #define Sensirion_I2C_CTRL_STOP_SHIFT            (6u)
    #define Sensirion_I2C_CTRL_RESTART_SHIFT         (5u)
    #define Sensirion_I2C_CTRL_NACK_SHIFT            (4u)
    #define Sensirion_I2C_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define Sensirion_I2C_CTRL_TRANSMIT_SHIFT        (2u)
    #define Sensirion_I2C_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define Sensirion_I2C_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define Sensirion_I2C_CTRL_START_MASK            ((uint8) (0x01u << Sensirion_I2C_CTRL_START_SHIFT))
    #define Sensirion_I2C_CTRL_STOP_MASK             ((uint8) (0x01u << Sensirion_I2C_CTRL_STOP_SHIFT))
    #define Sensirion_I2C_CTRL_RESTART_MASK          ((uint8) (0x01u << Sensirion_I2C_CTRL_RESTART_SHIFT))
    #define Sensirion_I2C_CTRL_NACK_MASK             ((uint8) (0x01u << Sensirion_I2C_CTRL_NACK_SHIFT))
    #define Sensirion_I2C_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << Sensirion_I2C_CTRL_ANY_ADDRESS_SHIFT))
    #define Sensirion_I2C_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << Sensirion_I2C_CTRL_TRANSMIT_SHIFT))
    #define Sensirion_I2C_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << Sensirion_I2C_CTRL_ENABLE_MASTER_SHIFT))
    #define Sensirion_I2C_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << Sensirion_I2C_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define Sensirion_I2C_STS_LOST_ARB_SHIFT         (6u)
    #define Sensirion_I2C_STS_STOP_SHIFT             (5u)
    #define Sensirion_I2C_STS_BUSY_SHIFT             (4u)
    #define Sensirion_I2C_STS_ADDR_SHIFT             (3u)
    #define Sensirion_I2C_STS_MASTER_MODE_SHIFT      (2u)
    #define Sensirion_I2C_STS_LRB_SHIFT              (1u)
    #define Sensirion_I2C_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define Sensirion_I2C_STS_LOST_ARB_MASK          ((uint8) (0x01u << Sensirion_I2C_STS_LOST_ARB_SHIFT))
    #define Sensirion_I2C_STS_STOP_MASK              ((uint8) (0x01u << Sensirion_I2C_STS_STOP_SHIFT))
    #define Sensirion_I2C_STS_BUSY_MASK              ((uint8) (0x01u << Sensirion_I2C_STS_BUSY_SHIFT))
    #define Sensirion_I2C_STS_ADDR_MASK              ((uint8) (0x01u << Sensirion_I2C_STS_ADDR_SHIFT))
    #define Sensirion_I2C_STS_MASTER_MODE_MASK       ((uint8) (0x01u << Sensirion_I2C_STS_MASTER_MODE_SHIFT))
    #define Sensirion_I2C_STS_LRB_MASK               ((uint8) (0x01u << Sensirion_I2C_STS_LRB_SHIFT))
    #define Sensirion_I2C_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << Sensirion_I2C_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define Sensirion_I2C_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter     */
    #define Sensirion_I2C_INT_ENABLE_MASK            (0x10u) /* Enable intr from statusi */
    #define Sensirion_I2C_CNT7_ENABLE                (Sensirion_I2C_COUNTER_ENABLE_MASK)
    #define Sensirion_I2C_INTR_ENABLE                (Sensirion_I2C_INT_ENABLE_MASK)

#endif /* (Sensirion_I2C_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define Sensirion_I2C_CHECK_ADDR_ACK(csr)    ((Sensirion_I2C_CSR_LRB_ACK | Sensirion_I2C_CSR_ADDRESS) == \
                                                 ((Sensirion_I2C_CSR_LRB    | Sensirion_I2C_CSR_ADDRESS) &  \
                                                  (csr)))


#define Sensirion_I2C_CHECK_ADDR_NAK(csr)    ((Sensirion_I2C_CSR_LRB_NAK | Sensirion_I2C_CSR_ADDRESS) == \
                                                 ((Sensirion_I2C_CSR_LRB    | Sensirion_I2C_CSR_ADDRESS) &  \
                                                  (csr)))

#define Sensirion_I2C_CHECK_DATA_ACK(csr)    (0u == ((csr) & Sensirion_I2C_CSR_LRB_NAK))

/* MCSR conditions check */
#define Sensirion_I2C_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & Sensirion_I2C_MCSR_BUS_BUSY))
#define Sensirion_I2C_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & Sensirion_I2C_MCSR_MSTR_MODE))

/* CSR conditions check */
#define Sensirion_I2C_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & Sensirion_I2C_CSR_BYTE_COMPLETE))
#define Sensirion_I2C_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (Sensirion_I2C_CSR_BYTE_COMPLETE | \
                                                                     Sensirion_I2C_CSR_STOP_STATUS)))
#define Sensirion_I2C_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & Sensirion_I2C_CSR_BYTE_COMPLETE))
#define Sensirion_I2C_CHECK_STOP_STS(csr)        (0u != ((csr) & Sensirion_I2C_CSR_STOP_STATUS))
#define Sensirion_I2C_CHECK_LOST_ARB(csr)        (0u != ((csr) & Sensirion_I2C_CSR_LOST_ARB))
#define Sensirion_I2C_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & Sensirion_I2C_CSR_ADDRESS))

/* Software start and end of transaction check */
#define Sensirion_I2C_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & Sensirion_I2C_MODE_REPEAT_START))
#define Sensirion_I2C_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & Sensirion_I2C_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define Sensirion_I2C_GET_MSTAT_CMPLT ((0u != (Sensirion_I2C_state & Sensirion_I2C_SM_MSTR_RD)) ? \
                                                 (Sensirion_I2C_MSTAT_RD_CMPLT) : (Sensirion_I2C_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address and used for software address match */
#define Sensirion_I2C_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> Sensirion_I2C_SLAVE_ADDR_SHIFT) & \
                                                                  Sensirion_I2C_SLAVE_ADDR_MASK)

#if(Sensirion_I2C_FF_IMPLEMENTED)
    /* Check enable of module */
    #define Sensirion_I2C_I2C_ENABLE_REG     (Sensirion_I2C_ACT_PWRMGR_REG)
    #define Sensirion_I2C_IS_I2C_ENABLE(reg) (0u != ((reg) & Sensirion_I2C_ACT_PWR_EN))
    #define Sensirion_I2C_IS_ENABLED         (0u != (Sensirion_I2C_ACT_PWRMGR_REG & Sensirion_I2C_ACT_PWR_EN))

    #define Sensirion_I2C_CHECK_PWRSYS_I2C_BACKUP    (0u != (Sensirion_I2C_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                Sensirion_I2C_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define Sensirion_I2C_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & Sensirion_I2C_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & Sensirion_I2C_MCSR_MSTR_MODE)))

    #define Sensirion_I2C_CLEAR_START_GEN        do{ \
                                                        Sensirion_I2C_MCSR_REG &=                                   \
                                                                           ((uint8) ~Sensirion_I2C_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define Sensirion_I2C_ENABLE_INT_ON_STOP     do{ \
                                                        Sensirion_I2C_CFG_REG |= Sensirion_I2C_CFG_STOP_IE; \
                                                    }while(0)

    #define Sensirion_I2C_DISABLE_INT_ON_STOP    do{ \
                                                        Sensirion_I2C_CFG_REG &=                                 \
                                                                           ((uint8) ~Sensirion_I2C_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define Sensirion_I2C_TRANSMIT_DATA          do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_TRANSMIT; \
                                                    }while(0)

    #define Sensirion_I2C_ACK_AND_TRANSMIT       do{ \
                                                        Sensirion_I2C_CSR_REG = (Sensirion_I2C_CSR_ACK |      \
                                                                                    Sensirion_I2C_CSR_TRANSMIT); \
                                                    }while(0)

    #define Sensirion_I2C_NAK_AND_TRANSMIT       do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define Sensirion_I2C_ACKNAK_AND_TRANSMIT    do{ \
                                                        Sensirion_I2C_CSR_REG  = (Sensirion_I2C_CSR_NAK |      \
                                                                                     Sensirion_I2C_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define Sensirion_I2C_ACK_AND_RECEIVE        do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_ACK; \
                                                    }while(0)

    #define Sensirion_I2C_NAK_AND_RECEIVE        do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_NAK; \
                                                    }while(0)

    #define Sensirion_I2C_READY_TO_READ          do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Master condition generation */
    #define Sensirion_I2C_GENERATE_START         do{ \
                                                        Sensirion_I2C_MCSR_REG = Sensirion_I2C_MCSR_START_GEN; \
                                                    }while(0)

    #if(CY_PSOC5A)
        #define Sensirion_I2C_GENERATE_RESTART \
                        do{ \
                            Sensirion_I2C_MCSR_REG = Sensirion_I2C_MCSR_RESTART_GEN; \
                            Sensirion_I2C_CSR_REG  = Sensirion_I2C_CSR_NAK;          \
                        }while(0)

        #define Sensirion_I2C_GENERATE_STOP      do{ \
                                                        Sensirion_I2C_CSR_REG = Sensirion_I2C_CSR_STOP_GEN; \
                                                    }while(0)

    #else   /* PSoC3 ES3 handlees zero lenght packets */
        #define Sensirion_I2C_GENERATE_RESTART \
                        do{ \
                            Sensirion_I2C_MCSR_REG = (Sensirion_I2C_MCSR_RESTART_GEN | \
                                                         Sensirion_I2C_MCSR_STOP_GEN);    \
                            Sensirion_I2C_CSR_REG  = Sensirion_I2C_CSR_TRANSMIT;       \
                        }while(0)

        #define Sensirion_I2C_GENERATE_STOP \
                        do{ \
                            Sensirion_I2C_MCSR_REG = Sensirion_I2C_MCSR_STOP_GEN; \
                            Sensirion_I2C_CSR_REG  = Sensirion_I2C_CSR_TRANSMIT;  \
                        }while(0)
    #endif /* (CY_PSOC5A) */

    /* Master manual APIs compatible defines */
    #define Sensirion_I2C_GENERATE_RESTART_MANUAL    Sensirion_I2C_GENERATE_RESTART
    #define Sensirion_I2C_GENERATE_STOP_MANUAL       Sensirion_I2C_GENERATE_STOP
    #define Sensirion_I2C_TRANSMIT_DATA_MANUAL       Sensirion_I2C_TRANSMIT_DATA
    #define Sensirion_I2C_READY_TO_READ_MANUAL       Sensirion_I2C_READY_TO_READ
    #define Sensirion_I2C_ACK_AND_RECEIVE_MANUAL     Sensirion_I2C_ACK_AND_RECEIVE

#else

    /* Masks to enalbe interrupts from Status register */
    #define Sensirion_I2C_STOP_IE_MASK           (Sensirion_I2C_STS_STOP_MASK)
    #define Sensirion_I2C_BYTE_COMPLETE_IE_MASK  (Sensirion_I2C_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR gegisters definitions */
    #define Sensirion_I2C_CSR_LOST_ARB       (Sensirion_I2C_STS_LOST_ARB_MASK)
    #define Sensirion_I2C_CSR_STOP_STATUS    (Sensirion_I2C_STS_STOP_MASK)
    #define Sensirion_I2C_CSR_BUS_ERROR      (0x00u)
    #define Sensirion_I2C_CSR_ADDRESS        (Sensirion_I2C_STS_ADDR_MASK)
    #define Sensirion_I2C_CSR_TRANSMIT       (Sensirion_I2C_CTRL_TRANSMIT_MASK)
    #define Sensirion_I2C_CSR_LRB            (Sensirion_I2C_STS_LRB_MASK)
    #define Sensirion_I2C_CSR_LRB_NAK        (Sensirion_I2C_STS_LRB_MASK)
    #define Sensirion_I2C_CSR_LRB_ACK        (0x00u)
    #define Sensirion_I2C_CSR_BYTE_COMPLETE  (Sensirion_I2C_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR gegisters definitions */
    #define Sensirion_I2C_MCSR_REG           (Sensirion_I2C_CSR_REG)   /* UDB incoporates master and slave regs */
    #define Sensirion_I2C_MCSR_BUS_BUSY      (Sensirion_I2C_STS_BUSY_MASK)       /* Is bus is busy              */
    #define Sensirion_I2C_MCSR_START_GEN     (Sensirion_I2C_CTRL_START_MASK)     /* Generate Sart condition     */
    #define Sensirion_I2C_MCSR_RESTART_GEN   (Sensirion_I2C_CTRL_RESTART_MASK)   /* Generates RESTART condition */
    #define Sensirion_I2C_MCSR_MSTR_MODE     (Sensirion_I2C_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define Sensirion_I2C_RELEASE_FSM         (0x00u)
    
    /* Check enable of module */
    #define Sensirion_I2C_I2C_ENABLE_REG     (Sensirion_I2C_CFG_REG)
    #define Sensirion_I2C_IS_I2C_ENABLE(reg) ((0u != ((reg) & Sensirion_I2C_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & Sensirion_I2C_ENABLE_SLAVE)))

    #define Sensirion_I2C_IS_ENABLED         (0u != (Sensirion_I2C_CFG_REG & Sensirion_I2C_ENABLE_MS))

    /* Check start condition generation */
    #define Sensirion_I2C_CHECK_START_GEN(mcsr)  ((0u != (Sensirion_I2C_CFG_REG &        \
                                                             Sensirion_I2C_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & Sensirion_I2C_MCSR_MSTR_MODE)))

    #define Sensirion_I2C_CLEAR_START_GEN        do{ \
                                                        Sensirion_I2C_CFG_REG &=                 \
                                                        ((uint8) ~Sensirion_I2C_MCSR_START_GEN); \
                                                    }while(0)


    /* Stop interrupt */
    #define Sensirion_I2C_ENABLE_INT_ON_STOP     do{ \
                                                       Sensirion_I2C_INT_MASK_REG |= Sensirion_I2C_STOP_IE_MASK; \
                                                    }while(0)

    #define Sensirion_I2C_DISABLE_INT_ON_STOP    do{ \
                                                        Sensirion_I2C_INT_MASK_REG &=                               \
                                                                             ((uint8) ~Sensirion_I2C_STOP_IE_MASK); \
                                                    }while(0)


    /* Transmit data */
    #define Sensirion_I2C_TRANSMIT_DATA      do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_TRANSMIT_MASK | \
                                                                                Sensirion_I2C_CTRL_DEFAULT);       \
                                                    Sensirion_I2C_GO_REG  = Sensirion_I2C_RELEASE_FSM;          \
                                                }while(0)

    #define Sensirion_I2C_ACK_AND_TRANSMIT   Sensirion_I2C_TRANSMIT_DATA


    #define Sensirion_I2C_NAK_AND_TRANSMIT   do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_NACK_MASK     | \
                                                                                Sensirion_I2C_CTRL_TRANSMIT_MASK | \
                                                                                Sensirion_I2C_CTRL_DEFAULT);       \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM;         \
                                                }while(0)

    /* Receive data */
    #define Sensirion_I2C_READY_TO_READ      do{ \
                                                    Sensirion_I2C_CFG_REG = Sensirion_I2C_CTRL_DEFAULT; \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM; \
                                                }while(0)

    #define Sensirion_I2C_ACK_AND_RECEIVE    Sensirion_I2C_READY_TO_READ

    #define Sensirion_I2C_NAK_AND_RECEIVE    do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_NACK_MASK | \
                                                                                Sensirion_I2C_CTRL_DEFAULT);   \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM;     \
                                                }while(0)

    /* Master condition generation */
    #define Sensirion_I2C_GENERATE_START     do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_START_MASK | \
                                                                                 Sensirion_I2C_CTRL_DEFAULT);   \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM;      \
                                                }while(0)

    #define Sensirion_I2C_GENERATE_RESTART   do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_RESTART_MASK | \
                                                                                Sensirion_I2C_CTRL_NACK_MASK    | \
                                                                                Sensirion_I2C_CTRL_DEFAULT);      \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM;        \
                                                }while(0)


    #define Sensirion_I2C_GENERATE_STOP      do{ \
                                                    Sensirion_I2C_CFG_REG = (Sensirion_I2C_CTRL_NACK_MASK | \
                                                                                Sensirion_I2C_CTRL_STOP_MASK | \
                                                                                Sensirion_I2C_CTRL_DEFAULT);   \
                                                    Sensirion_I2C_GO_REG  =  Sensirion_I2C_RELEASE_FSM;     \
                                                }while(0)

    /* Master manual APIs compatible defines */
    /* These defines wait while byte complete is cleared after command issued */
    #define Sensirion_I2C_GENERATE_RESTART_MANUAL    \
                                        do{             \
                                            Sensirion_I2C_GENERATE_RESTART;                                    \
                                            while(Sensirion_I2C_CHECK_BYTE_COMPLETE(Sensirion_I2C_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define Sensirion_I2C_GENERATE_STOP_MANUAL   \
                                        do{         \
                                            Sensirion_I2C_GENERATE_STOP;                                       \
                                            while(Sensirion_I2C_CHECK_BYTE_COMPLETE(Sensirion_I2C_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define Sensirion_I2C_TRANSMIT_DATA_MANUAL   \
                                        do{         \
                                            Sensirion_I2C_TRANSMIT_DATA;                                       \
                                            while(Sensirion_I2C_CHECK_BYTE_COMPLETE(Sensirion_I2C_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define Sensirion_I2C_READY_TO_READ_MANUAL   \
                                        do{         \
                                            Sensirion_I2C_READY_TO_READ;      \
                                            while(Sensirion_I2C_CHECK_BYTE_COMPLETE(Sensirion_I2C_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define Sensirion_I2C_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            Sensirion_I2C_ACK_AND_RECEIVE;                                     \
                                            while(Sensirion_I2C_CHECK_BYTE_COMPLETE(Sensirion_I2C_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)
#endif /* (Sensirion_I2C_FF_IMPLEMENTED) */

/* Comon for FF and UDB: used to release bus after lost arb */
#define Sensirion_I2C_BUS_RELEASE    Sensirion_I2C_READY_TO_READ


/***************************************
*     Default register init constants
***************************************/

#define Sensirion_I2C_DISABLE    (0u)
#define Sensirion_I2C_ENABLE     (1u)

#if(Sensirion_I2C_FF_IMPLEMENTED)
    /* Sensirion_I2C_XCFG_REG: bits definition */
    #define Sensirion_I2C_DEFAULT_XCFG_HW_ADDR_EN ((Sensirion_I2C_HW_ADRR_DECODE) ? \
                                                        (Sensirion_I2C_XCFG_HDWR_ADDR_EN) : (0u))

    #define Sensirion_I2C_DEFAULT_XCFG_I2C_ON    ((Sensirion_I2C_WAKEUP_ENABLED) ? \
                                                        (Sensirion_I2C_XCFG_I2C_ON) : (0u))


    #define Sensirion_I2C_DEFAULT_CFG_SIO_SELECT ((Sensirion_I2C_I2C1_SIO_PAIR) ? \
                                                        (Sensirion_I2C_CFG_SIO_SELECT) : (0u))


    /* Sensirion_I2C_CFG_REG: bits definition */
    #define Sensirion_I2C_DEFAULT_CFG_PSELECT    ((Sensirion_I2C_WAKEUP_ENABLED) ? \
                                                        (Sensirion_I2C_CFG_PSELECT) : (0u))

    #define Sensirion_I2C_DEFAULT_CLK_RATE0  ((Sensirion_I2C_DATA_RATE <= 50u) ?        \
                                                    (Sensirion_I2C_CFG_CLK_RATE_050) :     \
                                                    ((Sensirion_I2C_DATA_RATE <= 100u) ?   \
                                                        (Sensirion_I2C_CFG_CLK_RATE_100) : \
                                                        (Sensirion_I2C_CFG_CLK_RATE_400)))

    #define Sensirion_I2C_DEFAULT_CLK_RATE1  ((Sensirion_I2C_DATA_RATE <= 50u) ?           \
                                                 (Sensirion_I2C_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (Sensirion_I2C_CFG_CLK_RATE_GRATER_50))

    #define Sensirion_I2C_DEFAULT_CLK_RATE   ((CY_PSOC5A) ? (Sensirion_I2C_DEFAULT_CLK_RATE0) : \
                                                               (Sensirion_I2C_DEFAULT_CLK_RATE1))


    #define Sensirion_I2C_ENABLE_MASTER      ((Sensirion_I2C_MODE_MASTER_ENABLED) ? \
                                                 (Sensirion_I2C_CFG_EN_MSTR) : (0u))

    #define Sensirion_I2C_ENABLE_SLAVE       ((Sensirion_I2C_MODE_SLAVE_ENABLED) ? \
                                                 (Sensirion_I2C_CFG_EN_SLAVE) : (0u))

    #define Sensirion_I2C_ENABLE_MS      (Sensirion_I2C_ENABLE_MASTER | Sensirion_I2C_ENABLE_SLAVE)


    /* Sensirion_I2C_DEFAULT_XCFG_REG */
    #define Sensirion_I2C_DEFAULT_XCFG   (Sensirion_I2C_XCFG_CLK_EN         | \
                                             Sensirion_I2C_DEFAULT_XCFG_I2C_ON | \
                                             Sensirion_I2C_DEFAULT_XCFG_HW_ADDR_EN)

    /* Sensirion_I2C_DEFAULT_CFG_REG */
    #define Sensirion_I2C_DEFAULT_CFG    (Sensirion_I2C_DEFAULT_CFG_SIO_SELECT | \
                                             Sensirion_I2C_DEFAULT_CFG_PSELECT    | \
                                             Sensirion_I2C_DEFAULT_CLK_RATE       | \
                                             Sensirion_I2C_ENABLE_MASTER          | \
                                             Sensirion_I2C_ENABLE_SLAVE)

    /*Sensirion_I2C_DEFAULT_DIVIDE_FACTOR_REG */
    #define Sensirion_I2C_DEFAULT_DIVIDE_FACTOR  ((CY_PSOC5A) ? ((uint8) 0u) : ((uint16) 1u))

#else
    /* Sensirion_I2C_CFG_REG: bits definition  */
    #define Sensirion_I2C_ENABLE_MASTER  ((Sensirion_I2C_MODE_MASTER_ENABLED) ? \
                                             (Sensirion_I2C_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define Sensirion_I2C_ENABLE_SLAVE   ((Sensirion_I2C_MODE_SLAVE_ENABLED) ? \
                                             (Sensirion_I2C_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define Sensirion_I2C_ENABLE_MS      (Sensirion_I2C_ENABLE_MASTER | Sensirion_I2C_ENABLE_SLAVE)


    #define Sensirion_I2C_DEFAULT_CTRL_ANY_ADDR   ((Sensirion_I2C_HW_ADRR_DECODE) ? \
                                                      (0u) : (Sensirion_I2C_CTRL_ANY_ADDRESS_MASK))

    /* Sensirion_I2C_DEFAULT_CFG_REG */
    #define Sensirion_I2C_DEFAULT_CFG    (Sensirion_I2C_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define Sensirion_I2C_CTRL_DEFAULT   (Sensirion_I2C_DEFAULT_CTRL_ANY_ADDR | Sensirion_I2C_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define Sensirion_I2C_MCLK_PERIOD_VALUE  (0x0Fu)
    #define Sensirion_I2C_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: contorol period */
    #define Sensirion_I2C_PERIOD_VALUE       (0x07u)

    /* Sensirion_I2C_DEFAULT_INT_MASK */
    #define Sensirion_I2C_DEFAULT_INT_MASK   (Sensirion_I2C_BYTE_COMPLETE_IE_MASK)

    /* Sensirion_I2C_DEFAULT_MCLK_PRD_REG */
    #define Sensirion_I2C_DEFAULT_MCLK_PRD   (Sensirion_I2C_MCLK_PERIOD_VALUE)

    /* Sensirion_I2C_DEFAULT_MCLK_CMP_REG */
    #define Sensirion_I2C_DEFAULT_MCLK_CMP   (Sensirion_I2C_MCLK_COMPARE_VALUE)

    /* Sensirion_I2C_DEFAULT_PERIOD_REG */
    #define Sensirion_I2C_DEFAULT_PERIOD     (Sensirion_I2C_PERIOD_VALUE)

#endif /* (Sensirion_I2C_FF_IMPLEMENTED) */


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from I2C 3.20
 */
 
#define Sensirion_I2C_SSTAT_RD_ERR       (0x08u)
#define Sensirion_I2C_SSTAT_WR_ERR       (0x80u)
#define Sensirion_I2C_MSTR_SLAVE_BUSY    (Sensirion_I2C_MSTR_NOT_READY)
#define Sensirion_I2C_MSTAT_ERR_BUF_OVFL (0x80u)
#define Sensirion_I2C_SSTAT_RD_CMPT      (Sensirion_I2C_SSTAT_RD_CMPLT)
#define Sensirion_I2C_SSTAT_WR_CMPT      (Sensirion_I2C_SSTAT_WR_CMPLT)
#define Sensirion_I2C_MODE_MULTI_MASTER_ENABLE    (Sensirion_I2C_MODE_MULTI_MASTER_MASK)
#define Sensirion_I2C_DATA_RATE_50       (50u)
#define Sensirion_I2C_DATA_RATE_100      (100u)
#define Sensirion_I2C_DEV_MASK           (0xF0u)
#define Sensirion_I2C_SM_SL_STOP         (0x14u)
#define Sensirion_I2C_SM_MASTER_IDLE     (0x40u)
#define Sensirion_I2C_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_Sensirion_I2C_H */


/* [] END OF FILE */
