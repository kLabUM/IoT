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
#include <stdlib.h> 
#include <string.h>
#include "modem.h"

uint8   packet_get_value(char* packet, char* name, char* value);
uint8   packet_get_uint8(char* packet, char* name, uint8* value);
uint8   packet_get_uint32(char* packet, char* name, uint32* value);
uint8   clear_packet(char* packet);

//[] END OF FILE