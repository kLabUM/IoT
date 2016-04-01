/*******************************************************************************
* File: main.c      
*
* Version: 1.0
* 
* Description:
*  This is a source code for example project that demonstates how to generate
*  a simple SineWave using the WaveDAC8 component.
*
* Hardware Dependency:
*  Pin Connections:
*  P0[0] --> SineWave output
* 
* Code Tested With:
*  1. PPSoC Creator 3.0 build 1124
*  2. DP8051 Keil 9.51
*  3. ARM GCC 4.7.3
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>


int main()
{
    WaveDAC8_1_Start(); /* Start WaveDAC8  */
	
    for(;;);            /* Loop forever    */
}


/* [] END OF FILE */
