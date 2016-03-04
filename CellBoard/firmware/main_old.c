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
#include <project.h>
#include "modem.h"
#include "packet.h"
#include "ultrasonic.h"

// define global variables
#define SLEEPTIMER_INTERVAL_COUNTER (7650u) // Number of wakeups before turn LED on 7650 @ 16ms ~2 min
#define WRITE_DEBUG 1
#define FEED_ID 1531021687

const char *API_KEY = "vqu8tl0XYVRnzZPMcFezcf8jpYL5mH9ZjI9V96e8FNP7g50U";
char   data_packet[MAX_PACKET_LENGTH] = {0}, test_csv[100] = {0};
int    iter, sign;
uint8  ready, loops, lock, packet_ready;
uint16 packet_len;
uint32 wakeup_interval_counter;
UltrasonicReading ultrasonic_reading    = {.valid = 0};     // Initialize UltrasonicReading.valid to 0

/* autosampler variables
uint8 t_sample, trigger_sampler, bottle_count, tmp;
*/
CY_ISR_PROTO(Wakeup_ISR);
uint8   blink_LED(uint8 n_blinks);
uint8	modem_setup();
uint8   modem_get_time();
uint8   modem_check_network();
uint8   modem_get_signal_quality();
uint8   modem_get_serial_number();
uint8   modem_get_google();
uint8   modem_get_profile();
uint8   modem_set_flow_control(uint8 param);
uint8 	modem_set_error_reports(uint8 param);
uint8   modem_get_sw_version();
uint8 	modem_enable_CDMA_data(uint8 param);
uint8	modem_test_CDMA_data();
uint8	modem_set_user(char* user);
uint8	modem_set_password(char* pass);
uint8 	at_write_command(char* uart_string, char* expected_response, uint32 uart_timeout);

float   v_out;

CY_ISR(Wakeup_ISR)
{
    /***************************************************************************
    * This function must always be called (when the Sleep Timer's interrupt
    * is disabled or enabled) after wake up to clear the ctw_int status bit.
    * It is required to call SleepTimer_GetStatus() within 1 ms (1 clock cycle
    * of the ILO) after CTW event occurred.
    ***************************************************************************/
    SleepTimer_GetStatus();
}

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	CyDelay(5u);  // Short delay to make sure device is ready for low power entry
	
	sleep_isr_StartEx(Wakeup_ISR); // Start Sleep ISR
	SleepTimer_Start();			   // Start SleepTimer Compnent	
    
    modem_set_api_feed(FEED_ID, API_KEY);
    
    //ADC_SAR_1_Start();
    //modem_start();
    //modem_power_on();    
    //modem_get_serial_number();
    
    // Check/set flow control: Changed from 3 (default - bidirectional) to 0 (no flow control) --> Did NOT fix ability to connect using AT#SD
    /*
	modem_set_flow_control(0u); 
    modem_get_profile(); //
    modem_get_sw_version();
	modem_set_error_reports(2u);
	*/
	
	// Init and enable CDMA
	/*
	modem_set_user("");
	modem_set_password("");	
	modem_test_CDMA_data();
	modem_enable_CDMA_data(1u);
	modem_test_CDMA_data();
	*/

    /* OLD MODEM CODE
    Telit_PWR_Write(0u); // 0u Enables power to cell module
    
    Telit_ON_Write(1u); 
    CyDelay(2000u);
    Telit_ON_Write(0u); 
    */    
    
    // Initialize variables
    ready			= 1u;
	loops			= 0u;
	lock			= 0u;
	packet_ready	= 0u;
	iter            = 0;
    sign            = 1;
    packet_len      = 0u;
	wakeup_interval_counter = 0u;	
    v_out           = 0.0;

    
    VBAT_READ_EN_Write(0u);
	Pin2_Write(0u);
	Pin17_Write(0u);
	Pin18_Write(0u);
    Pin37_Write(0u);
    Pin38_Write(0u);
    Pin39_Write(0u);
    //Pin34_Write(0u);
    //Pin35_Write(0u);
    
