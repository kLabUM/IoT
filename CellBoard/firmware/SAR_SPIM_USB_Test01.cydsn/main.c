/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is the test project for the 4ch dual SAR with SPI master and USBUART 
*  Example Project.
*  
* Parameters used:
*  SPI slave
*   Mode                0(CPHA ==0, CPOL ==0)                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits	        16 
*   Bit Rate            1Mbit/s
*   Clock source        External 
*
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

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Starts used components.
*   2. Waits for, then receives data sent by SPI master.
*   3. Displays this data on Character LCD.
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
	/* Start SPI Slave and Character LCD */
	SPIS_Start();
	LCD_Char_Start();

	
    for(;;)
    {
	    /* Check if RxBuffer is non-empty If true, the SPI slave has received 
		 * data.
		 */
		if(SPIS_GetRxBufferSize())
		{
			/* Read and display received data on the LCD and verify this is same
			 * as sent by master.
			 */
			LCD_Char_ClearDisplay();
			LCD_Char_PrintString("0x");
			LCD_Char_PrintInt16(SPIS_ReadRxData());
			SPIS_ClearRxBuffer();
		}		
    } /* End forever loop */
} /* End main */


/* [] END OF FILE */
