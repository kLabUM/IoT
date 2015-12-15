/*******************************************************************************
* File Name: NEOMOTE_1_UART_MOTE.h
* Version 2.30
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_NEOMOTE_1_UART_MOTE_H)
#define CY_UART_NEOMOTE_1_UART_MOTE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define NEOMOTE_1_UART_MOTE_RX_ENABLED                     (1u)
#define NEOMOTE_1_UART_MOTE_TX_ENABLED                     (1u)
#define NEOMOTE_1_UART_MOTE_HD_ENABLED                     (0u)
#define NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED           (0u)
#define NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED           (0u)
#define NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED            (1u)
#define NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED           (0u)
#define NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT              (8u)
#define NEOMOTE_1_UART_MOTE_PARITY_TYPE                    (0u)
#define NEOMOTE_1_UART_MOTE_PARITY_TYPE_SW                 (0u)
#define NEOMOTE_1_UART_MOTE_BREAK_DETECT                   (0u)
#define NEOMOTE_1_UART_MOTE_BREAK_BITS_TX                  (13u)
#define NEOMOTE_1_UART_MOTE_BREAK_BITS_RX                  (13u)
#define NEOMOTE_1_UART_MOTE_TXCLKGEN_DP                    (1u)
#define NEOMOTE_1_UART_MOTE_USE23POLLING                   (1u)
#define NEOMOTE_1_UART_MOTE_FLOW_CONTROL                   (0u)
#define NEOMOTE_1_UART_MOTE_CLK_FREQ                       (0u)
#define NEOMOTE_1_UART_MOTE_TXBUFFERSIZE                   (4u)
#define NEOMOTE_1_UART_MOTE_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED            (0u)
#else
    #define NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED            (1u)
#endif /* End NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct NEOMOTE_1_UART_MOTE_backupStruct_
{
    uint8 enableState;

    #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */
    #if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED)*/

    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End NEOMOTE_1_UART_MOTE_TX_ENABLED */
} NEOMOTE_1_UART_MOTE_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void NEOMOTE_1_UART_MOTE_Start(void) ;
void NEOMOTE_1_UART_MOTE_Stop(void) ;
uint8 NEOMOTE_1_UART_MOTE_ReadControlRegister(void) ;
void NEOMOTE_1_UART_MOTE_WriteControlRegister(uint8 control) ;

void NEOMOTE_1_UART_MOTE_Init(void) ;
void NEOMOTE_1_UART_MOTE_Enable(void) ;
void NEOMOTE_1_UART_MOTE_SaveConfig(void) ;
void NEOMOTE_1_UART_MOTE_RestoreConfig(void) ;
void NEOMOTE_1_UART_MOTE_Sleep(void) ;
void NEOMOTE_1_UART_MOTE_Wakeup(void) ;

/* Only if RX is enabled */
#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )

    #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
        void  NEOMOTE_1_UART_MOTE_EnableRxInt(void) ;
        void  NEOMOTE_1_UART_MOTE_DisableRxInt(void) ;
        CY_ISR_PROTO(NEOMOTE_1_UART_MOTE_RXISR);
    #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

    void NEOMOTE_1_UART_MOTE_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void NEOMOTE_1_UART_MOTE_SetRxAddress1(uint8 address) ;
    void NEOMOTE_1_UART_MOTE_SetRxAddress2(uint8 address) ;

    void  NEOMOTE_1_UART_MOTE_SetRxInterruptMode(uint8 intSrc) ;
    uint8 NEOMOTE_1_UART_MOTE_ReadRxData(void) ;
    uint8 NEOMOTE_1_UART_MOTE_ReadRxStatus(void) ;
    uint8 NEOMOTE_1_UART_MOTE_GetChar(void) ;
    uint16 NEOMOTE_1_UART_MOTE_GetByte(void) ;
    uint8 NEOMOTE_1_UART_MOTE_GetRxBufferSize(void)
                                                            ;
    void NEOMOTE_1_UART_MOTE_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define NEOMOTE_1_UART_MOTE_GetRxInterruptSource   NEOMOTE_1_UART_MOTE_ReadRxStatus

