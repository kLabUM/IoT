/*******************************************************************************
* File Name: ultrasonic_uart.h
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


#if !defined(CY_UART_ultrasonic_uart_H)
#define CY_UART_ultrasonic_uart_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define ultrasonic_uart_RX_ENABLED                     (1u)
#define ultrasonic_uart_TX_ENABLED                     (1u)
#define ultrasonic_uart_HD_ENABLED                     (0u)
#define ultrasonic_uart_RX_INTERRUPT_ENABLED           (0u)
#define ultrasonic_uart_TX_INTERRUPT_ENABLED           (0u)
#define ultrasonic_uart_INTERNAL_CLOCK_USED            (1u)
#define ultrasonic_uart_RXHW_ADDRESS_ENABLED           (0u)
#define ultrasonic_uart_OVER_SAMPLE_COUNT              (8u)
#define ultrasonic_uart_PARITY_TYPE                    (0u)
#define ultrasonic_uart_PARITY_TYPE_SW                 (0u)
#define ultrasonic_uart_BREAK_DETECT                   (0u)
#define ultrasonic_uart_BREAK_BITS_TX                  (13u)
#define ultrasonic_uart_BREAK_BITS_RX                  (13u)
#define ultrasonic_uart_TXCLKGEN_DP                    (1u)
#define ultrasonic_uart_USE23POLLING                   (1u)
#define ultrasonic_uart_FLOW_CONTROL                   (0u)
#define ultrasonic_uart_CLK_FREQ                       (0u)
#define ultrasonic_uart_TXBUFFERSIZE                   (4u)
#define ultrasonic_uart_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define ultrasonic_uart_CONTROL_REG_REMOVED            (0u)
#else
    #define ultrasonic_uart_CONTROL_REG_REMOVED            (1u)
#endif /* End ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct ultrasonic_uart_backupStruct_
{
    uint8 enableState;

    #if(ultrasonic_uart_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End ultrasonic_uart_CONTROL_REG_REMOVED */
    #if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End ultrasonic_uart_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED)*/

    #if(ultrasonic_uart_TX_ENABLED)
        #if(ultrasonic_uart_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End ultrasonic_uart_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End ultrasonic_uart_TX_ENABLED */
} ultrasonic_uart_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void ultrasonic_uart_Start(void) ;
void ultrasonic_uart_Stop(void) ;
uint8 ultrasonic_uart_ReadControlRegister(void) ;
void ultrasonic_uart_WriteControlRegister(uint8 control) ;

void ultrasonic_uart_Init(void) ;
void ultrasonic_uart_Enable(void) ;
void ultrasonic_uart_SaveConfig(void) ;
void ultrasonic_uart_RestoreConfig(void) ;
void ultrasonic_uart_Sleep(void) ;
void ultrasonic_uart_Wakeup(void) ;

/* Only if RX is enabled */
#if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )

    #if(ultrasonic_uart_RX_INTERRUPT_ENABLED)
        void  ultrasonic_uart_EnableRxInt(void) ;
        void  ultrasonic_uart_DisableRxInt(void) ;
        CY_ISR_PROTO(ultrasonic_uart_RXISR);
    #endif /* ultrasonic_uart_RX_INTERRUPT_ENABLED */

    void ultrasonic_uart_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void ultrasonic_uart_SetRxAddress1(uint8 address) ;
    void ultrasonic_uart_SetRxAddress2(uint8 address) ;

    void  ultrasonic_uart_SetRxInterruptMode(uint8 intSrc) ;
    uint8 ultrasonic_uart_ReadRxData(void) ;
    uint8 ultrasonic_uart_ReadRxStatus(void) ;
    uint8 ultrasonic_uart_GetChar(void) ;
    uint16 ultrasonic_uart_GetByte(void) ;
    uint8 ultrasonic_uart_GetRxBufferSize(void)
                                                            ;
    void ultrasonic_uart_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define ultrasonic_uart_GetRxInterruptSource   ultrasonic_uart_ReadRxStatus

#endif /* End (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */

