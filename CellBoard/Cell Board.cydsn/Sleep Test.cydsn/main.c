/*******************************************************************************
* File Name: main.c
*
* Version: 2.00
*
* Description:
*  This is source code for the datasheet example of the Sleep Timer component.
*
********************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h> //#include <device.h>

/******************************************************************************
* Number of wakeups before turn LED on.
******************************************************************************/
#define SLEEPTIMER_INTERVAL_COUNTER     (3840u)

/* Used to count wakeup events */
uint16 wakeupIntervalCounter;


/*******************************************************************************
* Function Name: WakeupIsr
********************************************************************************
* Summary:
*  The wakeup interrupt service routine.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(WakeupIsr)
{
    /***************************************************************************
    * This function must always be called (when the Sleep Timer's interrupt
    * is disabled or enabled) after wake up to clear the ctw_int status bit.
    * It is required to call SleepTimer_GetStatus() within 1 ms (1 clock cycle
    * of the ILO) after CTW event occurred.
    ***************************************************************************/
    SleepTimer_GetStatus();
}


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  Main function reconfigures SleepTimer (only for demonstration purposes) and
*  continuously prepares device for the Sleep mode entry and enters it.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void main()
{
    wakeupIntervalCounter = 0u;

    /* Enable global interrupts */
    CyGlobalIntEnable;
    
    /* A short delay to make sure device is ready for low power mode entry */
    CyDelay(5u);
    
    /* Start components */
    isr_StartEx(WakeupIsr);
    
    /* Start SleepTimer's operation with the customizer's settings */
    SleepTimer_Start();

    /* Optional section used for demonstration purposes */
    SleepTimer_Stop();              /* Stop Sleep Timer's operation         */
    SleepTimer_EnableInt();         /* Enable interrupts. Not required.     */
    SleepTimer_SetInterval(SleepTimer__CTW_4_MS);    /* Set new interval    */
    SleepTimer_Start();             /* Start with the new settings          */
    
    for(;;)
    {
        /* Prepares system clocks for the Sleep mode */
        CyPmSaveClocks();

        do
        {
            /*******************************************************************
            * Switch to the Sleep Mode for the other devices:
            *  - PM_SLEEP_TIME_NONE: wakeup time is defined by Sleep Timer
            *  - PM_SLEEP_SRC_CTW :  wakeup on CTW sources is allowed
            *******************************************************************/
            CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);


            /***********************************************************************
            * After the device is woken up the Sleep Timer's ISR is executed.
            * Afterwards the CyPmSleep() execution is finished the clock
            * configuration is restored.
            ***********************************************************************/
            if(SLEEPTIMER_INTERVAL_COUNTER == wakeupIntervalCounter)
            {
                /* Blink with LED */
                //(0u == LED_Read()) ? LED_Write(1u) : LED_Write(0u);
				LED_Write(!LED_Read());
                wakeupIntervalCounter = 0u;
            }
            else
            {
                wakeupIntervalCounter++;
            }
                
        } while (wakeupIntervalCounter != 0u);
        

        /* Restore clock configuration */
        CyPmRestoreClocks();
    }
}


/* [] END OF FILE */
