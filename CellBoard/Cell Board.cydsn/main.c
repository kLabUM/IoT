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
//#include <device.h>
#include <project.h>
#include "modem.h"
#include "utilities.h"
#include "packet.h"


CY_ISR_PROTO(Wakeup_ISR);
void Goto_Sleep();

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	

	sleep_isr_StartEx(Wakeup_ISR); // Start Sleep ISR
	SleepTimer_SetInterval(SleepTimer__CTW_256_MS);
	SleepTimer_Start();			   // Start SleepTimer Compnent	
    

	// Number of sleep wakeups before we process a simple task
	//Total time in mili seconds = N * SleepInterval (e.g. 4*256 = 1 second)
	ScheduleSimpleTask(4u); 

	//start the modem, set the alarm, and shut the modem down
	modem_start();
	modem_rtc_set_repeating_minute_alarm(1u);
	uint8 x = modem_set_non_cyclic_sleep();//modem_shutdown();
	
	//struct tm cal = modem_get_rtc_time();
	//modem_get_serial_number();
	//uint8 i = modem_connect();
	//modem_get_nertwork_time();
	
    for(;;)
	{
		if( modem_rtc_alert_fired())
		{
			
		}else if( SimpleSchedulerTaskReady() ){
			LED_Write(!LED_Read());
		}/* If not ready, update the counter for the sleep timer */
		else {
			//Goto_Sleep();
		}
		
	}
		
		
		/*
		char   data_packet[MAX_PACKET_LENGTH] = {0}, test_csv[100] = {0};
int    iter, sign;
uint8  loops, packet_ready;
uint16 packet_len;
		    // Initialize variables
	loops			= 0u;
	packet_ready	= 0u;
	iter            = 0;
    sign            = 1;
    packet_len      = 0u;*/
		
		
		
		
		
		/*if ( ready == 1u ){
			iter = 0;
			if (clear_packet(data_packet)) {
                packet_len = 0u;
                packet_ready = 0u;
            }
			
			blink_LED(3u);
			
			// Set up the modem and connect to network					
			LED_Write(!LED_Read());
			
			if (modem_startup()) {
				//modem_get_serial_number();

				
				// Send a packet
				LED_Write(!LED_Read());	
//				sprintf(data_packet,"%s%s, %u\r\n", data_packet,
//	        		"tmp", loops);                                    DON'T NEED TMP  
				ready = modem_send_packet(data_packet);
				CyDelay(5000u);
				
				if (clear_packet(data_packet)) {
	                packet_len = 0u;
	                packet_ready = 0u;
	            }
				
				// Request a packet
				LED_Write(!LED_Read());	
				if( modem_get_packet(data_packet,"lock,tmp") ){
				

				}								
				
				
				//modem_power_off();
				//modem_stop();
				
			}
			modem_shutdown();
			
			loops += 10;
			ready = 0u;
		}*/

}

CY_ISR(Wakeup_ISR)
{
    /***************************************************************************
    * This function must always be called (when the Sleep Timer's interrupt
    * is disabled or enabled) after wake up to clear the ctw_int status bit.
    * It is required to call SleepTimer_GetStatus() within 1 ms (1 clock cycle
    * of the ILO) after CTW event occurred.
    ***************************************************************************/
    SleepTimer_GetStatus();
	SleepCounterUpdate();
	
}

void Goto_Sleep(){
	
			/* Prepares system clocks for the Sleep mode */
			//sleep all components
			modem_sleep();
			
			
			CyPmSaveClocks();
	        CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);
	        CyPmRestoreClocks();
			
			
			//wakeup all components
			modem_wakeup();
}