/* Only if TX is enabled */
#if(ultrasonic_uart_TX_ENABLED || ultrasonic_uart_HD_ENABLED)

    #if(ultrasonic_uart_TX_INTERRUPT_ENABLED)
        void ultrasonic_uart_EnableTxInt(void) ;
        void ultrasonic_uart_DisableTxInt(void) ;
        CY_ISR_PROTO(ultrasonic_uart_TXISR);
    #endif /* ultrasonic_uart_TX_INTERRUPT_ENABLED */

    void ultrasonic_uart_SetTxInterruptMode(uint8 intSrc) ;
    void ultrasonic_uart_WriteTxData(uint8 txDataByte) ;
    uint8 ultrasonic_uart_ReadTxStatus(void) ;
    void ultrasonic_uart_PutChar(uint8 txDataByte) ;
    void ultrasonic_uart_PutString(const char8 string[]) ;
    void ultrasonic_uart_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void ultrasonic_uart_PutCRLF(uint8 txDataByte) ;
    void ultrasonic_uart_ClearTxBuffer(void) ;
    void ultrasonic_uart_SetTxAddressMode(uint8 addressMode) ;
    void ultrasonic_uart_SendBreak(uint8 retMode) ;
    uint8 ultrasonic_uart_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define ultrasonic_uart_PutStringConst         ultrasonic_uart_PutString
    #define ultrasonic_uart_PutArrayConst          ultrasonic_uart_PutArray
    #define ultrasonic_uart_GetTxInterruptSource   ultrasonic_uart_ReadTxStatus

#endif /* End ultrasonic_uart_TX_ENABLED || ultrasonic_uart_HD_ENABLED */

#if(ultrasonic_uart_HD_ENABLED)
    void ultrasonic_uart_LoadRxConfig(void) ;
    void ultrasonic_uart_LoadTxConfig(void) ;
#endif /* End ultrasonic_uart_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ultrasonic_uart) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    ultrasonic_uart_CyBtldrCommStart(void) CYSMALL ;
    void    ultrasonic_uart_CyBtldrCommStop(void) CYSMALL ;
    void    ultrasonic_uart_CyBtldrCommReset(void) CYSMALL ;
    cystatus ultrasonic_uart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus ultrasonic_uart_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ultrasonic_uart)
        #define CyBtldrCommStart    ultrasonic_uart_CyBtldrCommStart
        #define CyBtldrCommStop     ultrasonic_uart_CyBtldrCommStop
        #define CyBtldrCommReset    ultrasonic_uart_CyBtldrCommReset
        #define CyBtldrCommWrite    ultrasonic_uart_CyBtldrCommWrite
        #define CyBtldrCommRead     ultrasonic_uart_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ultrasonic_uart) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define ultrasonic_uart_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define ultrasonic_uart_SET_SPACE                              (0x00u)
#define ultrasonic_uart_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (ultrasonic_uart_TX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
    #if(ultrasonic_uart_TX_INTERRUPT_ENABLED)
        #define ultrasonic_uart_TX_VECT_NUM            (uint8)ultrasonic_uart_TXInternalInterrupt__INTC_NUMBER
        #define ultrasonic_uart_TX_PRIOR_NUM           (uint8)ultrasonic_uart_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ultrasonic_uart_TX_INTERRUPT_ENABLED */
    #if(ultrasonic_uart_TX_ENABLED)
        #define ultrasonic_uart_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define ultrasonic_uart_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define ultrasonic_uart_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define ultrasonic_uart_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* ultrasonic_uart_TX_ENABLED */
    #if(ultrasonic_uart_HD_ENABLED)
        #define ultrasonic_uart_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define ultrasonic_uart_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define ultrasonic_uart_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define ultrasonic_uart_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* ultrasonic_uart_HD_ENABLED */
    #define ultrasonic_uart_TX_STS_COMPLETE            (uint8)(0x01u << ultrasonic_uart_TX_STS_COMPLETE_SHIFT)
    #define ultrasonic_uart_TX_STS_FIFO_EMPTY          (uint8)(0x01u << ultrasonic_uart_TX_STS_FIFO_EMPTY_SHIFT)
    #define ultrasonic_uart_TX_STS_FIFO_FULL           (uint8)(0x01u << ultrasonic_uart_TX_STS_FIFO_FULL_SHIFT)
    #define ultrasonic_uart_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << ultrasonic_uart_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (ultrasonic_uart_TX_ENABLED) || (ultrasonic_uart_HD_ENABLED)*/

