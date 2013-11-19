/* M2M SMS Datalogger */ 

#include <device.h>
#include <stdio.h>
#include <string.h>
#include <FS.h>
#include "neomote.h"
#include "sleep.h"
#include "modem.h"
#include "ultrasonic.h"
//#include "solinst_depth.h"

// define global variables
#define MAX_PACKET_SIZE 128
uint8   data_packet[MAX_PACKET_SIZE];
uint8   packet_ready;
uint8   take_reading;
UltrasonicReading ultrasonic_reading = {.valid = 0};    // Initialize UltrasonicReading.valid to 0
//SolinstReading solinst_reading = {.valid = 0};          // Initialize SolinstReading.valid to 0

// callback definitions
void rtcCallBackReceived(uint8 alarmType);

// prototype functions
void read_packet(uint8* packet, uint8 size);
void write_packet(uint8* dest, uint8* src_ultrasonic, uint8* src_pressure, uint8 size);
void clear_packet(uint8* packet, uint8 size);
void Write_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes);
CY_ISR_PROTO(isr_timer);

void main(){
   
    
    //timer_Start();
    //isr_timer_StartEx(isr_timer);
     SleepTimer_Start();
    modem_start();
    CyGlobalIntEnable;
    FS_Init();
    ultrasonic_start();
    //solinst_start();

    packet_ready = 0u; 
    take_reading = 1u;

    NeoRTC_Start(rtcCallBackReceived);      // Start and enable the RTC.   
    NeoRTC_Set_Repeating_Minute_Alarm(1u);  // Set 1-minute alarm
    
    for(;;){
        // No need to pause for short time in loop?
        RTC_Process_Tasks();
        
        if(packet_ready){
            if(modem_state == MODEM_STATE_OFF){
                modem_power_on();
            }
            else if(modem_state == MODEM_STATE_IDLE){
                //if(modem_send_packet(data_packet)){     // if packet sent
                if(modem_send_packet(data_packet)){     // if packet sent
                    modem_power_off();
                    clear_packet(data_packet, MAX_PACKET_SIZE);
                }
                else{                                   // if packet not sent
                    modem_reset();
                    modem_power_off();
                }
            }
        }else if(take_reading){
        
            // Get Readings for:
            // depth, pressure, temp
            // conductivity.
            //solinst_get_reading(&solinst_reading);
            ultrasonic_get_reading(&ultrasonic_reading);

            take_reading = 0u;
            NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();
            char sendBuffer [128];

            sprintf(data_packet, "%d:%d:%d %d/%d/%d u=%f", tm_neo.hour, tm_neo.minute,
                             tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, ultrasonic_reading.depth);
            
            Write_To_SD_Card("data.txt","a",data_packet,strlen(data_packet));

            
            packet_ready = 1u; 
            
        }
    }
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

/* [] END OF FILE */
