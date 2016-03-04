/*******************************************************************************
* File Name: NEOMOTE_1_I2C_0_INT.c
* Version 3.30
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for I2C component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NEOMOTE_1_I2C_0_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START NEOMOTE_1_I2C_0_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_ISR
********************************************************************************
*
* Summary:
*  Handler for I2C interrupt. The Slave and Master operations are handled here.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(NEOMOTE_1_I2C_0_ISR)
{
    #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
       uint8  tmp8;
    #endif  /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;

    #if(NEOMOTE_1_I2C_0_TIMEOUT_FF_ENABLED)
        if(0u != NEOMOTE_1_I2C_0_TimeoutGetStatus())
        {
            NEOMOTE_1_I2C_0_TimeoutReset();
            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_EXIT_IDLE;
            /* NEOMOTE_1_I2C_0_CSR_REG should be cleared after reset */
        }
    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_FF_ENABLED) */


    tmpCsr = NEOMOTE_1_I2C_0_CSR_REG;      /* Make copy as interrupts clear */

    #if(NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE_ENABLED)
        if(NEOMOTE_1_I2C_0_CHECK_START_GEN(NEOMOTE_1_I2C_0_MCSR_REG))
        {
            NEOMOTE_1_I2C_0_CLEAR_START_GEN;

            /* Set READ complete, but was aborted */
            NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_ERR_XFER |
                                            NEOMOTE_1_I2C_0_GET_MSTAT_CMPLT);

            /* The slave was addressed */
            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SLAVE;
        }
    #endif /* (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE_ENABLED) */


    #if(NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_ENABLED)
        if(NEOMOTE_1_I2C_0_CHECK_LOST_ARB(tmpCsr))
        {
            /* Set errors */
            NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_ERR_XFER     |
                                            NEOMOTE_1_I2C_0_MSTAT_ERR_ARB_LOST |
                                            NEOMOTE_1_I2C_0_GET_MSTAT_CMPLT);

            NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

            #if(NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE_ENABLED)
                if(NEOMOTE_1_I2C_0_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* The slave was addressed */
                    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SLAVE;
                }
                else
                {
                    NEOMOTE_1_I2C_0_BUS_RELEASE;

                    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_EXIT_IDLE;
                }
            #else
                NEOMOTE_1_I2C_0_BUS_RELEASE;

                NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_EXIT_IDLE;

            #endif /* (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_SLAVE_ENABLED) */
        }
    #endif /* (NEOMOTE_1_I2C_0_MODE_MULTI_MASTER_ENABLED) */

    /* Check for Master operation mode */
    if(NEOMOTE_1_I2C_0_CHECK_SM_MASTER)
    {
        #if(NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED)
            if(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                switch (NEOMOTE_1_I2C_0_state)
                {
                case NEOMOTE_1_I2C_0_SM_MSTR_WR_ADDR:  /* After address is sent, WRITE data */
                case NEOMOTE_1_I2C_0_SM_MSTR_RD_ADDR:  /* After address is sent, READ  data */

                    tmpCsr &= ((uint8) ~NEOMOTE_1_I2C_0_CSR_STOP_STATUS); /* Clear STOP bit history on address phase */
                    
                    if(NEOMOTE_1_I2C_0_CHECK_ADDR_ACK(tmpCsr))
                    {
                        /* Setup for transmit or receive of data */
                        if(NEOMOTE_1_I2C_0_state == NEOMOTE_1_I2C_0_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                        {
                            /* Check if at least one byte to transfer */
                            if(NEOMOTE_1_I2C_0_mstrWrBufSize > 0u)
                            {
                                /* Load the 1st data byte */
                                NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_mstrWrBufPtr[0u];
                                NEOMOTE_1_I2C_0_TRANSMIT_DATA;
                                NEOMOTE_1_I2C_0_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                                /* Set transmit state until done */
                                NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_WR_DATA;
                            }
                            /* End of buffer: complete writing */
                            else if(NEOMOTE_1_I2C_0_CHECK_NO_STOP(NEOMOTE_1_I2C_0_mstrControl))
                            {
                                #if(CY_PSOC5A)
                                    /* Do not handles 0 bytes transfer - HALT is NOT allowed */
                                    NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;
                                    NEOMOTE_1_I2C_0_GENERATE_STOP;
                                
                                #else
                                    /* Set WRITE complete and Master HALTED */
                                    NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_XFER_HALT |
                                                                    NEOMOTE_1_I2C_0_MSTAT_WR_CMPLT);

                                    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_HALT; /* Expect RESTART */
                                    NEOMOTE_1_I2C_0_DisableInt();
                                
                                #endif /* (CY_PSOC5A) */
                            }
                            else
                            {
                                NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                                NEOMOTE_1_I2C_0_GENERATE_STOP;
                            }
                        }
                        else  /* Master Receive data */
                        {
                            NEOMOTE_1_I2C_0_READY_TO_READ; /* Release bus to read data */

                            NEOMOTE_1_I2C_0_state  = NEOMOTE_1_I2C_0_SM_MSTR_RD_DATA;
                        }
                    }
                    /* Address is NACKed */
                    else if(NEOMOTE_1_I2C_0_CHECK_ADDR_NAK(tmpCsr))
                    {
                        /* Set Address NAK error */
                        NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_ERR_XFER |
                                                        NEOMOTE_1_I2C_0_MSTAT_ERR_ADDR_NAK);
                                                        
                        if(NEOMOTE_1_I2C_0_CHECK_NO_STOP(NEOMOTE_1_I2C_0_mstrControl))
                        {
                            NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_XFER_HALT | 
                                                            NEOMOTE_1_I2C_0_GET_MSTAT_CMPLT);

                            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_HALT; /* Expect RESTART */
                            NEOMOTE_1_I2C_0_DisableInt();
                        }
                        else  /* Do normal Stop */
                        {
                            NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                            NEOMOTE_1_I2C_0_GENERATE_STOP;
                        }
                    }
                    else
                    {
                        /* Address phase is not set for some reason: error */
                        #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
                            /* Exit from interrupt to take a chance for timeout timer handle this case */
                            NEOMOTE_1_I2C_0_DisableInt();
                            NEOMOTE_1_I2C_0_ClearPendingInt();
                        #else
                            /* Block execution flow: unexpected condition */
                            CYASSERT(0u != 0u);
                        #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
                    }
                    break;

                case NEOMOTE_1_I2C_0_SM_MSTR_WR_DATA:

                    if(NEOMOTE_1_I2C_0_CHECK_DATA_ACK(tmpCsr))
                    {
                        /* Check if end of buffer */
                        if(NEOMOTE_1_I2C_0_mstrWrBufIndex  < NEOMOTE_1_I2C_0_mstrWrBufSize)
                        {
                            NEOMOTE_1_I2C_0_DATA_REG =
                                                     NEOMOTE_1_I2C_0_mstrWrBufPtr[NEOMOTE_1_I2C_0_mstrWrBufIndex];
                            NEOMOTE_1_I2C_0_TRANSMIT_DATA;
                            NEOMOTE_1_I2C_0_mstrWrBufIndex++;
                        }
                        /* End of buffer: complete writing */
                        else if(NEOMOTE_1_I2C_0_CHECK_NO_STOP(NEOMOTE_1_I2C_0_mstrControl))
                        {
                            /* Set WRITE complete and Master HALTED */
                            NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_XFER_HALT |
                                                            NEOMOTE_1_I2C_0_MSTAT_WR_CMPLT);

                            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_HALT;    /* Expect RESTART */
                            NEOMOTE_1_I2C_0_DisableInt();
                        }
                        else  /* Do normal STOP */
                        {
                            NEOMOTE_1_I2C_0_Workaround();          /* Workaround: empty function */
                            NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                            NEOMOTE_1_I2C_0_GENERATE_STOP;
                        }
                    }
                    /* Last byte NAKed: end writing */
                    else if(NEOMOTE_1_I2C_0_CHECK_NO_STOP(NEOMOTE_1_I2C_0_mstrControl))
                    {
                        /* Set WRITE complete, SHORT transfer and Master HALTED */
                        NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_ERR_XFER       |
                                                        NEOMOTE_1_I2C_0_MSTAT_ERR_SHORT_XFER |
                                                        NEOMOTE_1_I2C_0_MSTAT_XFER_HALT      |
                                                        NEOMOTE_1_I2C_0_MSTAT_WR_CMPLT);

                        NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_HALT;    /* Expect RESTART */
                        NEOMOTE_1_I2C_0_DisableInt();
                    }
                    else  /* Do normal STOP */
                    {
                        NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                        NEOMOTE_1_I2C_0_GENERATE_STOP;

                        /* Set SHORT and ERR transfer */
                        NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_ERR_SHORT_XFER |
                                                        NEOMOTE_1_I2C_0_MSTAT_ERR_XFER);
                    }
                    
                    break;

                case NEOMOTE_1_I2C_0_SM_MSTR_RD_DATA:

                    NEOMOTE_1_I2C_0_mstrRdBufPtr[NEOMOTE_1_I2C_0_mstrRdBufIndex] = NEOMOTE_1_I2C_0_DATA_REG;
                    NEOMOTE_1_I2C_0_mstrRdBufIndex++;

                    /* Check if end of buffer */
                    if(NEOMOTE_1_I2C_0_mstrRdBufIndex < NEOMOTE_1_I2C_0_mstrRdBufSize)
                    {
                        NEOMOTE_1_I2C_0_ACK_AND_RECEIVE;       /* ACK and receive byte */
                    }
                    /* End of buffer: complete reading */
                    else if(NEOMOTE_1_I2C_0_CHECK_NO_STOP(NEOMOTE_1_I2C_0_mstrControl))
                    {                        
                        /* Set READ complete and Master HALTED */
                        NEOMOTE_1_I2C_0_mstrStatus |= (NEOMOTE_1_I2C_0_MSTAT_XFER_HALT |
                                                        NEOMOTE_1_I2C_0_MSTAT_RD_CMPLT);
                        
                        NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_MSTR_HALT;    /* Expect RESTART */
                        NEOMOTE_1_I2C_0_DisableInt();
                    }
                    else
                    {
                        NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;
                        NEOMOTE_1_I2C_0_NAK_AND_RECEIVE;       /* NACK and TRY to generate STOP */
                    }
                    break;

                default: /* This is an invalid state and should not occur */

                    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        NEOMOTE_1_I2C_0_DisableInt();
                        NEOMOTE_1_I2C_0_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */

                    break;
                }
            }

            /* Catches the Stop: end of transaction */
            if(NEOMOTE_1_I2C_0_CHECK_STOP_STS(tmpCsr))
            {
                NEOMOTE_1_I2C_0_mstrStatus |= NEOMOTE_1_I2C_0_GET_MSTAT_CMPLT;

                NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP;
                NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;
            }
        #endif /* (NEOMOTE_1_I2C_0_MODE_MASTER_ENABLED) */
    }
    else if(NEOMOTE_1_I2C_0_CHECK_SM_SLAVE)
    {
        #if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)
            
            if((NEOMOTE_1_I2C_0_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
               (NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(tmpCsr) && NEOMOTE_1_I2C_0_CHECK_ADDRESS_STS(tmpCsr)))
            {
                /* Catch end of master write transcation: use interrupt on Stop */
                /* The STOP bit history on address phase does not have correct state */
                if(NEOMOTE_1_I2C_0_SM_SL_WR_DATA == NEOMOTE_1_I2C_0_state)
                {
                    NEOMOTE_1_I2C_0_DISABLE_INT_ON_STOP;

                    NEOMOTE_1_I2C_0_slStatus &= ((uint8) ~NEOMOTE_1_I2C_0_SSTAT_WR_BUSY);
                    NEOMOTE_1_I2C_0_slStatus |= ((uint8)  NEOMOTE_1_I2C_0_SSTAT_WR_CMPLT);

                    NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;
                }
            }

            if(NEOMOTE_1_I2C_0_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                /* The address only issued after Start or ReStart: so check address
                   to catch this events:
                    FF : sets Addr phase with byte_complete interrupt trigger.
                    UDB: sets Addr phase immediately after Start or ReStart. */
                if(NEOMOTE_1_I2C_0_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* Check for software address detection */
                    #if(NEOMOTE_1_I2C_0_SW_ADRR_DECODE)
                        tmp8 = NEOMOTE_1_I2C_0_GET_SLAVE_ADDR(NEOMOTE_1_I2C_0_DATA_REG);

                        if(tmp8 == NEOMOTE_1_I2C_0_slAddress)   /* Check for address match */
                        {
                            if(0u != (NEOMOTE_1_I2C_0_DATA_REG & NEOMOTE_1_I2C_0_READ_FLAG))
                            {
                                /* Place code to prepare read buffer here                  */
                                /* `#START NEOMOTE_1_I2C_0_SW_PREPARE_READ_BUF_interrupt` */

                                /* `#END` */

                                /* Prepare next opeation to read, get data and place in data register */
                                if(NEOMOTE_1_I2C_0_slRdBufIndex < NEOMOTE_1_I2C_0_slRdBufSize)
                                {
                                    /* Load first data byte from array */
                                    NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_slRdBufPtr[NEOMOTE_1_I2C_0_slRdBufIndex];
                                    NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT;
                                    NEOMOTE_1_I2C_0_slRdBufIndex++;

                                    NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_RD_BUSY;
                                }
                                else    /* Overflow: provide 0xFF on the bus */
                                {
                                    NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_OVERFLOW_RETURN;
                                    NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT;

                                    NEOMOTE_1_I2C_0_slStatus  |= (NEOMOTE_1_I2C_0_SSTAT_RD_BUSY |
                                                                   NEOMOTE_1_I2C_0_SSTAT_RD_ERR_OVFL);
                                }

                                NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SL_RD_DATA;
                            }
                            else  /* Write transaction: receive 1st byte */
                            {
                                NEOMOTE_1_I2C_0_ACK_AND_RECEIVE;
                                NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SL_WR_DATA;

                                NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_WR_BUSY;
                                NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;
                            }
                        }    
                        else
                        {
                            /*     Place code to compare for additional address here    */
                            /* `#START NEOMOTE_1_I2C_0_SW_ADDR_COMPARE_interruptStart` */

                            /* `#END` */
                            
                            NEOMOTE_1_I2C_0_NAK_AND_RECEIVE;   /* NACK address */

                            /* Place code to end of condition for NACK generation here */
                            /* `#START NEOMOTE_1_I2C_0_SW_ADDR_COMPARE_interruptEnd`  */

                            /* `#END` */
                        }
                        
                    #else /* (NEOMOTE_1_I2C_0_HW_ADRR_DECODE) */
                        
                        if(0u != (NEOMOTE_1_I2C_0_DATA_REG & NEOMOTE_1_I2C_0_READ_FLAG))
                        {
                            /* Place code to prepare read buffer here                  */
                            /* `#START NEOMOTE_1_I2C_0_HW_PREPARE_READ_BUF_interrupt` */

                            /* `#END` */

                            /* Prepare next opeation to read, get data and place in data register */
                            if(NEOMOTE_1_I2C_0_slRdBufIndex < NEOMOTE_1_I2C_0_slRdBufSize)
                            {
                                /* Load first data byte from array */
                                NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_slRdBufPtr[NEOMOTE_1_I2C_0_slRdBufIndex];
                                NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT;
                                NEOMOTE_1_I2C_0_slRdBufIndex++;

                                NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_RD_BUSY;
                            }
                            else    /* Overflow: provide 0xFF on the bus */
                            {
                                NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_OVERFLOW_RETURN;
                                NEOMOTE_1_I2C_0_ACK_AND_TRANSMIT;

                                NEOMOTE_1_I2C_0_slStatus  |= (NEOMOTE_1_I2C_0_SSTAT_RD_BUSY |
                                                               NEOMOTE_1_I2C_0_SSTAT_RD_ERR_OVFL);
                            }

                            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SL_RD_DATA;
                        }
                        else  /* Write transaction: receive 1st byte */
                        {
                            NEOMOTE_1_I2C_0_ACK_AND_RECEIVE;
                            NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_SL_WR_DATA;

                            NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_WR_BUSY;
                            NEOMOTE_1_I2C_0_ENABLE_INT_ON_STOP;
                        }
                        
                    #endif /* (NEOMOTE_1_I2C_0_SW_ADRR_DECODE) */
                }
                /* Data states */
                /* Data master writes into slave */
                else if(NEOMOTE_1_I2C_0_state == NEOMOTE_1_I2C_0_SM_SL_WR_DATA)
                {
                    if(NEOMOTE_1_I2C_0_slWrBufIndex < NEOMOTE_1_I2C_0_slWrBufSize)
                    {
                        tmp8 = NEOMOTE_1_I2C_0_DATA_REG;
                        NEOMOTE_1_I2C_0_ACK_AND_RECEIVE;
                        NEOMOTE_1_I2C_0_slWrBufPtr[NEOMOTE_1_I2C_0_slWrBufIndex] = tmp8;
                        NEOMOTE_1_I2C_0_slWrBufIndex++;
                    }
                    else  /* of array: complete write, send NACK */
                    {
                        NEOMOTE_1_I2C_0_NAK_AND_RECEIVE;

                        NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_WR_ERR_OVFL;
                    }
                }
                /* Data master reads from slave */
                else if(NEOMOTE_1_I2C_0_state == NEOMOTE_1_I2C_0_SM_SL_RD_DATA)
                {
                    if(NEOMOTE_1_I2C_0_CHECK_DATA_ACK(tmpCsr))
                    {
                        if(NEOMOTE_1_I2C_0_slRdBufIndex < NEOMOTE_1_I2C_0_slRdBufSize)
                        {
                             /* Get data from array */
                            NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_slRdBufPtr[NEOMOTE_1_I2C_0_slRdBufIndex];
                            NEOMOTE_1_I2C_0_TRANSMIT_DATA;
                            NEOMOTE_1_I2C_0_slRdBufIndex++;
                        }
                        else   /* Overflow: provide 0xFF on the bus */
                        {
                            NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_OVERFLOW_RETURN;
                            NEOMOTE_1_I2C_0_TRANSMIT_DATA;

                            NEOMOTE_1_I2C_0_slStatus |= NEOMOTE_1_I2C_0_SSTAT_RD_ERR_OVFL;
                        }
                    }
                    else  /* Last byte was NACKed: read complete */
                    {
                        /* Only NACK appears on the bus */
                        NEOMOTE_1_I2C_0_DATA_REG = NEOMOTE_1_I2C_0_OVERFLOW_RETURN;
                        NEOMOTE_1_I2C_0_NAK_AND_TRANSMIT;

                        NEOMOTE_1_I2C_0_slStatus &= ((uint8) ~NEOMOTE_1_I2C_0_SSTAT_RD_BUSY);
                        NEOMOTE_1_I2C_0_slStatus |= ((uint8)  NEOMOTE_1_I2C_0_SSTAT_RD_CMPLT);

                        NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;
                    }
                }
                else
                {
                    #if(NEOMOTE_1_I2C_0_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        NEOMOTE_1_I2C_0_DisableInt();
                        NEOMOTE_1_I2C_0_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (NEOMOTE_1_I2C_0_TIMEOUT_ENABLED) */
                }
            }
        #endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        NEOMOTE_1_I2C_0_state = NEOMOTE_1_I2C_0_SM_IDLE;
    }
}


#if((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) && (NEOMOTE_1_I2C_0_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: NEOMOTE_1_I2C_0_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Empty interrupt handler to trigger after wakeup.
    *
    * Parameters:
    *  void
    *
    * Return:
    *  void
    *
    *******************************************************************************/
    CY_ISR(NEOMOTE_1_I2C_0_WAKEUP_ISR)
    {
        NEOMOTE_1_I2C_0_wakeupSource = 1u;  /* I2C was wakeup source */
        /* The SCL is stretched unitl the I2C_Wake() is called */
    }
#endif /* ((NEOMOTE_1_I2C_0_FF_IMPLEMENTED) && (NEOMOTE_1_I2C_0_WAKEUP_ENABLED))*/


/* [] END OF FILE */
