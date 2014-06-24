/*******************************************************************************
* File Name: ADC_SAR_Seq.c
* Version 1.0
*
* Description:
*  This file provides the API functionality of the ADC SAR Sequencer Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_Seq.h"
#include "ADC_SAR_Seq_SAR.h"
#if(ADC_SAR_Seq_IRQ_REMOVE == 0u)
    #include <ADC_SAR_Seq_IRQ.H>
#endif   /* End ADC_SAR_Seq_IRQ_REMOVE */

static void ADC_SAR_Seq_TempBufDmaInit(void);
static void ADC_SAR_Seq_TempBufDmaRelease(void);

static void ADC_SAR_Seq_FinalBufDmaInit(void);
static void ADC_SAR_Seq_FinalBufDmaRelease(void);

static int16 ADC_SAR_Seq_tempArray[ADC_SAR_Seq_NUMBER_OF_CHANNELS];
int16  ADC_SAR_Seq_finalArray[ADC_SAR_Seq_NUMBER_OF_CHANNELS];
uint32 ADC_SAR_Seq_initVar = 0u;
static uint8 ADC_SAR_Seq_tempChan;
static uint8 ADC_SAR_Seq_finalChan;
static uint8 ADC_SAR_Seq_tempTD;
static uint8 ADC_SAR_Seq_finalTD;


