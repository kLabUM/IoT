/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is source code for example project of the 4ch dual SAR with SPI Master
*  and USBUART.
*
* Parameters used:
*  SPI Master
*   Mode                0(CPHA ==0, CPOL ==0)
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits            16
*   Bit Rate            1Mbit/s
*   Clock source        External
*
*  USBFS
*    Configured as a CDC device (see datasheet and USBUART example project)
*    Note that for USB operation, a 24MHz crystal needs to be installed on
*    processor module for CY8CKIT-001.
*
*  SAR ADCs
*      Sample mode             Triggered
*     Clock source         Internal
*    Resolution            12 bits
*    Conversion Rate        100000 SPS
*    Input range            +/- Vdda (Differential)
*    Reference            Internal Vref bypassed
*    Bypass Capacitors    10uF each
*
*  IDAC
*    Polarity            Positive
*    Range                0-31.875 uA
*    Speed                Slow
*    Value                10uA
*
*  Analog Mux
*    Mux type            Differential
*    Channels            4
*
*  Clocking
*    IMO source            24 MHz Xtal
*    USB                    48 MHz (IMO*2)
*    ILO                    100 kHz
*
* In this project, data input to two 4ch SAR ADCs via two 4ch analog muxes
* is converted and sent to a USB host device and a SPI slave device. To
* accomplish this, the central PSoC device implements a SPI Master and USB UART
* for communication. The USB host device can select which channel of the mux is
* to be read.
*
* To access the PSoC using the USBUART follow these steps:
*    1. Connect CY8CKIT-001 to the PC using USB cable.
*    2. Select the USB_UART.inf file from the project directory, as the driver
*      for this example once Windows asks for it.
*    3. Go to Start > Devices and Printers and identify COM port number
*       associated with the project.
*    4. Open a terminal emulation software and connect to COM port number
*       identified in previous step.
*    5. The input window will open with a blank screen. Type in a channel value.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
#include <stdio.h>

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif


#define RD_BUFFER_LEN           (64u)
#define WR_BUFFER_LEN           (64u)
#define MUX_SIZE                (4u)

/* ASCII value of decimal zero is 48 */
#define ASCII_DECIMAL_ZERO      (48u)

/* Any value above 0x07 is an illegal input for mux channel selection */
#define ERROR_MASK              (0xF8u)

/* Function that encapsulates the process of writing text strings to USBUART */
void PrintToUSBUART(char8 * outText);


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main() performs following functions:
*   1. Starts all used components.
*   2. Enumerates and handles data transfer between PC and PSoC via USBUART.
*   3. Chooses mux channel to be read according to USB UART data .
*   4. Reads ADC converted data, sends this data to SPI SLAVE via a SPI Master
*       and also back to the USBUART.
*   5. Displays ADC converted data on Character LCD for debugging.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void main()
{
    /* adcReading holds the converted 16-bit data from the ADC */
    uint16 adcReading = 0u;
    uint8 rdBuffer[RD_BUFFER_LEN];
    uint8 wrBuffer[WR_BUFFER_LEN];
    uint8 rdValue;
    uint8 temp;

    /* Enable Global interrupts - used for USB communication */
    CyGlobalIntEnable;

    SPIM_Start();
    USBUART_1_Start(0u, USBUART_1_5V_OPERATION);
    LCD_Char_Start();
    IDAC8_Start();
    ADC_SAR_0_Start();
    ADC_SAR_1_Start();

    /* When implementing a <=4 channel mux, the Analog sequencing Mux is faster
     * on an average than the Analog Hardware mux. However, additional code is
     * required to select channels non-sequentially.
     */
    AMux_0_Start();
    AMux_1_Start();

    /* Wait for Device to enumerate */
    while(!USBUART_1_GetConfiguration());

    /* Enumeration is complete, enable OUT endpoint for received data from Host */
    USBUART_1_CDC_Init();

    for(;;)
    {
        PrintToUSBUART("Please choose the channel (0-7) \n\r");

        /* Wait for input data from PC */
        while(USBUART_1_DataIsReady() == 0u);
        USBUART_1_GetAll(rdBuffer);

        /* Convert ASCII value in rdBuffer to numerical value:
         * Note that ASCII 48, 49,...,57 (decimal) corresponds to 0,1,...,9
         */
        rdValue = rdBuffer[0] - ASCII_DECIMAL_ZERO;

        /* If the value read is not a number in the range [0,7] */
        if(rdValue & ERROR_MASK)
        {
            PrintToUSBUART("Input Error!\n\r\n\r");

            LCD_Char_ClearDisplay();
            LCD_Char_PrintString("Input Error");
        }

        else /* The input from user is valid */
        {
            /* If this input is in the range [0,3], use mux0 */
            if(!(rdValue/MUX_SIZE))
            {
                AMux_0_FastSelect(rdValue);

                /* Initiate a single conversion of input data (ADC is in triggered
                 * mode).
                 */
                ADC_SAR_0_StartConvert();
                ADC_SAR_0_IsEndConversion(ADC_SAR_0_WAIT_FOR_RESULT);
                adcReading = ADC_SAR_0_GetResult16();

                sprintf((char *)wrBuffer, "The ADC_0 channel(%d) is: 0x%4x \n\r\n\r",
                                                            (int)rdValue, adcReading);
            }

            else
            {
                /* If rdValue is between [4,7], scale down to [0,3] */
                AMux_1_FastSelect(rdValue % MUX_SIZE);

                ADC_SAR_1_StartConvert();
                ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
                adcReading = ADC_SAR_1_GetResult16();

                sprintf((char *)wrBuffer, "The ADC_1 channel(%d) is: 0x%4x \n\r\n\r",
                                                (int)(rdValue % MUX_SIZE), adcReading);
            }

            PrintToUSBUART((char8 *)wrBuffer);
        }

        /* For verification purposes, display the adcReading on the LCD */
        LCD_Char_ClearDisplay();
        LCD_Char_PrintString("0x");
        LCD_Char_PrintInt16(adcReading);

        /* Clear the transmit buffer before next reading (good practice) */
        SPIM_ClearTxBuffer();

        temp = SPIM_ReadTxStatus();

        /* Ensure that previous SPI read is done, or SPI is idle before sending data */
        if((temp & (SPIM_STS_SPI_DONE | SPIM_STS_SPI_IDLE)))
        {
            SPIM_WriteTxData(adcReading);
        }

    }  /* End of forever loop */
}  /* End of main */


/*******************************************************************************
* Function Name: PrintToUSBUART
********************************************************************************
*
* Summary:
*  The input string passed to the function is printed to the USBUART
*  interface when the CDC device is ready.
*
* Parameters:
*  Text to be printed to USBUART as a string.
*
* Return:
*  None.
*
*******************************************************************************/

void PrintToUSBUART(char8 * outText)
{
    /* Wait till the CDC device is ready before sending data */
    while(USBUART_1_CDCIsReady() == 0u);
    /* Send strlen number of characters of wrBuffer to USBUART */
    USBUART_1_PutData((uint8 *)outText, strlen(outText));
}


/* [] END OF FILE */
