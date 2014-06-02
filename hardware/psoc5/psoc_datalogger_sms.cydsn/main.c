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
#define FEED_ID 966630999

const char *API_KEY = "7inkCfgjLCcSq6t2E3RC7OnmZykBUXEU8Yv7K56c7JYUOxdn";
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
//void read_packet(uint8* packet, uint8 size);
//void write_packet(uint8* dest, uint8* src_ultrasonic, uint8* src_pressure, uint8 size);
//void clear_packet(char* packet);
void Write_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes);
CY_ISR_PROTO(isr_timer);
void Goto_Low_Power_Mode();
void debugLog(const void *pData);


void main(){

    CyGlobalIntEnable;
    SleepTimer_Start();
    isr_SleepTimer_StartEx(sleepTimerWake_INT);
    FS_Init();
    modem_set_api_feed(FEED_ID, API_KEY);
    modem_start();
    //modem_power_off();
    ultrasonic_start();
    solinst_start();
    ADC_SAR_1_Start();
    
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
         
        if(take_reading){ 

            modem_power_on();   
           
            if (clear_packet(data_packet)) {
                packet_ready = 0u;
            }
                        
            // modem_get_packet(data_packet);
            if (modem_get_packet(data_packet,"t_sample,trigger_sampler")) {
                // Send in acknowledgement that packet containing
                // info re:automated sampler has been received:
                modem_send_packet("trigger_sampler, 0");
                
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
            if (trigger_sampler){
            
                if (bottle_count < MAX_BOTTLE_COUNT) {
                    // Turn off modem to conserve energy
                    modem_power_off();
                    
                    autosampler_start();
                    autosampler_power_on();
                    
                    /*
                    if (autosampler_take_sample(&bottle_count) ) {
                        sprintf(data_packet,"%s, %u\r\n",
                            "bottle", bottle_count);
                    }
                    */ 
                    
                    autosampler_take_sample(&bottle_count);
                    
                    autosampler_power_off(); 
                    autosampler_stop();    
                }
                else {
                    debug_write("bottle_count >= MAX_BOTTLE_COUNT");
                }
            }
            
            // Get Readings for:
            // depth, pressure, temp
            // conductivity.
            sprintf(data_packet,"%s, %u\r\n",
                "bottle", bottle_count);
                
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
            
            /* Moved to after packet is written to server
            NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();

            sprintf(data_packet, "\r\n%d:%d:%d %d/%d/%d -- [ID %d] u_d=%f s_d=%f s_t=%f v_b=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, moteID,
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp,vBattery);
            
            Write_To_SD_Card("data.txt","a",data_packet,strlen(data_packet));
            */
            /* Old AWS packet
            sprintf(data_packet, "\n%d:%d:%d %d/%d/%d -- [ID %d] u_d=%f s_d=%f s_t=%f v_b=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, moteID,
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp,vBattery);
            */
   
            /* Create Xively Packet */
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
            /*
            sprintf(data_packet, "%s, %f\r\n%s, %f\r\n%s, %f\r\n%s, %f",
                "depth_sonic", ultrasonic_reading.depth,
                "depth_press", solinst_reading.depth,
                "temp_press", solinst_reading.temp,
                "V_batt", vBattery
                );
            */
            packet_ready = 1u;
            //send_attempts = 0u;
            take_reading = 0u;
            
  
        } else if(packet_ready){
            isr_SleepTimer_Stop;  //  <============= ADDRESS THIS WITH B.K.
            
            // Power on the modem in case it was turned off
            modem_power_on();
            
            // modem_state should now be IDLE or READY
            modem_send_packet(data_packet);
            
            modem_power_off();
            
            // Backup data to SD Card
            NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();

            sprintf(data_packet, "\r\n%d:%d:%d %d/%d/%d -- [ID %d] u_d=%f s_d=%f s_t=%f bottle=%d v_b=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, moteID,
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp,bottle_count,vBattery);
            
            Write_To_SD_Card("data.txt","a",data_packet,strlen(data_packet));
            
            if (clear_packet(data_packet)) {
                packet_ready = 0u;
            }
            
            /*
            // else if(modem_state == MODEM_STATE_IDLE){
            else { // modem state is ON (aka IDLE or READY)
                
                
                ////if(modem_send_packet(data_packet)){     // if packet sent
                //if(modem_send_packet(data_packet)){     // if packet sent
                //    modem_power_off();
                //    clear_packet(data_packet);
                //}
                //else{                                   // if packet not sent
                //    modem_reset();
                //    modem_power_off();
                //}
                
                if(send_attempts < MAX_SEND_ATTEMPTS){
                    
                    send_attempts++;
                    
                    if (modem_send_packet(data_packet)){     
                    // the packet is sent within the number of maximum attempts allowed
                        //debug_write("Packet sent within max attempts.");
                        modem_power_off();
                        //debug_write("Modem powered off.");
                        clear_packet(data_packet);
                        send_attempts = 0u;
                    }
                    else {
                        //modem_reset();
                    }
                    
                } 
                else {
                // SEND ATTEMPTS MOVED TO modem.c
                // the number of maximum attempts allowed has been exceeded
                    modem_power_off();
                    clear_packet(data_packet);
                    send_attempts = 0u;
                    debug_write("MAX_SEND_ATTEMPTS Exceeded");     
                
                }                
                 
            }
            */
        }else{
            NeoRTC_Set_Repeating_Minute_Alarm(t_sample);  // Set 1-minute alarm
            Goto_Low_Power_Mode();
        }
    CyDelay(1u);  // Quick Pause to prevent locking
    }
}

//pulls down all pins relatd to mote to save power since we're nousing it
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

//void read_packet(){
//}

/*
void clear_packet(char* packet){
    
    //uint8 i;
    //for(i = 0u; i < packet_size; i++){
    //    packet[i] = 0u;
    //}
    
    memset(packet,0,sizeof(packet));
    packet_ready = 0u;
}
*/
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

/*
void debugLog(const void *pData){
    if(WRITE_DEBUG)
         Write_To_SD_Card("debugLog.txt", "a",  pData, strlen(pData));
}
*/
/* [] END OF FILE */
