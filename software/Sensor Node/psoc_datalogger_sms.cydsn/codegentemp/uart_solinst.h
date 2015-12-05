/*******************************************************************************
* File Name: uart_solinst.h
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


#if !defined(CY_UART_uart_solinst_H)
#define CY_UART_uart_solinst_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define uart_solinst_RX_ENABLED                     (1u)
#define uart_solinst_TX_ENABLED                     (1u)
#define uart_solinst_HD_ENABLED                     (0u)
#define uart_solinst_RX_INTERRUPT_ENABLED           (0u)
#define uart_solinst_TX_INTERRUPT_ENABLED           (0u)
#define uart_solinst_INTERNAL_CLOCK_USED            (1u)
#define uart_solinst_RXHW_ADDRESS_ENABLED           (1u)
#define uart_solinst_OVER_SAMPLE_COUNT              (8u)
#define uart_solinst_PARITY_TYPE                    (0u)
#define uart_solinst_PARITY_TYPE_SW                 (0u)
#define uart_solinst_BREAK_DETECT                   (0u)
#define uart_solinst_BREAK_BITS_TX                  (13u)
#define uart_solinst_BREAK_BITS_RX                  (13u)
#define uart_solinst_TXCLKGEN_DP                    (1u)
#define uart_solinst_USE23POLLING                   (1u)
#define uart_solinst_FLOW_CONTROL                   (0u)
#define uart_solinst_CLK_FREQ                       (0u)
#define uart_solinst_TXBUFFERSIZE                   (4u)
#define uart_solinst_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define uart_solinst_CONTROL_REG_REMOVED            (0u)
#else
    #define uart_solinst_CONTROL_REG_REMOVED            (1u)
#endif /* End uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct uart_solinst_backupStruct_
{
    uint8 enableState;

    #if(uart_solinst_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End uart_solinst_CONTROL_REG_REMOVED */
    #if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (uart_solinst_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End uart_solinst_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED)*/

    #if(uart_solinst_TX_ENABLED)
        #if(uart_solinst_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End uart_solinst_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End uart_solinst_TX_ENABLED */
} uart_solinst_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void uart_solinst_Start(void) ;
void uart_solinst_Stop(void) ;
uint8 uart_solinst_ReadControlRegister(void) ;
void uart_solinst_WriteControlRegister(uint8 control) ;

void uart_solinst_Init(void) ;
void uart_solinst_Enable(void) ;
void uart_solinst_SaveConfig(void) ;
void uart_solinst_RestoreConfig(void) ;
void uart_solinst_Sleep(void) ;
void uart_solinst_Wakeup(void) ;

/* Only if RX is enabled */
#if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )

    #if(uart_solinst_RX_INTERRUPT_ENABLED)
        void  uart_solinst_EnableRxInt(void) ;
        void  uart_solinst_DisableRxInt(void) ;
        CY_ISR_PROTO(uart_solinst_RXISR);
    #endif /* uart_solinst_RX_INTERRUPT_ENABLED */

    void uart_solinst_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void uart_solinst_SetRxAddress1(uint8 address) ;
    void uart_solinst_SetRxAddress2(uint8 address) ;

    void  uart_solinst_SetRxInterruptMode(uint8 intSrc) ;
    uint8 uart_solinst_ReadRxData(void) ;
    uint8 uart_solinst_ReadRxStatus(void) ;
    uint8 uart_solinst_GetChar(void) ;
    uint16 uart_solinst_GetByte(void) ;
    uint8 uart_solinst_GetRxBufferSize(void)
                                                            ;
    void uart_solinst_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define uart_solinst_GetRxInterruptSource   uart_solinst_ReadRxStatus

#endif /* End (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */

