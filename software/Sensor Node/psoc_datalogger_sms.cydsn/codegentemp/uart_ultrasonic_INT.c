/*******************************************************************************
* File Name: uart_ultrasonic_INT.c
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

#include "uart_ultrasonic.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (uart_ultrasonic_RX_ENABLED || uart_ultrasonic_HD_ENABLED) && \
     (uart_ultrasonic_RXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: uart_ultrasonic_RXISR
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
    *  uart_ultrasonic_rxBuffer - RAM buffer pointer for save received data.
    *  uart_ultrasonic_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  uart_ultrasonic_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  uart_ultrasonic_rxBufferOverflow - software overflow flag. Set to one
    *     when uart_ultrasonic_rxBufferWrite index overtakes
    *     uart_ultrasonic_rxBufferRead index.
    *  uart_ultrasonic_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when uart_ultrasonic_rxBufferWrite is equal to
    *    uart_ultrasonic_rxBufferRead
    *  uart_ultrasonic_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  uart_ultrasonic_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_ultrasonic_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START uart_ultrasonic_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = uart_ultrasonic_RXSTATUS_REG;

        if((readData & (uart_ultrasonic_RX_STS_BREAK | uart_ultrasonic_RX_STS_PAR_ERROR |
                        uart_ultrasonic_RX_STS_STOP_ERROR | uart_ultrasonic_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START uart_ultrasonic_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & uart_ultrasonic_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (uart_ultrasonic_RXHW_ADDRESS_ENABLED)
                if(uart_ultrasonic_rxAddressMode == (uint8)uart_ultrasonic__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & uart_ultrasonic_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & uart_ultrasonic_RX_STS_ADDR_MATCH) != 0u)
                        {
                            uart_ultrasonic_rxAddressDetected = 1u;
                        }
                        else
                        {
                            uart_ultrasonic_rxAddressDetected = 0u;
                        }
                    }

                    readData = uart_ultrasonic_RXDATA_REG;
                    if(uart_ultrasonic_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        uart_ultrasonic_rxBuffer[uart_ultrasonic_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    uart_ultrasonic_rxBuffer[uart_ultrasonic_rxBufferWrite] = uart_ultrasonic_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                uart_ultrasonic_rxBuffer[uart_ultrasonic_rxBufferWrite] = uart_ultrasonic_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(uart_ultrasonic_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    uart_ultrasonic_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                uart_ultrasonic_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(uart_ultrasonic_rxBufferWrite >= uart_ultrasonic_RXBUFFERSIZE)
                {
                    uart_ultrasonic_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(uart_ultrasonic_rxBufferWrite == uart_ultrasonic_rxBufferRead)
                {
                    uart_ultrasonic_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(uart_ultrasonic_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        uart_ultrasonic_RXSTATUS_MASK_REG  &= (uint8)~uart_ultrasonic_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(uart_ultrasonic_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End uart_ultrasonic_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = uart_ultrasonic_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_ultrasonic_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End uart_ultrasonic_RX_ENABLED && (uart_ultrasonic_RXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH) */


#if(uart_ultrasonic_TX_ENABLED && (uart_ultrasonic_TXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: uart_ultrasonic_TXISR
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
    *  uart_ultrasonic_txBuffer - RAM buffer pointer for transmit data from.
    *  uart_ultrasonic_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  uart_ultrasonic_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_ultrasonic_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START uart_ultrasonic_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((uart_ultrasonic_txBufferRead != uart_ultrasonic_txBufferWrite) &&
             ((uart_ultrasonic_TXSTATUS_REG & uart_ultrasonic_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(uart_ultrasonic_txBufferRead >= uart_ultrasonic_TXBUFFERSIZE)
            {
                uart_ultrasonic_txBufferRead = 0u;
            }

            uart_ultrasonic_TXDATA_REG = uart_ultrasonic_txBuffer[uart_ultrasonic_txBufferRead];

            /* Set next pointer. */
            uart_ultrasonic_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_ultrasonic_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End uart_ultrasonic_TX_ENABLED && (uart_ultrasonic_TXBUFFERSIZE > uart_ultrasonic_FIFO_LENGTH) */


/* [] END OF FILE */
