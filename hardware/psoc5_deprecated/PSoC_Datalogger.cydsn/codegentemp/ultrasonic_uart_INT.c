/*******************************************************************************
* File Name: ultrasonic_uart_INT.c
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

#include "ultrasonic_uart.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (ultrasonic_uart_RX_ENABLED || ultrasonic_uart_HD_ENABLED) && \
     (ultrasonic_uart_RXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: ultrasonic_uart_RXISR
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
    *  ultrasonic_uart_rxBuffer - RAM buffer pointer for save received data.
    *  ultrasonic_uart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  ultrasonic_uart_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  ultrasonic_uart_rxBufferOverflow - software overflow flag. Set to one
    *     when ultrasonic_uart_rxBufferWrite index overtakes
    *     ultrasonic_uart_rxBufferRead index.
    *  ultrasonic_uart_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when ultrasonic_uart_rxBufferWrite is equal to
    *    ultrasonic_uart_rxBufferRead
    *  ultrasonic_uart_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  ultrasonic_uart_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(ultrasonic_uart_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START ultrasonic_uart_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = ultrasonic_uart_RXSTATUS_REG;

        if((readData & (ultrasonic_uart_RX_STS_BREAK | ultrasonic_uart_RX_STS_PAR_ERROR |
                        ultrasonic_uart_RX_STS_STOP_ERROR | ultrasonic_uart_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START ultrasonic_uart_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & ultrasonic_uart_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (ultrasonic_uart_RXHW_ADDRESS_ENABLED)
                if(ultrasonic_uart_rxAddressMode == (uint8)ultrasonic_uart__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & ultrasonic_uart_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & ultrasonic_uart_RX_STS_ADDR_MATCH) != 0u)
                        {
                            ultrasonic_uart_rxAddressDetected = 1u;
                        }
                        else
                        {
                            ultrasonic_uart_rxAddressDetected = 0u;
                        }
                    }

                    readData = ultrasonic_uart_RXDATA_REG;
                    if(ultrasonic_uart_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        ultrasonic_uart_rxBuffer[ultrasonic_uart_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    ultrasonic_uart_rxBuffer[ultrasonic_uart_rxBufferWrite] = ultrasonic_uart_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                ultrasonic_uart_rxBuffer[ultrasonic_uart_rxBufferWrite] = ultrasonic_uart_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(ultrasonic_uart_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    ultrasonic_uart_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                ultrasonic_uart_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(ultrasonic_uart_rxBufferWrite >= ultrasonic_uart_RXBUFFERSIZE)
                {
                    ultrasonic_uart_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(ultrasonic_uart_rxBufferWrite == ultrasonic_uart_rxBufferRead)
                {
                    ultrasonic_uart_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(ultrasonic_uart_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        ultrasonic_uart_RXSTATUS_MASK_REG  &= (uint8)~ultrasonic_uart_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(ultrasonic_uart_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End ultrasonic_uart_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = ultrasonic_uart_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ultrasonic_uart_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End ultrasonic_uart_RX_ENABLED && (ultrasonic_uart_RXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH) */


#if(ultrasonic_uart_TX_ENABLED && (ultrasonic_uart_TXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: ultrasonic_uart_TXISR
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
    *  ultrasonic_uart_txBuffer - RAM buffer pointer for transmit data from.
    *  ultrasonic_uart_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  ultrasonic_uart_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(ultrasonic_uart_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START ultrasonic_uart_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((ultrasonic_uart_txBufferRead != ultrasonic_uart_txBufferWrite) &&
             ((ultrasonic_uart_TXSTATUS_REG & ultrasonic_uart_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(ultrasonic_uart_txBufferRead >= ultrasonic_uart_TXBUFFERSIZE)
            {
                ultrasonic_uart_txBufferRead = 0u;
            }

            ultrasonic_uart_TXDATA_REG = ultrasonic_uart_txBuffer[ultrasonic_uart_txBufferRead];

            /* Set next pointer. */
            ultrasonic_uart_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ultrasonic_uart_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End ultrasonic_uart_TX_ENABLED && (ultrasonic_uart_TXBUFFERSIZE > ultrasonic_uart_FIFO_LENGTH) */


/* [] END OF FILE */