/* Only if TX is enabled */
#if(uart_solinst_TX_ENABLED || uart_solinst_HD_ENABLED)

    #if(uart_solinst_TX_INTERRUPT_ENABLED)
        void uart_solinst_EnableTxInt(void) ;
        void uart_solinst_DisableTxInt(void) ;
        CY_ISR_PROTO(uart_solinst_TXISR);
    #endif /* uart_solinst_TX_INTERRUPT_ENABLED */

    void uart_solinst_SetTxInterruptMode(uint8 intSrc) ;
    void uart_solinst_WriteTxData(uint8 txDataByte) ;
    uint8 uart_solinst_ReadTxStatus(void) ;
    void uart_solinst_PutChar(uint8 txDataByte) ;
    void uart_solinst_PutString(const char8 string[]) ;
    void uart_solinst_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void uart_solinst_PutCRLF(uint8 txDataByte) ;
    void uart_solinst_ClearTxBuffer(void) ;
    void uart_solinst_SetTxAddressMode(uint8 addressMode) ;
    void uart_solinst_SendBreak(uint8 retMode) ;
    uint8 uart_solinst_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define uart_solinst_PutStringConst         uart_solinst_PutString
    #define uart_solinst_PutArrayConst          uart_solinst_PutArray
    #define uart_solinst_GetTxInterruptSource   uart_solinst_ReadTxStatus

#endif /* End uart_solinst_TX_ENABLED || uart_solinst_HD_ENABLED */

#if(uart_solinst_HD_ENABLED)
    void uart_solinst_LoadRxConfig(void) ;
    void uart_solinst_LoadTxConfig(void) ;
#endif /* End uart_solinst_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_solinst) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    uart_solinst_CyBtldrCommStart(void) CYSMALL ;
    void    uart_solinst_CyBtldrCommStop(void) CYSMALL ;
    void    uart_solinst_CyBtldrCommReset(void) CYSMALL ;
    cystatus uart_solinst_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus uart_solinst_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_solinst)
        #define CyBtldrCommStart    uart_solinst_CyBtldrCommStart
        #define CyBtldrCommStop     uart_solinst_CyBtldrCommStop
        #define CyBtldrCommReset    uart_solinst_CyBtldrCommReset
        #define CyBtldrCommWrite    uart_solinst_CyBtldrCommWrite
        #define CyBtldrCommRead     uart_solinst_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_solinst) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define uart_solinst_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define uart_solinst_SET_SPACE                              (0x00u)
#define uart_solinst_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (uart_solinst_TX_ENABLED) || (uart_solinst_HD_ENABLED) )
    #if(uart_solinst_TX_INTERRUPT_ENABLED)
        #define uart_solinst_TX_VECT_NUM            (uint8)uart_solinst_TXInternalInterrupt__INTC_NUMBER
        #define uart_solinst_TX_PRIOR_NUM           (uint8)uart_solinst_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_solinst_TX_INTERRUPT_ENABLED */
    #if(uart_solinst_TX_ENABLED)
        #define uart_solinst_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define uart_solinst_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define uart_solinst_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define uart_solinst_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* uart_solinst_TX_ENABLED */
    #if(uart_solinst_HD_ENABLED)
        #define uart_solinst_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define uart_solinst_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define uart_solinst_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define uart_solinst_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* uart_solinst_HD_ENABLED */
    #define uart_solinst_TX_STS_COMPLETE            (uint8)(0x01u << uart_solinst_TX_STS_COMPLETE_SHIFT)
    #define uart_solinst_TX_STS_FIFO_EMPTY          (uint8)(0x01u << uart_solinst_TX_STS_FIFO_EMPTY_SHIFT)
    #define uart_solinst_TX_STS_FIFO_FULL           (uint8)(0x01u << uart_solinst_TX_STS_FIFO_FULL_SHIFT)
    #define uart_solinst_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << uart_solinst_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (uart_solinst_TX_ENABLED) || (uart_solinst_HD_ENABLED)*/