#endif /* End (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */

/* Only if TX is enabled */
#if(NEOMOTE_1_UART_MOTE_TX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)

    #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
        void NEOMOTE_1_UART_MOTE_EnableTxInt(void) ;
        void NEOMOTE_1_UART_MOTE_DisableTxInt(void) ;
        CY_ISR_PROTO(NEOMOTE_1_UART_MOTE_TXISR);
    #endif /* NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

    void NEOMOTE_1_UART_MOTE_SetTxInterruptMode(uint8 intSrc) ;
    void NEOMOTE_1_UART_MOTE_WriteTxData(uint8 txDataByte) ;
    uint8 NEOMOTE_1_UART_MOTE_ReadTxStatus(void) ;
    void NEOMOTE_1_UART_MOTE_PutChar(uint8 txDataByte) ;
    void NEOMOTE_1_UART_MOTE_PutString(const char8 string[]) ;
    void NEOMOTE_1_UART_MOTE_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void NEOMOTE_1_UART_MOTE_PutCRLF(uint8 txDataByte) ;
    void NEOMOTE_1_UART_MOTE_ClearTxBuffer(void) ;
    void NEOMOTE_1_UART_MOTE_SetTxAddressMode(uint8 addressMode) ;
    void NEOMOTE_1_UART_MOTE_SendBreak(uint8 retMode) ;
    uint8 NEOMOTE_1_UART_MOTE_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define NEOMOTE_1_UART_MOTE_PutStringConst         NEOMOTE_1_UART_MOTE_PutString
    #define NEOMOTE_1_UART_MOTE_PutArrayConst          NEOMOTE_1_UART_MOTE_PutArray
    #define NEOMOTE_1_UART_MOTE_GetTxInterruptSource   NEOMOTE_1_UART_MOTE_ReadTxStatus

#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED */

#if(NEOMOTE_1_UART_MOTE_HD_ENABLED)
    void NEOMOTE_1_UART_MOTE_LoadRxConfig(void) ;
    void NEOMOTE_1_UART_MOTE_LoadTxConfig(void) ;
#endif /* End NEOMOTE_1_UART_MOTE_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_UART_MOTE) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    NEOMOTE_1_UART_MOTE_CyBtldrCommStart(void) CYSMALL ;
    void    NEOMOTE_1_UART_MOTE_CyBtldrCommStop(void) CYSMALL ;
    void    NEOMOTE_1_UART_MOTE_CyBtldrCommReset(void) CYSMALL ;
    cystatus NEOMOTE_1_UART_MOTE_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus NEOMOTE_1_UART_MOTE_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_UART_MOTE)
        #define CyBtldrCommStart    NEOMOTE_1_UART_MOTE_CyBtldrCommStart
        #define CyBtldrCommStop     NEOMOTE_1_UART_MOTE_CyBtldrCommStop
        #define CyBtldrCommReset    NEOMOTE_1_UART_MOTE_CyBtldrCommReset
        #define CyBtldrCommWrite    NEOMOTE_1_UART_MOTE_CyBtldrCommWrite
        #define CyBtldrCommRead     NEOMOTE_1_UART_MOTE_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_NEOMOTE_1_UART_MOTE) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define NEOMOTE_1_UART_MOTE_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define NEOMOTE_1_UART_MOTE_SET_SPACE                              (0x00u)
