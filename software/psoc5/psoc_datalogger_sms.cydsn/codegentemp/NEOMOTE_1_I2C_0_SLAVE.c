/*******************************************************************************
* File Name: NEOMOTE_1_I2C_0_SLAVE.c
* Version 3.30
*
* Description:
*  This file provides the source code of APIs for the I2C component Slave mode.
*
* Note:
*
*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NEOMOTE_1_I2C_0_PVT.h"

#if(NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED)

/**********************************
*      System variables
**********************************/

volatile uint8 NEOMOTE_1_I2C_0_slStatus;   /* Slave Status  */

/* Transmit buffer variables */
volatile uint8 * NEOMOTE_1_I2C_0_slRdBufPtr;   /* Pointer to Transmit buffer  */
volatile uint8   NEOMOTE_1_I2C_0_slRdBufSize;  /* Slave Transmit buffer size  */
volatile uint8   NEOMOTE_1_I2C_0_slRdBufIndex; /* Slave Transmit buffer Index */

/* Receive buffer variables */
volatile uint8 * NEOMOTE_1_I2C_0_slWrBufPtr;   /* Pointer to Receive buffer  */
volatile uint8   NEOMOTE_1_I2C_0_slWrBufSize;  /* Slave Receive buffer size  */
volatile uint8   NEOMOTE_1_I2C_0_slWrBufIndex; /* Slave Receive buffer Index */

#if(NEOMOTE_1_I2C_0_SW_ADRR_DECODE)
    volatile uint8 NEOMOTE_1_I2C_0_slAddress;  /* Software address variable */