#if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
    #if(uart_solinst_RX_INTERRUPT_ENABLED)
        #define uart_solinst_RX_VECT_NUM            (uint8)uart_solinst_RXInternalInterrupt__INTC_NUMBER
        #define uart_solinst_RX_PRIOR_NUM           (uint8)uart_solinst_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_solinst_RX_INTERRUPT_ENABLED */
    #define uart_solinst_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define uart_solinst_RX_STS_BREAK_SHIFT             (0x01u)
    #define uart_solinst_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define uart_solinst_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define uart_solinst_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define uart_solinst_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define uart_solinst_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define uart_solinst_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define uart_solinst_RX_STS_MRKSPC           (uint8)(0x01u << uart_solinst_RX_STS_MRKSPC_SHIFT)
    #define uart_solinst_RX_STS_BREAK            (uint8)(0x01u << uart_solinst_RX_STS_BREAK_SHIFT)
    #define uart_solinst_RX_STS_PAR_ERROR        (uint8)(0x01u << uart_solinst_RX_STS_PAR_ERROR_SHIFT)
    #define uart_solinst_RX_STS_STOP_ERROR       (uint8)(0x01u << uart_solinst_RX_STS_STOP_ERROR_SHIFT)
    #define uart_solinst_RX_STS_OVERRUN          (uint8)(0x01u << uart_solinst_RX_STS_OVERRUN_SHIFT)
    #define uart_solinst_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << uart_solinst_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define uart_solinst_RX_STS_ADDR_MATCH       (uint8)(0x01u << uart_solinst_RX_STS_ADDR_MATCH_SHIFT)
    #define uart_solinst_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << uart_solinst_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define uart_solinst_RX_HW_MASK                     (0x7Fu)
#endif /* End (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */

/* Control Register definitions */
#define uart_solinst_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define uart_solinst_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define uart_solinst_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define uart_solinst_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define uart_solinst_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define uart_solinst_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define uart_solinst_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define uart_solinst_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define uart_solinst_CTRL_HD_SEND               (uint8)(0x01u << uart_solinst_CTRL_HD_SEND_SHIFT)
#define uart_solinst_CTRL_HD_SEND_BREAK         (uint8)(0x01u << uart_solinst_CTRL_HD_SEND_BREAK_SHIFT)
#define uart_solinst_CTRL_MARK                  (uint8)(0x01u << uart_solinst_CTRL_MARK_SHIFT)
#define uart_solinst_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << uart_solinst_CTRL_PARITY_TYPE0_SHIFT)
#define uart_solinst_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << uart_solinst_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define uart_solinst_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define uart_solinst_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define uart_solinst_SEND_BREAK                         (0x00u)
#define uart_solinst_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define uart_solinst_REINIT                             (0x02u)
#define uart_solinst_SEND_WAIT_REINIT                   (0x03u)

#define uart_solinst_OVER_SAMPLE_8                      (8u)
#define uart_solinst_OVER_SAMPLE_16                     (16u)

#define uart_solinst_BIT_CENTER                         (uart_solinst_OVER_SAMPLE_COUNT - 1u)

#define uart_solinst_FIFO_LENGTH                        (4u)
#define uart_solinst_NUMBER_OF_START_BIT                (1u)
#define uart_solinst_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define uart_solinst_TXBITCTR_BREAKBITS8X   ((uart_solinst_BREAK_BITS_TX * uart_solinst_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define uart_solinst_TXBITCTR_BREAKBITS ((uart_solinst_BREAK_BITS_TX * uart_solinst_OVER_SAMPLE_COUNT) - 1u)

#define uart_solinst_HALF_BIT_COUNT   \
                            (((uart_solinst_OVER_SAMPLE_COUNT / 2u) + (uart_solinst_USE23POLLING * 1u)) - 2u)
#if (uart_solinst_OVER_SAMPLE_COUNT == uart_solinst_OVER_SAMPLE_8)
    #define uart_solinst_HD_TXBITCTR_INIT   (((uart_solinst_BREAK_BITS_TX + \
                            uart_solinst_NUMBER_OF_START_BIT) * uart_solinst_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define uart_solinst_RXBITCTR_INIT  ((((uart_solinst_BREAK_BITS_RX + uart_solinst_NUMBER_OF_START_BIT) \
                            * uart_solinst_OVER_SAMPLE_COUNT) + uart_solinst_HALF_BIT_COUNT) - 1u)


#else /* uart_solinst_OVER_SAMPLE_COUNT == uart_solinst_OVER_SAMPLE_16 */
    #define uart_solinst_HD_TXBITCTR_INIT   ((8u * uart_solinst_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define uart_solinst_RXBITCTR_INIT      (((7u * uart_solinst_OVER_SAMPLE_COUNT) - 1u) + \
                                                      uart_solinst_HALF_BIT_COUNT)
