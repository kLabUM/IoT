/*******************************************************************************
* File Name: NEOMOTE_1_I2C_0.h
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

#if !defined(CY_I2C_NEOMOTE_1_I2C_0_H)
#define CY_I2C_NEOMOTE_1_I2C_0_H

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

#define NEOMOTE_1_I2C_0_IMPLEMENTATION     (1u)
#define NEOMOTE_1_I2C_0_MODE               (2u)
#define NEOMOTE_1_I2C_0_ENABLE_WAKEUP      (0u)
#define NEOMOTE_1_I2C_0_ADDR_DECODE        (1u)
#define NEOMOTE_1_I2C_0_UDB_INTRN_CLOCK    (0u)


/* I2C implementation enum */
#define NEOMOTE_1_I2C_0_UDB    (0x00u)
#define NEOMOTE_1_I2C_0_FF     (0x01u)

#define NEOMOTE_1_I2C_0_FF_IMPLEMENTED     (NEOMOTE_1_I2C_0_FF  == NEOMOTE_1_I2C_0_IMPLEMENTATION)
#define NEOMOTE_1_I2C_0_UDB_IMPLEMENTED    (NEOMOTE_1_I2C_0_UDB == NEOMOTE_1_I2C_0_IMPLEMENTATION)

#define NEOMOTE_1_I2C_0_UDB_INTRN_CLOCK_ENABLED    (NEOMOTE_1_I2C_0_UDB_IMPLEMENTED && \
                                                     (0u != NEOMOTE_1_I2C_0_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define NEOMOTE_1_I2C_0_MODE_SLAVE                 (0x01u)
#define NEOMOTE_1_I2C_0_MODE_MASTER                (0x02u)
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER          (0x06u)
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_MASK     (0x04u)

#define NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED         (0u != (NEOMOTE_1_I2C_0_MODE_SLAVE  & NEOMOTE_1_I2C_0_MODE))
#define NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED        (0u != (NEOMOTE_1_I2C_0_MODE_MASTER & NEOMOTE_1_I2C_0_MODE))
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_ENABLED  (0u != (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_MASK & \
                                                            NEOMOTE_1_I2C_0_MODE))
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE_ENABLED    (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE == \
                                                             NEOMOTE_1_I2C_0_MODE)

/* Address detection enum */
#define NEOMOTE_1_I2C_0_SW_DECODE      (0x00u)
#define NEOMOTE_1_I2C_0_HW_DECODE      (0x01u)

#define NEOMOTE_1_I2C_0_SW_ADRR_DECODE             (NEOMOTE_1_I2C_0_SW_DECODE == NEOMOTE_1_I2C_0_ADDR_DECODE)
#define NEOMOTE_1_I2C_0_HW_ADRR_DECODE             (NEOMOTE_1_I2C_0_HW_DECODE == NEOMOTE_1_I2C_0_ADDR_DECODE)

/* Wakeup enabled */
#define NEOMOTE_1_I2C_0_WAKEUP_ENABLED             (0u != NEOMOTE_1_I2C_0_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define NEOMOTE_1_I2C_0_BOOTLOADER_INTERFACE_ENABLED   (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_I2C_0) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define NEOMOTE_1_I2C_0_TIMEOUT_ENABLE             (0u)
#define NEOMOTE_1_I2C_0_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define NEOMOTE_1_I2C_0_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLE   (0u)
#define NEOMOTE_1_I2C_0_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define NEOMOTE_1_I2C_0_TIMEOUT_ENABLED            (0u != NEOMOTE_1_I2C_0_TIMEOUT_ENABLE)
#define NEOMOTE_1_I2C_0_TIMEOUT_SCL_TMOUT_ENABLED  (0u != NEOMOTE_1_I2C_0_TIMEOUT_SCL_TMOUT_ENABLE)
#define NEOMOTE_1_I2C_0_TIMEOUT_SDA_TMOUT_ENABLED  (0u != NEOMOTE_1_I2C_0_TIMEOUT_SDA_TMOUT_ENABLE)
#define NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLED  (0u != NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define NEOMOTE_1_I2C_0_TIMEOUT_UDB    (0x00u)
#define NEOMOTE_1_I2C_0_TIMEOUT_FF     (0x01u)

#define NEOMOTE_1_I2C_0_TIMEOUT_FF_IMPLEMENTED     (NEOMOTE_1_I2C_0_TIMEOUT_FF  == \
                                                        NEOMOTE_1_I2C_0_TIMEOUT_IMPLEMENTATION)
#define NEOMOTE_1_I2C_0_TIMEOUT_UDB_IMPLEMENTED    (NEOMOTE_1_I2C_0_TIMEOUT_UDB == \
                                                        NEOMOTE_1_I2C_0_TIMEOUT_IMPLEMENTATION)

#define NEOMOTE_1_I2C_0_TIMEOUT_FF_ENABLED         (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED && \
                                                     NEOMOTE_1_I2C_0_TIMEOUT_FF_IMPLEMENTED && \
                                                     CY_PSOC5LP)

#define NEOMOTE_1_I2C_0_TIMEOUT_UDB_ENABLED        (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED && \
                                                     NEOMOTE_1_I2C_0_TIMEOUT_UDB_IMPLEMENTED)

#define NEOMOTE_1_I2C_0_EXTERN_I2C_INTR_HANDLER    (0u)
#define NEOMOTE_1_I2C_0_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define NEOMOTE_1_I2C_0_INTERN_I2C_INTR_HANDLER    (0u == NEOMOTE_1_I2C_0_EXTERN_I2C_INTR_HANDLER)
#define NEOMOTE_1_I2C_0_INTERN_TMOUT_INTR_HANDLER  (0u == NEOMOTE_1_I2C_0_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

    #if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
        uint8 xcfg;
        uint8 cfg;

        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            uint8 addr;
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

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

            #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
                uint8 addr;
            #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */
        #endif     /* (CY_UDB_V0) */

    #endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
        uint16 tmoutCfg;
        uint8  tmoutIntr;

        #if(NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            uint8 tmoutPrd;
        #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0) */

    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */

} NEOMOTE_1_I2C_0_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void NEOMOTE_1_I2C_0_Init(void)                            ;
void NEOMOTE_1_I2C_0_Enable(void)                          ;

void NEOMOTE_1_I2C_0_Start(void)                           ;
void NEOMOTE_1_I2C_0_Stop(void)                            ;

