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
//[] END OF FILE
#include <device.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FS.h>
#include "neomote.h"

#define MAX_DEBUG_LENGTH 256

uint8 debug_on();
uint8 debug_off();
uint8 debug_is_on();
void debug_write(const void *pData);
void Write_Debug_To_SD_Card(const char* fileName, const char* pMode, const void* pData, U32 NumBytes);
void clear_debug_packet();