#endif /* End uart_solinst_OVER_SAMPLE_COUNT */
#define uart_solinst_HD_RXBITCTR_INIT                   uart_solinst_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 uart_solinst_initVar;
#if( uart_solinst_TX_ENABLED && (uart_solinst_TXBUFFERSIZE > uart_solinst_FIFO_LENGTH))
    extern volatile uint8 uart_solinst_txBuffer[uart_solinst_TXBUFFERSIZE];
    extern volatile uint8 uart_solinst_txBufferRead;
    extern uint8 uart_solinst_txBufferWrite;
#endif /* End uart_solinst_TX_ENABLED */
#if( ( uart_solinst_RX_ENABLED || uart_solinst_HD_ENABLED ) && \
     (uart_solinst_RXBUFFERSIZE > uart_solinst_FIFO_LENGTH) )
    extern volatile uint8 uart_solinst_rxBuffer[uart_solinst_RXBUFFERSIZE];
    extern volatile uint8 uart_solinst_rxBufferRead;
    extern volatile uint8 uart_solinst_rxBufferWrite;
    extern volatile uint8 uart_solinst_rxBufferLoopDetect;
    extern volatile uint8 uart_solinst_rxBufferOverflow;
    #if (uart_solinst_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 uart_solinst_rxAddressMode;
        extern volatile uint8 uart_solinst_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End uart_solinst_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define uart_solinst__B_UART__AM_SW_BYTE_BYTE 1
#define uart_solinst__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define uart_solinst__B_UART__AM_HW_BYTE_BY_BYTE 3
#define uart_solinst__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define uart_solinst__B_UART__AM_NONE 0

#define uart_solinst__B_UART__NONE_REVB 0
#define uart_solinst__B_UART__EVEN_REVB 1
#define uart_solinst__B_UART__ODD_REVB 2
#define uart_solinst__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define uart_solinst_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define uart_solinst_NUMBER_OF_STOP_BITS    (1u)

#if (uart_solinst_RXHW_ADDRESS_ENABLED)
    #define uart_solinst_RXADDRESSMODE      (3u)
    #define uart_solinst_RXHWADDRESS1       (255u)
    #define uart_solinst_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define uart_solinst_RXAddressMode      uart_solinst_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define uart_solinst_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << uart_solinst_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_BREAK_SHIFT) \
                                        | (0 << uart_solinst_RX_STS_OVERRUN_SHIFT))

