/*******************************************************************************
* File Name: Sensirion_I2C_INT.c
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

#include "Sensirion_I2C_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START Sensirion_I2C_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: Sensirion_I2C_ISR
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
CY_ISR(Sensirion_I2C_ISR)
{
    #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
       uint8  tmp8;
    #endif  /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;

    #if(Sensirion_I2C_TIMEOUT_FF_ENABLED)
        if(0u != Sensirion_I2C_TimeoutGetStatus())
        {
            Sensirion_I2C_TimeoutReset();
            Sensirion_I2C_state = Sensirion_I2C_SM_EXIT_IDLE;
            /* Sensirion_I2C_CSR_REG should be cleared after reset */
        }
    #endif /* (Sensirion_I2C_TIMEOUT_FF_ENABLED) */


    tmpCsr = Sensirion_I2C_CSR_REG;      /* Make copy as interrupts clear */

    #if(Sensirion_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED)
        if(Sensirion_I2C_CHECK_START_GEN(Sensirion_I2C_MCSR_REG))
        {
            Sensirion_I2C_CLEAR_START_GEN;

            /* Set READ complete, but was aborted */
            Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_ERR_XFER |
                                            Sensirion_I2C_GET_MSTAT_CMPLT);

            /* The slave was addressed */
            Sensirion_I2C_state = Sensirion_I2C_SM_SLAVE;
        }
    #endif /* (Sensirion_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED) */


    #if(Sensirion_I2C_MODE_MULTI_MASTER_ENABLED)
        if(Sensirion_I2C_CHECK_LOST_ARB(tmpCsr))
        {
            /* Set errors */
            Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_ERR_XFER     |
                                            Sensirion_I2C_MSTAT_ERR_ARB_LOST |
                                            Sensirion_I2C_GET_MSTAT_CMPLT);

            Sensirion_I2C_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

            #if(Sensirion_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED)
                if(Sensirion_I2C_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* The slave was addressed */
                    Sensirion_I2C_state = Sensirion_I2C_SM_SLAVE;
                }
                else
                {
                    Sensirion_I2C_BUS_RELEASE;

                    Sensirion_I2C_state = Sensirion_I2C_SM_EXIT_IDLE;
                }
            #else
                Sensirion_I2C_BUS_RELEASE;

                Sensirion_I2C_state = Sensirion_I2C_SM_EXIT_IDLE;

            #endif /* (Sensirion_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED) */
        }
    #endif /* (Sensirion_I2C_MODE_MULTI_MASTER_ENABLED) */

    /* Check for Master operation mode */
    if(Sensirion_I2C_CHECK_SM_MASTER)
    {
        #if(Sensirion_I2C_MODE_MASTER_ENABLED)
            if(Sensirion_I2C_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                switch (Sensirion_I2C_state)
                {
                case Sensirion_I2C_SM_MSTR_WR_ADDR:  /* After address is sent, WRITE data */
                case Sensirion_I2C_SM_MSTR_RD_ADDR:  /* After address is sent, READ  data */

                    tmpCsr &= ((uint8) ~Sensirion_I2C_CSR_STOP_STATUS); /* Clear STOP bit history on address phase */
                    
                    if(Sensirion_I2C_CHECK_ADDR_ACK(tmpCsr))
                    {
                        /* Setup for transmit or receive of data */
                        if(Sensirion_I2C_state == Sensirion_I2C_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                        {
                            /* Check if at least one byte to transfer */
                            if(Sensirion_I2C_mstrWrBufSize > 0u)
                            {
                                /* Load the 1st data byte */
                                Sensirion_I2C_DATA_REG = Sensirion_I2C_mstrWrBufPtr[0u];
                                Sensirion_I2C_TRANSMIT_DATA;
                                Sensirion_I2C_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                                /* Set transmit state until done */
                                Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_WR_DATA;
                            }
                            /* End of buffer: complete writing */
                            else if(Sensirion_I2C_CHECK_NO_STOP(Sensirion_I2C_mstrControl))
                            {
                                #if(CY_PSOC5A)
                                    /* Do not handles 0 bytes transfer - HALT is NOT allowed */
                                    Sensirion_I2C_ENABLE_INT_ON_STOP;
                                    Sensirion_I2C_GENERATE_STOP;
                                
                                #else
                                    /* Set WRITE complete and Master HALTED */
                                    Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_XFER_HALT |
                                                                    Sensirion_I2C_MSTAT_WR_CMPLT);

                                    Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_HALT; /* Expect RESTART */
                                    Sensirion_I2C_DisableInt();
                                
                                #endif /* (CY_PSOC5A) */
                            }
                            else
                            {
                                Sensirion_I2C_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                                Sensirion_I2C_GENERATE_STOP;
                            }
                        }
                        else  /* Master Receive data */
                        {
                            Sensirion_I2C_READY_TO_READ; /* Release bus to read data */

                            Sensirion_I2C_state  = Sensirion_I2C_SM_MSTR_RD_DATA;
                        }
                    }
                    /* Address is NACKed */
                    else if(Sensirion_I2C_CHECK_ADDR_NAK(tmpCsr))
                    {
                        /* Set Address NAK error */
                        Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_ERR_XFER |
                                                        Sensirion_I2C_MSTAT_ERR_ADDR_NAK);
                                                        
                        if(Sensirion_I2C_CHECK_NO_STOP(Sensirion_I2C_mstrControl))
                        {
                            Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_XFER_HALT | 
                                                            Sensirion_I2C_GET_MSTAT_CMPLT);

                            Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_HALT; /* Expect RESTART */
                            Sensirion_I2C_DisableInt();
                        }
                        else  /* Do normal Stop */
                        {
                            Sensirion_I2C_ENABLE_INT_ON_STOP; /* Enable interrupt on STOP, to catch it */
                            Sensirion_I2C_GENERATE_STOP;
                        }
                    }
                    else
                    {
                        /* Address phase is not set for some reason: error */
                        #if(Sensirion_I2C_TIMEOUT_ENABLED)
                            /* Exit from interrupt to take a chance for timeout timer handle this case */
                            Sensirion_I2C_DisableInt();
                            Sensirion_I2C_ClearPendingInt();
                        #else
                            /* Block execution flow: unexpected condition */
                            CYASSERT(0u != 0u);
                        #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
                    }
                    break;

                case Sensirion_I2C_SM_MSTR_WR_DATA:

                    if(Sensirion_I2C_CHECK_DATA_ACK(tmpCsr))
                    {
                        /* Check if end of buffer */
                        if(Sensirion_I2C_mstrWrBufIndex  < Sensirion_I2C_mstrWrBufSize)
                        {
                            Sensirion_I2C_DATA_REG =
                                                     Sensirion_I2C_mstrWrBufPtr[Sensirion_I2C_mstrWrBufIndex];
                            Sensirion_I2C_TRANSMIT_DATA;
                            Sensirion_I2C_mstrWrBufIndex++;
                        }
                        /* End of buffer: complete writing */
                        else if(Sensirion_I2C_CHECK_NO_STOP(Sensirion_I2C_mstrControl))
                        {
                            /* Set WRITE complete and Master HALTED */
                            Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_XFER_HALT |
                                                            Sensirion_I2C_MSTAT_WR_CMPLT);

                            Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_HALT;    /* Expect RESTART */
                            Sensirion_I2C_DisableInt();
                        }
                        else  /* Do normal STOP */
                        {
                            Sensirion_I2C_Workaround();          /* Workaround: empty function */
                            Sensirion_I2C_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                            Sensirion_I2C_GENERATE_STOP;
                        }
                    }
                    /* Last byte NAKed: end writing */
                    else if(Sensirion_I2C_CHECK_NO_STOP(Sensirion_I2C_mstrControl))
                    {
                        /* Set WRITE complete, SHORT transfer and Master HALTED */
                        Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_ERR_XFER       |
                                                        Sensirion_I2C_MSTAT_ERR_SHORT_XFER |
                                                        Sensirion_I2C_MSTAT_XFER_HALT      |
                                                        Sensirion_I2C_MSTAT_WR_CMPLT);

                        Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_HALT;    /* Expect RESTART */
                        Sensirion_I2C_DisableInt();
                    }
                    else  /* Do normal STOP */
                    {
                        Sensirion_I2C_ENABLE_INT_ON_STOP;    /* Enable interrupt on STOP, to catch it */
                        Sensirion_I2C_GENERATE_STOP;

                        /* Set SHORT and ERR transfer */
                        Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_ERR_SHORT_XFER |
                                                        Sensirion_I2C_MSTAT_ERR_XFER);
                    }
                    
                    break;

                case Sensirion_I2C_SM_MSTR_RD_DATA:

                    Sensirion_I2C_mstrRdBufPtr[Sensirion_I2C_mstrRdBufIndex] = Sensirion_I2C_DATA_REG;
                    Sensirion_I2C_mstrRdBufIndex++;

                    /* Check if end of buffer */
                    if(Sensirion_I2C_mstrRdBufIndex < Sensirion_I2C_mstrRdBufSize)
                    {
                        Sensirion_I2C_ACK_AND_RECEIVE;       /* ACK and receive byte */
                    }
                    /* End of buffer: complete reading */
                    else if(Sensirion_I2C_CHECK_NO_STOP(Sensirion_I2C_mstrControl))
                    {                        
                        /* Set READ complete and Master HALTED */
                        Sensirion_I2C_mstrStatus |= (Sensirion_I2C_MSTAT_XFER_HALT |
                                                        Sensirion_I2C_MSTAT_RD_CMPLT);
                        
                        Sensirion_I2C_state = Sensirion_I2C_SM_MSTR_HALT;    /* Expect RESTART */
                        Sensirion_I2C_DisableInt();
                    }
                    else
                    {
                        Sensirion_I2C_ENABLE_INT_ON_STOP;
                        Sensirion_I2C_NAK_AND_RECEIVE;       /* NACK and TRY to generate STOP */
                    }
                    break;

                default: /* This is an invalid state and should not occur */

                    #if(Sensirion_I2C_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        Sensirion_I2C_DisableInt();
                        Sensirion_I2C_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */

                    break;
                }
            }

            /* Catches the Stop: end of transaction */
            if(Sensirion_I2C_CHECK_STOP_STS(tmpCsr))
            {
                Sensirion_I2C_mstrStatus |= Sensirion_I2C_GET_MSTAT_CMPLT;

                Sensirion_I2C_DISABLE_INT_ON_STOP;
                Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;
            }
        #endif /* (Sensirion_I2C_MODE_MASTER_ENABLED) */
    }
    else if(Sensirion_I2C_CHECK_SM_SLAVE)
    {
        #if(Sensirion_I2C_MODE_SLAVE_ENABLED)
            
            if((Sensirion_I2C_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
               (Sensirion_I2C_CHECK_BYTE_COMPLETE(tmpCsr) && Sensirion_I2C_CHECK_ADDRESS_STS(tmpCsr)))
            {
                /* Catch end of master write transcation: use interrupt on Stop */
                /* The STOP bit history on address phase does not have correct state */
                if(Sensirion_I2C_SM_SL_WR_DATA == Sensirion_I2C_state)
                {
                    Sensirion_I2C_DISABLE_INT_ON_STOP;

                    Sensirion_I2C_slStatus &= ((uint8) ~Sensirion_I2C_SSTAT_WR_BUSY);
                    Sensirion_I2C_slStatus |= ((uint8)  Sensirion_I2C_SSTAT_WR_CMPLT);

                    Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;
                }
            }

            if(Sensirion_I2C_CHECK_BYTE_COMPLETE(tmpCsr))
            {
                /* The address only issued after Start or ReStart: so check address
                   to catch this events:
                    FF : sets Addr phase with byte_complete interrupt trigger.
                    UDB: sets Addr phase immediately after Start or ReStart. */
                if(Sensirion_I2C_CHECK_ADDRESS_STS(tmpCsr))
                {
                    /* Check for software address detection */
                    #if(Sensirion_I2C_SW_ADRR_DECODE)
                        tmp8 = Sensirion_I2C_GET_SLAVE_ADDR(Sensirion_I2C_DATA_REG);

                        if(tmp8 == Sensirion_I2C_slAddress)   /* Check for address match */
                        {
                            if(0u != (Sensirion_I2C_DATA_REG & Sensirion_I2C_READ_FLAG))
                            {
                                /* Place code to prepare read buffer here                  */
                                /* `#START Sensirion_I2C_SW_PREPARE_READ_BUF_interrupt` */

                                /* `#END` */

                                /* Prepare next opeation to read, get data and place in data register */
                                if(Sensirion_I2C_slRdBufIndex < Sensirion_I2C_slRdBufSize)
                                {
                                    /* Load first data byte from array */
                                    Sensirion_I2C_DATA_REG = Sensirion_I2C_slRdBufPtr[Sensirion_I2C_slRdBufIndex];
                                    Sensirion_I2C_ACK_AND_TRANSMIT;
                                    Sensirion_I2C_slRdBufIndex++;

                                    Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_RD_BUSY;
                                }
                                else    /* Overflow: provide 0xFF on the bus */
                                {
                                    Sensirion_I2C_DATA_REG = Sensirion_I2C_OVERFLOW_RETURN;
                                    Sensirion_I2C_ACK_AND_TRANSMIT;

                                    Sensirion_I2C_slStatus  |= (Sensirion_I2C_SSTAT_RD_BUSY |
                                                                   Sensirion_I2C_SSTAT_RD_ERR_OVFL);
                                }

                                Sensirion_I2C_state = Sensirion_I2C_SM_SL_RD_DATA;
                            }
                            else  /* Write transaction: receive 1st byte */
                            {
                                Sensirion_I2C_ACK_AND_RECEIVE;
                                Sensirion_I2C_state = Sensirion_I2C_SM_SL_WR_DATA;

                                Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_WR_BUSY;
                                Sensirion_I2C_ENABLE_INT_ON_STOP;
                            }
                        }    
                        else
                        {
                            /*     Place code to compare for additional address here    */
                            /* `#START Sensirion_I2C_SW_ADDR_COMPARE_interruptStart` */

                            /* `#END` */
                            
                            Sensirion_I2C_NAK_AND_RECEIVE;   /* NACK address */

                            /* Place code to end of condition for NACK generation here */
                            /* `#START Sensirion_I2C_SW_ADDR_COMPARE_interruptEnd`  */

                            /* `#END` */
                        }
                        
                    #else /* (Sensirion_I2C_HW_ADRR_DECODE) */
                        
                        if(0u != (Sensirion_I2C_DATA_REG & Sensirion_I2C_READ_FLAG))
                        {
                            /* Place code to prepare read buffer here                  */
                            /* `#START Sensirion_I2C_HW_PREPARE_READ_BUF_interrupt` */

                            /* `#END` */

                            /* Prepare next opeation to read, get data and place in data register */
                            if(Sensirion_I2C_slRdBufIndex < Sensirion_I2C_slRdBufSize)
                            {
                                /* Load first data byte from array */
                                Sensirion_I2C_DATA_REG = Sensirion_I2C_slRdBufPtr[Sensirion_I2C_slRdBufIndex];
                                Sensirion_I2C_ACK_AND_TRANSMIT;
                                Sensirion_I2C_slRdBufIndex++;

                                Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_RD_BUSY;
                            }
                            else    /* Overflow: provide 0xFF on the bus */
                            {
                                Sensirion_I2C_DATA_REG = Sensirion_I2C_OVERFLOW_RETURN;
                                Sensirion_I2C_ACK_AND_TRANSMIT;

                                Sensirion_I2C_slStatus  |= (Sensirion_I2C_SSTAT_RD_BUSY |
                                                               Sensirion_I2C_SSTAT_RD_ERR_OVFL);
                            }

                            Sensirion_I2C_state = Sensirion_I2C_SM_SL_RD_DATA;
                        }
                        else  /* Write transaction: receive 1st byte */
                        {
                            Sensirion_I2C_ACK_AND_RECEIVE;
                            Sensirion_I2C_state = Sensirion_I2C_SM_SL_WR_DATA;

                            Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_WR_BUSY;
                            Sensirion_I2C_ENABLE_INT_ON_STOP;
                        }
                        
                    #endif /* (Sensirion_I2C_SW_ADRR_DECODE) */
                }
                /* Data states */
                /* Data master writes into slave */
                else if(Sensirion_I2C_state == Sensirion_I2C_SM_SL_WR_DATA)
                {
                    if(Sensirion_I2C_slWrBufIndex < Sensirion_I2C_slWrBufSize)
                    {
                        tmp8 = Sensirion_I2C_DATA_REG;
                        Sensirion_I2C_ACK_AND_RECEIVE;
                        Sensirion_I2C_slWrBufPtr[Sensirion_I2C_slWrBufIndex] = tmp8;
                        Sensirion_I2C_slWrBufIndex++;
                    }
                    else  /* of array: complete write, send NACK */
                    {
                        Sensirion_I2C_NAK_AND_RECEIVE;

                        Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_WR_ERR_OVFL;
                    }
                }
                /* Data master reads from slave */
                else if(Sensirion_I2C_state == Sensirion_I2C_SM_SL_RD_DATA)
                {
                    if(Sensirion_I2C_CHECK_DATA_ACK(tmpCsr))
                    {
                        if(Sensirion_I2C_slRdBufIndex < Sensirion_I2C_slRdBufSize)
                        {
                             /* Get data from array */
                            Sensirion_I2C_DATA_REG = Sensirion_I2C_slRdBufPtr[Sensirion_I2C_slRdBufIndex];
                            Sensirion_I2C_TRANSMIT_DATA;
                            Sensirion_I2C_slRdBufIndex++;
                        }
                        else   /* Overflow: provide 0xFF on the bus */
                        {
                            Sensirion_I2C_DATA_REG = Sensirion_I2C_OVERFLOW_RETURN;
                            Sensirion_I2C_TRANSMIT_DATA;

                            Sensirion_I2C_slStatus |= Sensirion_I2C_SSTAT_RD_ERR_OVFL;
                        }
                    }
                    else  /* Last byte was NACKed: read complete */
                    {
                        /* Only NACK appears on the bus */
                        Sensirion_I2C_DATA_REG = Sensirion_I2C_OVERFLOW_RETURN;
                        Sensirion_I2C_NAK_AND_TRANSMIT;

                        Sensirion_I2C_slStatus &= ((uint8) ~Sensirion_I2C_SSTAT_RD_BUSY);
                        Sensirion_I2C_slStatus |= ((uint8)  Sensirion_I2C_SSTAT_RD_CMPLT);

                        Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;
                    }
                }
                else
                {
                    #if(Sensirion_I2C_TIMEOUT_ENABLED)
                        /* Exit from interrupt to take a chance for timeout timer handle this case */
                        Sensirion_I2C_DisableInt();
                        Sensirion_I2C_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (Sensirion_I2C_TIMEOUT_ENABLED) */
                }
            }
        #endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        Sensirion_I2C_state = Sensirion_I2C_SM_IDLE;
    }
}


#if((Sensirion_I2C_FF_IMPLEMENTED) && (Sensirion_I2C_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: Sensirion_I2C_WAKEUP_ISR
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
    CY_ISR(Sensirion_I2C_WAKEUP_ISR)
    {
        Sensirion_I2C_wakeupSource = 1u;  /* I2C was wakeup source */
        /* The SCL is stretched unitl the I2C_Wake() is called */
    }
#endif /* ((Sensirion_I2C_FF_IMPLEMENTED) && (Sensirion_I2C_WAKEUP_ENABLED))*/


/* [] END OF FILE */
