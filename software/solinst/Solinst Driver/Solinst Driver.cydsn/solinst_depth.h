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
#include "uart_solinst.h"

typedef struct{
    float temp;
    float depth;
    uint8 valid;
} SolinstReading;

void    solinst_start();        // Start the UART
void    solinst_stop();         // Stop the UART
uint8   solinst_get_reading(SolinstReading *reading);  // Start ISR, Fill array, Return array, Stop ISR
uint8   solinst_power_on();     // Provide power to Solinst sensor
uint8   solinst_power_off();    // Cut power to the Solinst sensor


//[] END OF FILE
