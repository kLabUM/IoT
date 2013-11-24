/* M2M SMS Datalogger */ 

#include <device.h>
#include <stdio.h>
#include <string.h>
#include <FS.h>
#include "neomote.h"
#include "sleep.h"
#include "modem.h"
#include "ultrasonic.h"
#include "solinst_depth.h"

// define global variables
#define MAX_SEND_ATTEMPTS 2
#define MAX_PACKET_SIZE 128
#define WRITE_DEBUG 1
uint8   data_packet[MAX_PACKET_SIZE], debug_packet[MAX_PACKET_SIZE];
uint8   packet_ready;
uint8   take_reading;
uint8   send_attempts;

UltrasonicReading ultrasonic_reading = {.valid = 0};    // Initialize UltrasonicReading.valid to 0
SolinstReading solinst_reading = {.valid = 0};          // Initialize SolinstReading.valid to 0

// callback definitions
void rtcCallBackReceived(uint8 alarmType);

// prototype functions
void read_packet(uint8* packet, uint8 size);
void write_packet(uint8* dest, uint8* src_ultrasonic, uint8* src_pressure, uint8 size);
void clear_packet(uint8* packet, uint8 size);
void Write_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes);
CY_ISR_PROTO(isr_timer);
void Goto_Low_Power_Mode();
void debugLog(const void *pData);


void main(){



    CyGlobalIntEnable;
     SleepTimer_Start();
    isr_SleepTimer_StartEx(sleepTimerWake_INT);
    FS_Init();
    modem_start();
    //modem_power_off();
    ultrasonic_start();
    solinst_start();

    
    packet_ready = 0u; 
    take_reading = 0u;
    send_attempts = 0u;

    NeoRTC_Start(rtcCallBackReceived);      // Start and enable the RTC.   
    NeoRTC_Set_Repeating_Minute_Alarm(2u);  // Set 1-minute alarm
   
    
    //  Uncomment below to set RTC
    /*
    NeoRtcTimeStruct tm = {
      .second = 0,
      .minute = 58,
      .hour = 20,
      .day = 20,
      .weekday = 4,
      .month = 11,
      .year = 2013,
    } ;
    RTC_WriteTime(tm); //sets time
    */

    for(;;){
        // No need to pause for short time in loop?
        RTC_Process_Tasks();
       
        
        if(take_reading){ 
            
            take_reading = 0u;
            
            if (send_attempts > 0) {
                debug_write("New reading taken before previous packet was sent");
            }
            
            // Get Readings for:
            // depth, pressure, temp
            // conductivity.
            solinst_get_reading(&solinst_reading);
            ultrasonic_get_reading(&ultrasonic_reading);
            
            NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();

            sprintf(data_packet, "\r\n%d:%d:%d %d/%d/%d -- u_d=%f s_d=%f s_t=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, 
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp);
            
            Write_To_SD_Card("data.txt","a",data_packet,strlen(data_packet));

            sprintf(data_packet, "%d:%d:%d %d/%d/%d -- u_d=%f s_d=%f s_t=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, 
                             ultrasonic_reading.depth, solinst_reading.depth, solinst_reading.temp);
            
            packet_ready = 1u; 
            send_attempts = 0u;
            
            
        } else if(packet_ready){
            isr_SleepTimer_Stop;
            if(modem_state == MODEM_STATE_OFF){
                modem_power_on();
            }
            else if(modem_state == MODEM_STATE_IDLE){
                
                /*
                //if(modem_send_packet(data_packet)){     // if packet sent
                if(modem_send_packet(data_packet)){     // if packet sent
                    modem_power_off();
                    clear_packet(data_packet, MAX_PACKET_SIZE);
                }
                else{                                   // if packet not sent
                    modem_reset();
                    modem_power_off();
                }
                */
                if(send_attempts < MAX_SEND_ATTEMPTS){
                    
                    send_attempts++;
                    
                    if (modem_send_packet(data_packet)){     
                    // the packet is sent within the number of maximum attempts allowed
                        modem_power_off();
                        clear_packet(data_packet, MAX_PACKET_SIZE);
                        send_attempts = 0u;
                    }
                    else {
                        //modem_reset();
                    }
                    
                } 
                else {
                // the number of maximum attempts allowed has been exceeded
                    modem_power_off();
                    clear_packet(data_packet, MAX_PACKET_SIZE);
                    send_attempts = 0u;
                    debug_write("MAX_SEND_ATTEMPTS Exceeded");                    
                }                
                 
            }
        }else{
            Goto_Low_Power_Mode();
        }
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


void clear_packet(uint8* packet, uint8 packet_size){
    uint8 i;
    for(i = 0u; i < packet_size; i++){
        packet[i] = 0u;
    }
    
    packet_ready = 0u;
}

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