/*******************************************************************************
* Function Name: ADC_SAR_Seq_TempBufDmaInit()
********************************************************************************
*
* Summary:
*  Provides initialization procedure for the TempBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void ADC_SAR_Seq_TempBufDmaInit(void)
{
    ADC_SAR_Seq_tempTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the destination address, but not the source address
    */
    (void) CyDmaTdSetConfiguration(ADC_SAR_Seq_tempTD, ADC_SAR_Seq_TEMP_TRANSFER_COUNT,
        ADC_SAR_Seq_tempTD, ((uint8)ADC_SAR_Seq_TempBuf__TD_TERMOUT_EN | (uint8)TD_INC_DST_ADR));

    /* From the SAR to the TempArray */
    (void) CyDmaTdSetAddress(ADC_SAR_Seq_tempTD, (uint16)(LO16((uint32)ADC_SAR_Seq_SAR_DATA_ADDR_0)),
        (uint16)(LO16((uint32)ADC_SAR_Seq_tempArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(ADC_SAR_Seq_tempChan, ADC_SAR_Seq_tempTD);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_TempBufDmaRelease()
********************************************************************************
*
* Summary:
*  Provides release procedure for the TempBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void ADC_SAR_Seq_TempBufDmaRelease(void)
{
    (void) CyDmaChDisable(ADC_SAR_Seq_tempChan);

    /* Clear any potential DMA requests and re-reset TD pointers */
    while(0u != (CY_DMA_CH_STRUCT_PTR[ADC_SAR_Seq_tempChan].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
    {
        ; /* Wait for to be cleared */
    }

    (void) CyDmaChSetRequest(ADC_SAR_Seq_tempChan, CY_DMA_CPU_TERM_CHAIN);
    (void) CyDmaChEnable    (ADC_SAR_Seq_tempChan, 1u);

    while(0u != (CY_DMA_CH_STRUCT_PTR[ADC_SAR_Seq_tempChan].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

    /* Release allocated TD and mark it as invalid */
    CyDmaTdFree(ADC_SAR_Seq_tempTD);
    ADC_SAR_Seq_tempTD = CY_DMA_INVALID_TD;

}


/****************************************************************************
* Function Name: ADC_SAR_Seq_FinalBufDmaInit()
*****************************************************************************
*
* Summary:
*  Provides initialization procedure for the FinalBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
static void ADC_SAR_Seq_FinalBufDmaInit(void)
{
    ADC_SAR_Seq_finalTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the source and destination address
    */
    (void) CyDmaTdSetConfiguration(ADC_SAR_Seq_finalTD, ((uint16)ADC_SAR_Seq_FINAL_BYTES_PER_BURST),
        ADC_SAR_Seq_finalTD, ((uint8)(ADC_SAR_Seq_FinalBuf__TD_TERMOUT_EN) | (uint8)TD_INC_SRC_ADR |
            (uint8)TD_INC_DST_ADR));

    /* From the the TempArray to Final Array */
    (void) CyDmaTdSetAddress(ADC_SAR_Seq_finalTD, (uint16)(LO16((uint32)ADC_SAR_Seq_tempArray)),
        (uint16)(LO16((uint32)ADC_SAR_Seq_finalArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(ADC_SAR_Seq_finalChan, ADC_SAR_Seq_finalTD);
}


/****************************************************************************
* Function Name: ADC_SAR_Seq_FinalBufDmaRelease()
*****************************************************************************
*
* Summary:
*  Provides release procedure for the FinalBuf DMA.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
static void ADC_SAR_Seq_FinalBufDmaRelease(void)
{
    (void) CyDmaChDisable(ADC_SAR_Seq_finalChan);

    /* Clear any potential DMA requests and re-reset TD pointers */
    while(0u != (CY_DMA_CH_STRUCT_PTR[ADC_SAR_Seq_finalChan].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
    {
        ; /* Wait for to be cleared */
    }

    (void) CyDmaChSetRequest(ADC_SAR_Seq_finalChan, CY_DMA_CPU_TERM_CHAIN);
    (void) CyDmaChEnable    (ADC_SAR_Seq_finalChan, 1u);

    while(0u != (CY_DMA_CH_STRUCT_PTR[ADC_SAR_Seq_finalChan].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

    /* Release allocated TD and mark it as invalid */
    CyDmaTdFree(ADC_SAR_Seq_finalTD);
    ADC_SAR_Seq_finalTD = CY_DMA_INVALID_TD;
}


/****************************************************************************
* Function Name: ADC_SAR_Seq_Disable()
*****************************************************************************
*
* Summary:
*  Disables the component without disabling the ADC SAR.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
void ADC_SAR_Seq_Disable(void)
{
    uint8 enableInterrupts;

    ADC_SAR_Seq_CONTROL_REG &= ((uint8)(~ADC_SAR_Seq_BASE_COMPONENT_ENABLE));

    /* Disable Counter */
    enableInterrupts = CyEnterCriticalSection();
    ADC_SAR_Seq_CYCLE_COUNTER_AUX_CONTROL_REG &= ((uint8)(~ADC_SAR_Seq_CYCLE_COUNTER_ENABLE));
    CyExitCriticalSection(enableInterrupts);
    ADC_SAR_Seq_COUNT_REG = 0u;

    ADC_SAR_Seq_TempBufDmaRelease();
    ADC_SAR_Seq_FinalBufDmaRelease();
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_Init
********************************************************************************
*
* Summary:
*  Inits channels for DMA transfer. Provides loading period to the AMUX address
*  selection counter
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_Init(void)
{
    /* Init DMA, 2 bytes bursts, each burst requires a request */
    ADC_SAR_Seq_tempChan = ADC_SAR_Seq_TempBuf_DmaInitialize(ADC_SAR_Seq_TEMP_BYTES_PER_BURST,
        ADC_SAR_Seq_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_PERIPH_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    /* Init DMA, (ADC_SAR_Seq_NUMBER_OF_CHANNELS << 1u) bytes bursts, each burst requires a request */
    ADC_SAR_Seq_finalChan = ADC_SAR_Seq_FinalBuf_DmaInitialize(ADC_SAR_Seq_FINAL_BYTES_PER_BURST,
        ADC_SAR_Seq_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_SRAM_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    #if(ADC_SAR_Seq_IRQ_REMOVE == 0u)
        /* Set the ISR to point to the ADC_SAR_SEQ_1_IRQ Interrupt. */
        ADC_SAR_Seq_IRQ_SetVector(&ADC_SAR_Seq_ISR);
        /* Set the priority. */
        ADC_SAR_Seq_IRQ_SetPriority((uint8)ADC_SAR_Seq_INTC_NUMBER);
    #endif   /* End ADC_SAR_Seq_IRQ_REMOVE */

}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_Enable
********************************************************************************
*
* Summary:
*  Enables DMA channels, address selection counter and FSM of Base component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_Enable(void)
{
    uint8 enableInterrupts;

    ADC_SAR_Seq_FinalBufDmaInit();
    ADC_SAR_Seq_TempBufDmaInit();

    (void) CyDmaChEnable(ADC_SAR_Seq_tempChan, 1u);
    (void) CyDmaChEnable(ADC_SAR_Seq_finalChan, 1u);

    /* Enable Counter and give Enable pulse to set an address of the last channel */
    enableInterrupts = CyEnterCriticalSection();
    ADC_SAR_Seq_CYCLE_COUNTER_AUX_CONTROL_REG |= ((uint8)(ADC_SAR_Seq_CYCLE_COUNTER_ENABLE));
    CyExitCriticalSection(enableInterrupts);

    /* Enable FSM of the Base Component */
    ADC_SAR_Seq_CONTROL_REG |= ((uint8)(ADC_SAR_Seq_BASE_COMPONENT_ENABLE));
    ADC_SAR_Seq_CONTROL_REG |= ((uint8)(ADC_SAR_Seq_LOAD_COUNTER_PERIOD));

    #if(ADC_SAR_Seq_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(ADC_SAR_Seq_INTC_NUMBER);
    #endif   /* End ADC_SAR_Seq_IRQ_REMOVE */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_Start
********************************************************************************
*
* Summary:
*  Starts component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_Start(void)
{
    if(ADC_SAR_Seq_initVar == 0u)
    {
        ADC_SAR_Seq_Init();
        ADC_SAR_Seq_initVar = 1u;
    }

    ADC_SAR_Seq_Enable();
    ADC_SAR_Seq_SAR_Start();
    (void) CY_GET_REG8(ADC_SAR_Seq_STATUS_PTR);

}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_Stop
********************************************************************************
*
* Summary:
*  Stops component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_Stop(void)
{
    ADC_SAR_Seq_SAR_Stop();
    ADC_SAR_Seq_Disable();
}

#if(ADC_SAR_Seq_SAMPLE_MODE != ADC_SAR_Seq_SAMPLE_MODE_HW_TRIGGERED)

    /*******************************************************************************
    * Function Name: ADC_SAR_Seq_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  When the Sample Mode parameter is set to 'Free Running', the component will
    * operate in a continuous mode. The channels will be scanned continuously until
    * _StopConvert()or  _Stop() is called
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ADC_SAR_Seq_StartConvert(void)
    {
        #if(ADC_SAR_Seq_SAMPLE_MODE != ADC_SAR_Seq_SAMPLE_MODE_FREE_RUNNING)

            ADC_SAR_Seq_CONTROL_REG |= ((uint8)(ADC_SAR_Seq_SOFTWARE_SOC_PULSE));

        #else

            ADC_SAR_Seq_SAR_StartConvert();

        #endif /* 
                #if(ADC_SAR_Seq_SAMPLE_MODE != 
                ADC_SAR_Seq_SAMPLE_MODE_FREE_RUNNING) 
               */
    }


    /*******************************************************************************
    * Function Name: ADC_SAR_Seq_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the component to stop all conversions
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ADC_SAR_Seq_StopConvert(void)
    {
        ADC_SAR_Seq_SAR_StopConvert();
    }

#endif /* ADC_SAR_Seq_SAMPLE_MODE != ADC_SAR_Seq_SAMPLE_MODE_HW_TRIGGERED */


/*******************************************************************************
* Function Name: ADC_SAR_Seq_IsEndConversion
********************************************************************************
*
* Summary:
*  Checks for ADC end of conversion for the case one channel and end of scan
*  for the case of multiple channels
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32 ADC_SAR_Seq_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
      status = ADC_SAR_Seq_STATUS_REG;
    } while ((status == 0u) && (retMode == ADC_SAR_Seq_WAIT_FOR_RESULT));

    return((uint32)status);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_GetResult16
********************************************************************************
*
* Summary:
*  Returns the ADC result for channel 'chan
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 ADC_SAR_Seq_GetResult16(uint16 chan)
{
    return (ADC_SAR_Seq_finalArray[ADC_SAR_Seq_GET_RESULT_INDEX_OFFSET - chan] - ADC_SAR_Seq_SAR_shift);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_GetAdcResult
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA register, not the results buffer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 ADC_SAR_Seq_GetAdcResult(void)
{
    return (ADC_SAR_Seq_SAR_GetResult16());
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset which is used by the functions _CountsTo_uVolts(),
*  _CountsTo_mVolts() and _CountsTo_Volts() to substract the offset from the
*  given reading before calculating the voltage conversion
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_SetOffset(int32 offset)
{
    ADC_SAR_Seq_SAR_SetOffset((int16)offset);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC_SAR_Seq resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_SAR_Seq_StopConvert(), change the resolution, then restart the
*  conversions with ADC_SAR_Seq_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_SAR_Seq_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SAR_Seq_SetResolution() is called before data is valid again.
*  Affects ADC_SAR_Seq_CountsTo_Volts(), ADC_SAR_Seq_CountsTo_mVolts(), and
*  ADC_SAR_Seq_CountsTo_uVolts() by calculating the correct conversion between
*  ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void ADC_SAR_Seq_SetResolution(uint8 resolution)
{
    ADC_SAR_Seq_SAR_SetResolution(resolution);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ADC_SAR_Seq_SetGain(int32 adcGain)
{
    ADC_SAR_Seq_SAR_SetGain((int16)adcGain);
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to mVolts as a 32-bit integer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 ADC_SAR_Seq_CountsTo_mVolts(int16 adcCounts)
{
    return ((int32) ADC_SAR_Seq_SAR_CountsTo_mVolts(adcCounts));
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to uVolts as a 32-bit integer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 ADC_SAR_Seq_CountsTo_uVolts(int16 adcCounts)
{
    return (ADC_SAR_Seq_SAR_CountsTo_uVolts(adcCounts));
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to Volts as a floating point number
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
float32 ADC_SAR_Seq_CountsTo_Volts(int16 adcCounts)
{
    return (ADC_SAR_Seq_SAR_CountsTo_Volts(adcCounts));
}


/* [] END OF FILE */