#define NEOMOTE_1_I2C_0_EnableInt()        CyIntEnable      (NEOMOTE_1_I2C_0_ISR_NUMBER)
#define NEOMOTE_1_I2C_0_DisableInt()       CyIntDisable     (NEOMOTE_1_I2C_0_ISR_NUMBER)
#define NEOMOTE_1_I2C_0_ClearPendingInt()  CyIntClearPending(NEOMOTE_1_I2C_0_ISR_NUMBER)
#define NEOMOTE_1_I2C_0_SetPendingInt()    CyIntSetPending  (NEOMOTE_1_I2C_0_ISR_NUMBER)

void NEOMOTE_1_I2C_0_SaveConfig(void)                      ;
void NEOMOTE_1_I2C_0_Sleep(void)                           ;
void NEOMOTE_1_I2C_0_RestoreConfig(void)                   ;
void NEOMOTE_1_I2C_0_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 NEOMOTE_1_I2C_0_MasterStatus(void)                ;
    uint8 NEOMOTE_1_I2C_0_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 NEOMOTE_1_I2C_0_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 NEOMOTE_1_I2C_0_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 NEOMOTE_1_I2C_0_MasterGetReadBufSize(void)       ;
    uint8 NEOMOTE_1_I2C_0_MasterGetWriteBufSize(void)      ;
    void  NEOMOTE_1_I2C_0_MasterClearReadBuf(void)         ;
    void  NEOMOTE_1_I2C_0_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 NEOMOTE_1_I2C_0_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 NEOMOTE_1_I2C_0_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 NEOMOTE_1_I2C_0_MasterSendStop(void)             ;
    uint8 NEOMOTE_1_I2C_0_MasterWriteByte(uint8 theByte)   ;
    uint8 NEOMOTE_1_I2C_0_MasterReadByte(uint8 acknNak)    ;

    /* This fake function use as workaround */
    void  NEOMOTE_1_I2C_0_Workaround(void)                 ;

#endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 NEOMOTE_1_I2C_0_SlaveStatus(void)                ;
    uint8 NEOMOTE_1_I2C_0_SlaveClearReadStatus(void)       ;
    uint8 NEOMOTE_1_I2C_0_SlaveClearWriteStatus(void)      ;

    void  NEOMOTE_1_I2C_0_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  NEOMOTE_1_I2C_0_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  NEOMOTE_1_I2C_0_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 NEOMOTE_1_I2C_0_SlaveGetReadBufSize(void)        ;
    uint8 NEOMOTE_1_I2C_0_SlaveGetWriteBufSize(void)       ;
    void  NEOMOTE_1_I2C_0_SlaveClearReadBuf(void)          ;
    void  NEOMOTE_1_I2C_0_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (NEOMOTE_1_I2C_0_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     NEOMOTE_1_I2C_0_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     NEOMOTE_1_I2C_0_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     NEOMOTE_1_I2C_0_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus NEOMOTE_1_I2C_0_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus NEOMOTE_1_I2C_0_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_I2C_0)
            #define CyBtldrCommStart    NEOMOTE_1_I2C_0_CyBtldrCommStart
            #define CyBtldrCommStop     NEOMOTE_1_I2C_0_CyBtldrCommStop
            #define CyBtldrCommReset    NEOMOTE_1_I2C_0_CyBtldrCommReset
            #define CyBtldrCommWrite    NEOMOTE_1_I2C_0_CyBtldrCommWrite
            #define CyBtldrCommRead     NEOMOTE_1_I2C_0_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_I2C_0) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define NEOMOTE_1_I2C_0_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define NEOMOTE_1_I2C_0_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define NEOMOTE_1_I2C_0_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define NEOMOTE_1_I2C_0_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (NEOMOTE_1_I2C_0_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

/* I2C interrupt handler */
CY_ISR_PROTO(NEOMOTE_1_I2C_0_ISR);
#if((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) || (NEOMOTE_1_I2C_0_WAKEUP_ENABLED))
    CY_ISR_PROTO(NEOMOTE_1_I2C_0_WAKEUP_ISR);
#endif /* ((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) || (NEOMOTE_1_I2C_0_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 NEOMOTE_1_I2C_0_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define NEOMOTE_1_I2C_0_DATA_RATE          (100u)
#define NEOMOTE_1_I2C_0_DEFAULT_ADDR       (8u)
#define NEOMOTE_1_I2C_0_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define NEOMOTE_1_I2C_0_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define NEOMOTE_1_I2C_0_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define NEOMOTE_1_I2C_0_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define NEOMOTE_1_I2C_0_I2C1_SIO_PAIR  (NEOMOTE_1_I2C_0_I2C_PAIR1 == NEOMOTE_1_I2C_0_I2C_PAIR_SELECTED)
#define NEOMOTE_1_I2C_0_I2C0_SIO_PAIR  (NEOMOTE_1_I2C_0_I2C_PAIR0 == NEOMOTE_1_I2C_0_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define NEOMOTE_1_I2C_0_READ_XFER_MODE     (0x01u) /* Read */
#define NEOMOTE_1_I2C_0_WRITE_XFER_MODE    (0x00u) /* Write */
#define NEOMOTE_1_I2C_0_ACK_DATA           (0x01u) /* Send ACK */
#define NEOMOTE_1_I2C_0_NAK_DATA           (0x00u) /* Send NAK */
#define NEOMOTE_1_I2C_0_OVERFLOW_RETURN    (0xFFu) /* Senf on bus in case of overflow */

#if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define NEOMOTE_1_I2C_0_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define NEOMOTE_1_I2C_0_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define NEOMOTE_1_I2C_0_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define NEOMOTE_1_I2C_0_MSTAT_CLEAR            (0x00u) /* Clear (init) status value */

    #define NEOMOTE_1_I2C_0_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define NEOMOTE_1_I2C_0_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define NEOMOTE_1_I2C_0_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define NEOMOTE_1_I2C_0_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define NEOMOTE_1_I2C_0_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define NEOMOTE_1_I2C_0_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define NEOMOTE_1_I2C_0_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define NEOMOTE_1_I2C_0_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define NEOMOTE_1_I2C_0_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define NEOMOTE_1_I2C_0_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define NEOMOTE_1_I2C_0_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define NEOMOTE_1_I2C_0_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define NEOMOTE_1_I2C_0_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define NEOMOTE_1_I2C_0_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define NEOMOTE_1_I2C_0_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */

#if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define NEOMOTE_1_I2C_0_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define NEOMOTE_1_I2C_0_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define NEOMOTE_1_I2C_0_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define NEOMOTE_1_I2C_0_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define NEOMOTE_1_I2C_0_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define NEOMOTE_1_I2C_0_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define NEOMOTE_1_I2C_0_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define NEOMOTE_1_I2C_0_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define NEOMOTE_1_I2C_0_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define NEOMOTE_1_I2C_0_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define NEOMOTE_1_I2C_0_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define NEOMOTE_1_I2C_0_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  NEOMOTE_1_I2C_0_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  NEOMOTE_1_I2C_0_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  NEOMOTE_1_I2C_0_SM_SLAVE          (NEOMOTE_1_I2C_0_SM_IDLE) /* Any Slave state */
#define  NEOMOTE_1_I2C_0_SM_SL_WR_DATA     (0x11u) /* Master writes data to slzve  */
#define  NEOMOTE_1_I2C_0_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  NEOMOTE_1_I2C_0_SM_MASTER         (0x40u) /* Any master state */

#define  NEOMOTE_1_I2C_0_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  NEOMOTE_1_I2C_0_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  NEOMOTE_1_I2C_0_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  NEOMOTE_1_I2C_0_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  NEOMOTE_1_I2C_0_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  NEOMOTE_1_I2C_0_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  NEOMOTE_1_I2C_0_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define NEOMOTE_1_I2C_0_CHECK_SM_MASTER    (0u != (NEOMOTE_1_I2C_0_SM_MASTER & NEOMOTE_1_I2C_0_state))
#define NEOMOTE_1_I2C_0_CHECK_SM_SLAVE     (0u != (NEOMOTE_1_I2C_0_SM_SLAVE  & NEOMOTE_1_I2C_0_state))


/***************************************
*              Registers
***************************************/

#if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define NEOMOTE_1_I2C_0_XCFG_REG           (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__XCFG)
    #define NEOMOTE_1_I2C_0_XCFG_PTR           (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__XCFG)

    #define NEOMOTE_1_I2C_0_ADDR_REG           (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__ADR)
    #define NEOMOTE_1_I2C_0_ADDR_PTR           (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__ADR)

    #define NEOMOTE_1_I2C_0_CFG_REG            (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CFG)
    #define NEOMOTE_1_I2C_0_CFG_PTR            (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CFG)

    #define NEOMOTE_1_I2C_0_CSR_REG            (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CSR)
    #define NEOMOTE_1_I2C_0_CSR_PTR            (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CSR)

    #define NEOMOTE_1_I2C_0_DATA_REG           (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__D)
    #define NEOMOTE_1_I2C_0_DATA_PTR           (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__D)

    #define NEOMOTE_1_I2C_0_MCSR_REG           (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__MCSR)
    #define NEOMOTE_1_I2C_0_MCSR_PTR           (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__MCSR)

    #define NEOMOTE_1_I2C_0_ACT_PWRMGR_REG     (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__PM_ACT_CFG)
    #define NEOMOTE_1_I2C_0_ACT_PWRMGR_PTR     (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__PM_ACT_CFG)
    #define NEOMOTE_1_I2C_0_ACT_PWR_EN         (  (uint8)  NEOMOTE_1_I2C_0_I2C_FF__PM_ACT_MSK)

    #define NEOMOTE_1_I2C_0_STBY_PWRMGR_REG    (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__PM_STBY_CFG)
    #define NEOMOTE_1_I2C_0_STBY_PWRMGR_PTR    (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__PM_STBY_CFG)
    #define NEOMOTE_1_I2C_0_STBY_PWR_EN        (  (uint8)  NEOMOTE_1_I2C_0_I2C_FF__PM_STBY_MSK)

    #define NEOMOTE_1_I2C_0_PWRSYS_CR1_REG     (* (reg8 *) CYREG_PWRSYS_CR1)
    #define NEOMOTE_1_I2C_0_PWRSYS_CR1_PTR     (  (reg8 *) CYREG_PWRSYS_CR1)

    /* Clock divider register depends on silicon */
    #if(CY_PSOC5A)
        #define NEOMOTE_1_I2C_0_CLKDIV_REG     (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV)
        #define NEOMOTE_1_I2C_0_CLKDIV_PTR     (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV)

    #else
        #define NEOMOTE_1_I2C_0_CLKDIV1_REG    (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV1)
        #define NEOMOTE_1_I2C_0_CLKDIV1_PTR    (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV1)

        #define NEOMOTE_1_I2C_0_CLKDIV2_REG    (* (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV2)
        #define NEOMOTE_1_I2C_0_CLKDIV2_PTR    (  (reg8 *) NEOMOTE_1_I2C_0_I2C_FF__CLK_DIV2)

    #endif /* (CY_PSOC5A) */