#define NEOMOTE_1_UART_MOTE_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (NEOMOTE_1_UART_MOTE_TX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
    #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
        #define NEOMOTE_1_UART_MOTE_TX_VECT_NUM            (uint8)NEOMOTE_1_UART_MOTE_TXInternalInterrupt__INTC_NUMBER
        #define NEOMOTE_1_UART_MOTE_TX_PRIOR_NUM           (uint8)NEOMOTE_1_UART_MOTE_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */
    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        #define NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* NEOMOTE_1_UART_MOTE_TX_ENABLED */
    #if(NEOMOTE_1_UART_MOTE_HD_ENABLED)
        #define NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* NEOMOTE_1_UART_MOTE_HD_ENABLED */
    #define NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE            (uint8)(0x01u << NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE_SHIFT)
    #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY          (uint8)(0x01u << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY_SHIFT)
    #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL           (uint8)(0x01u << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL_SHIFT)
    #define NEOMOTE_1_UART_MOTE_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (NEOMOTE_1_UART_MOTE_TX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED)*/

#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
    #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
        #define NEOMOTE_1_UART_MOTE_RX_VECT_NUM            (uint8)NEOMOTE_1_UART_MOTE_RXInternalInterrupt__INTC_NUMBER
        #define NEOMOTE_1_UART_MOTE_RX_PRIOR_NUM           (uint8)NEOMOTE_1_UART_MOTE_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
    #define NEOMOTE_1_UART_MOTE_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_BREAK_SHIFT             (0x01u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define NEOMOTE_1_UART_MOTE_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define NEOMOTE_1_UART_MOTE_RX_STS_MRKSPC           (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_MRKSPC_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_BREAK            (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_BREAK_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR        (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR       (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN          (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_ADDR_MATCH       (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_ADDR_MATCH_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << NEOMOTE_1_UART_MOTE_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define NEOMOTE_1_UART_MOTE_RX_HW_MASK                     (0x7Fu)
#endif /* End (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */

/* Control Register definitions */
#define NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define NEOMOTE_1_UART_MOTE_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define NEOMOTE_1_UART_MOTE_CTRL_HD_SEND               (uint8)(0x01u << NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_SHIFT)
#define NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK         (uint8)(0x01u << NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK_SHIFT)
#define NEOMOTE_1_UART_MOTE_CTRL_MARK                  (uint8)(0x01u << NEOMOTE_1_UART_MOTE_CTRL_MARK_SHIFT)
#define NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE0_SHIFT)
#define NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define NEOMOTE_1_UART_MOTE_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define NEOMOTE_1_UART_MOTE_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define NEOMOTE_1_UART_MOTE_SEND_BREAK                         (0x00u)
#define NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define NEOMOTE_1_UART_MOTE_REINIT                             (0x02u)
#define NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT                   (0x03u)

#define NEOMOTE_1_UART_MOTE_OVER_SAMPLE_8                      (8u)
#define NEOMOTE_1_UART_MOTE_OVER_SAMPLE_16                     (16u)

#define NEOMOTE_1_UART_MOTE_BIT_CENTER                         (NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT - 1u)

#define NEOMOTE_1_UART_MOTE_FIFO_LENGTH                        (4u)
#define NEOMOTE_1_UART_MOTE_NUMBER_OF_START_BIT                (1u)
#define NEOMOTE_1_UART_MOTE_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define NEOMOTE_1_UART_MOTE_TXBITCTR_BREAKBITS8X   ((NEOMOTE_1_UART_MOTE_BREAK_BITS_TX * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define NEOMOTE_1_UART_MOTE_TXBITCTR_BREAKBITS ((NEOMOTE_1_UART_MOTE_BREAK_BITS_TX * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT) - 1u)

#define NEOMOTE_1_UART_MOTE_HALF_BIT_COUNT   \
                            (((NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT / 2u) + (NEOMOTE_1_UART_MOTE_USE23POLLING * 1u)) - 2u)