#if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
    #if(ultrasonic_uart_RX_INTERRUPT_ENABLED)
        #define ultrasonic_uart_RX_VECT_NUM            (uint8)ultrasonic_uart_RXInternalInterrupt__INTC_NUMBER
        #define ultrasonic_uart_RX_PRIOR_NUM           (uint8)ultrasonic_uart_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ultrasonic_uart_RX_INTERRUPT_ENABLED */
    #define ultrasonic_uart_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define ultrasonic_uart_RX_STS_BREAK_SHIFT             (0x01u)
    #define ultrasonic_uart_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define ultrasonic_uart_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define ultrasonic_uart_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define ultrasonic_uart_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define ultrasonic_uart_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define ultrasonic_uart_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define ultrasonic_uart_RX_STS_MRKSPC           (uint8)(0x01u << ultrasonic_uart_RX_STS_MRKSPC_SHIFT)
    #define ultrasonic_uart_RX_STS_BREAK            (uint8)(0x01u << ultrasonic_uart_RX_STS_BREAK_SHIFT)
    #define ultrasonic_uart_RX_STS_PAR_ERROR        (uint8)(0x01u << ultrasonic_uart_RX_STS_PAR_ERROR_SHIFT)
    #define ultrasonic_uart_RX_STS_STOP_ERROR       (uint8)(0x01u << ultrasonic_uart_RX_STS_STOP_ERROR_SHIFT)
    #define ultrasonic_uart_RX_STS_OVERRUN          (uint8)(0x01u << ultrasonic_uart_RX_STS_OVERRUN_SHIFT)
    #define ultrasonic_uart_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << ultrasonic_uart_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define ultrasonic_uart_RX_STS_ADDR_MATCH       (uint8)(0x01u << ultrasonic_uart_RX_STS_ADDR_MATCH_SHIFT)
    #define ultrasonic_uart_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << ultrasonic_uart_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define ultrasonic_uart_RX_HW_MASK                     (0x7Fu)
#endif /* End (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */

/* Control Register definitions */
#define ultrasonic_uart_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define ultrasonic_uart_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define ultrasonic_uart_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define ultrasonic_uart_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define ultrasonic_uart_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define ultrasonic_uart_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define ultrasonic_uart_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define ultrasonic_uart_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define ultrasonic_uart_CTRL_HD_SEND               (uint8)(0x01u << ultrasonic_uart_CTRL_HD_SEND_SHIFT)
#define ultrasonic_uart_CTRL_HD_SEND_BREAK         (uint8)(0x01u << ultrasonic_uart_CTRL_HD_SEND_BREAK_SHIFT)
#define ultrasonic_uart_CTRL_MARK                  (uint8)(0x01u << ultrasonic_uart_CTRL_MARK_SHIFT)
#define ultrasonic_uart_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << ultrasonic_uart_CTRL_PARITY_TYPE0_SHIFT)
#define ultrasonic_uart_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << ultrasonic_uart_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define ultrasonic_uart_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define ultrasonic_uart_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define ultrasonic_uart_SEND_BREAK                         (0x00u)
#define ultrasonic_uart_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define ultrasonic_uart_REINIT                             (0x02u)
#define ultrasonic_uart_SEND_WAIT_REINIT                   (0x03u)

#define ultrasonic_uart_OVER_SAMPLE_8                      (8u)
#define ultrasonic_uart_OVER_SAMPLE_16                     (16u)

#define ultrasonic_uart_BIT_CENTER                         (ultrasonic_uart_OVER_SAMPLE_COUNT - 1u)