#else
    /* UDB implementation registers */
    #define NEOMOTE_1_I2C_0_CFG_REG    (* (reg8 *) \
                                           NEOMOTE_1_I2C_0_bI2C_UDB_AsyncCtl_CtrlReg__CONTROL_REG)
    #define NEOMOTE_1_I2C_0_CFG_PTR    (  (reg8 *) \
                                           NEOMOTE_1_I2C_0_bI2C_UDB_AsyncCtl_CtrlReg__CONTROL_REG)

    #define NEOMOTE_1_I2C_0_CSR_REG        (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__STATUS_REG)
    #define NEOMOTE_1_I2C_0_CSR_PTR        (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__STATUS_REG)

    #define NEOMOTE_1_I2C_0_INT_MASK_REG   (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__MASK_REG)
    #define NEOMOTE_1_I2C_0_INT_MASK_PTR   (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__MASK_REG)

    #define NEOMOTE_1_I2C_0_INT_ENABLE_REG (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define NEOMOTE_1_I2C_0_INT_ENABLE_PTR (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define NEOMOTE_1_I2C_0_DATA_REG       (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__A0_REG)
    #define NEOMOTE_1_I2C_0_DATA_PTR       (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__A0_REG)

    #define NEOMOTE_1_I2C_0_GO_REG         (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__F1_REG)
    #define NEOMOTE_1_I2C_0_GO_PTR         (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__F1_REG)

    #define NEOMOTE_1_I2C_0_MCLK_PRD_REG   (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define NEOMOTE_1_I2C_0_MCLK_PRD_PTR   (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define NEOMOTE_1_I2C_0_MCLK_CMP_REG   (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define NEOMOTE_1_I2C_0_MCLK_CMP_PTR   (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
        #define NEOMOTE_1_I2C_0_ADDR_REG       (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__D0_REG)
        #define NEOMOTE_1_I2C_0_ADDR_PTR       (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Shifter_u0__D0_REG)

        #define NEOMOTE_1_I2C_0_PERIOD_REG     (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define NEOMOTE_1_I2C_0_PERIOD_PTR     (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define NEOMOTE_1_I2C_0_COUNTER_REG    (* (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define NEOMOTE_1_I2C_0_COUNTER_PTR    (  (reg8 *) NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define NEOMOTE_1_I2C_0_COUNTER_AUX_CTL_REG  (* (reg8 *) \
                                                        NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define NEOMOTE_1_I2C_0_COUNTER_AUX_CTL_PTR  (  (reg8 *) \
                                                        NEOMOTE_1_I2C_0_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

#endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* NEOMOTE_1_I2C_0_I2C_IRQ */
#define NEOMOTE_1_I2C_0_ISR_NUMBER     ((uint8) NEOMOTE_1_I2C_0_I2C_IRQ__INTC_NUMBER)
#define NEOMOTE_1_I2C_0_ISR_PRIORITY   ((uint8) NEOMOTE_1_I2C_0_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define NEOMOTE_1_I2C_0_SLAVE_ADDR_MASK    (0x7Fu)
#define NEOMOTE_1_I2C_0_SLAVE_ADDR_SHIFT   (0x01u)
#define NEOMOTE_1_I2C_0_DATA_MASK          (0xFFu)
#define NEOMOTE_1_I2C_0_READ_FLAG          (0x01u)

#define NEOMOTE_1_I2C_0_FF_RESET_DELAY     (0x02u)

#if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define NEOMOTE_1_I2C_0_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define NEOMOTE_1_I2C_0_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define NEOMOTE_1_I2C_0_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define NEOMOTE_1_I2C_0_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incomming transactions */
    #define NEOMOTE_1_I2C_0_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define NEOMOTE_1_I2C_0_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define NEOMOTE_1_I2C_0_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define NEOMOTE_1_I2C_0_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define NEOMOTE_1_I2C_0_CFG_PSELECT        (0x40u) /* Pin Select */
    #define NEOMOTE_1_I2C_0_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define NEOMOTE_1_I2C_0_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select  **CHECK**  */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define NEOMOTE_1_I2C_0_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define NEOMOTE_1_I2C_0_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define NEOMOTE_1_I2C_0_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define NEOMOTE_1_I2C_0_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occured */
    #define NEOMOTE_1_I2C_0_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define NEOMOTE_1_I2C_0_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define NEOMOTE_1_I2C_0_CSR_ACK            (0x10u) /* ACK response */
    #define NEOMOTE_1_I2C_0_CSR_NAK            (0x00u) /* NAK response */
    #define NEOMOTE_1_I2C_0_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define NEOMOTE_1_I2C_0_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define NEOMOTE_1_I2C_0_CSR_LRB            (0x02u) /* Last received bit */
    #define NEOMOTE_1_I2C_0_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define NEOMOTE_1_I2C_0_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define NEOMOTE_1_I2C_0_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define NEOMOTE_1_I2C_0_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define NEOMOTE_1_I2C_0_CSR_RDY_TO_RD      (0x00u) /* Set to recieve mode */

    /* MCSR I2C Master Control and Status Register */
    #define NEOMOTE_1_I2C_0_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define NEOMOTE_1_I2C_0_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define NEOMOTE_1_I2C_0_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define NEOMOTE_1_I2C_0_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define NEOMOTE_1_I2C_0_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* CLK_DIV I2C Clock Divide Factor Register */
    #define NEOMOTE_1_I2C_0_CLK_DIV_MSK    (0x07u) /* Status bit, Set at Start and cleared at Stop condition */
    #define NEOMOTE_1_I2C_0_CLK_DIV_1      (0x00u) /* Divide input clock by  1 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_2      (0x01u) /* Divide input clock by  2 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_4      (0x02u) /* Divide input clock by  4 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_8      (0x03u) /* Divide input clock by  8 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_16     (0x04u) /* Divide input clock by 16 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_32     (0x05u) /* Divide input clock by 32 */
    #define NEOMOTE_1_I2C_0_CLK_DIV_64     (0x06u) /* Divide input clock by 64 */

    /* PWRSYS_CR1 to handle Sleep */
    #define NEOMOTE_1_I2C_0_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define NEOMOTE_1_I2C_0_CTRL_START_SHIFT           (7u)
    #define NEOMOTE_1_I2C_0_CTRL_STOP_SHIFT            (6u)
    #define NEOMOTE_1_I2C_0_CTRL_RESTART_SHIFT         (5u)
    #define NEOMOTE_1_I2C_0_CTRL_NACK_SHIFT            (4u)
    #define NEOMOTE_1_I2C_0_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define NEOMOTE_1_I2C_0_CTRL_TRANSMIT_SHIFT        (2u)
    #define NEOMOTE_1_I2C_0_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define NEOMOTE_1_I2C_0_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define NEOMOTE_1_I2C_0_CTRL_START_MASK            ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_START_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_STOP_MASK             ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_STOP_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_RESTART_MASK          ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_RESTART_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_NACK_MASK             ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_NACK_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_ANY_ADDRESS_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_TRANSMIT_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_ENABLE_MASTER_SHIFT))
    #define NEOMOTE_1_I2C_0_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << NEOMOTE_1_I2C_0_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define NEOMOTE_1_I2C_0_STS_LOST_ARB_SHIFT         (6u)
    #define NEOMOTE_1_I2C_0_STS_STOP_SHIFT             (5u)
    #define NEOMOTE_1_I2C_0_STS_BUSY_SHIFT             (4u)
    #define NEOMOTE_1_I2C_0_STS_ADDR_SHIFT             (3u)
    #define NEOMOTE_1_I2C_0_STS_MASTER_MODE_SHIFT      (2u)
    #define NEOMOTE_1_I2C_0_STS_LRB_SHIFT              (1u)
    #define NEOMOTE_1_I2C_0_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define NEOMOTE_1_I2C_0_STS_LOST_ARB_MASK          ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_LOST_ARB_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_STOP_MASK              ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_STOP_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_BUSY_MASK              ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_BUSY_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_ADDR_MASK              ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_ADDR_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_MASTER_MODE_MASK       ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_MASTER_MODE_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_LRB_MASK               ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_LRB_SHIFT))
    #define NEOMOTE_1_I2C_0_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << NEOMOTE_1_I2C_0_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define NEOMOTE_1_I2C_0_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter     */
    #define NEOMOTE_1_I2C_0_INT_ENABLE_MASK            (0x10u) /* Enable intr from statusi */
    #define NEOMOTE_1_I2C_0_CNT7_ENABLE                (NEOMOTE_1_I2C_0_COUNTER_ENABLE_MASK)
    #define NEOMOTE_1_I2C_0_INTR_ENABLE                (NEOMOTE_1_I2C_0_INT_ENABLE_MASK)

#endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define NEOMOTE_1_I2C_0_CHECK_ADDR_ACK(csr)    ((NEOMOTE_1_I2C_0_CSR_LRB_ACK | NEOMOTE_1_I2C_0_CSR_ADDRESS) == \
                                                 ((NEOMOTE_1_I2C_0_CSR_LRB    | NEOMOTE_1_I2C_0_CSR_ADDRESS) &  \
                                                  (csr)))