//    WaveDAC8_1_Start(); /* Start WaveDAC8  */


    for(;;)
	{
	/*	
		modem_start();
	    modem_power_on();    
	    modem_get_serial_number();
	
	uint8 k = 0;		
	for(k = 0; k < 5; k++)
    {	
	*/
		if ( ready == 1u ){
			iter = 0;
			if (clear_packet(data_packet)) {
                packet_len = 0u;
                packet_ready = 0u;
            }
			
			LED_Write(1u);
			
			blink_LED(3u);
			ultrasonic_start();
			CyDelay(1000u);
			
            if (ultrasonic_get_reading(&ultrasonic_reading)){
                sprintf(data_packet,"%s%s, %d\r\n", data_packet,
                    "depth_sonic", (uint16) (ultrasonic_reading.depth));              
            }
			ultrasonic_stop();
			blink_LED(3u);
			
			
			// Set up the modem and connect to network					
			LED_Write(!LED_Read());
			//modem_get_serial_number();
			modem_start();
			
			while( iter < MAX_CONN_ATTEMPTS) {
				iter++;
	
				// Set up the modem
				LED_Write(!LED_Read());
				ready = modem_power_on();
				//LED_Write(!LED_Read());
    			//ready = at_write_command("AT\r","OK",1000u);      
				modem_set_flow_control(0u);	
				modem_setup();
				
				if ( ready == 1u ) {
					// Connect modem to network
					// (modem_connect already accounts for retries)
					LED_Write(!LED_Read());
					ready = modem_connect();
					
					if( ready == 3u ) {
						
						LED_Write(!LED_Read());	
						sprintf(data_packet,"%s%s, %u\r\n", data_packet,
                    		"tmp", loops);  
						ready = modem_send_packet(data_packet);
						CyDelay(5000u);
						
						if (clear_packet(data_packet)) {
			                packet_len = 0u;
			                packet_ready = 0u;
			            }
						
						LED_Write(!LED_Read());	
						if( modem_get_packet(data_packet,"lock,tmp") ){
						
							/* Testing code to move the actuator */
							
							if(packet_get_uint8(data_packet,"lock",&lock)){
								if(lock == 1u){	
									// Supply power to breakout board
									// This powers the Reed Switch
									Pin2_Write(1u);
									CyDelay(1000u);
									
									// Move the actuator out
									Pin17_Write(1u);
									CyDelay(3000u);
									Pin17_Write(0u);
									
									CyDelay(2000u);
									
									// Move the actuator in
									Pin18_Write(1u);
									CyDelay(3000u);
									Pin18_Write(0u);
									
									// Cut power to breakout board
									CyDelay(1000u);
									Pin2_Write(0u);
								}
							}	
						}
						
						loops += 10;
						CyDelay(5000u);	
						
						ready = 0u;
						iter = MAX_CONN_ATTEMPTS;//break;					
					}
				}
				else {
					modem_reset();
				}
			}
			modem_power_off();
			modem_stop();
		}
		/* If not ready, update the counter for the sleep timer */
		else {
			/* Blink the LED to indicate sleeping */
			blink_LED(5u);
			
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
	            if(SLEEPTIMER_INTERVAL_COUNTER == wakeup_interval_counter)
	            {
	                /* Blink with LED */
	                //(0u == LED_P1_2_Read()) ? LED_P1_2_Write(1u) : LED_P1_2_Write(0u);
	                wakeup_interval_counter = 0u;
					ready = 1u;
	            }
	            else
	            {
	                wakeup_interval_counter++;
	            }
	                
	        } while (wakeup_interval_counter != 0u);
	        

	        /* Restore clock configuration */
	        CyPmRestoreClocks();
		}
		
		/*
        // Place your application code here.
        Pin37_Write(!Pin37_Read());
        
        clear_packet(data_packet);
        sprintf(data_packet,"%s, %u\r\n", "tmp", iter);
        
        modem_connect();
        LED_Write(!LED_Read());
        
        // modem_state should now be IDLE or READY
        //modem_send_packet(data_packet);        
        modem_get_google(); //Can't get to work
               
        if (tmp > 10) {
            sign = -1;
        } else if (tmp < -10) {
            sign = 1;
        }
        tmp = tmp + sign;        
        
        
        Pin37_Write(!Pin37_Read());
        LED_Write(!LED_Read());
        CyDelay(100u);  
        
        modem_get_time();
        Pin38_Write(!Pin38_Read());
        LED_Write(!LED_Read());
        CyDelay(100u);      
        
        modem_get_signal_quality();
        Pin39_Write(!Pin39_Read());
        LED_Write(!LED_Read());
        CyDelay(100u);  
        
        modem_check_network();
        //Pin34_Write(!Pin34_Read());
        LED_Write(!LED_Read());
        CyDelay(100u);  
        
        modem_get_serial_number();
        //modem_disconnect();
        //Pin35_Write(!Pin35_Read());
        LED_Write(!LED_Read());
        CyDelay(100u);   
        
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        v_out = ADC_SAR_1_CountsTo_Volts(ADC_SAR_1_GetResult16());        
        //v_out = Pin30_Read();
        Pin25_Write(v_out);
		*/
    }
	
	/*
	modem_power_off();  
	modem_stop();
	
	LED_Write(1u);
	CyDelay(200u);
	LED_Write(0u);
	CyDelay(200u);
	LED_Write(1u);
	CyDelay(200u);
	LED_Write(0u);
	CyDelay(200u);
	LED_Write(1u);
	CyDelay(200u);
	LED_Write(0u);
	CyDelay(200u);		
	CyPmSaveClocks();
	CyPmHibernate();
	*/
}

uint8 blink_LED(uint8 n_blinks) {
	uint8 k;
	for (k = 0; k < n_blinks; k++) {
		LED_Write(1u);
		CyDelay(200u);
		LED_Write(0u);
		CyDelay(200u);
	}	
}

/* [] END OF FILE */
