/*******************************************************************************
* File Name: NEOMOTE_1_UART_MOTE.c
* Version 2.30
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NEOMOTE_1_UART_MOTE.h"
#include "CyLib.h"
#if(NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED)
    #include "NEOMOTE_1_UART_MOTE_IntClock.h"
#endif /* End NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 NEOMOTE_1_UART_MOTE_initVar = 0u;
#if( NEOMOTE_1_UART_MOTE_TX_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
    volatile uint8 NEOMOTE_1_UART_MOTE_txBuffer[NEOMOTE_1_UART_MOTE_TXBUFFERSIZE];
    volatile uint8 NEOMOTE_1_UART_MOTE_txBufferRead = 0u;
    uint8 NEOMOTE_1_UART_MOTE_txBufferWrite = 0u;
#endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */
#if( ( NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED ) && \
     (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) )
    volatile uint8 NEOMOTE_1_UART_MOTE_rxBuffer[NEOMOTE_1_UART_MOTE_RXBUFFERSIZE];
    volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferRead = 0u;
    volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferWrite = 0u;
    volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferLoopDetect = 0u;
    volatile uint8 NEOMOTE_1_UART_MOTE_rxBufferOverflow = 0u;
    #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
        volatile uint8 NEOMOTE_1_UART_MOTE_rxAddressMode = NEOMOTE_1_UART_MOTE_RXADDRESSMODE;
        volatile uint8 NEOMOTE_1_UART_MOTE_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */
#endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED */


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The NEOMOTE_1_UART_MOTE_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time UART_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the NEOMOTE_1_UART_MOTE_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(NEOMOTE_1_UART_MOTE_initVar == 0u)
    {
        NEOMOTE_1_UART_MOTE_Init();
        NEOMOTE_1_UART_MOTE_initVar = 1u;
    }
    NEOMOTE_1_UART_MOTE_Enable();
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  NEOMOTE_1_UART_MOTE_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Init(void) 
{
    #if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)

        #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            (void)CyIntSetVector(NEOMOTE_1_UART_MOTE_RX_VECT_NUM, &NEOMOTE_1_UART_MOTE_RXISR);
            CyIntSetPriority(NEOMOTE_1_UART_MOTE_RX_VECT_NUM, NEOMOTE_1_UART_MOTE_RX_PRIOR_NUM);
        #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

        #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
            NEOMOTE_1_UART_MOTE_SetRxAddressMode(NEOMOTE_1_UART_MOTE_RXAddressMode);
            NEOMOTE_1_UART_MOTE_SetRxAddress1(NEOMOTE_1_UART_MOTE_RXHWADDRESS1);
            NEOMOTE_1_UART_MOTE_SetRxAddress2(NEOMOTE_1_UART_MOTE_RXHWADDRESS2);
        #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  = NEOMOTE_1_UART_MOTE_INIT_RX_INTERRUPTS_MASK;
    #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED*/

    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            (void)CyIntSetVector(NEOMOTE_1_UART_MOTE_TX_VECT_NUM, &NEOMOTE_1_UART_MOTE_TXISR);
            CyIntSetPriority(NEOMOTE_1_UART_MOTE_TX_VECT_NUM, NEOMOTE_1_UART_MOTE_TX_PRIOR_NUM);
        #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
            NEOMOTE_1_UART_MOTE_TXBITCLKGEN_CTR_REG = NEOMOTE_1_UART_MOTE_BIT_CENTER;
            NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG = (NEOMOTE_1_UART_MOTE_NUMBER_OF_DATA_BITS +
                        NEOMOTE_1_UART_MOTE_NUMBER_OF_START_BIT) * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_COUNT;
        #else
            NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG = ((NEOMOTE_1_UART_MOTE_NUMBER_OF_DATA_BITS +
                        NEOMOTE_1_UART_MOTE_NUMBER_OF_START_BIT) * NEOMOTE_1_UART_MOTE_OVER_SAMPLE_8) - 1u;
        #endif /* End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG = NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY;
        #else
            NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG = NEOMOTE_1_UART_MOTE_INIT_TX_INTERRUPTS_MASK;
        #endif /*End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED*/

    #endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

    #if(NEOMOTE_1_UART_MOTE_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        NEOMOTE_1_UART_MOTE_WriteControlRegister( \
            (NEOMOTE_1_UART_MOTE_ReadControlRegister() & (uint8)~NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(NEOMOTE_1_UART_MOTE_PARITY_TYPE << NEOMOTE_1_UART_MOTE_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End NEOMOTE_1_UART_MOTE_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  NEOMOTE_1_UART_MOTE_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL_REG |= NEOMOTE_1_UART_MOTE_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_REG  |= NEOMOTE_1_UART_MOTE_INT_ENABLE;
        #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            CyIntEnable(NEOMOTE_1_UART_MOTE_RX_VECT_NUM);
            #if (NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
                NEOMOTE_1_UART_MOTE_rxAddressDetected = 0u;
            #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
        #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
    #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED*/

    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
            NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL_REG |= NEOMOTE_1_UART_MOTE_CNTR_ENABLE;
        #endif /* End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG |= NEOMOTE_1_UART_MOTE_INT_ENABLE;
        #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            CyIntEnable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
        #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED*/
     #endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

    #if(NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED)
        /* Enable the clock. */
        NEOMOTE_1_UART_MOTE_IntClock_Start();
    #endif /* End NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void NEOMOTE_1_UART_MOTE_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)
        NEOMOTE_1_UART_MOTE_RXBITCTR_CONTROL_REG &= (uint8)~NEOMOTE_1_UART_MOTE_CNTR_ENABLE;
    #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED */

    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        #if(!NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
            NEOMOTE_1_UART_MOTE_TXBITCTR_CONTROL_REG &= (uint8)~NEOMOTE_1_UART_MOTE_CNTR_ENABLE;
        #endif /* End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */
    #endif /* NEOMOTE_1_UART_MOTE_TX_ENABLED */

    #if(NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED)
        /* Disable the clock. */
        NEOMOTE_1_UART_MOTE_IntClock_Stop();
    #endif /* End NEOMOTE_1_UART_MOTE_INTERNAL_CLOCK_USED */

    /* Disable internal interrupt component */
    #if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)
        NEOMOTE_1_UART_MOTE_RXSTATUS_ACTL_REG  &= (uint8)~NEOMOTE_1_UART_MOTE_INT_ENABLE;
        #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            NEOMOTE_1_UART_MOTE_DisableRxInt();
        #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
    #endif /* End NEOMOTE_1_UART_MOTE_RX_ENABLED */

    #if(NEOMOTE_1_UART_MOTE_TX_ENABLED)
        NEOMOTE_1_UART_MOTE_TXSTATUS_ACTL_REG &= (uint8)~NEOMOTE_1_UART_MOTE_INT_ENABLE;
        #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED && (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            NEOMOTE_1_UART_MOTE_DisableTxInt();
        #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */
    #endif /* End NEOMOTE_1_UART_MOTE_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 NEOMOTE_1_UART_MOTE_ReadControlRegister(void) 
{
    #if( NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(NEOMOTE_1_UART_MOTE_CONTROL_REG);
    #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_UART_MOTE_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  NEOMOTE_1_UART_MOTE_WriteControlRegister(uint8 control) 
{
    #if( NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED )
        if(control != 0u) { }      /* release compiler warning */
    #else
       NEOMOTE_1_UART_MOTE_CONTROL_REG = control;
    #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */
}


#if(NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED)

    #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: NEOMOTE_1_UART_MOTE_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void NEOMOTE_1_UART_MOTE_EnableRxInt(void) 
        {
            CyIntEnable(NEOMOTE_1_UART_MOTE_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: NEOMOTE_1_UART_MOTE_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void NEOMOTE_1_UART_MOTE_DisableRxInt(void) 
        {
            CyIntDisable(NEOMOTE_1_UART_MOTE_RX_VECT_NUM);
        }

    #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetRxInterruptMode(uint8 intSrc) 
    {
        NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxBuffer - RAM buffer pointer for save received data.
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  NEOMOTE_1_UART_MOTE_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  NEOMOTE_1_UART_MOTE_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_ReadRxData(void) 
    {
        uint8 rxData;

        #if(NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableRxInt();
            #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = NEOMOTE_1_UART_MOTE_rxBufferRead;
            loc_rxBufferWrite = NEOMOTE_1_UART_MOTE_rxBufferWrite;

            if( (NEOMOTE_1_UART_MOTE_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = NEOMOTE_1_UART_MOTE_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;

                if(loc_rxBufferRead >= NEOMOTE_1_UART_MOTE_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                NEOMOTE_1_UART_MOTE_rxBufferRead = loc_rxBufferRead;

                if(NEOMOTE_1_UART_MOTE_rxBufferLoopDetect != 0u )
                {
                    NEOMOTE_1_UART_MOTE_rxBufferLoopDetect = 0u;
                    #if( (NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED) && (NEOMOTE_1_UART_MOTE_FLOW_CONTROL != 0u) && \
                         (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( NEOMOTE_1_UART_MOTE_HD_ENABLED )
                            if((NEOMOTE_1_UART_MOTE_CONTROL_REG & NEOMOTE_1_UART_MOTE_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only in RX
                                *  configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  |= NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  |= NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end NEOMOTE_1_UART_MOTE_HD_ENABLED */
                    #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = NEOMOTE_1_UART_MOTE_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableRxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

        #else /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = NEOMOTE_1_UART_MOTE_RXDATA_REG;

        #endif /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn?t free space in
    *   NEOMOTE_1_UART_MOTE_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   NEOMOTE_1_UART_MOTE_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_ReadRxStatus(void) 
    {
        uint8 status;

        status = NEOMOTE_1_UART_MOTE_RXSTATUS_REG & NEOMOTE_1_UART_MOTE_RX_HW_MASK;

        #if(NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)
            if( NEOMOTE_1_UART_MOTE_rxBufferOverflow != 0u )
            {
                status |= NEOMOTE_1_UART_MOTE_RX_STS_SOFT_BUFF_OVER;
                NEOMOTE_1_UART_MOTE_rxBufferOverflow = 0u;
            }
        #endif /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error
    *  condition exists, zero is returned; otherwise, character is read and
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxBuffer - RAM buffer pointer for save received data.
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  NEOMOTE_1_UART_MOTE_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  NEOMOTE_1_UART_MOTE_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableRxInt();
            #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = NEOMOTE_1_UART_MOTE_rxBufferRead;
            loc_rxBufferWrite = NEOMOTE_1_UART_MOTE_rxBufferWrite;

            if( (NEOMOTE_1_UART_MOTE_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = NEOMOTE_1_UART_MOTE_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;
                if(loc_rxBufferRead >= NEOMOTE_1_UART_MOTE_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                NEOMOTE_1_UART_MOTE_rxBufferRead = loc_rxBufferRead;

                if(NEOMOTE_1_UART_MOTE_rxBufferLoopDetect > 0u )
                {
                    NEOMOTE_1_UART_MOTE_rxBufferLoopDetect = 0u;
                    #if( (NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED) && (NEOMOTE_1_UART_MOTE_FLOW_CONTROL != 0u) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( NEOMOTE_1_UART_MOTE_HD_ENABLED )
                            if((NEOMOTE_1_UART_MOTE_CONTROL_REG & NEOMOTE_1_UART_MOTE_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only if
                                *  RX configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  |= NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            NEOMOTE_1_UART_MOTE_RXSTATUS_MASK_REG  |= NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end NEOMOTE_1_UART_MOTE_HD_ENABLED */
                    #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus = NEOMOTE_1_UART_MOTE_RXSTATUS_REG;
                if((rxStatus & NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY) != 0u)
                {   /* Read received data from FIFO*/
                    rxData = NEOMOTE_1_UART_MOTE_RXDATA_REG;
                    /*Check status on error*/
                    if((rxStatus & (NEOMOTE_1_UART_MOTE_RX_STS_BREAK | NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR |
                                   NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR | NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN)) != 0u)
                    {
                        rxData = 0u;
                    }
                }
            }

            /* Enable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableRxInt();
            #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

        #else /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

            rxStatus =NEOMOTE_1_UART_MOTE_RXSTATUS_REG;
            if((rxStatus & NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO*/
                rxData = NEOMOTE_1_UART_MOTE_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (NEOMOTE_1_UART_MOTE_RX_STS_BREAK | NEOMOTE_1_UART_MOTE_RX_STS_PAR_ERROR |
                               NEOMOTE_1_UART_MOTE_RX_STS_STOP_ERROR | NEOMOTE_1_UART_MOTE_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        #endif /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 NEOMOTE_1_UART_MOTE_GetByte(void) 
    {
        return ( ((uint16)NEOMOTE_1_UART_MOTE_ReadRxStatus() << 8u) | NEOMOTE_1_UART_MOTE_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left
    *  in the RX buffer
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - used to calculate left bytes.
    *  NEOMOTE_1_UART_MOTE_rxBufferRead - used to calculate left bytes.
    *  NEOMOTE_1_UART_MOTE_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableRxInt();
            #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

            if(NEOMOTE_1_UART_MOTE_rxBufferRead == NEOMOTE_1_UART_MOTE_rxBufferWrite)
            {
                if(NEOMOTE_1_UART_MOTE_rxBufferLoopDetect > 0u)
                {
                    size = NEOMOTE_1_UART_MOTE_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(NEOMOTE_1_UART_MOTE_rxBufferRead < NEOMOTE_1_UART_MOTE_rxBufferWrite)
            {
                size = (NEOMOTE_1_UART_MOTE_rxBufferWrite - NEOMOTE_1_UART_MOTE_rxBufferRead);
            }
            else
            {
                size = (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE - NEOMOTE_1_UART_MOTE_rxBufferRead) + NEOMOTE_1_UART_MOTE_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableRxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

        #else /* NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = ((NEOMOTE_1_UART_MOTE_RXSTATUS_REG & NEOMOTE_1_UART_MOTE_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

        #endif /* End NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxBufferWrite - cleared to zero.
    *  NEOMOTE_1_UART_MOTE_rxBufferRead - cleared to zero.
    *  NEOMOTE_1_UART_MOTE_rxBufferLoopDetect - cleared to zero.
    *  NEOMOTE_1_UART_MOTE_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        NEOMOTE_1_UART_MOTE_RXDATA_AUX_CTL_REG |=  NEOMOTE_1_UART_MOTE_RX_FIFO_CLR;
        NEOMOTE_1_UART_MOTE_RXDATA_AUX_CTL_REG &= (uint8)~NEOMOTE_1_UART_MOTE_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableRxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

            NEOMOTE_1_UART_MOTE_rxBufferRead = 0u;
            NEOMOTE_1_UART_MOTE_rxBufferWrite = 0u;
            NEOMOTE_1_UART_MOTE_rxBufferLoopDetect = 0u;
            NEOMOTE_1_UART_MOTE_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableRxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
        #endif /* End NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  NEOMOTE_1_UART_MOTE__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  NEOMOTE_1_UART_MOTE__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  NEOMOTE_1_UART_MOTE__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  NEOMOTE_1_UART_MOTE__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  NEOMOTE_1_UART_MOTE__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  NEOMOTE_1_UART_MOTE_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED)
            #if(NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED)
                if(addressMode != 0u) { }     /* release compiler warning */
            #else /* NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = NEOMOTE_1_UART_MOTE_CONTROL_REG & (uint8)~NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << NEOMOTE_1_UART_MOTE_CTRL_RXADDR_MODE0_SHIFT);
                NEOMOTE_1_UART_MOTE_CONTROL_REG = tmpCtrl;
                #if(NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED && \
                   (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH) )
                    NEOMOTE_1_UART_MOTE_rxAddressMode = addressMode;
                    NEOMOTE_1_UART_MOTE_rxAddressDetected = 0u;
                #endif /* End NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH*/
            #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED */
        #else /* NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
            if(addressMode != 0u) { }     /* release compiler warning */
        #endif /* End NEOMOTE_1_UART_MOTE_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetRxAddress1(uint8 address) 

    {
        NEOMOTE_1_UART_MOTE_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetRxAddress2(uint8 address) 
    {
        NEOMOTE_1_UART_MOTE_RXADDRESS2_REG = address;
    }

#endif  /* NEOMOTE_1_UART_MOTE_RX_ENABLED || NEOMOTE_1_UART_MOTE_HD_ENABLED*/


#if( (NEOMOTE_1_UART_MOTE_TX_ENABLED) || (NEOMOTE_1_UART_MOTE_HD_ENABLED) )

    #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: NEOMOTE_1_UART_MOTE_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void NEOMOTE_1_UART_MOTE_EnableTxInt(void) 
        {
            CyIntEnable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: NEOMOTE_1_UART_MOTE_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void NEOMOTE_1_UART_MOTE_DisableTxInt(void) 
        {
            CyIntDisable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
        }

    #endif /* NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetTxInterruptMode(uint8 intSrc) 
    {
        NEOMOTE_1_UART_MOTE_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the
    *  bus is available. WriteTxData sends a byte without checking for buffer room
    *  or status. It is up to the user to separately check status.
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_txBuffer - RAM buffer pointer for save data for transmission
    *  NEOMOTE_1_UART_MOTE_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  NEOMOTE_1_UART_MOTE_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(NEOMOTE_1_UART_MOTE_initVar != 0u)
        {
            #if(NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                    NEOMOTE_1_UART_MOTE_DisableTxInt();
                #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

                if( (NEOMOTE_1_UART_MOTE_txBufferRead == NEOMOTE_1_UART_MOTE_txBufferWrite) &&
                    ((NEOMOTE_1_UART_MOTE_TXSTATUS_REG & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    NEOMOTE_1_UART_MOTE_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(NEOMOTE_1_UART_MOTE_txBufferWrite >= NEOMOTE_1_UART_MOTE_TXBUFFERSIZE)
                    {
                        NEOMOTE_1_UART_MOTE_txBufferWrite = 0u;
                    }

                    NEOMOTE_1_UART_MOTE_txBuffer[NEOMOTE_1_UART_MOTE_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    NEOMOTE_1_UART_MOTE_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                    NEOMOTE_1_UART_MOTE_EnableTxInt();
                #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

            #else /* NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                NEOMOTE_1_UART_MOTE_TXDATA_REG = txDataByte;

            #endif /* End NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to
    *  the user to handle all bits in this return value accordingly, even if the bit
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_ReadTxStatus(void) 
    {
        return(NEOMOTE_1_UART_MOTE_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_txBuffer - RAM buffer pointer for save data for transmission
    *  NEOMOTE_1_UART_MOTE_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  NEOMOTE_1_UART_MOTE_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_PutChar(uint8 txDataByte) 
    {
            #if(NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)
                /* The temporary output pointer is used since it takes two instructions
                *  to increment with a wrap, and we can't risk doing that with the real
                *  pointer and getting an interrupt in between instructions.
                */
                uint8 loc_txBufferWrite;
                uint8 loc_txBufferRead;

                do{
                    /* Block if software buffer is full, so we don't overwrite. */
                    #if ((NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Disable TX interrupt to protect variables that could change on interrupt */
                        CyIntDisable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    loc_txBufferWrite = NEOMOTE_1_UART_MOTE_txBufferWrite;
                    loc_txBufferRead = NEOMOTE_1_UART_MOTE_txBufferRead;
                    #if ((NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Enable interrupt to continue transmission */
                        CyIntEnable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }while( (loc_txBufferWrite < loc_txBufferRead) ? (loc_txBufferWrite == (loc_txBufferRead - 1u)) :
                                        ((loc_txBufferWrite - loc_txBufferRead) ==
                                        (uint8)(NEOMOTE_1_UART_MOTE_TXBUFFERSIZE - 1u)) );

                if( (loc_txBufferRead == loc_txBufferWrite) &&
                    ((NEOMOTE_1_UART_MOTE_TXSTATUS_REG & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    NEOMOTE_1_UART_MOTE_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(loc_txBufferWrite >= NEOMOTE_1_UART_MOTE_TXBUFFERSIZE)
                    {
                        loc_txBufferWrite = 0u;
                    }
                    /* Add to the software buffer. */
                    NEOMOTE_1_UART_MOTE_txBuffer[loc_txBufferWrite] = txDataByte;
                    loc_txBufferWrite++;

                    /* Finally, update the real output pointer */
                    #if ((NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntDisable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    NEOMOTE_1_UART_MOTE_txBufferWrite = loc_txBufferWrite;
                    #if ((NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntEnable(NEOMOTE_1_UART_MOTE_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }

            #else /* NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

                while((NEOMOTE_1_UART_MOTE_TXSTATUS_REG & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL) != 0u)
                {
                    ; /* Wait for room in the FIFO. */
                }

                /* Add directly to the FIFO. */
                NEOMOTE_1_UART_MOTE_TXDATA_REG = txDataByte;

            #endif /* End NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_PutString(const char8 string[]) 
    {
        uint16 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(NEOMOTE_1_UART_MOTE_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(string[buf_index] != (char8)0)
            {
                NEOMOTE_1_UART_MOTE_PutChar((uint8)string[buf_index]);
                buf_index++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(NEOMOTE_1_UART_MOTE_initVar != 0u)
        {
            do
            {
                NEOMOTE_1_UART_MOTE_PutChar(string[buf_index]);
                buf_index++;
            }while(buf_index < byteCount);
        }
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(NEOMOTE_1_UART_MOTE_initVar != 0u)
        {
            NEOMOTE_1_UART_MOTE_PutChar(txDataByte);
            NEOMOTE_1_UART_MOTE_PutChar(0x0Du);
            NEOMOTE_1_UART_MOTE_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_txBufferWrite - used to calculate left space.
    *  NEOMOTE_1_UART_MOTE_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 NEOMOTE_1_UART_MOTE_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableTxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

            if(NEOMOTE_1_UART_MOTE_txBufferRead == NEOMOTE_1_UART_MOTE_txBufferWrite)
            {
                size = 0u;
            }
            else if(NEOMOTE_1_UART_MOTE_txBufferRead < NEOMOTE_1_UART_MOTE_txBufferWrite)
            {
                size = (NEOMOTE_1_UART_MOTE_txBufferWrite - NEOMOTE_1_UART_MOTE_txBufferRead);
            }
            else
            {
                size = (NEOMOTE_1_UART_MOTE_TXBUFFERSIZE - NEOMOTE_1_UART_MOTE_txBufferRead) + NEOMOTE_1_UART_MOTE_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableTxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

        #else /* NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

            size = NEOMOTE_1_UART_MOTE_TXSTATUS_REG;

            /* Is the fifo is full. */
            if((size & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_FULL) != 0u)
            {
                size = NEOMOTE_1_UART_MOTE_FIFO_LENGTH;
            }
            else if((size & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY) != 0u)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_txBufferWrite - cleared to zero.
    *  NEOMOTE_1_UART_MOTE_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        /* clear the HW FIFO */
        NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_REG |=  NEOMOTE_1_UART_MOTE_TX_FIFO_CLR;
        NEOMOTE_1_UART_MOTE_TXDATA_AUX_CTL_REG &= (uint8)~NEOMOTE_1_UART_MOTE_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_DisableTxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

            NEOMOTE_1_UART_MOTE_txBufferRead = 0u;
            NEOMOTE_1_UART_MOTE_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED)
                NEOMOTE_1_UART_MOTE_EnableTxInt();
            #endif /* End NEOMOTE_1_UART_MOTE_TX_INTERRUPT_ENABLED */

        #endif /* End NEOMOTE_1_UART_MOTE_TXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  NEOMOTE_1_UART_MOTE_initVar - checked to identify that the component has been
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(NEOMOTE_1_UART_MOTE_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(NEOMOTE_1_UART_MOTE_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == NEOMOTE_1_UART_MOTE_SEND_BREAK) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() |
                                                          NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    NEOMOTE_1_UART_MOTE_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = NEOMOTE_1_UART_MOTE_TXSTATUS_REG;
                    }while((tmpStat & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = NEOMOTE_1_UART_MOTE_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT) )
                {
                    NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() &
                                                  (uint8)~NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK);
                }

            #else /* NEOMOTE_1_UART_MOTE_HD_ENABLED Full Duplex mode */

                static uint8 tx_period;

                if( (retMode == NEOMOTE_1_UART_MOTE_SEND_BREAK) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode*/
                    #if( (NEOMOTE_1_UART_MOTE_PARITY_TYPE != NEOMOTE_1_UART_MOTE__B_UART__NONE_REVB) || \
                                        (NEOMOTE_1_UART_MOTE_PARITY_TYPE_SW != 0u) )
                        NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() |
                                                              NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK);
                    #endif /* End NEOMOTE_1_UART_MOTE_PARITY_TYPE != NEOMOTE_1_UART_MOTE__B_UART__NONE_REVB  */

                    #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
                        tx_period = NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG;
                        NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG = NEOMOTE_1_UART_MOTE_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG;
                        NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_TXBITCTR_BREAKBITS8X;
                    #endif /* End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */

                    /* Send zeros*/
                    NEOMOTE_1_UART_MOTE_TXDATA_REG = 0u;

                    do /* wait until transmit starts */
                    {
                        tmpStat = NEOMOTE_1_UART_MOTE_TXSTATUS_REG;
                    }while((tmpStat & NEOMOTE_1_UART_MOTE_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = NEOMOTE_1_UART_MOTE_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & NEOMOTE_1_UART_MOTE_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == NEOMOTE_1_UART_MOTE_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_REINIT) ||
                    (retMode == NEOMOTE_1_UART_MOTE_SEND_WAIT_REINIT) )
                {

                    #if(NEOMOTE_1_UART_MOTE_TXCLKGEN_DP)
                        NEOMOTE_1_UART_MOTE_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        NEOMOTE_1_UART_MOTE_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End NEOMOTE_1_UART_MOTE_TXCLKGEN_DP */

                    #if( (NEOMOTE_1_UART_MOTE_PARITY_TYPE != NEOMOTE_1_UART_MOTE__B_UART__NONE_REVB) || \
                         (NEOMOTE_1_UART_MOTE_PARITY_TYPE_SW != 0u) )
                        NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() &
                                                      (uint8)~NEOMOTE_1_UART_MOTE_CTRL_HD_SEND_BREAK);
                    #endif /* End NEOMOTE_1_UART_MOTE_PARITY_TYPE != NONE */
                }
            #endif    /* End NEOMOTE_1_UART_MOTE_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0u)
        {
            #if( NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u )
                NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() |
                                                      NEOMOTE_1_UART_MOTE_CTRL_MARK);
            #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
            #if( NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u )
                NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() &
                                                    (uint8)~NEOMOTE_1_UART_MOTE_CTRL_MARK);
            #endif /* End NEOMOTE_1_UART_MOTE_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndNEOMOTE_1_UART_MOTE_TX_ENABLED */

#if(NEOMOTE_1_UART_MOTE_HD_ENABLED)


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART.
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_LoadTxConfig(void) 
    {
        #if((NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED) && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            NEOMOTE_1_UART_MOTE_SetRxInterruptMode(0u);
        #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */

        NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() | NEOMOTE_1_UART_MOTE_CTRL_HD_SEND);
        NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(NEOMOTE_1_UART_MOTE_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: NEOMOTE_1_UART_MOTE_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer
    *  has been used.
    *
    *******************************************************************************/
    void NEOMOTE_1_UART_MOTE_LoadRxConfig(void) 
    {
        NEOMOTE_1_UART_MOTE_WriteControlRegister(NEOMOTE_1_UART_MOTE_ReadControlRegister() &
                                                (uint8)~NEOMOTE_1_UART_MOTE_CTRL_HD_SEND);
        NEOMOTE_1_UART_MOTE_RXBITCTR_PERIOD_REG = NEOMOTE_1_UART_MOTE_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(NEOMOTE_1_UART_MOTE_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED) && (NEOMOTE_1_UART_MOTE_RXBUFFERSIZE > NEOMOTE_1_UART_MOTE_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            NEOMOTE_1_UART_MOTE_SetRxInterruptMode(NEOMOTE_1_UART_MOTE_INIT_RX_INTERRUPTS_MASK);
        #endif /* NEOMOTE_1_UART_MOTE_RX_INTERRUPT_ENABLED */
    }

#endif  /* NEOMOTE_1_UART_MOTE_HD_ENABLED */


/* [] END OF FILE */