#define uart_solinst_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << uart_solinst_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << uart_solinst_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << uart_solinst_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << uart_solinst_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define uart_solinst_CONTROL_REG \
                            (* (reg8 *) uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define uart_solinst_CONTROL_PTR \
                            (  (reg8 *) uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(uart_solinst_TX_ENABLED)
    #define uart_solinst_TXDATA_REG          (* (reg8 *) uart_solinst_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_solinst_TXDATA_PTR          (  (reg8 *) uart_solinst_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_solinst_TXDATA_AUX_CTL_REG  (* (reg8 *) uart_solinst_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_solinst_TXDATA_AUX_CTL_PTR  (  (reg8 *) uart_solinst_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_solinst_TXSTATUS_REG        (* (reg8 *) uart_solinst_BUART_sTX_TxSts__STATUS_REG)
    #define uart_solinst_TXSTATUS_PTR        (  (reg8 *) uart_solinst_BUART_sTX_TxSts__STATUS_REG)
    #define uart_solinst_TXSTATUS_MASK_REG   (* (reg8 *) uart_solinst_BUART_sTX_TxSts__MASK_REG)
    #define uart_solinst_TXSTATUS_MASK_PTR   (  (reg8 *) uart_solinst_BUART_sTX_TxSts__MASK_REG)
    #define uart_solinst_TXSTATUS_ACTL_REG   (* (reg8 *) uart_solinst_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define uart_solinst_TXSTATUS_ACTL_PTR   (  (reg8 *) uart_solinst_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(uart_solinst_TXCLKGEN_DP)
        #define uart_solinst_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_solinst_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_solinst_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define uart_solinst_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define uart_solinst_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_solinst_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_solinst_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_solinst_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_solinst_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define uart_solinst_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) uart_solinst_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* uart_solinst_TXCLKGEN_DP */

#endif /* End uart_solinst_TX_ENABLED */

#if(uart_solinst_HD_ENABLED)

    #define uart_solinst_TXDATA_REG             (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_solinst_TXDATA_PTR             (  (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_solinst_TXDATA_AUX_CTL_REG     (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define uart_solinst_TXDATA_AUX_CTL_PTR     (  (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_solinst_TXSTATUS_REG           (* (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_REG )
    #define uart_solinst_TXSTATUS_PTR           (  (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_REG )
    #define uart_solinst_TXSTATUS_MASK_REG      (* (reg8 *) uart_solinst_BUART_sRX_RxSts__MASK_REG )
    #define uart_solinst_TXSTATUS_MASK_PTR      (  (reg8 *) uart_solinst_BUART_sRX_RxSts__MASK_REG )
    #define uart_solinst_TXSTATUS_ACTL_REG      (* (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_solinst_TXSTATUS_ACTL_PTR      (  (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End uart_solinst_HD_ENABLED */

#if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
    #define uart_solinst_RXDATA_REG             (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_solinst_RXDATA_PTR             (  (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_solinst_RXADDRESS1_REG         (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_solinst_RXADDRESS1_PTR         (  (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_solinst_RXADDRESS2_REG         (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_solinst_RXADDRESS2_PTR         (  (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_solinst_RXDATA_AUX_CTL_REG     (* (reg8 *) uart_solinst_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_solinst_RXBITCTR_PERIOD_REG    (* (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_solinst_RXBITCTR_PERIOD_PTR    (  (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_solinst_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_solinst_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_solinst_RXBITCTR_COUNTER_REG   (* (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__COUNT_REG )
    #define uart_solinst_RXBITCTR_COUNTER_PTR   (  (reg8 *) uart_solinst_BUART_sRX_RxBitCounter__COUNT_REG )

    #define uart_solinst_RXSTATUS_REG           (* (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_REG )
    #define uart_solinst_RXSTATUS_PTR           (  (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_REG )
    #define uart_solinst_RXSTATUS_MASK_REG      (* (reg8 *) uart_solinst_BUART_sRX_RxSts__MASK_REG )
    #define uart_solinst_RXSTATUS_MASK_PTR      (  (reg8 *) uart_solinst_BUART_sRX_RxSts__MASK_REG )
    #define uart_solinst_RXSTATUS_ACTL_REG      (* (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_solinst_RXSTATUS_ACTL_PTR      (  (reg8 *) uart_solinst_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */

#if(uart_solinst_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define uart_solinst_INTCLOCK_CLKEN_REG     (* (reg8 *) uart_solinst_IntClock__PM_ACT_CFG)
    #define uart_solinst_INTCLOCK_CLKEN_PTR     (  (reg8 *) uart_solinst_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define uart_solinst_INTCLOCK_CLKEN_MASK    uart_solinst_IntClock__PM_ACT_MSK
#endif /* End uart_solinst_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(uart_solinst_TX_ENABLED)
    #define uart_solinst_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End uart_solinst_TX_ENABLED */

#if(uart_solinst_HD_ENABLED)
    #define uart_solinst_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End uart_solinst_HD_ENABLED */

#if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
    #define uart_solinst_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define uart_solinst_initvar                    uart_solinst_initVar

#define uart_solinst_RX_Enabled                 uart_solinst_RX_ENABLED
#define uart_solinst_TX_Enabled                 uart_solinst_TX_ENABLED
#define uart_solinst_HD_Enabled                 uart_solinst_HD_ENABLED
#define uart_solinst_RX_IntInterruptEnabled     uart_solinst_RX_INTERRUPT_ENABLED
#define uart_solinst_TX_IntInterruptEnabled     uart_solinst_TX_INTERRUPT_ENABLED
#define uart_solinst_InternalClockUsed          uart_solinst_INTERNAL_CLOCK_USED
#define uart_solinst_RXHW_Address_Enabled       uart_solinst_RXHW_ADDRESS_ENABLED
#define uart_solinst_OverSampleCount            uart_solinst_OVER_SAMPLE_COUNT
#define uart_solinst_ParityType                 uart_solinst_PARITY_TYPE

#if( uart_solinst_TX_ENABLED && (uart_solinst_TXBUFFERSIZE > uart_solinst_FIFO_LENGTH))
    #define uart_solinst_TXBUFFER               uart_solinst_txBuffer
    #define uart_solinst_TXBUFFERREAD           uart_solinst_txBufferRead
    #define uart_solinst_TXBUFFERWRITE          uart_solinst_txBufferWrite
#endif /* End uart_solinst_TX_ENABLED */
#if( ( uart_solinst_RX_ENABLED || uart_solinst_HD_ENABLED ) && \
     (uart_solinst_RXBUFFERSIZE > uart_solinst_FIFO_LENGTH) )
    #define uart_solinst_RXBUFFER               uart_solinst_rxBuffer
    #define uart_solinst_RXBUFFERREAD           uart_solinst_rxBufferRead
    #define uart_solinst_RXBUFFERWRITE          uart_solinst_rxBufferWrite
    #define uart_solinst_RXBUFFERLOOPDETECT     uart_solinst_rxBufferLoopDetect
    #define uart_solinst_RXBUFFER_OVERFLOW      uart_solinst_rxBufferOverflow
#endif /* End uart_solinst_RX_ENABLED */

#ifdef uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define uart_solinst_CONTROL                uart_solinst_CONTROL_REG
#endif /* End uart_solinst_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(uart_solinst_TX_ENABLED)
    #define uart_solinst_TXDATA                 uart_solinst_TXDATA_REG
    #define uart_solinst_TXSTATUS               uart_solinst_TXSTATUS_REG
    #define uart_solinst_TXSTATUS_MASK          uart_solinst_TXSTATUS_MASK_REG
    #define uart_solinst_TXSTATUS_ACTL          uart_solinst_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(uart_solinst_TXCLKGEN_DP)
        #define uart_solinst_TXBITCLKGEN_CTR        uart_solinst_TXBITCLKGEN_CTR_REG
        #define uart_solinst_TXBITCLKTX_COMPLETE    uart_solinst_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define uart_solinst_TXBITCTR_PERIOD        uart_solinst_TXBITCTR_PERIOD_REG
        #define uart_solinst_TXBITCTR_CONTROL       uart_solinst_TXBITCTR_CONTROL_REG
        #define uart_solinst_TXBITCTR_COUNTER       uart_solinst_TXBITCTR_COUNTER_REG
    #endif /* uart_solinst_TXCLKGEN_DP */
#endif /* End uart_solinst_TX_ENABLED */

#if(uart_solinst_HD_ENABLED)
    #define uart_solinst_TXDATA                 uart_solinst_TXDATA_REG
    #define uart_solinst_TXSTATUS               uart_solinst_TXSTATUS_REG
    #define uart_solinst_TXSTATUS_MASK          uart_solinst_TXSTATUS_MASK_REG
    #define uart_solinst_TXSTATUS_ACTL          uart_solinst_TXSTATUS_ACTL_REG
#endif /* End uart_solinst_HD_ENABLED */

#if( (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) )
    #define uart_solinst_RXDATA                 uart_solinst_RXDATA_REG
    #define uart_solinst_RXADDRESS1             uart_solinst_RXADDRESS1_REG
    #define uart_solinst_RXADDRESS2             uart_solinst_RXADDRESS2_REG
    #define uart_solinst_RXBITCTR_PERIOD        uart_solinst_RXBITCTR_PERIOD_REG
    #define uart_solinst_RXBITCTR_CONTROL       uart_solinst_RXBITCTR_CONTROL_REG
    #define uart_solinst_RXBITCTR_COUNTER       uart_solinst_RXBITCTR_COUNTER_REG
    #define uart_solinst_RXSTATUS               uart_solinst_RXSTATUS_REG
    #define uart_solinst_RXSTATUS_MASK          uart_solinst_RXSTATUS_MASK_REG
    #define uart_solinst_RXSTATUS_ACTL          uart_solinst_RXSTATUS_ACTL_REG
#endif /* End  (uart_solinst_RX_ENABLED) || (uart_solinst_HD_ENABLED) */

#if(uart_solinst_INTERNAL_CLOCK_USED)
    #define uart_solinst_INTCLOCK_CLKEN         uart_solinst_INTCLOCK_CLKEN_REG
#endif /* End uart_solinst_INTERNAL_CLOCK_USED */

#define uart_solinst_WAIT_FOR_COMLETE_REINIT    uart_solinst_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_uart_solinst_H */


/* [] END OF FILE */
