/*******************************************************************************
* File Name: Telit_UART_INT.c
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

#include "Telit_UART.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (Telit_UART_RX_ENABLED || Telit_UART_HD_ENABLED) && \
     (Telit_UART_RXBUFFERSIZE > Telit_UART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Telit_UART_RXISR
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
    *  Telit_UART_rxBuffer - RAM buffer pointer for save received data.
    *  Telit_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Telit_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Telit_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when Telit_UART_rxBufferWrite index overtakes
    *     Telit_UART_rxBufferRead index.
    *  Telit_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Telit_UART_rxBufferWrite is equal to
    *    Telit_UART_rxBufferRead
    *  Telit_UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Telit_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Telit_UART_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Telit_UART_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = Telit_UART_RXSTATUS_REG;

        if((readData & (Telit_UART_RX_STS_BREAK | Telit_UART_RX_STS_PAR_ERROR |
                        Telit_UART_RX_STS_STOP_ERROR | Telit_UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START Telit_UART_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Telit_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (Telit_UART_RXHW_ADDRESS_ENABLED)
                if(Telit_UART_rxAddressMode == (uint8)Telit_UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & Telit_UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & Telit_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Telit_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Telit_UART_rxAddressDetected = 0u;
                        }
                    }

                    readData = Telit_UART_RXDATA_REG;
                    if(Telit_UART_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        Telit_UART_rxBuffer[Telit_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    Telit_UART_rxBuffer[Telit_UART_rxBufferWrite] = Telit_UART_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                Telit_UART_rxBuffer[Telit_UART_rxBufferWrite] = Telit_UART_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(Telit_UART_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Telit_UART_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Telit_UART_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Telit_UART_rxBufferWrite >= Telit_UART_RXBUFFERSIZE)
                {
                    Telit_UART_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(Telit_UART_rxBufferWrite == Telit_UART_rxBufferRead)
                {
                    Telit_UART_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(Telit_UART_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        Telit_UART_RXSTATUS_MASK_REG  &= (uint8)~Telit_UART_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Telit_UART_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End Telit_UART_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = Telit_UART_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Telit_UART_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Telit_UART_RX_ENABLED && (Telit_UART_RXBUFFERSIZE > Telit_UART_FIFO_LENGTH) */


#if(Telit_UART_TX_ENABLED && (Telit_UART_TXBUFFERSIZE > Telit_UART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Telit_UART_TXISR
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
    *  Telit_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  Telit_UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  Telit_UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Telit_UART_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Telit_UART_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((Telit_UART_txBufferRead != Telit_UART_txBufferWrite) &&
             ((Telit_UART_TXSTATUS_REG & Telit_UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(Telit_UART_txBufferRead >= Telit_UART_TXBUFFERSIZE)
            {
                Telit_UART_txBufferRead = 0u;
            }

            Telit_UART_TXDATA_REG = Telit_UART_txBuffer[Telit_UART_txBufferRead];

            /* Set next pointer. */
            Telit_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Telit_UART_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Telit_UART_TX_ENABLED && (Telit_UART_TXBUFFERSIZE > Telit_UART_FIFO_LENGTH) */


/* [] END OF FILE */
