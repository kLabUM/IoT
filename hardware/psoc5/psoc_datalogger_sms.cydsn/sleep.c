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

/* [] END OF FILE */

#include <device.h>
#include "sleep.h"


void Components_Sleep(){
    uart_Sleep();
    uart_ultrasonic_Sleep();
    uart_solinst_Sleep();
    emFile_1_Sleep();
     NeoRTC_Sleep();
}

void Components_Wakeup(){
    uart_Wakeup();
    uart_ultrasonic_Wakeup();
    uart_solinst_Wakeup();
    emFile_1_Wakeup();
    NeoRTC_Wakeup();
}

void Goto_Low_Power_Mode(){
    Components_Sleep(); //define this function somewhere and put all of your hardware components in it -- eg. uart, spi, etc. Call component_sleep() for each component	
	CyPmSaveClocks();
    #if(CY_PSOC5LP)
	    CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);
    #else
        CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_NONE);
    #endif

	CyPmRestoreClocks();
	Components_Wakeup(); //wakeup each component -- once again, define yourself
}

CY_ISR(sleepTimerWake_INT){
        SleepTimer_GetStatus();
}
