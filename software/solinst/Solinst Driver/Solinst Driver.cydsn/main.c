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
#include <stdio.h>
#include <string.h>
#include <FS.h>
#include "neomote.h"
#include "solinst_depth.h"
#include "ultrasonic.h"

void rtcCallBackReceived(uint8 alarmType);
void Write_To_SD_Card(const char * fileName, const char * pMode, 
                                const void * pData, U32 NumBytes);

#define MAX_PACKET_SIZE 128
uint8   data_packet[MAX_PACKET_SIZE];
SolinstReading solinst_reading = {.valid = 0};          // Initialize SolinstReading.valid to 0
UltrasonicReading ultrasonic_reading = {.valid = 0};    // Initialize UltrasonicReading.valid to 0

void main()
{
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    solinst_start();
    ultrasonic_start();
    
    NeoRTC_Start(rtcCallBackReceived); // Start and enable the RTC
    NeoRTC_Set_Repeating_Minute_Alarm(1u);
    NeoRTC_Enble_Second_Interrupt();
    
    FS_Init(); // Start the File System
       
    for(;;)
    {
        //RTC_Process_Tasks();
        
        //SolinstReading reading;
        solinst_get_reading(&solinst_reading);
        /*
        ultrasonic_get_reading(&ultrasonic_reading);
        //sprintf(data_packet,"\r\n%s","MAX_SEND_ATTEMPTS EXCEEDED");
        //Write_To_SD_Card("debug.txt","a",data_packet,strlen(data_packet));
        if (debug_is_on()) {
            debug_off();
            debug_write("off");
        } else {
            debug_on();
            debug_write("on");
        }
        */
        CyDelay(5000u);
        
    }
}

void Write_To_SD_Card(const char * fileName, const char * pMode, 
                                const void * pData, U32 NumBytes){

	NEOMOTE_1_SD_Card_Power_Write(0u); // Power on SD Card
    
	FS_FILE * pFile;
	char sdVolName[10]; // Buffer that will hold SD card volume name.
   
	if(0 != FS_GetVolumeName(0, &sdVolName[0], 9)){
		pFile = FS_FOpen(fileName, pMode);
		if (pFile == 0){ // If the SD card doesn't open.
			FS_DeInit();        
			FS_Init();
			pFile = FS_FOpen(fileName, pMode);
		}
		FS_Write(pFile, pData, NumBytes);
		FS_FClose(pFile);
       }
	NEOMOTE_1_SD_Card_Power_Write(1u); // Power off SD Card.
}


void rtcCallBackReceived(uint8 alarmType){ // RTC Event Handler.
    /*
    if(alarmType == RTC_SECOND_ALARM){
        
    }else */
    if(alarmType == RTC_MINUTE_ALARM){
        
        solinst_get_reading(&solinst_reading);
        ultrasonic_get_reading(&ultrasonic_reading);
        
        NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();
        sprintf(data_packet, "\r\n%d:%d:%d %d/%d/%d s_d=%f s_t=%f u_d=%f", 
                        tm_neo.hour, tm_neo.minute, tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, 
                        solinst_reading.depth, solinst_reading.temp, ultrasonic_reading.depth);
        
        Write_To_SD_Card("myData.txt","a",data_packet,strlen(data_packet));
    }
}


/* [] END OF FILE */