#endif   /* (NEOMOTE_1_I2C_0_SW_ADRR_DECODE) */


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveStatus
********************************************************************************
*
* Summary:
*  Returns I2C slave's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C slave.
*
* Global variables:
*  NEOMOTE_1_I2C_0_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
uint8 NEOMOTE_1_I2C_0_SlaveStatus(void) 
{
    return(NEOMOTE_1_I2C_0_slStatus);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveClearReadStatus
********************************************************************************
*
* Summary:
*  Clears the read status flags and returns they values.
*  The NEOMOTE_1_I2C_0_SSTAT_RD_BUSY flag is not effected by clear.
*
* Parameters:
*  None
*
* Return:
*  Current read status of I2C slave.
*
* Global variables:
*  NEOMOTE_1_I2C_0_slStatus  - used to store current status of I2C slave.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 NEOMOTE_1_I2C_0_SlaveClearReadStatus(void) 
{
    uint8 status;

    /* Mask of transfer complete flag and Error status */
    status = (NEOMOTE_1_I2C_0_slStatus & NEOMOTE_1_I2C_0_SSTAT_RD_MASK);
    NEOMOTE_1_I2C_0_slStatus &= ((uint8) ~NEOMOTE_1_I2C_0_SSTAT_RD_CLEAR);

    return(status);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveClearWriteStatus
********************************************************************************
*
* Summary:
*  Clears the write status flags and returns they values.
*  The NEOMOTE_1_I2C_0_SSTAT_WR_BUSY flag is not effected by clear.
*
* Parameters:
*  None
*
* Return:
*  Current write status of I2C slave.
*
* Global variables:
*  NEOMOTE_1_I2C_0_slStatus  - used to store current status of I2C slave.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 NEOMOTE_1_I2C_0_SlaveClearWriteStatus(void) 
{
    uint8 status;

    /* Mask of transfer complete flag and Error status */
    status = (NEOMOTE_1_I2C_0_slStatus & NEOMOTE_1_I2C_0_SSTAT_WR_MASK);
    NEOMOTE_1_I2C_0_slStatus &= ((uint8) ~NEOMOTE_1_I2C_0_SSTAT_WR_CLEAR);

    return(status);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveSetAddress
********************************************************************************
*
* Summary:
*  Sets the I2C slave address.
*
* Parameters:
*  address: I2C slave address for the primary device. This value may be any
*  address between 0 and 127.
*
* Return:
*  None
*
* Global variables:
*  NEOMOTE_1_I2C_0_Address  - used to store I2C slave address for the primary
*  device when software address detect feature is used.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SlaveSetAddress(uint8 address) 
{
    #if(NEOMOTE_1_I2C_0_SW_ADRR_DECODE)
        NEOMOTE_1_I2C_0_slAddress = (address & NEOMOTE_1_I2C_0_SLAVE_ADDR_MASK);
    #else
        NEOMOTE_1_I2C_0_ADDR_REG  = (address & NEOMOTE_1_I2C_0_SLAVE_ADDR_MASK);
    #endif /* (NEOMOTE_1_I2C_0_SW_ADRR_DECODE) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveInitReadBuf
********************************************************************************
*
* Summary:
*  Sets the buffer pointer and size of the read buffer. This function also
*  resets the transfer count returned with the I2C_SlaveGetReadBufSize function.
*
* Parameters:
*  readBuf:  Pointer to the data buffer to be read by the master.
*  bufSize:  Size of the read buffer exposed to the I2C master.
*
* Return:
*  None
*
* Global variables:
*  NEOMOTE_1_I2C_0_slRdBufPtr   - used to store pointer to slave read buffer.
*  NEOMOTE_1_I2C_0_slRdBufSize  - used to store salve read buffer size.
*  NEOMOTE_1_I2C_0_slRdBufIndex - used to store current index within slave
*  read buffer.
*
* Side Effects:
*  If this function is called during a bus transaction, data from the previous
*  buffer location and the beginning of current buffer may be transmitted.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize)
     
{
    /* Check for proper buffer */
    if(NULL != rdBuf)
    {
        NEOMOTE_1_I2C_0_slRdBufPtr   = (volatile uint8 *) rdBuf;    /* Set buffer pointer */
        NEOMOTE_1_I2C_0_slRdBufSize  = bufSize;    /* Set buffer size */
        NEOMOTE_1_I2C_0_slRdBufIndex = 0u;         /* Clears buffer index */
    }
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveInitWriteBuf
********************************************************************************
*
* Summary:
*  Sets the buffer pointer and size of the read buffer. This function also
*  resets the transfer count returned with the I2C_SlaveGetReadBufSize function.
*
* Parameters:
*  writeBuf:  Pointer to the data buffer to be read by the master.
*  bufSize:  Size of the buffer exposed to the I2C master.
*
* Return:
*  None
*
* Global variables:
*  NEOMOTE_1_I2C_0_slWrBufPtr   - used to store pointer to slave write buffer.
*  NEOMOTE_1_I2C_0_slWrBufSize  - used to store salve write buffer size.
*  NEOMOTE_1_I2C_0_slWrBufIndex - used to store current index within slave
*  write buffer.
*
* Side Effects:
*  If this function is called during a bus transaction, data from the previous
*  buffer location and the beginning of current buffer may be transmitted.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize)
     
{
    /* Check for proper buffer */
    if(NULL != wrBuf)
    {
        NEOMOTE_1_I2C_0_slWrBufPtr   = (volatile uint8 *) wrBuf;  /* Set buffer pointer */
        NEOMOTE_1_I2C_0_slWrBufSize  = bufSize;   /* Set buffer size */
        NEOMOTE_1_I2C_0_slWrBufIndex = 0u;        /* Clears buffer index */
    }
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes read by the I2C master since an
*  I2C_SlaveInitReadBuf or I2C_SlaveClearReadBuf function was executed.
*  The maximum return value will be the size of the read buffer.
*
* Parameters:
*  None
*
* Return:
*  Bytes read by master.
*
* Global variables:
*  NEOMOTE_1_I2C_0_slRdBufIndex - used to store current index within slave
*  read buffer.
*
*******************************************************************************/
uint8 NEOMOTE_1_I2C_0_SlaveGetReadBufSize(void) 
{
    return(NEOMOTE_1_I2C_0_slRdBufIndex);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes written by the I2C master since an
*  I2C_SlaveInitWriteBuf or I2C_SlaveClearWriteBuf function was executed.
*  The maximum return value will be the size of the write buffer.
*
* Parameters:
*  None
*
* Return:
*  Bytes written by master.
*
* Global variables:
*  NEOMOTE_1_I2C_0_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
uint8 NEOMOTE_1_I2C_0_SlaveGetWriteBufSize(void) 
{
    return(NEOMOTE_1_I2C_0_slWrBufIndex);
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read pointer to the first byte in the read buffer. The next byte
*  read by the master will be the first byte in the read buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NEOMOTE_1_I2C_0_slRdBufIndex - used to store current index within slave
*  read buffer.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SlaveClearReadBuf(void) 
{
    NEOMOTE_1_I2C_0_slRdBufIndex = 0u;
}


/*******************************************************************************
* Function Name: NEOMOTE_1_I2C_0_SlaveClearRxBuf
********************************************************************************
*
* Summary:
*  Resets the write pointer to the first byte in the write buffer. The next byte
*  written by the master will be the first byte in the write buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NEOMOTE_1_I2C_0_slWrBufIndex - used to store current index within slave
*  write buffer.
*
* Reentrant:
*  No
*
*******************************************************************************/
void NEOMOTE_1_I2C_0_SlaveClearWriteBuf(void) 
{
    NEOMOTE_1_I2C_0_slWrBufIndex = 0u;
}

#endif /* (NEOMOTE_1_I2C_0_MODE_SLAVE_ENABLED) */


/* [] END OF FILE */