#define ultrasonic_uart_FIFO_LENGTH                        (4u)
#define ultrasonic_uart_NUMBER_OF_START_BIT                (1u)
#define ultrasonic_uart_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define ultrasonic_uart_TXBITCTR_BREAKBITS8X   ((ultrasonic_uart_BREAK_BITS_TX * ultrasonic_uart_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define ultrasonic_uart_TXBITCTR_BREAKBITS ((ultrasonic_uart_BREAK_BITS_TX * ultrasonic_uart_OVER_SAMPLE_COUNT) - 1u)

#define ultrasonic_uart_HALF_BIT_COUNT   \
                            (((ultrasonic_uart_OVER_SAMPLE_COUNT / 2u) + (ultrasonic_uart_USE23POLLING * 1u)) - 2u)
#if (ultrasonic_uart_OVER_SAMPLE_COUNT == ultrasonic_uart_OVER_SAMPLE_8)
    #define ultrasonic_uart_HD_TXBITCTR_INIT   (((ultrasonic_uart_BREAK_BITS_TX + \
                            ultrasonic_uart_NUMBER_OF_START_BIT) * ultrasonic_uart_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define ultrasonic_uart_RXBITCTR_INIT  ((((ultrasonic_uart_BREAK_BITS_RX + ultrasonic_uart_NUMBER_OF_START_BIT) \
                            * ultrasonic_uart_OVER_SAMPLE_COUNT) + ultrasonic_uart_HALF_BIT_COUNT) - 1u)


#else /* ultrasonic_uart_OVER_SAMPLE_COUNT == ultrasonic_uart_OVER_SAMPLE_16 */
    #define ultrasonic_uart_HD_TXBITCTR_INIT   ((8u * ultrasonic_uart_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define ultrasonic_uart_RXBITCTR_INIT      (((7u * ultrasonic_uart_OVER_SAMPLE_COUNT) - 1u) + \
                                                      ultrasonic_uart_HALF_BIT_COUNT)
#endif /* End ultrasonic_uart_OVER_SAMPLE_COUNT */
#define ultrasonic_uart_HD_RXBITCTR_INIT                   ultrasonic_uart_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 ultrasonic_uart_initVar;
#if( ultrasonic_uart_TX_ENABLED && (ultrasonic_uart_TXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH))
    extern volatile uint8 ultrasonic_uart_txBuffer[ultrasonic_uart_TXBUFFERSIZE];
    extern volatile uint8 ultrasonic_uart_txBufferRead;
    extern uint8 ultrasonic_uart_txBufferWrite;
#endif /* End ultrasonic_uart_TX_ENABLED */
#if( ( ultrasonic_uart_RX_ENABLED || ultrasonic_uart_HD_ENABLED ) && \
     (ultrasonic_uart_RXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH) )
    extern volatile uint8 ultrasonic_uart_rxBuffer[ultrasonic_uart_RXBUFFERSIZE];
    extern volatile uint8 ultrasonic_uart_rxBufferRead;
    extern volatile uint8 ultrasonic_uart_rxBufferWrite;
    extern volatile uint8 ultrasonic_uart_rxBufferLoopDetect;
    extern volatile uint8 ultrasonic_uart_rxBufferOverflow;
    #if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 ultrasonic_uart_rxAddressMode;
        extern volatile uint8 ultrasonic_uart_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End ultrasonic_uart_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define ultrasonic_uart__B_UART__AM_SW_BYTE_BYTE 1
#define ultrasonic_uart__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define ultrasonic_uart__B_UART__AM_HW_BYTE_BY_BYTE 3
#define ultrasonic_uart__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define ultrasonic_uart__B_UART__AM_NONE 0

#define ultrasonic_uart__B_UART__NONE_REVB 0
#define ultrasonic_uart__B_UART__EVEN_REVB 1
#define ultrasonic_uart__B_UART__ODD_REVB 2
#define ultrasonic_uart__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define ultrasonic_uart_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define ultrasonic_uart_NUMBER_OF_STOP_BITS    (1u)

