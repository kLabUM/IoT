/*******************************************************************************
* File Name: ADC_SAR_Seq.h
* Version 1.0
*
* Description:
*  Contains the function prototypes, constants and register definition of the
*  ADC SAR Sequencer Component.
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

#if !defined(CY_ADC_SAR_Seq_H)
    #define CY_ADC_SAR_Seq_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "ADC_SAR_Seq_TempBuf_dma.h"
#include "ADC_SAR_Seq_FinalBuf_dma.h"

#define ADC_SAR_Seq_NUMBER_OF_CHANNELS    (1u)
#define ADC_SAR_Seq_SAMPLE_MODE           (0u)

extern int16  ADC_SAR_Seq_finalArray[ADC_SAR_Seq_NUMBER_OF_CHANNELS];
extern uint32 ADC_SAR_Seq_initVar;

/* references to ADC_SAR global variables */
extern volatile int16 ADC_SAR_Seq_SAR_offset;
extern volatile int16 ADC_SAR_Seq_SAR_countsPerVolt;
extern volatile int16 ADC_SAR_Seq_SAR_shift;

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ADC_SAR_SEQ_v1_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*        Function Prototypes
***************************************/
void ADC_SAR_Seq_Init(void);
void ADC_SAR_Seq_Enable(void);
void ADC_SAR_Seq_Disable(void);
void ADC_SAR_Seq_Start(void);
void ADC_SAR_Seq_Stop(void);

uint32 ADC_SAR_Seq_IsEndConversion(uint8 retMode);
int16 ADC_SAR_Seq_GetResult16(uint16 chan);
int16 ADC_SAR_Seq_GetAdcResult(void);
void ADC_SAR_Seq_SetOffset(int32 offset);
void ADC_SAR_Seq_SetResolution(uint8 resolution);
void ADC_SAR_Seq_SetGain(int32 adcGain);
int32 ADC_SAR_Seq_CountsTo_mVolts(int16 adcCounts);
int32 ADC_SAR_Seq_CountsTo_uVolts(int16 adcCounts);
float32 ADC_SAR_Seq_CountsTo_Volts(int16 adcCounts);
void ADC_SAR_Seq_Sleep(void);
void ADC_SAR_Seq_Wakeup(void);
void ADC_SAR_Seq_SaveConfig(void);
void ADC_SAR_Seq_RestoreConfig(void);

CY_ISR_PROTO( ADC_SAR_Seq_ISR );


/**************************************
*    Initial Parameter Constants
**************************************/
#define ADC_SAR_Seq_IRQ_REMOVE             (0u)                /* Removes internal interrupt */


/***************************************
*             Registers
***************************************/
#define ADC_SAR_Seq_CYCLE_COUNTER_AUX_CONTROL_REG \
                                               (*(reg8 *) ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define ADC_SAR_Seq_CYCLE_COUNTER_AUX_CONTROL_PTR \
                                               ( (reg8 *) ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define ADC_SAR_Seq_CONTROL_REG    (*(reg8 *) \
                                             ADC_SAR_Seq_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define ADC_SAR_Seq_CONTROL_PTR    ( (reg8 *) \
                                             ADC_SAR_Seq_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define ADC_SAR_Seq_COUNT_REG      (*(reg8 *) \
                                             ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define ADC_SAR_Seq_COUNT_PTR      ( (reg8 *) \
                                             ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define ADC_SAR_Seq_STATUS_REG     (*(reg8 *) ADC_SAR_Seq_bSAR_SEQ_EOCSts__STATUS_REG)
#define ADC_SAR_Seq_STATUS_PTR     ( (reg8 *) ADC_SAR_Seq_bSAR_SEQ_EOCSts__STATUS_REG)

#define ADC_SAR_Seq_SAR_DATA_ADDR_0 (ADC_SAR_Seq_SAR_ADC_SAR__WRK0)
#define ADC_SAR_Seq_SAR_DATA_ADDR_1 (ADC_SAR_Seq_SAR_ADC_SAR__WRK1)
#define ADC_SAR_Seq_SAR_DATA_ADDR_0_REG (*(reg8 *) \
                                              ADC_SAR_Seq_SAR_ADC_SAR__WRK0)
#define ADC_SAR_Seq_SAR_DATA_ADDR_1_REG (*(reg8 *) \
                                              ADC_SAR_Seq_SAR_ADC_SAR__WRK1)


/**************************************
*       Register Constants
**************************************/

#if(ADC_SAR_Seq_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define ADC_SAR_Seq_INTC_PRIOR_NUMBER          (uint8)(ADC_SAR_Seq_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define ADC_SAR_Seq_INTC_NUMBER                (uint8)(ADC_SAR_Seq_IRQ__INTC_NUMBER)

#endif   /* End ADC_SAR_Seq_IRQ_REMOVE */


/***************************************
*       API Constants
***************************************/

/* Constants for IsEndConversion() "retMode" parameter */
#define ADC_SAR_Seq_RETURN_STATUS              (0x01u)
#define ADC_SAR_Seq_WAIT_FOR_RESULT            (0x00u)

/* Defines for the Resolution parameter */
#define ADC_SAR_Seq_BITS_12    ADC_SAR_Seq_SAR__BITS_12
#define ADC_SAR_Seq_BITS_10    ADC_SAR_Seq_SAR__BITS_10
#define ADC_SAR_Seq_BITS_8     ADC_SAR_Seq_SAR__BITS_8

#define ADC_SAR_Seq_CYCLE_COUNTER_ENABLE    (0x20u)
#define ADC_SAR_Seq_BASE_COMPONENT_ENABLE   (0x01u)
#define ADC_SAR_Seq_LOAD_COUNTER_PERIOD     (0x02u)
#define ADC_SAR_Seq_SOFTWARE_SOC_PULSE      (0x04u)

/* Generic DMA Configuration parameters */
#define ADC_SAR_Seq_TEMP_BYTES_PER_BURST     (uint8)(2u)
#define ADC_SAR_Seq_TEMP_TRANSFER_COUNT      ((uint16)ADC_SAR_Seq_NUMBER_OF_CHANNELS << 1u)
#define ADC_SAR_Seq_FINAL_BYTES_PER_BURST    ((uint8)ADC_SAR_Seq_NUMBER_OF_CHANNELS << 1u)
#define ADC_SAR_Seq_REQUEST_PER_BURST        (uint8)(1u)

#define ADC_SAR_Seq_GET_RESULT_INDEX_OFFSET    ((uint8)ADC_SAR_Seq_NUMBER_OF_CHANNELS - 1u)

/* Define for Sample Mode  */
#define ADC_SAR_Seq_SAMPLE_MODE_FREE_RUNNING    (0x00u)
#define ADC_SAR_Seq_SAMPLE_MODE_SW_TRIGGERED    (0x01u)
#define ADC_SAR_Seq_SAMPLE_MODE_HW_TRIGGERED    (0x02u)


/***************************************
*        Optional Function Prototypes
***************************************/
#if(ADC_SAR_Seq_SAMPLE_MODE != ADC_SAR_Seq_SAMPLE_MODE_HW_TRIGGERED)
    void ADC_SAR_Seq_StartConvert(void);
    void ADC_SAR_Seq_StopConvert(void);
#endif /* ADC_SAR_Seq_SAMPLE_MODE != ADC_SAR_Seq_SAMPLE_MODE_HW_TRIGGERED */

#endif  /* !defined(CY_ADC_SAR_Seq_H) */

/* [] END OF FILE */
