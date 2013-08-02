/*******************************************************************************
* File Name: uart_1_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uart_1.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (uart_1_RX_ENABLED || uart_1_HD_ENABLED) && \
     (uart_1_RXBUFFERSIZE > uart_1_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: uart_1_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_1_rxBuffer - RAM buffer pointer for save received data.
    *  uart_1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  uart_1_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  uart_1_rxBufferOverflow - software overflow flag. Set to one
    *     when uart_1_rxBufferWrite index overtakes
    *     uart_1_rxBufferRead index.
    *  uart_1_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when uart_1_rxBufferWrite is equal to
    *    uart_1_rxBufferRead
    *  uart_1_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  uart_1_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_1_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START uart_1_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = uart_1_RXSTATUS_REG;

        if((readData & (uart_1_RX_STS_BREAK | uart_1_RX_STS_PAR_ERROR |
                        uart_1_RX_STS_STOP_ERROR | uart_1_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START uart_1_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & uart_1_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (uart_1_RXHW_ADDRESS_ENABLED)
                if(uart_1_rxAddressMode == (uint8)uart_1__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & uart_1_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & uart_1_RX_STS_ADDR_MATCH) != 0u)
                        {
                            uart_1_rxAddressDetected = 1u;
                        }
                        else
                        {
                            uart_1_rxAddressDetected = 0u;
                        }
                    }

                    readData = uart_1_RXDATA_REG;
                    if(uart_1_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        uart_1_rxBuffer[uart_1_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    uart_1_rxBuffer[uart_1_rxBufferWrite] = uart_1_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                uart_1_rxBuffer[uart_1_rxBufferWrite] = uart_1_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(uart_1_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    uart_1_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                uart_1_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(uart_1_rxBufferWrite >= uart_1_RXBUFFERSIZE)
                {
                    uart_1_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(uart_1_rxBufferWrite == uart_1_rxBufferRead)
                {
                    uart_1_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(uart_1_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        uart_1_RXSTATUS_MASK_REG  &= (uint8)~uart_1_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(uart_1_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End uart_1_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = uart_1_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_1_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End uart_1_RX_ENABLED && (uart_1_RXBUFFERSIZE > uart_1_FIFO_LENGTH) */


#if(uart_1_TX_ENABLED && (uart_1_TXBUFFERSIZE > uart_1_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: uart_1_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_1_txBuffer - RAM buffer pointer for transmit data from.
    *  uart_1_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  uart_1_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_1_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START uart_1_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((uart_1_txBufferRead != uart_1_txBufferWrite) &&
             ((uart_1_TXSTATUS_REG & uart_1_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(uart_1_txBufferRead >= uart_1_TXBUFFERSIZE)
            {
                uart_1_txBufferRead = 0u;
            }

            uart_1_TXDATA_REG = uart_1_txBuffer[uart_1_txBufferRead];

            /* Set next pointer. */
            uart_1_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_1_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End uart_1_TX_ENABLED && (uart_1_TXBUFFERSIZE > uart_1_FIFO_LENGTH) */


/* [] END OF FILE */