#define NEOMOTE_1_I2C_0_CHECK_ADDR_NAK(csr)    ((NEOMOTE_1_I2C_0_CSR_LRB_NAK | NEOMOTE_1_I2C_0_CSR_ADDRESS) == \
                                                 ((NEOMOTE_1_I2C_0_CSR_LRB    | NEOMOTE_1_I2C_0_CSR_ADDRESS) &  \
                                                  (csr)))

#define NEOMOTE_1_I2C_0_CHECK_DATA_ACK(csr)    (0u == ((csr) & NEOMOTE_1_I2C_0_CSR_LRB_NAK))

/* MCSR conditions check */
#define NEOMOTE_1_I2C_0_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & NEOMOTE_1_I2C_0_MCSR_BUS_BUSY))
#define NEOMOTE_1_I2C_0_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & NEOMOTE_1_I2C_0_MCSR_MSTR_MODE))

/* CSR conditions check */
#define NEOMOTE_1_I2C_0_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & NEOMOTE_1_I2C_0_CSR_BYTE_COMPLETE))
#define NEOMOTE_1_I2C_0_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (NEOMOTE_1_I2C_0_CSR_BYTE_COMPLETE | \
                                                                     NEOMOTE_1_I2C_0_CSR_STOP_STATUS)))
#define NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & NEOMOTE_1_I2C_0_CSR_BYTE_COMPLETE))
#define NEOMOTE_1_I2C_0_CHECK_STOP_STS(csr)        (0u != ((csr) & NEOMOTE_1_I2C_0_CSR_STOP_STATUS))
#define NEOMOTE_1_I2C_0_CHECK_LOST_ARB(csr)        (0u != ((csr) & NEOMOTE_1_I2C_0_CSR_LOST_ARB))
#define NEOMOTE_1_I2C_0_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & NEOMOTE_1_I2C_0_CSR_ADDRESS))

/* Software start and end of transaction check */
#define NEOMOTE_1_I2C_0_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & NEOMOTE_1_I2C_0_MODE_REPEAT_START))
#define NEOMOTE_1_I2C_0_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & NEOMOTE_1_I2C_0_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define NEOMOTE_1_I2C_0_GET_MSTAT_CMPLT ((0u != (NEOMOTE_1_I2C_0_state & NEOMOTE_1_I2C_0_SM_MSTR_RD)) ? \
                                                 (NEOMOTE_1_I2C_0_MSTAT_RD_CMPLT) : (NEOMOTE_1_I2C_0_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address and used for software address match */
#define NEOMOTE_1_I2C_0_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> NEOMOTE_1_I2C_0_SLAVE_ADDR_SHIFT) & \
                                                                  NEOMOTE_1_I2C_0_SLAVE_ADDR_MASK)

