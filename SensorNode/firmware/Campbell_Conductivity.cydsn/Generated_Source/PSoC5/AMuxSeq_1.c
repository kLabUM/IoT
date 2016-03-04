/*******************************************************************************
* File Name: AMuxSeq_1.c
* Version 1.70
*
*  Description:
*    This file contains functions for the AMuxSeq.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AMuxSeq_1.h"

uint8 AMuxSeq_1_initVar = 0u;


/*******************************************************************************
* Function Name: AMuxSeq_1_Start
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxSeq_1_Start(void)
{
    AMuxSeq_1_DisconnectAll();
    AMuxSeq_1_initVar = 1u;
}


/*******************************************************************************
* Function Name: AMuxSeq_1_Init
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxSeq_1_Init(void)
{
    AMuxSeq_1_DisconnectAll();
}


/*******************************************************************************
* Function Name: AMuxSeq_1_Stop
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxSeq_1_Stop(void)
{
    AMuxSeq_1_DisconnectAll();
}

#if(AMuxSeq_1_MUXTYPE == AMuxSeq_1_MUX_DIFF)

extern int8 AMuxSeq_1_CYAMUXSIDE_A_curChannel;


/*******************************************************************************
* Function Name: AMuxSeq_1_Next
********************************************************************************
* Summary:
*  Disconnects the previous channel and connects the next one in the sequence.
*  When Next is called for the first time after Init, Start, Enable, Stop, or
*  DisconnectAll, it connects channel 0.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxSeq_1_Next(void)
{
    AMuxSeq_1_CYAMUXSIDE_A_Next();
    AMuxSeq_1_CYAMUXSIDE_B_Next();
}


/*******************************************************************************
* Function Name: AMuxSeq_1_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels. The next time Next is called, channel
*  0 will be connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxSeq_1_DisconnectAll(void)
{
    AMuxSeq_1_CYAMUXSIDE_A_DisconnectAll();
    AMuxSeq_1_CYAMUXSIDE_B_DisconnectAll();
}


/*******************************************************************************
* Function Name: AMuxSeq_1_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 AMuxSeq_1_GetChannel(void)
{
    return AMuxSeq_1_CYAMUXSIDE_A_curChannel;
}

#else

extern int8 AMuxSeq_1_curChannel;


/*******************************************************************************
* Function Name: AMuxSeq_1_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 AMuxSeq_1_GetChannel(void)
{
    return AMuxSeq_1_curChannel;
}

#endif


/* [] END OF FILE */
