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
#include <project.h>
#include "maxbotix.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */


    for(;;)
    {
                
        Maxbotix Maxbotix_reading = Maxbotix_Take_Reading();
		CyDelay(1000u);

    }
}