#if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
    /* Check enable of module */
    #define NEOMOTE_1_I2C_0_I2C_ENABLE_REG     (NEOMOTE_1_I2C_0_ACT_PWRMGR_REG)
    #define NEOMOTE_1_I2C_0_IS_I2C_ENABLE(reg) (0u != ((reg) & NEOMOTE_1_I2C_0_ACT_PWR_EN))
    #define NEOMOTE_1_I2C_0_IS_ENABLED         (0u != (NEOMOTE_1_I2C_0_ACT_PWRMGR_REG & NEOMOTE_1_I2C_0_ACT_PWR_EN))

    #define NEOMOTE_1_I2C_0_CHECK_PWRSYS_I2C_BACKUP    (0u != (NEOMOTE_1_I2C_0_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                NEOMOTE_1_I2C_0_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define NEOMOTE_1_I2C_0_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & NEOMOTE_1_I2C_0_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & NEOMOTE_1_I2C_0_MCSR_MSTR_MODE)))

    #define NEOMOTE_1_I2C_0_CLEAR_START_GEN        do{ \
                                                        NEOMOTE_1_I2C_0_MCSR_REG &=                                   \
                                                                           ((uint8) ~NEOMOTE_1_I2C_0_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP     do{ \
                                                        NEOMOTE_1_I2C_0_CFG_REG |= NEOMOTE_1_I2C_0_CFG_STOP_IE; \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP    do{ \
                                                        NEOMOTE_1_I2C_0_CFG_REG &=                                 \
                                                                           ((uint8) ~NEOMOTE_1_I2C_0_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define NEOMOTE_1_I2C_0_TRANSMIT_DATA          do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_TRANSMIT; \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT       do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = (NEOMOTE_1_I2C_0_CSR_ACK |      \
                                                                                    NEOMOTE_1_I2C_0_CSR_TRANSMIT); \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_NAK_AND_TRANSMIT       do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define NEOMOTE_1_I2C_0_ACKNAK_AND_TRANSMIT    do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG  = (NEOMOTE_1_I2C_0_CSR_NAK |      \
                                                                                     NEOMOTE_1_I2C_0_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define NEOMOTE_1_I2C_0_ACK_AND_RECEIVE        do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_ACK; \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_NAK_AND_RECEIVE        do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_NAK; \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_READY_TO_READ          do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Master condition generation */
    #define NEOMOTE_1_I2C_0_GENERATE_START         do{ \
                                                        NEOMOTE_1_I2C_0_MCSR_REG = NEOMOTE_1_I2C_0_MCSR_START_GEN; \
                                                    }while(0)

    #if(CY_PSOC5A)
        #define NEOMOTE_1_I2C_0_GENERATE_RESTART \
                        do{ \
                            NEOMOTE_1_I2C_0_MCSR_REG = NEOMOTE_1_I2C_0_MCSR_RESTART_GEN; \
                            NEOMOTE_1_I2C_0_CSR_REG  = NEOMOTE_1_I2C_0_CSR_NAK;          \
                        }while(0)

        #define NEOMOTE_1_I2C_0_GENERATE_STOP      do{ \
                                                        NEOMOTE_1_I2C_0_CSR_REG = NEOMOTE_1_I2C_0_CSR_STOP_GEN; \
                                                    }while(0)

    #else   /* PSoC3 ES3 handlees zero lenght packets */
        #define NEOMOTE_1_I2C_0_GENERATE_RESTART \
                        do{ \
                            NEOMOTE_1_I2C_0_MCSR_REG = (NEOMOTE_1_I2C_0_MCSR_RESTART_GEN | \
                                                         NEOMOTE_1_I2C_0_MCSR_STOP_GEN);    \
                            NEOMOTE_1_I2C_0_CSR_REG  = NEOMOTE_1_I2C_0_CSR_TRANSMIT;       \
                        }while(0)

        #define NEOMOTE_1_I2C_0_GENERATE_STOP \
                        do{ \
                            NEOMOTE_1_I2C_0_MCSR_REG = NEOMOTE_1_I2C_0_MCSR_STOP_GEN; \
                            NEOMOTE_1_I2C_0_CSR_REG  = NEOMOTE_1_I2C_0_CSR_TRANSMIT;  \
                        }while(0)
    #endif /* (CY_PSOC5A) */

    /* Master manual APIs compatible defines */
    #define NEOMOTE_1_I2C_0_GENERATE_RESTART_MANUAL    NEOMOTE_1_I2C_0_GENERATE_RESTART
    #define NEOMOTE_1_I2C_0_GENERATE_STOP_MANUAL       NEOMOTE_1_I2C_0_GENERATE_STOP
    #define NEOMOTE_1_I2C_0_TRANSMIT_DATA_MANUAL       NEOMOTE_1_I2C_0_TRANSMIT_DATA
    #define NEOMOTE_1_I2C_0_READY_TO_READ_MANUAL       NEOMOTE_1_I2C_0_READY_TO_READ
    #define NEOMOTE_1_I2C_0_ACK_AND_RECEIVE_MANUAL     NEOMOTE_1_I2C_0_ACK_AND_RECEIVE

#else

    /* Masks to enalbe interrupts from Status register */
    #define NEOMOTE_1_I2C_0_STOP_IE_MASK           (NEOMOTE_1_I2C_0_STS_STOP_MASK)
    #define NEOMOTE_1_I2C_0_BYTE_COMPLETE_IE_MASK  (NEOMOTE_1_I2C_0_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR gegisters definitions */
    #define NEOMOTE_1_I2C_0_CSR_LOST_ARB       (NEOMOTE_1_I2C_0_STS_LOST_ARB_MASK)
    #define NEOMOTE_1_I2C_0_CSR_STOP_STATUS    (NEOMOTE_1_I2C_0_STS_STOP_MASK)
    #define NEOMOTE_1_I2C_0_CSR_BUS_ERROR      (0x00u)
    #define NEOMOTE_1_I2C_0_CSR_ADDRESS        (NEOMOTE_1_I2C_0_STS_ADDR_MASK)
    #define NEOMOTE_1_I2C_0_CSR_TRANSMIT       (NEOMOTE_1_I2C_0_CTRL_TRANSMIT_MASK)
    #define NEOMOTE_1_I2C_0_CSR_LRB            (NEOMOTE_1_I2C_0_STS_LRB_MASK)
    #define NEOMOTE_1_I2C_0_CSR_LRB_NAK        (NEOMOTE_1_I2C_0_STS_LRB_MASK)
    #define NEOMOTE_1_I2C_0_CSR_LRB_ACK        (0x00u)
    #define NEOMOTE_1_I2C_0_CSR_BYTE_COMPLETE  (NEOMOTE_1_I2C_0_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR gegisters definitions */
    #define NEOMOTE_1_I2C_0_MCSR_REG           (NEOMOTE_1_I2C_0_CSR_REG)   /* UDB incoporates master and slave regs */
    #define NEOMOTE_1_I2C_0_MCSR_BUS_BUSY      (NEOMOTE_1_I2C_0_STS_BUSY_MASK)       /* Is bus is busy              */
    #define NEOMOTE_1_I2C_0_MCSR_START_GEN     (NEOMOTE_1_I2C_0_CTRL_START_MASK)     /* Generate Sart condition     */
    #define NEOMOTE_1_I2C_0_MCSR_RESTART_GEN   (NEOMOTE_1_I2C_0_CTRL_RESTART_MASK)   /* Generates RESTART condition */
    #define NEOMOTE_1_I2C_0_MCSR_MSTR_MODE     (NEOMOTE_1_I2C_0_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define NEOMOTE_1_I2C_0_RELEASE_FSM         (0x00u)
    
    /* Check enable of module */
    #define NEOMOTE_1_I2C_0_I2C_ENABLE_REG     (NEOMOTE_1_I2C_0_CFG_REG)
    #define NEOMOTE_1_I2C_0_IS_I2C_ENABLE(reg) ((0u != ((reg) & NEOMOTE_1_I2C_0_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & NEOMOTE_1_I2C_0_ENABLE_SLAVE)))

    #define NEOMOTE_1_I2C_0_IS_ENABLED         (0u != (NEOMOTE_1_I2C_0_CFG_REG & NEOMOTE_1_I2C_0_ENABLE_MS))

    /* Check start condition generation */
    #define NEOMOTE_1_I2C_0_CHECK_START_GEN(mcsr)  ((0u != (NEOMOTE_1_I2C_0_CFG_REG &        \
                                                             NEOMOTE_1_I2C_0_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & NEOMOTE_1_I2C_0_MCSR_MSTR_MODE)))

    #define NEOMOTE_1_I2C_0_CLEAR_START_GEN        do{ \
                                                        NEOMOTE_1_I2C_0_CFG_REG &=                 \
                                                        ((uint8) ~NEOMOTE_1_I2C_0_MCSR_START_GEN); \
                                                    }while(0)


    /* Stop interrupt */
    #define NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP     do{ \
                                                       NEOMOTE_1_I2C_0_INT_MASK_REG |= NEOMOTE_1_I2C_0_STOP_IE_MASK; \
                                                    }while(0)

    #define NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP    do{ \
                                                        NEOMOTE_1_I2C_0_INT_MASK_REG &=                               \
                                                                             ((uint8) ~NEOMOTE_1_I2C_0_STOP_IE_MASK); \
                                                    }while(0)


    /* Transmit data */
    #define NEOMOTE_1_I2C_0_TRANSMIT_DATA      do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_TRANSMIT_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_DEFAULT);       \
                                                    NEOMOTE_1_I2C_0_GO_REG  = NEOMOTE_1_I2C_0_RELEASE_FSM;          \
                                                }while(0)

    #define NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT   NEOMOTE_1_I2C_0_TRANSMIT_DATA


    #define NEOMOTE_1_I2C_0_NAK_AND_TRANSMIT   do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_NACK_MASK     | \
                                                                                NEOMOTE_1_I2C_0_CTRL_TRANSMIT_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_DEFAULT);       \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM;         \
                                                }while(0)

    /* Receive data */
    #define NEOMOTE_1_I2C_0_READY_TO_READ      do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = NEOMOTE_1_I2C_0_CTRL_DEFAULT; \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM; \
                                                }while(0)

    #define NEOMOTE_1_I2C_0_ACK_AND_RECEIVE    NEOMOTE_1_I2C_0_READY_TO_READ

    #define NEOMOTE_1_I2C_0_NAK_AND_RECEIVE    do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_NACK_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_DEFAULT);   \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM;     \
                                                }while(0)

    /* Master condition generation */
    #define NEOMOTE_1_I2C_0_GENERATE_START     do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_START_MASK | \
                                                                                 NEOMOTE_1_I2C_0_CTRL_DEFAULT);   \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM;      \
                                                }while(0)

    #define NEOMOTE_1_I2C_0_GENERATE_RESTART   do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_RESTART_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_NACK_MASK    | \
                                                                                NEOMOTE_1_I2C_0_CTRL_DEFAULT);      \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM;        \
                                                }while(0)


    #define NEOMOTE_1_I2C_0_GENERATE_STOP      do{ \
                                                    NEOMOTE_1_I2C_0_CFG_REG = (NEOMOTE_1_I2C_0_CTRL_NACK_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_STOP_MASK | \
                                                                                NEOMOTE_1_I2C_0_CTRL_DEFAULT);   \
                                                    NEOMOTE_1_I2C_0_GO_REG  =  NEOMOTE_1_I2C_0_RELEASE_FSM;     \
                                                }while(0)

    /* Master manual APIs compatible defines */
    /* These defines wait while byte complete is cleared after command issued */
    #define NEOMOTE_1_I2C_0_GENERATE_RESTART_MANUAL    \
                                        do{             \
                                            NEOMOTE_1_I2C_0_GENERATE_RESTART;                                    \
                                            while(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(NEOMOTE_1_I2C_0_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define NEOMOTE_1_I2C_0_GENERATE_STOP_MANUAL   \
                                        do{         \
                                            NEOMOTE_1_I2C_0_GENERATE_STOP;                                       \
                                            while(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(NEOMOTE_1_I2C_0_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define NEOMOTE_1_I2C_0_TRANSMIT_DATA_MANUAL   \
                                        do{         \
                                            NEOMOTE_1_I2C_0_TRANSMIT_DATA;                                       \
                                            while(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(NEOMOTE_1_I2C_0_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define NEOMOTE_1_I2C_0_READY_TO_READ_MANUAL   \
                                        do{         \
                                            NEOMOTE_1_I2C_0_READY_TO_READ;      \
                                            while(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(NEOMOTE_1_I2C_0_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)

    #define NEOMOTE_1_I2C_0_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            NEOMOTE_1_I2C_0_ACK_AND_RECEIVE;                                     \
                                            while(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(NEOMOTE_1_I2C_0_CSR_REG)) \
                                            {                                                                     \
                                                ; /* Wait when byte complete is cleared */                        \
                                            }                                                                     \
                                        }while(0)
#endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */

/* Comon for FF and UDB: used to release bus after lost arb */
#define NEOMOTE_1_I2C_0_BUS_RELEASE    NEOMOTE_1_I2C_0_READY_TO_READ


/***************************************
*     Default register init constants
***************************************/

#define NEOMOTE_1_I2C_0_DISABLE    (0u)
#define NEOMOTE_1_I2C_0_ENABLE     (1u)

#if(NEOMOTE_1_I2C_0_FF_IMPLEMENTED)
    /* NEOMOTE_1_I2C_0_XCFG_REG: bits definition */
    #define NEOMOTE_1_I2C_0_DEFAULT_XCFG_HW_ADDR_EN ((NEOMOTE_1_I2C_0_HW_ADRR_DECODE) ? \
                                                        (NEOMOTE_1_I2C_0_XCFG_HDWR_ADDR_EN) : (0u))

    #define NEOMOTE_1_I2C_0_DEFAULT_XCFG_I2C_ON    ((NEOMOTE_1_I2C_0_WAKEUP_ENABLED) ? \
                                                        (NEOMOTE_1_I2C_0_XCFG_I2C_ON) : (0u))


    #define NEOMOTE_1_I2C_0_DEFAULT_CFG_SIO_SELECT ((NEOMOTE_1_I2C_0_I2C1_SIO_PAIR) ? \
                                                        (NEOMOTE_1_I2C_0_CFG_SIO_SELECT) : (0u))


    /* NEOMOTE_1_I2C_0_CFG_REG: bits definition */
    #define NEOMOTE_1_I2C_0_DEFAULT_CFG_PSELECT    ((NEOMOTE_1_I2C_0_WAKEUP_ENABLED) ? \
                                                        (NEOMOTE_1_I2C_0_CFG_PSELECT) : (0u))

    #define NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE0  ((NEOMOTE_1_I2C_0_DATA_RATE <= 50u) ?        \
                                                    (NEOMOTE_1_I2C_0_CFG_CLK_RATE_050) :     \
                                                    ((NEOMOTE_1_I2C_0_DATA_RATE <= 100u) ?   \
                                                        (NEOMOTE_1_I2C_0_CFG_CLK_RATE_100) : \
                                                        (NEOMOTE_1_I2C_0_CFG_CLK_RATE_400)))

    #define NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE1  ((NEOMOTE_1_I2C_0_DATA_RATE <= 50u) ?           \
                                                 (NEOMOTE_1_I2C_0_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (NEOMOTE_1_I2C_0_CFG_CLK_RATE_GRATER_50))

    #define NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE   ((CY_PSOC5A) ? (NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE0) : \
                                                               (NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE1))


    #define NEOMOTE_1_I2C_0_ENABLE_MASTER      ((NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) ? \
                                                 (NEOMOTE_1_I2C_0_CFG_EN_MSTR) : (0u))

    #define NEOMOTE_1_I2C_0_ENABLE_SLAVE       ((NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) ? \
                                                 (NEOMOTE_1_I2C_0_CFG_EN_SLAVE) : (0u))

    #define NEOMOTE_1_I2C_0_ENABLE_MS      (NEOMOTE_1_I2C_0_ENABLE_MASTER | NEOMOTE_1_I2C_0_ENABLE_SLAVE)


    /* NEOMOTE_1_I2C_0_DEFAULT_XCFG_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_XCFG   (NEOMOTE_1_I2C_0_XCFG_CLK_EN         | \
                                             NEOMOTE_1_I2C_0_DEFAULT_XCFG_I2C_ON | \
                                             NEOMOTE_1_I2C_0_DEFAULT_XCFG_HW_ADDR_EN)

    /* NEOMOTE_1_I2C_0_DEFAULT_CFG_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_CFG    (NEOMOTE_1_I2C_0_DEFAULT_CFG_SIO_SELECT | \
                                             NEOMOTE_1_I2C_0_DEFAULT_CFG_PSELECT    | \
                                             NEOMOTE_1_I2C_0_DEFAULT_CLK_RATE       | \
                                             NEOMOTE_1_I2C_0_ENABLE_MASTER          | \
                                             NEOMOTE_1_I2C_0_ENABLE_SLAVE)

    /*NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_DIVIDE_FACTOR  ((CY_PSOC5A) ? ((uint8) 4u) : ((uint16) 15u))

#else
    /* NEOMOTE_1_I2C_0_CFG_REG: bits definition  */
    #define NEOMOTE_1_I2C_0_ENABLE_MASTER  ((NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) ? \
                                             (NEOMOTE_1_I2C_0_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define NEOMOTE_1_I2C_0_ENABLE_SLAVE   ((NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) ? \
                                             (NEOMOTE_1_I2C_0_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define NEOMOTE_1_I2C_0_ENABLE_MS      (NEOMOTE_1_I2C_0_ENABLE_MASTER | NEOMOTE_1_I2C_0_ENABLE_SLAVE)


    #define NEOMOTE_1_I2C_0_DEFAULT_CTRL_ANY_ADDR   ((NEOMOTE_1_I2C_0_HW_ADRR_DECODE) ? \
                                                      (0u) : (NEOMOTE_1_I2C_0_CTRL_ANY_ADDRESS_MASK))

    /* NEOMOTE_1_I2C_0_DEFAULT_CFG_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_CFG    (NEOMOTE_1_I2C_0_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define NEOMOTE_1_I2C_0_CTRL_DEFAULT   (NEOMOTE_1_I2C_0_DEFAULT_CTRL_ANY_ADDR | NEOMOTE_1_I2C_0_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define NEOMOTE_1_I2C_0_MCLK_PERIOD_VALUE  (0x0Fu)
    #define NEOMOTE_1_I2C_0_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: contorol period */
    #define NEOMOTE_1_I2C_0_PERIOD_VALUE       (0x07u)

    /* NEOMOTE_1_I2C_0_DEFAULT_INT_MASK */
    #define NEOMOTE_1_I2C_0_DEFAULT_INT_MASK   (NEOMOTE_1_I2C_0_BYTE_COMPLETE_IE_MASK)

    /* NEOMOTE_1_I2C_0_DEFAULT_MCLK_PRD_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_MCLK_PRD   (NEOMOTE_1_I2C_0_MCLK_PERIOD_VALUE)

    /* NEOMOTE_1_I2C_0_DEFAULT_MCLK_CMP_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_MCLK_CMP   (NEOMOTE_1_I2C_0_MCLK_COMPARE_VALUE)

    /* NEOMOTE_1_I2C_0_DEFAULT_PERIOD_REG */
    #define NEOMOTE_1_I2C_0_DEFAULT_PERIOD     (NEOMOTE_1_I2C_0_PERIOD_VALUE)

#endif /* (NEOMOTE_1_I2C_0_FF_IMPLEMENTED) */


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from I2C 3.20
 */
 
#define NEOMOTE_1_I2C_0_SSTAT_RD_ERR       (0x08u)
#define NEOMOTE_1_I2C_0_SSTAT_WR_ERR       (0x80u)
#define NEOMOTE_1_I2C_0_MSTR_SLAVE_BUSY    (NEOMOTE_1_I2C_0_MSTR_NOT_READY)
#define NEOMOTE_1_I2C_0_MSTAT_ERR_BUF_OVFL (0x80u)
#define NEOMOTE_1_I2C_0_SSTAT_RD_CMPT      (NEOMOTE_1_I2C_0_SSTAT_RD_CMPLT)
#define NEOMOTE_1_I2C_0_SSTAT_WR_CMPT      (NEOMOTE_1_I2C_0_SSTAT_WR_CMPLT)
#define NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_ENABLE    (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_MASK)
#define NEOMOTE_1_I2C_0_DATA_RATE_50       (50u)
#define NEOMOTE_1_I2C_0_DATA_RATE_100      (100u)
#define NEOMOTE_1_I2C_0_DEV_MASK           (0xF0u)
#define NEOMOTE_1_I2C_0_SM_SL_STOP         (0x14u)
#define NEOMOTE_1_I2C_0_SM_MASTER_IDLE     (0x40u)
#define NEOMOTE_1_I2C_0_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_NEOMOTE_1_I2C_0_H */


/* [] END OF FILE */
