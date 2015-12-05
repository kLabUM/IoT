/* M2M SMS Datalogger */ 

#include <device.h>
#include <stdio.h>
#include <string.h>
#include <FS.h>
#include "neomote.h"
#include "sleep.h"
#include "modem.h"
#include "packet.h"
#include "ultrasonic.h"
#include "solinst_depth.h"
#include "autosampler.h"
#include "BatteryVoltage.h"
#include "debug.h"

// define global variables
#define WRITE_DEBUG 1
#define FEED_ID 123456789

const char *API_KEY = "YOUR_KEY_HERE";
char   data_packet[MAX_PACKET_LENGTH] = {0}, debug_packet[MAX_PACKET_LENGTH] = {0};
uint8   packet_ready, take_reading;
float   vBattery;

// Set NeoMote ID Number
uint8 moteID = 2;

uint8 t_sample, trigger_sampler, bottle_count, tmp;
UltrasonicReading ultrasonic_reading = {.valid = 0};    // Initialize UltrasonicReading.valid to 0
SolinstReading solinst_reading = {.valid = 0};          // Initialize SolinstReading.valid to 0

// callback definitions
void rtcCallBackReceived(uint8 alarmType);

// prototype functions
void Write_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes);
CY_ISR_PROTO(isr_timer);
void Goto_Low_Power_Mode();
void debugLog(const void *pData);


void main(){

    CyGlobalIntEnable;

    // Start up initial mote processes
    SleepTimer_Start();
    isr_SleepTimer_StartEx(sleepTimerWake_INT);
    FS_Init();  // SD Card
    modem_set_api_feed(FEED_ID, API_KEY);
    modem_start();
    ultrasonic_start();
    solinst_start();
    ADC_SAR_1_Start();
    //modem_power_off();
    
    packet_ready = 0u; 
    take_reading = 1u;
    t_sample = 2u;                                  // Initialize Sample Period to 2 minutes
    trigger_sampler = 0u;                           // Initialize automated sampler to not take a sample    
    bottle_count = 0u;                              // Initialize bottle count to zero

    NeoRTC_Start(rtcCallBackReceived);              // Start and enable the RTC.   
    NeoRTC_Set_Repeating_Minute_Alarm(t_sample);    // Set 1-minute alarm
   
    
    //  Uncomment below to set RTC
    /*
    NeoRtcTimeStruct tm = {
      .second = 00,
      .minute = 54,
      .hour = 18,
      .day = 27,
      .weekday = 2,
      .month = 5,
      .year = 2014,
    } ;
    RTC_WriteTime(tm); //sets time
    */


    for(;;){
    
        RTC_Process_Tasks();
        
        // Loop continuously and take a reading  
        // every "t_sample" minutes.
        // The variable "take_reading" is set to TRUE 
        // by rtcCallBackReceived() defined after the for() loop
        if(take_reading){ 

            // Turn on the modem to update state variables:
            //  sampling frequency; triggering the autosampler
            modem_power_on();   
           
            if (clear_packet(data_packet)) {
                packet_ready = 0u;
            }
                        
            // To communicate with the IoT platform, the node 
            // 1) listens on a given port and 2) parses an incoming string 
            // for relevant commands. Once a packet is ready to send (3), 
            // the node 4) transmits the packet.  This is achieved in as little 
            // as four lines of code by leveraging an existing TCP/IP library.
            //
            // 1) modem_get_packet()
            // 2) packet_get_uint8()
            // 3) sprintf(data_packet, ...
            // 4) modem_send_packet()
            //
            if (modem_get_packet(data_packet,"t_sample,trigger_sampler")) {
                
                // Read in any updated values
                if(packet_get_uint8(data_packet, "t_sample", &tmp)){
                    t_sample = tmp;
                }
                if(packet_get_uint8(data_packet, "trigger_sampler", &tmp)){
                    trigger_sampler = tmp;
                }
            }

            /*
            if (send_attempts > 0) {
                debug_write("New reading taken before previous packet was sent");
            }
            */

            // Trigger the autosampler to collect the sample 
            // if a sample is requested
            if (trigger_sampler){
                
                // Send in acknowledgement that packet containing
                // info re:automated sampler has been received:
                modem_send_packet("trigger_sampler, 0");
                
                trigger_sampler = 0; // Update the value locally
                
                // Trigger the autosampler as long as there are still available samples
                // If bottle_count >= MAX_BOTTLE_COUNT, skip taking a sample and avoid
                // waiting for the code to timeout
                if (bottle_count < MAX_BOTTLE_COUNT) {
                    // Turn off modem to conserve energy
                    modem_power_off();
                    
                    // Start up the autosampler processes 
                    // and power on the autosampler
                    autosampler_start();
                    autosampler_power_on();
                    

                    // Trigger the autosampler and update current bottle_count
                    autosampler_take_sample(&bottle_count);
                    
                    // Power off the autosampler
                    // and shut down the autosampler processes 
                    autosampler_power_off(); 
                    autosampler_stop();    
                }
                else {
                    debug_write("bottle_count >= MAX_BOTTLE_COUNT");
                }
            }
            
            // Construct the data packet that will be transmitted
            // by the sensor node, starting with the bottle the
            // autosampler last collected a sample in
            // (the packet is in .csv format)
            sprintf(data_packet,"%s, %u\r\n",
                "bottle", bottle_count);

            // Get Sensor Readings for:
            //  Depth, Pressure, Temperature, Conductivity
            // and update the data packet                
            if (solinst_get_reading(&solinst_reading)){
                sprintf(data_packet,"%s%s, %f\r\n", data_packet,
                    "depth_press", solinst_reading.depth);            
                    
                sprintf(data_packet,"%s%s, %f\r\n", data_packet,
                    "temp_press", solinst_reading.temp);                      
            }
            
            if (ultrasonic_get_reading(&ultrasonic_reading)){
                sprintf(data_packet,"%s%s, %f\r\n", data_packet,
                    "depth_sonic", ultrasonic_reading.depth);              
            }
            if (ReadBatteryVoltage(&vBattery)){
                sprintf(data_packet,"%s%s, %f\r\n", data_packet,
                    "V_batt", vBattery);              
            }

            // An example of writing data in JSON format
            // This was replaced with .csv format due to 
            // .csv's smaller packet size
            /*
            sprintf(data_packet, "{"
                      "\"method\":\"put\","
                      "\"resource\":\"/feeds/%d\","
                      "\"headers\":{\"X-ApiKey\":\"%s\"},"
                      "\"body\":{\"version\":\"1.0.0\",\"datastreams\":["
                            "{ \"id\" : \"depth_sonic\", \"current_value\" : \"%f\"},"
                            "{ \"id\" : \"depth_press\", \"current_value\" : \"%f\"},"
                            "{ \"id\" : \"temp_press\", \"current_value\" : \"%f\"},"
                            "{ \"id\" : \"trigger_sampler\", \"current_value\" : \"%d\"},"
                            "{ \"id\" : \"V_batt\",  \"current_value\" : \"%f\"}"
                      "]}}",
                      FEED_ID,API_KEY,
                      ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp,0u,vBattery);
            */

            // Update flags for sending a packet and taking sensor readings
            packet_ready = 1u;
            take_reading = 0u;
            //send_attempts = 0u;
        
        // Once the flag for packet_ready has been set, 
        // send the packet and save the packet locally
        } else if(packet_ready){
            isr_SleepTimer_Stop;  //  <============= ADDRESS THIS WITH B.K.
            
            // Power on the modem in case it was turned off
            modem_power_on();
            
            // modem_state should now be IDLE or READY
            // and we can send the packet
            modem_send_packet(data_packet);
            
            // Power off the modem and conserve energy
            modem_power_off();
            
            // Backup data to SD Card
            // Use the current time to time-stamp the current reading
            NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();

            // Overwrite current data_packet with time-stamped data
            sprintf(data_packet, "\r\n%d:%d:%d %d/%d/%d -- [ID %d] u_d=%f s_d=%f s_t=%f bottle=%d v_b=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, moteID,
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp,bottle_count,vBattery);
            
            // Write data_packet to a *.txt file on the SD Card
            Write_To_SD_Card("data.txt","a",data_packet,strlen(data_packet));            

            // Clear the current packet in preparation for the next reading
            // when the node awakens from sleep
            if (clear_packet(data_packet)) {
                packet_ready = 0u;
            }
        
        // If either the sensor node should take a reading nor send a packet
        // go to low power mode to increase battery life    
        }else{
            // Set repeating alarm to trigger every "t_sample" minutes
            NeoRTC_Set_Repeating_Minute_Alarm(t_sample);  
            Goto_Low_Power_Mode();
        }
    CyDelay(1u);  // Quick Pause to prevent locking
    }
}

