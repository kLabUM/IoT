/*******************************************************************************
* File Name: NEOMOTE_1_UART_MOTE_INT.c
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

#include "NEOMOTE_1_UART_MOTE.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED) && \
     (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_RXISR
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
    *  NEOMOTE_1_UART_MOTE_rxBuffer - RAM buffer pointer for save received data.
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  NEOMOTE_1_UART_MOTE_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  NEOMOTE_1_UART_MOTE_rxBufferOverflow - software overflow flag. Set to one
    *     when NEOMOTE_1_UART_MOTE_rxBufferWrite index overtakes
    *     NEOMOTE_1_UART_MOTE_rxBufferRead index.
    *  NEOMOTE_1_UART_MOTE_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when NEOMOTE_1_UART_MOTE_rxBufferWrite is equal to
    *    NEOMOTE_1_UART_MOTE_rxBufferRead
    *  NEOMOTE_1_UART_MOTE_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  NEOMOTE_1_UART_MOTE_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(NEOMOTE_1_UART_MOTE_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START NEOMOTE_1_UART_MOTE_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = NEOMOTE_1_UART_MOTE_RXSTATUS_REG;

        if((readData & (NEOMOTE_1_UART_MOTE_RX_STS_BREAK | NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR |
                        NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR | NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START NEOMOTE_1_UART_MOTE_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
                if(NEOMOTE_1_UART_MOTE_rxAddressMode == (uint8)NEOMOTE_1_UART_MOTE__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & NEOMOTE_1_UART_MOTE_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & NEOMOTE_1_UART_MOTE_RX_STS_ADDR_MATCH) != 0u)
                        {
                            NEOMOTE_1_UART_MOTE_rxAddressDetected = 1u;
                        }
                        else
                        {
                            NEOMOTE_1_UART_MOTE_rxAddressDetected = 0u;
                        }
                    }

                    readData = NEOMOTE_1_UART_MOTE_RXDATA_REG;
                    if(NEOMOTE_1_UART_MOTE_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        NEOMOTE_1_UART_MOTE_rxBuffer[NEOMOTE_1_UART_MOTE_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    NEOMOTE_1_UART_MOTE_rxBuffer[NEOMOTE_1_UART_MOTE_rxBufferWrite] = NEOMOTE_1_UART_MOTE_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                NEOMOTE_1_UART_MOTE_rxBuffer[NEOMOTE_1_UART_MOTE_rxBufferWrite] = NEOMOTE_1_UART_MOTE_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(NEOMOTE_1_UART_MOTE_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    NEOMOTE_1_UART_MOTE_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                NEOMOTE_1_UART_MOTE_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(NEOMOTE_1_UART_MOTE_rxBufferWrite >= NEOMOTE_1_UART_MOTE_RXBUFFERSIZE)
                {
                    NEOMOTE_1_UART_MOTE_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(NEOMOTE_1_UART_MOTE_rxBufferWrite == NEOMOTE_1_UART_MOTE_rxBufferRead)
                {
                    NEOMOTE_1_UART_MOTE_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(NEOMOTE_1_UART_MOTE_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  &= (uint8)~NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(NEOMOTE_1_UART_MOTE_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End NEOMOTE_1_UART_MOTE_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = NEOMOTE_1_UART_MOTE_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START NEOMOTE_1_UART_MOTE_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) */


#if(NEOMOTE_1_UART_MOTE_TX_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_TXISR
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
    *  NEOMOTE_1_UART_MOTE_txBuffer - RAM buffer pointer for transmit data from.
    *  NEOMOTE_1_UART_MOTE_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(NEOMOTE_1_UART_MOTE_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START NEOMOTE_1_UART_MOTE_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((NEOMOTE_1_UART_MOTE_txBufferRead != NEOMOTE_1_UART_MOTE_txBufferWrite) &&
             ((NEOMOTE_1_UART_MOTE_TXSTATUS_REG & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(NEOMOTE_1_UART_MOTE_txBufferRead >= NEOMOTE_1_UART_MOTE_TXBUFFERSIZE)
            {
                NEOMOTE_1_UART_MOTE_txBufferRead = 0u;
            }

            NEOMOTE_1_UART_MOTE_TXDATA_REG = NEOMOTE_1_UART_MOTE_txBuffer[NEOMOTE_1_UART_MOTE_txBufferRead];

            /* Set next pointer. */
            NEOMOTE_1_UART_MOTE_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START NEOMOTE_1_UART_MOTE_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) */


/* [] END OF FILE */