#if (NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT == NEOMOTE_1_UART_MOTE_OVER_SAMPLE_8)
    #define NEOMOTE_1_UART_MOTE_HD_TXBITCTR_INIT   (((NEOMOTE_1_UART_MOTE_BREAK_BITS_TX + \
                            NEOMOTE_1_UART_MOTE_NUMBER_OF_START_BIT) * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_INIT  ((((NEOMOTE_1_UART_MOTE_BREAK_BITS_RX + NEOMOTE_1_UART_MOTE_NUMBER_OF_START_BIT) \
                            * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT) + NEOMOTE_1_UART_MOTE_HALF_BIT_COUNT) - 1u)


#else /* NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT == NEOMOTE_1_UART_MOTE_OVER_SAMPLE_16 */
    #define NEOMOTE_1_UART_MOTE_HD_TXBITCTR_INIT   ((8u * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_INIT      (((7u * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT) - 1u) + \
                                                      NEOMOTE_1_UART_MOTE_HALF_BIT_COUNT)
#endif /* End NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT */
#define NEOMOTE_1_UART_MOTE_HD_RXBITCTR_INIT                   NEOMOTE_1_UART_MOTE_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 NEOMOTE_1_UART_MOTE_initVar;
#if( NEOMOTE_1_UART_MOTE_TX_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
    extern volatile uint8 NEOMOTE_1_UART_MOTE_txBuffer[NEOMOTE_1_UART_MOTE_TXBUFFERSIZE];
    extern volatile uint8 NEOMOTE_1_UART_MOTE_txBufferRead;
    extern uint8 NEOMOTE_1_UART_MOTE_txBufferWrite;
#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */
#if( ( NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED ) && \
     (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) )
    extern volatile uint8 NEOMOTE_1_UART_MOTE_rxBuffer[NEOMOTE_1_UART_MOTE_RXBUFFERSIZE];
    extern volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferRead;
    extern volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferWrite;
    extern volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferLoopDetect;
    extern volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferOverflow;
    #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 NEOMOTE_1_UART_MOTE_rxAddressMode;
        extern volatile uint8 NEOMOTE_1_UART_MOTE_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define NEOMOTE_1_UART_MOTE__B_UART__AM_SW_BYTE_BYTE 1
#define NEOMOTE_1_UART_MOTE__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define NEOMOTE_1_UART_MOTE__B_UART__AM_HW_BYTE_BY_BYTE 3
#define NEOMOTE_1_UART_MOTE__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define NEOMOTE_1_UART_MOTE__B_UART__AM_NONE 0

#define NEOMOTE_1_UART_MOTE__B_UART__NONE_REVB 0
#define NEOMOTE_1_UART_MOTE__B_UART__EVEN_REVB 1
#define NEOMOTE_1_UART_MOTE__B_UART__ODD_REVB 2
#define NEOMOTE_1_UART_MOTE__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define NEOMOTE_1_UART_MOTE_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define NEOMOTE_1_UART_MOTE_NUMBER_OF_STOP_BITS    (1u)

#if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
    #define NEOMOTE_1_UART_MOTE_RXADDRESSMODE      (0u)
    #define NEOMOTE_1_UART_MOTE_RXHWADDRESS1       (0u)
    #define NEOMOTE_1_UART_MOTE_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define NEOMOTE_1_UART_MOTE_RXAddressMode      NEOMOTE_1_UART_MOTE_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define NEOMOTE_1_UART_MOTE_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_BREAK_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN_SHIFT))