// Pull down all pins related to mote to save power since we're not using it
void killMotePower(){
    NEOMOTE_1_RX_RTS_n_Write(0u);
    NEOMOTE_1_RX_CTS_n_Write(0u);
    NEOMOTE_1_TX_RTS_n_Write(0u);
    NEOMOTE_1_TX_CTS_n_Write(0u);
    NEOMOTE_1_RX_Pin_Write(0u);
    NEOMOTE_1_TX_Pin_Write(0u);
    NEOMOTE_1_TimeN_Write(0u);
}



CY_ISR(isr_timer){
    //take_reading = 1u;
    //timer_ReadStatusRegister();
}


// This function is triggered by the RTC on the mote
// Here, take_reading is set to TRUE once every t_sample minutes,
// as set with NeoRTC_Set_Repeating_Minute_Alarm(t_sample);  
void rtcCallBackReceived(uint8 alarmType){ // RTC Event Handler.
      
    if(alarmType == RTC_MINUTE_ALARM){
         
        take_reading = 1u;
        
    }   
}


void Write_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes) {
// Remember to add line below to rtcCallBack Function
// Write_To_SD_Card("myData.txt","a",sendBuffer,strlen(sendBuffer));

    NEOMOTE_1_SD_Card_Power_Write(0u); // Power on the SD Card
    
    FS_FILE *  pFile;
    char sdVolName[10];  // Buffer that will hold SD card Volume name
    
    if (0 != FS_GetVolumeName(0, &sdVolName[0], 9)) {
        pFile = FS_FOpen(fileName, pMode);
        if (pFile == 0){
            FS_DeInit();
            FS_Init(); //poipoi debug error
            pFile = FS_FOpen(fileName, pMode);
        }
        FS_Write(pFile, pData, NumBytes);
        FS_FClose(pFile);
    }
    
    NEOMOTE_1_SD_Card_Power_Write(1u); // Power off the SD Card

}

/* [] END OF FILE */
