/*******************************************************************************
* File Name: Sensirion_I2C_SLAVE.c
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

#include "Sensirion_I2C_PVT.h"

#if(Sensirion_I2C_MODE_SLAVE_ENABLED)

/**********************************
*      System variables
**********************************/

volatile uint8 Sensirion_I2C_slStatus;   /* Slave Status  */

/* Transmit buffer variables */
volatile uint8 * Sensirion_I2C_slRdBufPtr;   /* Pointer to Transmit buffer  */
volatile uint8   Sensirion_I2C_slRdBufSize;  /* Slave Transmit buffer size  */
volatile uint8   Sensirion_I2C_slRdBufIndex; /* Slave Transmit buffer Index */

/* Receive buffer variables */
volatile uint8 * Sensirion_I2C_slWrBufPtr;   /* Pointer to Receive buffer  */
volatile uint8   Sensirion_I2C_slWrBufSize;  /* Slave Receive buffer size  */
volatile uint8   Sensirion_I2C_slWrBufIndex; /* Slave Receive buffer Index */

#if(Sensirion_I2C_SW_ADRR_DECODE)
    volatile uint8 Sensirion_I2C_slAddress;  /* Software address variable */
#endif   /* (Sensirion_I2C_SW_ADRR_DECODE) */


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveStatus
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
*  Sensirion_I2C_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
uint8 Sensirion_I2C_SlaveStatus(void) 
{
    return(Sensirion_I2C_slStatus);
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveClearReadStatus
********************************************************************************
*
* Summary:
*  Clears the read status flags and returns they values.
*  The Sensirion_I2C_SSTAT_RD_BUSY flag is not effected by clear.
*
* Parameters:
*  None
*
* Return:
*  Current read status of I2C slave.
*
* Global variables:
*  Sensirion_I2C_slStatus  - used to store current status of I2C slave.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 Sensirion_I2C_SlaveClearReadStatus(void) 
{
    uint8 status;

    /* Mask of transfer complete flag and Error status */
    status = (Sensirion_I2C_slStatus & Sensirion_I2C_SSTAT_RD_MASK);
    Sensirion_I2C_slStatus &= ((uint8) ~Sensirion_I2C_SSTAT_RD_CLEAR);

    return(status);
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveClearWriteStatus
********************************************************************************
*
* Summary:
*  Clears the write status flags and returns they values.
*  The Sensirion_I2C_SSTAT_WR_BUSY flag is not effected by clear.
*
* Parameters:
*  None
*
* Return:
*  Current write status of I2C slave.
*
* Global variables:
*  Sensirion_I2C_slStatus  - used to store current status of I2C slave.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 Sensirion_I2C_SlaveClearWriteStatus(void) 
{
    uint8 status;

    /* Mask of transfer complete flag and Error status */
    status = (Sensirion_I2C_slStatus & Sensirion_I2C_SSTAT_WR_MASK);
    Sensirion_I2C_slStatus &= ((uint8) ~Sensirion_I2C_SSTAT_WR_CLEAR);

    return(status);
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveSetAddress
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
*  Sensirion_I2C_Address  - used to store I2C slave address for the primary
*  device when software address detect feature is used.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Sensirion_I2C_SlaveSetAddress(uint8 address) 
{
    #if(Sensirion_I2C_SW_ADRR_DECODE)
        Sensirion_I2C_slAddress = (address & Sensirion_I2C_SLAVE_ADDR_MASK);
    #else
        Sensirion_I2C_ADDR_REG  = (address & Sensirion_I2C_SLAVE_ADDR_MASK);
    #endif /* (Sensirion_I2C_SW_ADRR_DECODE) */
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveInitReadBuf
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
*  Sensirion_I2C_slRdBufPtr   - used to store pointer to slave read buffer.
*  Sensirion_I2C_slRdBufSize  - used to store salve read buffer size.
*  Sensirion_I2C_slRdBufIndex - used to store current index within slave
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
void Sensirion_I2C_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize)
     
{
    /* Check for proper buffer */
    if(NULL != rdBuf)
    {
        Sensirion_I2C_slRdBufPtr   = (volatile uint8 *) rdBuf;    /* Set buffer pointer */
        Sensirion_I2C_slRdBufSize  = bufSize;    /* Set buffer size */
        Sensirion_I2C_slRdBufIndex = 0u;         /* Clears buffer index */
    }
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveInitWriteBuf
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
*  Sensirion_I2C_slWrBufPtr   - used to store pointer to slave write buffer.
*  Sensirion_I2C_slWrBufSize  - used to store salve write buffer size.
*  Sensirion_I2C_slWrBufIndex - used to store current index within slave
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
void Sensirion_I2C_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize)
     
{
    /* Check for proper buffer */
    if(NULL != wrBuf)
    {
        Sensirion_I2C_slWrBufPtr   = (volatile uint8 *) wrBuf;  /* Set buffer pointer */
        Sensirion_I2C_slWrBufSize  = bufSize;   /* Set buffer size */
        Sensirion_I2C_slWrBufIndex = 0u;        /* Clears buffer index */
    }
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveGetReadBufSize
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
*  Sensirion_I2C_slRdBufIndex - used to store current index within slave
*  read buffer.
*
*******************************************************************************/
uint8 Sensirion_I2C_SlaveGetReadBufSize(void) 
{
    return(Sensirion_I2C_slRdBufIndex);
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveGetWriteBufSize
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
*  Sensirion_I2C_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
uint8 Sensirion_I2C_SlaveGetWriteBufSize(void) 
{
    return(Sensirion_I2C_slWrBufIndex);
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveClearReadBuf
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
*  Sensirion_I2C_slRdBufIndex - used to store current index within slave
*  read buffer.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Sensirion_I2C_SlaveClearReadBuf(void) 
{
    Sensirion_I2C_slRdBufIndex = 0u;
}


/*******************************************************************************
* Function Name: Sensirion_I2C_SlaveClearRxBuf
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
*  Sensirion_I2C_slWrBufIndex - used to store current index within slave
*  write buffer.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Sensirion_I2C_SlaveClearWriteBuf(void) 
{
    Sensirion_I2C_slWrBufIndex = 0u;
}

#endif /* (Sensirion_I2C_MODE_SLAVE_ENABLED) */


/* [] END OF FILE */
