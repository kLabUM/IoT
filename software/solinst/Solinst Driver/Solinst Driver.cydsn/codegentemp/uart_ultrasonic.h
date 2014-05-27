/*******************************************************************************
* File Name: uart_ultrasonic.h
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


#if !defined(CY_UART_uart_ultrasonic_H)
#define CY_UART_uart_ultrasonic_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define uart_ultrasonic_RX_ENABLED                     (1u)
#define uart_ultrasonic_TX_ENABLED                     (1u)
#define uart_ultrasonic_HD_ENABLED                     (0u)
#define uart_ultrasonic_RX_INTERRUPT_ENABLED           (0u)
#define uart_ultrasonic_TX_INTERRUPT_ENABLED           (0u)
#define uart_ultrasonic_INTERNAL_CLOCK_USED            (1u)
#define uart_ultrasonic_RXHW_ADDRESS_ENABLED           (0u)
#define uart_ultrasonic_OVER_SAMPLE_COUNT              (8u)
#define uart_ultrasonic_PARITY_TYPE                    (0u)
#define uart_ultrasonic_PARITY_TYPE_SW                 (0u)
#define uart_ultrasonic_BREAK_DETECT                   (0u)
#define uart_ultrasonic_BREAK_BITS_TX                  (13u)
#define uart_ultrasonic_BREAK_BITS_RX                  (13u)
#define uart_ultrasonic_TXCLKGEN_DP                    (1u)
#define uart_ultrasonic_USE23POLLING                   (1u)
#define uart_ultrasonic_FLOW_CONTROL                   (0u)
#define uart_ultrasonic_CLK_FREQ                       (0u)
#define uart_ultrasonic_TXBUFFERSIZE                   (4u)
#define uart_ultrasonic_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define uart_ultrasonic_CONTROL_REG_REMOVED            (0u)
#else
    #define uart_ultrasonic_CONTROL_REG_REMOVED            (1u)
#endif /* End uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct uart_ultrasonic_backupStruct_
{
    uint8 enableState;

    #if(uart_ultrasonic_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End uart_ultrasonic_CONTROL_REG_REMOVED */
    #if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (uart_ultrasonic_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End uart_ultrasonic_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED)*/

    #if(uart_ultrasonic_TX_ENABLED)
        #if(uart_ultrasonic_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End uart_ultrasonic_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End uart_ultrasonic_TX_ENABLED */
} uart_ultrasonic_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void uart_ultrasonic_Start(void) ;
void uart_ultrasonic_Stop(void) ;
uint8 uart_ultrasonic_ReadControlRegister(void) ;
void uart_ultrasonic_WriteControlRegister(uint8 control) ;

void uart_ultrasonic_Init(void) ;
void uart_ultrasonic_Enable(void) ;
void uart_ultrasonic_SaveConfig(void) ;
void uart_ultrasonic_RestoreConfig(void) ;
void uart_ultrasonic_Sleep(void) ;
void uart_ultrasonic_Wakeup(void) ;

/* Only if RX is enabled */
#if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )

    #if(uart_ultrasonic_RX_INTERRUPT_ENABLED)
        void  uart_ultrasonic_EnableRxInt(void) ;
        void  uart_ultrasonic_DisableRxInt(void) ;
        CY_ISR_PROTO(uart_ultrasonic_RXISR);
    #endif /* uart_ultrasonic_RX_INTERRUPT_ENABLED */

    void uart_ultrasonic_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void uart_ultrasonic_SetRxAddress1(uint8 address) ;
    void uart_ultrasonic_SetRxAddress2(uint8 address) ;

    void  uart_ultrasonic_SetRxInterruptMode(uint8 intSrc) ;
    uint8 uart_ultrasonic_ReadRxData(void) ;
    uint8 uart_ultrasonic_ReadRxStatus(void) ;
    uint8 uart_ultrasonic_GetChar(void) ;
    uint16 uart_ultrasonic_GetByte(void) ;
    uint8 uart_ultrasonic_GetRxBufferSize(void)
                                                            ;
    void uart_ultrasonic_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define uart_ultrasonic_GetRxInterruptSource   uart_ultrasonic_ReadRxStatus

