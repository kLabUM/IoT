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
#include <stdlib.h>
#include <string.h>
#include "uart_ultrasonic.h"

#define MAX_STRING_LENGTH       128
#define DEPTH_STRING_LENGTH     4

typedef struct{
    float temp;
    float depth;
    uint8 valid;
} UltrasonicReading;

void  ultrasonic_start();
void ultrasonic_stop();
uint8 ultrasonic_power_on();
uint8 ultrasonic_power_off();
uint8 ultrasonic_get_reading(UltrasonicReading* reading);


//[] END OF FILE