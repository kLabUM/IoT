/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#include "solinst_depth.h"

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    solinst_start();
     CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        SolinstReading reading;
        solinst_get_reading(&reading);
        CyDelay(5000u);
       
    }
}

/* [] END OF FILE */