#endif /* End (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) */

/* Only if TX is enabled */
#if(uart_ultrasonic_TX_ENABLED || uart_ultrasonic_HD_ENABLED)

    #if(uart_ultrasonic_TX_INTERRUPT_ENABLED)
        void uart_ultrasonic_EnableTxInt(void) ;
        void uart_ultrasonic_DisableTxInt(void) ;
        CY_ISR_PROTO(uart_ultrasonic_TXISR);
    #endif /* uart_ultrasonic_TX_INTERRUPT_ENABLED */

    void uart_ultrasonic_SetTxInterruptMode(uint8 intSrc) ;
    void uart_ultrasonic_WriteTxData(uint8 txDataByte) ;
    uint8 uart_ultrasonic_ReadTxStatus(void) ;
    void uart_ultrasonic_PutChar(uint8 txDataByte) ;
    void uart_ultrasonic_PutString(const char8 string[]) ;
    void uart_ultrasonic_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void uart_ultrasonic_PutCRLF(uint8 txDataByte) ;
    void uart_ultrasonic_ClearTxBuffer(void) ;
    void uart_ultrasonic_SetTxAddressMode(uint8 addressMode) ;
    void uart_ultrasonic_SendBreak(uint8 retMode) ;
    uint8 uart_ultrasonic_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define uart_ultrasonic_PutStringConst         uart_ultrasonic_PutString
    #define uart_ultrasonic_PutArrayConst          uart_ultrasonic_PutArray
    #define uart_ultrasonic_GetTxInterruptSource   uart_ultrasonic_ReadTxStatus

#endif /* End uart_ultrasonic_TX_ENABLED || uart_ultrasonic_HD_ENABLED */

#if(uart_ultrasonic_HD_ENABLED)
    void uart_ultrasonic_LoadRxConfig(void) ;
    void uart_ultrasonic_LoadTxConfig(void) ;
#endif /* End uart_ultrasonic_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_ultrasonic) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    uart_ultrasonic_CyBtldrCommStart(void) CYSMALL ;
    void    uart_ultrasonic_CyBtldrCommStop(void) CYSMALL ;
    void    uart_ultrasonic_CyBtldrCommReset(void) CYSMALL ;
    cystatus uart_ultrasonic_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus uart_ultrasonic_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_ultrasonic)
        #define CyBtldrCommStart    uart_ultrasonic_CyBtldrCommStart
        #define CyBtldrCommStop     uart_ultrasonic_CyBtldrCommStop
        #define CyBtldrCommReset    uart_ultrasonic_CyBtldrCommReset
        #define CyBtldrCommWrite    uart_ultrasonic_CyBtldrCommWrite
        #define CyBtldrCommRead     uart_ultrasonic_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_ultrasonic) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define uart_ultrasonic_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define uart_ultrasonic_SET_SPACE                              (0x00u)
#define uart_ultrasonic_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (uart_ultrasonic_TX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
    #if(uart_ultrasonic_TX_INTERRUPT_ENABLED)
        #define uart_ultrasonic_TX_VECT_NUM            (uint8)uart_ultrasonic_TXInternalInterrupt__INTC_NUMBER
        #define uart_ultrasonic_TX_PRIOR_NUM           (uint8)uart_ultrasonic_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_ultrasonic_TX_INTERRUPT_ENABLED */
    #if(uart_ultrasonic_TX_ENABLED)
        #define uart_ultrasonic_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define uart_ultrasonic_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define uart_ultrasonic_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define uart_ultrasonic_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* uart_ultrasonic_TX_ENABLED */
    #if(uart_ultrasonic_HD_ENABLED)
        #define uart_ultrasonic_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define uart_ultrasonic_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define uart_ultrasonic_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define uart_ultrasonic_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* uart_ultrasonic_HD_ENABLED */
    #define uart_ultrasonic_TX_STS_COMPLETE            (uint8)(0x01u << uart_ultrasonic_TX_STS_COMPLETE_SHIFT)
    #define uart_ultrasonic_TX_STS_FIFO_EMPTY          (uint8)(0x01u << uart_ultrasonic_TX_STS_FIFO_EMPTY_SHIFT)
    #define uart_ultrasonic_TX_STS_FIFO_FULL           (uint8)(0x01u << uart_ultrasonic_TX_STS_FIFO_FULL_SHIFT)
    #define uart_ultrasonic_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << uart_ultrasonic_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (uart_ultrasonic_TX_ENABLED) || (uart_ultrasonic_HD_ENABLED)*/