#define NEOMOTE_1_UART_MOTE_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << NEOMOTE_1_UART_MOTE_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define NEOMOTE_1_UART_MOTE_CONTROL_REG \
                            (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define NEOMOTE_1_UART_MOTE_CONTROL_PTR \
                            (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
    #define NEOMOTE_1_UART_MOTE_TXDATA_REG          (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxShifter_u0__F0_REG)
    #define NEOMOTE_1_UART_MOTE_TXDATA_PTR          (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxShifter_u0__F0_REG)
    #define NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_REG  (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_PTR  (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_REG        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__STATUS_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_PTR        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__STATUS_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG   (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__MASK_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_PTR   (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__MASK_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG   (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_PTR   (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
        #define NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */

#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

#if(NEOMOTE_1_UART_MOTE_HD_ENABLED)

    #define NEOMOTE_1_UART_MOTE_TXDATA_REG             (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__F1_REG )
    #define NEOMOTE_1_UART_MOTE_TXDATA_PTR             (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__F1_REG )
    #define NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_REG     (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_PTR     (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define NEOMOTE_1_UART_MOTE_TXSTATUS_REG           (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_REG )
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_PTR           (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_REG )
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG      (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__MASK_REG )
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_PTR      (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__MASK_REG )
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG      (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_PTR      (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End NEOMOTE_1_UART_MOTE_HD_ENABLED */

#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
    #define NEOMOTE_1_UART_MOTE_RXDATA_REG             (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__F0_REG )
    #define NEOMOTE_1_UART_MOTE_RXDATA_PTR             (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__F0_REG )
    #define NEOMOTE_1_UART_MOTE_RXADDRESS1_REG         (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__D0_REG )
    #define NEOMOTE_1_UART_MOTE_RXADDRESS1_PTR         (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__D0_REG )
    #define NEOMOTE_1_UART_MOTE_RXADDRESS2_REG         (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__D1_REG )
    #define NEOMOTE_1_UART_MOTE_RXADDRESS2_PTR         (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__D1_REG )
    #define NEOMOTE_1_UART_MOTE_RXDATA_AUX_CTL_REG     (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG    (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_PTR    (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_COUNTER_REG   (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__COUNT_REG )
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_COUNTER_PTR   (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxBitCounter__COUNT_REG )

    #define NEOMOTE_1_UART_MOTE_RXSTATUS_REG           (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_REG )
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_PTR           (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_REG )
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG      (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__MASK_REG )
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_PTR      (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__MASK_REG )
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_REG      (* (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_PTR      (  (reg8 *) NEOMOTE_1_UART_MOTE_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */

#if(NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define NEOMOTE_1_UART_MOTE_INTCLOCK_CLKEN_REG     (* (reg8 *) NEOMOTE_1_UART_MOTE_IntClock__PM_ACT_CFG)
    #define NEOMOTE_1_UART_MOTE_INTCLOCK_CLKEN_PTR     (  (reg8 *) NEOMOTE_1_UART_MOTE_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define NEOMOTE_1_UART_MOTE_INTCLOCK_CLKEN_MASK    NEOMOTE_1_UART_MOTE_IntClock__PM_ACT_MSK
#endif /* End NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
    #define NEOMOTE_1_UART_MOTE_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

#if(NEOMOTE_1_UART_MOTE_HD_ENABLED)
    #define NEOMOTE_1_UART_MOTE_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End NEOMOTE_1_UART_MOTE_HD_ENABLED */

#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
    #define NEOMOTE_1_UART_MOTE_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define NEOMOTE_1_UART_MOTE_initvar                    NEOMOTE_1_UART_MOTE_initVar

#define NEOMOTE_1_UART_MOTE_RX_Enabled                 NEOMOTE_1_UART_MOTE_RX_ENABLED
#define NEOMOTE_1_UART_MOTE_TX_Enabled                 NEOMOTE_1_UART_MOTE_TX_ENABLED
#define NEOMOTE_1_UART_MOTE_HD_Enabled                 NEOMOTE_1_UART_MOTE_HD_ENABLED
#define NEOMOTE_1_UART_MOTE_RX_IntInterruptEnabled     NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED
#define NEOMOTE_1_UART_MOTE_TX_IntInterruptEnabled     NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED
#define NEOMOTE_1_UART_MOTE_InternalClockUsed          NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED
#define NEOMOTE_1_UART_MOTE_RXHW_Address_Enabled       NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED
#define NEOMOTE_1_UART_MOTE_OverSampleCount            NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT
#define NEOMOTE_1_UART_MOTE_ParityType                 NEOMOTE_1_UART_MOTE_PARITY_TYPE

#if( NEOMOTE_1_UART_MOTE_TX_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
    #define NEOMOTE_1_UART_MOTE_TXBUFFER               NEOMOTE_1_UART_MOTE_txBuffer
    #define NEOMOTE_1_UART_MOTE_TXBUFFERREAD           NEOMOTE_1_UART_MOTE_txBufferRead
    #define NEOMOTE_1_UART_MOTE_TXBUFFERWRITE          NEOMOTE_1_UART_MOTE_txBufferWrite
#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */
#if( ( NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED ) && \
     (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) )
    #define NEOMOTE_1_UART_MOTE_RXBUFFER               NEOMOTE_1_UART_MOTE_rxBuffer
    #define NEOMOTE_1_UART_MOTE_RXBUFFERREAD           NEOMOTE_1_UART_MOTE_rxBufferRead
    #define NEOMOTE_1_UART_MOTE_RXBUFFERWRITE          NEOMOTE_1_UART_MOTE_rxBufferWrite
    #define NEOMOTE_1_UART_MOTE_RXBUFFERLOOPDETECT     NEOMOTE_1_UART_MOTE_rxBufferLoopDetect
    #define NEOMOTE_1_UART_MOTE_RXBUFFER_OVERFLOW      NEOMOTE_1_UART_MOTE_rxBufferOverflow
#endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED */

#ifdef NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define NEOMOTE_1_UART_MOTE_CONTROL                NEOMOTE_1_UART_MOTE_CONTROL_REG
#endif /* End NEOMOTE_1_UART_MOTE_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
    #define NEOMOTE_1_UART_MOTE_TXDATA                 NEOMOTE_1_UART_MOTE_TXDATA_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS               NEOMOTE_1_UART_MOTE_TXSTATUS_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK          NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL          NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
        #define NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR        NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_REG
        #define NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE    NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD        NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL       NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL_REG
        #define NEOMOTE_1_UART_MOTE_TXBITCTR_COUNTER       NEOMOTE_1_UART_MOTE_TXBITCTR_COUNTER_REG
    #endif /* NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

#if(NEOMOTE_1_UART_MOTE_HD_ENABLED)
    #define NEOMOTE_1_UART_MOTE_TXDATA                 NEOMOTE_1_UART_MOTE_TXDATA_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS               NEOMOTE_1_UART_MOTE_TXSTATUS_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_MASK          NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG
    #define NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL          NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG
#endif /* End NEOMOTE_1_UART_MOTE_HD_ENABLED */

#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )
    #define NEOMOTE_1_UART_MOTE_RXDATA                 NEOMOTE_1_UART_MOTE_RXDATA_REG
    #define NEOMOTE_1_UART_MOTE_RXADDRESS1             NEOMOTE_1_UART_MOTE_RXADDRESS1_REG
    #define NEOMOTE_1_UART_MOTE_RXADDRESS2             NEOMOTE_1_UART_MOTE_RXADDRESS2_REG
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD        NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL       NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL_REG
    #define NEOMOTE_1_UART_MOTE_RXBITCTR_COUNTER       NEOMOTE_1_UART_MOTE_RXBITCTR_COUNTER_REG
    #define NEOMOTE_1_UART_MOTE_RXSTATUS               NEOMOTE_1_UART_MOTE_RXSTATUS_REG
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_MASK          NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG
    #define NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL          NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_REG
#endif /* End  (NEOMOTE_1_UART_MOTE_RX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) */

#if(NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED)
    #define NEOMOTE_1_UART_MOTE_INTCLOCK_CLKEN         NEOMOTE_1_UART_MOTE_INTCLOCK_CLKEN_REG
#endif /* End NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED */

#define NEOMOTE_1_UART_MOTE_WAIT_FOR_COMLETE_REINIT    NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_NEOMOTE_1_UART_MOTE_H */


/* [] END OF FILE */