#if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
    #define ultrasonic_uart_RXADDRESSMODE      (0u)
    #define ultrasonic_uart_RXHWADDRESS1       (0u)
    #define ultrasonic_uart_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define ultrasonic_uart_RXAddressMode      ultrasonic_uart_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define ultrasonic_uart_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << ultrasonic_uart_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_BREAK_SHIFT) \
                                        | (0 << ultrasonic_uart_RX_STS_OVERRUN_SHIFT))

#define ultrasonic_uart_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << ultrasonic_uart_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << ultrasonic_uart_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << ultrasonic_uart_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << ultrasonic_uart_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define ultrasonic_uart_CONTROL_REG \
                            (* (reg8 *) ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
    #define ultrasonic_uart_CONTROL_PTR \
                            (  (reg8 *) ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
#endif /* End ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(ultrasonic_uart_TX_ENABLED)
    #define ultrasonic_uart_TXDATA_REG          (* (reg8 *) ultrasonic_uart_BUART_sTX_TxShifter_u0__F0_REG)
    #define ultrasonic_uart_TXDATA_PTR          (  (reg8 *) ultrasonic_uart_BUART_sTX_TxShifter_u0__F0_REG)
    #define ultrasonic_uart_TXDATA_AUX_CTL_REG  (* (reg8 *) ultrasonic_uart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ultrasonic_uart_TXDATA_AUX_CTL_PTR  (  (reg8 *) ultrasonic_uart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ultrasonic_uart_TXSTATUS_REG        (* (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__STATUS_REG)
    #define ultrasonic_uart_TXSTATUS_PTR        (  (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__STATUS_REG)
    #define ultrasonic_uart_TXSTATUS_MASK_REG   (* (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__MASK_REG)
    #define ultrasonic_uart_TXSTATUS_MASK_PTR   (  (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__MASK_REG)
    #define ultrasonic_uart_TXSTATUS_ACTL_REG   (* (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define ultrasonic_uart_TXSTATUS_ACTL_PTR   (  (reg8 *) ultrasonic_uart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(ultrasonic_uart_TXCLKGEN_DP)
        #define ultrasonic_uart_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ultrasonic_uart_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ultrasonic_uart_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define ultrasonic_uart_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define ultrasonic_uart_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ultrasonic_uart_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ultrasonic_uart_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ultrasonic_uart_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ultrasonic_uart_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define ultrasonic_uart_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) ultrasonic_uart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* ultrasonic_uart_TXCLKGEN_DP */

#endif /* End ultrasonic_uart_TX_ENABLED */

#if(ultrasonic_uart_HD_ENABLED)

    #define ultrasonic_uart_TXDATA_REG             (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__F1_REG )
    #define ultrasonic_uart_TXDATA_PTR             (  (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__F1_REG )
    #define ultrasonic_uart_TXDATA_AUX_CTL_REG     (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define ultrasonic_uart_TXDATA_AUX_CTL_PTR     (  (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ultrasonic_uart_TXSTATUS_REG           (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_REG )
    #define ultrasonic_uart_TXSTATUS_PTR           (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_REG )
    #define ultrasonic_uart_TXSTATUS_MASK_REG      (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__MASK_REG )
    #define ultrasonic_uart_TXSTATUS_MASK_PTR      (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__MASK_REG )
    #define ultrasonic_uart_TXSTATUS_ACTL_REG      (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ultrasonic_uart_TXSTATUS_ACTL_PTR      (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End ultrasonic_uart_HD_ENABLED */

#if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
    #define ultrasonic_uart_RXDATA_REG             (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__F0_REG )
    #define ultrasonic_uart_RXDATA_PTR             (  (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__F0_REG )
    #define ultrasonic_uart_RXADDRESS1_REG         (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__D0_REG )
    #define ultrasonic_uart_RXADDRESS1_PTR         (  (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__D0_REG )
    #define ultrasonic_uart_RXADDRESS2_REG         (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__D1_REG )
    #define ultrasonic_uart_RXADDRESS2_PTR         (  (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__D1_REG )
    #define ultrasonic_uart_RXDATA_AUX_CTL_REG     (* (reg8 *) ultrasonic_uart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ultrasonic_uart_RXBITCTR_PERIOD_REG    (* (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ultrasonic_uart_RXBITCTR_PERIOD_PTR    (  (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ultrasonic_uart_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ultrasonic_uart_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ultrasonic_uart_RXBITCTR_COUNTER_REG   (* (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__COUNT_REG )
    #define ultrasonic_uart_RXBITCTR_COUNTER_PTR   (  (reg8 *) ultrasonic_uart_BUART_sRX_RxBitCounter__COUNT_REG )

    #define ultrasonic_uart_RXSTATUS_REG           (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_REG )
    #define ultrasonic_uart_RXSTATUS_PTR           (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_REG )
    #define ultrasonic_uart_RXSTATUS_MASK_REG      (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__MASK_REG )
    #define ultrasonic_uart_RXSTATUS_MASK_PTR      (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__MASK_REG )
    #define ultrasonic_uart_RXSTATUS_ACTL_REG      (* (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ultrasonic_uart_RXSTATUS_ACTL_PTR      (  (reg8 *) ultrasonic_uart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */

#if(ultrasonic_uart_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define ultrasonic_uart_INTCLOCK_CLKEN_REG     (* (reg8 *) ultrasonic_uart_IntClock__PM_ACT_CFG)
    #define ultrasonic_uart_INTCLOCK_CLKEN_PTR     (  (reg8 *) ultrasonic_uart_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define ultrasonic_uart_INTCLOCK_CLKEN_MASK    ultrasonic_uart_IntClock__PM_ACT_MSK
#endif /* End ultrasonic_uart_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(ultrasonic_uart_TX_ENABLED)
    #define ultrasonic_uart_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End ultrasonic_uart_TX_ENABLED */

#if(ultrasonic_uart_HD_ENABLED)
    #define ultrasonic_uart_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End ultrasonic_uart_HD_ENABLED */

#if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
    #define ultrasonic_uart_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define ultrasonic_uart_initvar                    ultrasonic_uart_initVar

#define ultrasonic_uart_RX_Enabled                 ultrasonic_uart_RX_ENABLED
#define ultrasonic_uart_TX_Enabled                 ultrasonic_uart_TX_ENABLED
#define ultrasonic_uart_HD_Enabled                 ultrasonic_uart_HD_ENABLED
#define ultrasonic_uart_RX_IntInterruptEnabled     ultrasonic_uart_RX_INTERRUPT_ENABLED
#define ultrasonic_uart_TX_IntInterruptEnabled     ultrasonic_uart_TX_INTERRUPT_ENABLED
#define ultrasonic_uart_InternalClockUsed          ultrasonic_uart_INTERNAL_CLOCK_USED
#define ultrasonic_uart_RXHW_Address_Enabled       ultrasonic_uart_RXHW_ADDRESS_ENABLED
#define ultrasonic_uart_OverSampleCount            ultrasonic_uart_OVER_SAMPLE_COUNT
#define ultrasonic_uart_ParityType                 ultrasonic_uart_PARITY_TYPE

#if( ultrasonic_uart_TX_ENABLED && (ultrasonic_uart_TXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH))
    #define ultrasonic_uart_TXBUFFER               ultrasonic_uart_txBuffer
    #define ultrasonic_uart_TXBUFFERREAD           ultrasonic_uart_txBufferRead
    #define ultrasonic_uart_TXBUFFERWRITE          ultrasonic_uart_txBufferWrite
#endif /* End ultrasonic_uart_TX_ENABLED */
#if( ( ultrasonic_uart_RX_ENABLED || ultrasonic_uart_HD_ENABLED ) && \
     (ultrasonic_uart_RXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH) )
    #define ultrasonic_uart_RXBUFFER               ultrasonic_uart_rxBuffer
    #define ultrasonic_uart_RXBUFFERREAD           ultrasonic_uart_rxBufferRead
    #define ultrasonic_uart_RXBUFFERWRITE          ultrasonic_uart_rxBufferWrite
    #define ultrasonic_uart_RXBUFFERLOOPDETECT     ultrasonic_uart_rxBufferLoopDetect
    #define ultrasonic_uart_RXBUFFER_OVERFLOW      ultrasonic_uart_rxBufferOverflow
#endif /* End ultrasonic_uart_RX_ENABLED */

#ifdef ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define ultrasonic_uart_CONTROL                ultrasonic_uart_CONTROL_REG
#endif /* End ultrasonic_uart_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(ultrasonic_uart_TX_ENABLED)
    #define ultrasonic_uart_TXDATA                 ultrasonic_uart_TXDATA_REG
    #define ultrasonic_uart_TXSTATUS               ultrasonic_uart_TXSTATUS_REG
    #define ultrasonic_uart_TXSTATUS_MASK          ultrasonic_uart_TXSTATUS_MASK_REG
    #define ultrasonic_uart_TXSTATUS_ACTL          ultrasonic_uart_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(ultrasonic_uart_TXCLKGEN_DP)
        #define ultrasonic_uart_TXBITCLKGEN_CTR        ultrasonic_uart_TXBITCLKGEN_CTR_REG
        #define ultrasonic_uart_TXBITCLKTX_COMPLETE    ultrasonic_uart_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define ultrasonic_uart_TXBITCTR_PERIOD        ultrasonic_uart_TXBITCTR_PERIOD_REG
        #define ultrasonic_uart_TXBITCTR_CONTROL       ultrasonic_uart_TXBITCTR_CONTROL_REG
        #define ultrasonic_uart_TXBITCTR_COUNTER       ultrasonic_uart_TXBITCTR_COUNTER_REG
    #endif /* ultrasonic_uart_TXCLKGEN_DP */
#endif /* End ultrasonic_uart_TX_ENABLED */

#if(ultrasonic_uart_HD_ENABLED)
    #define ultrasonic_uart_TXDATA                 ultrasonic_uart_TXDATA_REG
    #define ultrasonic_uart_TXSTATUS               ultrasonic_uart_TXSTATUS_REG
    #define ultrasonic_uart_TXSTATUS_MASK          ultrasonic_uart_TXSTATUS_MASK_REG
    #define ultrasonic_uart_TXSTATUS_ACTL          ultrasonic_uart_TXSTATUS_ACTL_REG
#endif /* End ultrasonic_uart_HD_ENABLED */

#if( (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) )
    #define ultrasonic_uart_RXDATA                 ultrasonic_uart_RXDATA_REG
    #define ultrasonic_uart_RXADDRESS1             ultrasonic_uart_RXADDRESS1_REG
    #define ultrasonic_uart_RXADDRESS2             ultrasonic_uart_RXADDRESS2_REG
    #define ultrasonic_uart_RXBITCTR_PERIOD        ultrasonic_uart_RXBITCTR_PERIOD_REG
    #define ultrasonic_uart_RXBITCTR_CONTROL       ultrasonic_uart_RXBITCTR_CONTROL_REG
    #define ultrasonic_uart_RXBITCTR_COUNTER       ultrasonic_uart_RXBITCTR_COUNTER_REG
    #define ultrasonic_uart_RXSTATUS               ultrasonic_uart_RXSTATUS_REG
    #define ultrasonic_uart_RXSTATUS_MASK          ultrasonic_uart_RXSTATUS_MASK_REG
    #define ultrasonic_uart_RXSTATUS_ACTL          ultrasonic_uart_RXSTATUS_ACTL_REG
#endif /* End  (ultrasonic_uart_RX_ENABLED) || (ultrasonic_uart_HD_ENABLED) */

#if(ultrasonic_uart_INTERNAL_CLOCK_USED)
    #define ultrasonic_uart_INTCLOCK_CLKEN         ultrasonic_uart_INTCLOCK_CLKEN_REG
#endif /* End ultrasonic_uart_INTERNAL_CLOCK_USED */

#define ultrasonic_uart_WAIT_FOR_COMLETE_REINIT    ultrasonic_uart_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_ultrasonic_uart_H */


/* [] END OF FILE */