#if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
    #if(uart_ultrasonic_RX_INTERRUPT_ENABLED)
        #define uart_ultrasonic_RX_VECT_NUM            (uint8)uart_ultrasonic_RXInternalInterrupt__INTC_NUMBER
        #define uart_ultrasonic_RX_PRIOR_NUM           (uint8)uart_ultrasonic_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_ultrasonic_RX_INTERRUPT_ENABLED */
    #define uart_ultrasonic_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define uart_ultrasonic_RX_STS_BREAK_SHIFT             (0x01u)
    #define uart_ultrasonic_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define uart_ultrasonic_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define uart_ultrasonic_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define uart_ultrasonic_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define uart_ultrasonic_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define uart_ultrasonic_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define uart_ultrasonic_RX_STS_MRKSPC           (uint8)(0x01u << uart_ultrasonic_RX_STS_MRKSPC_SHIFT)
    #define uart_ultrasonic_RX_STS_BREAK            (uint8)(0x01u << uart_ultrasonic_RX_STS_BREAK_SHIFT)
    #define uart_ultrasonic_RX_STS_PAR_ERROR        (uint8)(0x01u << uart_ultrasonic_RX_STS_PAR_ERROR_SHIFT)
    #define uart_ultrasonic_RX_STS_STOP_ERROR       (uint8)(0x01u << uart_ultrasonic_RX_STS_STOP_ERROR_SHIFT)
    #define uart_ultrasonic_RX_STS_OVERRUN          (uint8)(0x01u << uart_ultrasonic_RX_STS_OVERRUN_SHIFT)
    #define uart_ultrasonic_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << uart_ultrasonic_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define uart_ultrasonic_RX_STS_ADDR_MATCH       (uint8)(0x01u << uart_ultrasonic_RX_STS_ADDR_MATCH_SHIFT)
    #define uart_ultrasonic_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << uart_ultrasonic_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define uart_ultrasonic_RX_HW_MASK                     (0x7Fu)
#endif /* End (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) */

/* Control Register definitions */
#define uart_ultrasonic_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define uart_ultrasonic_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define uart_ultrasonic_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define uart_ultrasonic_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define uart_ultrasonic_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define uart_ultrasonic_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define uart_ultrasonic_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define uart_ultrasonic_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define uart_ultrasonic_CTRL_HD_SEND               (uint8)(0x01u << uart_ultrasonic_CTRL_HD_SEND_SHIFT)
#define uart_ultrasonic_CTRL_HD_SEND_BREAK         (uint8)(0x01u << uart_ultrasonic_CTRL_HD_SEND_BREAK_SHIFT)
#define uart_ultrasonic_CTRL_MARK                  (uint8)(0x01u << uart_ultrasonic_CTRL_MARK_SHIFT)
#define uart_ultrasonic_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << uart_ultrasonic_CTRL_PARITY_TYPE0_SHIFT)
#define uart_ultrasonic_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << uart_ultrasonic_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define uart_ultrasonic_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define uart_ultrasonic_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define uart_ultrasonic_SEND_BREAK                         (0x00u)
#define uart_ultrasonic_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define uart_ultrasonic_REINIT                             (0x02u)
#define uart_ultrasonic_SEND_WAIT_REINIT                   (0x03u)

#define uart_ultrasonic_OVER_SAMPLE_8                      (8u)
#define uart_ultrasonic_OVER_SAMPLE_16                     (16u)

