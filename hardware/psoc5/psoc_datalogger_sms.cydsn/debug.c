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
#include "debug.h"
#include "neomote.h"

uint8 write_to_log = 1u;
char debug_packet[MAX_DEBUG_LENGTH];
char* debug_file = "debuglog.txt";

uint8 debug_on() {
    //FS_Init() command needed?
    return write_to_log = 1u;    
}

uint8 debug_off() {
    return write_to_log = 0u;    
}

uint8 debug_is_on() {
    return write_to_log;    
}

void debug_write(const void *pData){
    if(write_to_log) {
/*
        uint8 i;
        for(i = 0u; i < MAX_DEBUG_LENGTH; i++){
            debug_packet[i] = 0u;
        }
*/
        NeoRtcTimeStruct tm_neo = NeoRTC_Read_Time();

        sprintf((char*) &debug_packet[0], "\r\n%d:%d:%d %d/%d/%d -- [ID %d] %s", tm_neo.hour, tm_neo.minute,
                         tm_neo.second, tm_neo.day, tm_neo.month, tm_neo.year, 
                         moteID, (const char*) pData);
                         
        Write_Debug_To_SD_Card((const char*) debug_file, "a",  debug_packet, strlen(debug_packet));
    }
}

void Write_Debug_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes) {
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

void clear_debug_packet() {
/*
    uint8 i;
    for(i = 0u; i < MAX_DEBUG_LENGTH; i++){
        debug_packet[i] = 0u;
    }
*/
    memset(&debug_packet[0],0,sizeof(debug_packet));
}


/* [] END OF FILE */