#define uart_ultrasonic_BIT_CENTER                         (uart_ultrasonic_OVER_SAMPLE_COUNT - 1u)

#define uart_ultrasonic_FIFO_LENGTH                        (4u)
#define uart_ultrasonic_NUMBER_OF_START_BIT                (1u)
#define uart_ultrasonic_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define uart_ultrasonic_TXBITCTR_BREAKBITS8X   ((uart_ultrasonic_BREAK_BITS_TX * uart_ultrasonic_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define uart_ultrasonic_TXBITCTR_BREAKBITS ((uart_ultrasonic_BREAK_BITS_TX * uart_ultrasonic_OVER_SAMPLE_COUNT) - 1u)

#define uart_ultrasonic_HALF_BIT_COUNT   \
                            (((uart_ultrasonic_OVER_SAMPLE_COUNT / 2u) + (uart_ultrasonic_USE23POLLING * 1u)) - 2u)
#if (uart_ultrasonic_OVER_SAMPLE_COUNT == uart_ultrasonic_OVER_SAMPLE_8)
    #define uart_ultrasonic_HD_TXBITCTR_INIT   (((uart_ultrasonic_BREAK_BITS_TX + \
                            uart_ultrasonic_NUMBER_OF_START_BIT) * uart_ultrasonic_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define uart_ultrasonic_RXBITCTR_INIT  ((((uart_ultrasonic_BREAK_BITS_RX + uart_ultrasonic_NUMBER_OF_START_BIT) \
                            * uart_ultrasonic_OVER_SAMPLE_COUNT) + uart_ultrasonic_HALF_BIT_COUNT) - 1u)


#else /* uart_ultrasonic_OVER_SAMPLE_COUNT == uart_ultrasonic_OVER_SAMPLE_16 */
    #define uart_ultrasonic_HD_TXBITCTR_INIT   ((8u * uart_ultrasonic_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define uart_ultrasonic_RXBITCTR_INIT      (((7u * uart_ultrasonic_OVER_SAMPLE_COUNT) - 1u) + \
                                                      uart_ultrasonic_HALF_BIT_COUNT)
#endif /* End uart_ultrasonic_OVER_SAMPLE_COUNT */
#define uart_ultrasonic_HD_RXBITCTR_INIT                   uart_ultrasonic_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 uart_ultrasonic_initVar;
#if( uart_ultrasonic_TX_ENABLED && (uart_ultrasonic_TXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH))
    extern volatile uint8 uart_ultrasonic_txBuffer[uart_ultrasonic_TXBUFFERSIZE];
    extern volatile uint8 uart_ultrasonic_txBufferRead;
    extern uint8 uart_ultrasonic_txBufferWrite;
#endif /* End uart_ultrasonic_TX_ENABLED */
#if( ( uart_ultrasonic_RX_ENABLED || uart_ultrasonic_HD_ENABLED ) && \
     (uart_ultrasonic_RXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH) )
    extern volatile uint8 uart_ultrasonic_rxBuffer[uart_ultrasonic_RXBUFFERSIZE];
    extern volatile uint8 uart_ultrasonic_rxBufferRead;
    extern volatile uint8 uart_ultrasonic_rxBufferWrite;
    extern volatile uint8 uart_ultrasonic_rxBufferLoopDetect;
    extern volatile uint8 uart_ultrasonic_rxBufferOverflow;
    #if (uart_ultrasonic_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 uart_ultrasonic_rxAddressMode;
        extern volatile uint8 uart_ultrasonic_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End uart_ultrasonic_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define uart_ultrasonic__B_UART__AM_SW_BYTE_BYTE 1
#define uart_ultrasonic__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define uart_ultrasonic__B_UART__AM_HW_BYTE_BY_BYTE 3
#define uart_ultrasonic__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define uart_ultrasonic__B_UART__AM_NONE 0

#define uart_ultrasonic__B_UART__NONE_REVB 0
#define uart_ultrasonic__B_UART__EVEN_REVB 1
#define uart_ultrasonic__B_UART__ODD_REVB 2
#define uart_ultrasonic__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define uart_ultrasonic_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define uart_ultrasonic_NUMBER_OF_STOP_BITS    (1u)

#if (uart_ultrasonic_RXHW_ADDRESS_ENABLED)
    #define uart_ultrasonic_RXADDRESSMODE      (0u)
    #define uart_ultrasonic_RXHWADDRESS1       (0u)
    #define uart_ultrasonic_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define uart_ultrasonic_RXAddressMode      uart_ultrasonic_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define uart_ultrasonic_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << uart_ultrasonic_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_BREAK_SHIFT) \
                                        | (0 << uart_ultrasonic_RX_STS_OVERRUN_SHIFT))

#define uart_ultrasonic_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << uart_ultrasonic_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << uart_ultrasonic_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << uart_ultrasonic_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << uart_ultrasonic_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define uart_ultrasonic_CONTROL_REG \
                            (* (reg8 *) uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
    #define uart_ultrasonic_CONTROL_PTR \
                            (  (reg8 *) uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
#endif /* End uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(uart_ultrasonic_TX_ENABLED)
    #define uart_ultrasonic_TXDATA_REG          (* (reg8 *) uart_ultrasonic_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_ultrasonic_TXDATA_PTR          (  (reg8 *) uart_ultrasonic_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_ultrasonic_TXDATA_AUX_CTL_REG  (* (reg8 *) uart_ultrasonic_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_ultrasonic_TXDATA_AUX_CTL_PTR  (  (reg8 *) uart_ultrasonic_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_ultrasonic_TXSTATUS_REG        (* (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__STATUS_REG)
    #define uart_ultrasonic_TXSTATUS_PTR        (  (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__STATUS_REG)
    #define uart_ultrasonic_TXSTATUS_MASK_REG   (* (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__MASK_REG)
    #define uart_ultrasonic_TXSTATUS_MASK_PTR   (  (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__MASK_REG)
    #define uart_ultrasonic_TXSTATUS_ACTL_REG   (* (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define uart_ultrasonic_TXSTATUS_ACTL_PTR   (  (reg8 *) uart_ultrasonic_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(uart_ultrasonic_TXCLKGEN_DP)
        #define uart_ultrasonic_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_ultrasonic_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_ultrasonic_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define uart_ultrasonic_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define uart_ultrasonic_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_ultrasonic_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_ultrasonic_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_ultrasonic_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_ultrasonic_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define uart_ultrasonic_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) uart_ultrasonic_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* uart_ultrasonic_TXCLKGEN_DP */

#endif /* End uart_ultrasonic_TX_ENABLED */

#if(uart_ultrasonic_HD_ENABLED)

    #define uart_ultrasonic_TXDATA_REG             (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_ultrasonic_TXDATA_PTR             (  (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_ultrasonic_TXDATA_AUX_CTL_REG     (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define uart_ultrasonic_TXDATA_AUX_CTL_PTR     (  (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_ultrasonic_TXSTATUS_REG           (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_REG )
    #define uart_ultrasonic_TXSTATUS_PTR           (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_REG )
    #define uart_ultrasonic_TXSTATUS_MASK_REG      (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__MASK_REG )
    #define uart_ultrasonic_TXSTATUS_MASK_PTR      (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__MASK_REG )
    #define uart_ultrasonic_TXSTATUS_ACTL_REG      (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_ultrasonic_TXSTATUS_ACTL_PTR      (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End uart_ultrasonic_HD_ENABLED */

#if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
    #define uart_ultrasonic_RXDATA_REG             (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_ultrasonic_RXDATA_PTR             (  (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_ultrasonic_RXADDRESS1_REG         (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_ultrasonic_RXADDRESS1_PTR         (  (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_ultrasonic_RXADDRESS2_REG         (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_ultrasonic_RXADDRESS2_PTR         (  (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_ultrasonic_RXDATA_AUX_CTL_REG     (* (reg8 *) uart_ultrasonic_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_ultrasonic_RXBITCTR_PERIOD_REG    (* (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_ultrasonic_RXBITCTR_PERIOD_PTR    (  (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_ultrasonic_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_ultrasonic_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_ultrasonic_RXBITCTR_COUNTER_REG   (* (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__COUNT_REG )
    #define uart_ultrasonic_RXBITCTR_COUNTER_PTR   (  (reg8 *) uart_ultrasonic_BUART_sRX_RxBitCounter__COUNT_REG )

    #define uart_ultrasonic_RXSTATUS_REG           (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_REG )
    #define uart_ultrasonic_RXSTATUS_PTR           (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_REG )
    #define uart_ultrasonic_RXSTATUS_MASK_REG      (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__MASK_REG )
    #define uart_ultrasonic_RXSTATUS_MASK_PTR      (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__MASK_REG )
    #define uart_ultrasonic_RXSTATUS_ACTL_REG      (* (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_ultrasonic_RXSTATUS_ACTL_PTR      (  (reg8 *) uart_ultrasonic_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) */

#if(uart_ultrasonic_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define uart_ultrasonic_INTCLOCK_CLKEN_REG     (* (reg8 *) uart_ultrasonic_IntClock__PM_ACT_CFG)
    #define uart_ultrasonic_INTCLOCK_CLKEN_PTR     (  (reg8 *) uart_ultrasonic_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define uart_ultrasonic_INTCLOCK_CLKEN_MASK    uart_ultrasonic_IntClock__PM_ACT_MSK
#endif /* End uart_ultrasonic_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(uart_ultrasonic_TX_ENABLED)
    #define uart_ultrasonic_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End uart_ultrasonic_TX_ENABLED */

#if(uart_ultrasonic_HD_ENABLED)
    #define uart_ultrasonic_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End uart_ultrasonic_HD_ENABLED */

#if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
    #define uart_ultrasonic_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define uart_ultrasonic_initvar                    uart_ultrasonic_initVar

#define uart_ultrasonic_RX_Enabled                 uart_ultrasonic_RX_ENABLED
#define uart_ultrasonic_TX_Enabled                 uart_ultrasonic_TX_ENABLED
#define uart_ultrasonic_HD_Enabled                 uart_ultrasonic_HD_ENABLED
#define uart_ultrasonic_RX_IntInterruptEnabled     uart_ultrasonic_RX_INTERRUPT_ENABLED
#define uart_ultrasonic_TX_IntInterruptEnabled     uart_ultrasonic_TX_INTERRUPT_ENABLED
#define uart_ultrasonic_InternalClockUsed          uart_ultrasonic_INTERNAL_CLOCK_USED
#define uart_ultrasonic_RXHW_Address_Enabled       uart_ultrasonic_RXHW_ADDRESS_ENABLED
#define uart_ultrasonic_OverSampleCount            uart_ultrasonic_OVER_SAMPLE_COUNT
#define uart_ultrasonic_ParityType                 uart_ultrasonic_PARITY_TYPE

#if( uart_ultrasonic_TX_ENABLED && (uart_ultrasonic_TXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH))
    #define uart_ultrasonic_TXBUFFER               uart_ultrasonic_txBuffer
    #define uart_ultrasonic_TXBUFFERREAD           uart_ultrasonic_txBufferRead
    #define uart_ultrasonic_TXBUFFERWRITE          uart_ultrasonic_txBufferWrite
#endif /* End uart_ultrasonic_TX_ENABLED */
#if( ( uart_ultrasonic_RX_ENABLED || uart_ultrasonic_HD_ENABLED ) && \
     (uart_ultrasonic_RXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH) )
    #define uart_ultrasonic_RXBUFFER               uart_ultrasonic_rxBuffer
    #define uart_ultrasonic_RXBUFFERREAD           uart_ultrasonic_rxBufferRead
    #define uart_ultrasonic_RXBUFFERWRITE          uart_ultrasonic_rxBufferWrite
    #define uart_ultrasonic_RXBUFFERLOOPDETECT     uart_ultrasonic_rxBufferLoopDetect
    #define uart_ultrasonic_RXBUFFER_OVERFLOW      uart_ultrasonic_rxBufferOverflow
#endif /* End uart_ultrasonic_RX_ENABLED */

#ifdef uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define uart_ultrasonic_CONTROL                uart_ultrasonic_CONTROL_REG
#endif /* End uart_ultrasonic_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(uart_ultrasonic_TX_ENABLED)
    #define uart_ultrasonic_TXDATA                 uart_ultrasonic_TXDATA_REG
    #define uart_ultrasonic_TXSTATUS               uart_ultrasonic_TXSTATUS_REG
    #define uart_ultrasonic_TXSTATUS_MASK          uart_ultrasonic_TXSTATUS_MASK_REG
    #define uart_ultrasonic_TXSTATUS_ACTL          uart_ultrasonic_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(uart_ultrasonic_TXCLKGEN_DP)
        #define uart_ultrasonic_TXBITCLKGEN_CTR        uart_ultrasonic_TXBITCLKGEN_CTR_REG
        #define uart_ultrasonic_TXBITCLKTX_COMPLETE    uart_ultrasonic_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define uart_ultrasonic_TXBITCTR_PERIOD        uart_ultrasonic_TXBITCTR_PERIOD_REG
        #define uart_ultrasonic_TXBITCTR_CONTROL       uart_ultrasonic_TXBITCTR_CONTROL_REG
        #define uart_ultrasonic_TXBITCTR_COUNTER       uart_ultrasonic_TXBITCTR_COUNTER_REG
    #endif /* uart_ultrasonic_TXCLKGEN_DP */
#endif /* End uart_ultrasonic_TX_ENABLED */

#if(uart_ultrasonic_HD_ENABLED)
    #define uart_ultrasonic_TXDATA                 uart_ultrasonic_TXDATA_REG
    #define uart_ultrasonic_TXSTATUS               uart_ultrasonic_TXSTATUS_REG
    #define uart_ultrasonic_TXSTATUS_MASK          uart_ultrasonic_TXSTATUS_MASK_REG
    #define uart_ultrasonic_TXSTATUS_ACTL          uart_ultrasonic_TXSTATUS_ACTL_REG
#endif /* End uart_ultrasonic_HD_ENABLED */

#if( (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) )
    #define uart_ultrasonic_RXDATA                 uart_ultrasonic_RXDATA_REG
    #define uart_ultrasonic_RXADDRESS1             uart_ultrasonic_RXADDRESS1_REG
    #define uart_ultrasonic_RXADDRESS2             uart_ultrasonic_RXADDRESS2_REG
    #define uart_ultrasonic_RXBITCTR_PERIOD        uart_ultrasonic_RXBITCTR_PERIOD_REG
    #define uart_ultrasonic_RXBITCTR_CONTROL       uart_ultrasonic_RXBITCTR_CONTROL_REG
    #define uart_ultrasonic_RXBITCTR_COUNTER       uart_ultrasonic_RXBITCTR_COUNTER_REG
    #define uart_ultrasonic_RXSTATUS               uart_ultrasonic_RXSTATUS_REG
    #define uart_ultrasonic_RXSTATUS_MASK          uart_ultrasonic_RXSTATUS_MASK_REG
    #define uart_ultrasonic_RXSTATUS_ACTL          uart_ultrasonic_RXSTATUS_ACTL_REG
#endif /* End  (uart_ultrasonic_RX_ENABLED) || (uart_ultrasonic_HD_ENABLED) */

#if(uart_ultrasonic_INTERNAL_CLOCK_USED)
    #define uart_ultrasonic_INTCLOCK_CLKEN         uart_ultrasonic_INTCLOCK_CLKEN_REG
#endif /* End uart_ultrasonic_INTERNAL_CLOCK_USED */

#define uart_ultrasonic_WAIT_FOR_COMLETE_REINIT    uart_ultrasonic_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_uart_ultrasonic_H */


/* [] END OF FILE */
