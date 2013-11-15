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

#include "solinst_depth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare variables
uint8 uart_solinst_received_string[128];
uint8 uart_solinst_string_index = 0;
SolinstReading reading = {.valid = 0}; // Need to initialize SolinstReading.valid to 0

// prototype modem interrupt
CY_ISR_PROTO(isr_solinst_byte_rx);

// prototype functions
void uart_solinst_string_reset();





// Start the UART
void solinst_start(){
    uart_solinst_Start();
}   

// Stop the UART
void solinst_stop(){
    uart_solinst_Stop();
}         

// Start ISR, Fill array, Return array, Stop ISR
uint8 solinst_get_reading(SolinstReading *reading){

    int i, index;
    uint8 temp[6], depth[7], t;
    uint8 command[6] = {0x00, 0x61, 0xff, 0x18, 0x24, 0x10};
    
    // Reset variables
    uart_solinst_string_reset();
    (*reading).temp = -9999.99;    
    (*reading).depth = -9999.99;
    (*reading).valid = 0u;
    
    // Start the ISR to read the uart
    isr_solinst_byte_rx_StartEx(isr_solinst_byte_rx);
    solinst_power_on();
    CyDelay(100u);
    

    uart_solinst_PutArray(command,6);
    
    CyDelay(1000);
    // Stop the ISR
    isr_solinst_byte_rx_Stop();
    solinst_power_off();
    
    // Get the data
    index = 0;
    for (i = 0; i < sizeof(uart_solinst_received_string); i++) {
        t = uart_solinst_received_string[i];
        
        if ((t >= '0' && t <= '9') || t == '.') {
            temp[index] = t;
            index++;
        }
        else if (t == '+')
            continue;
        else if (t == '-')
            continue;
        else if (t == 'C')
            break;
           
    }
    
    index = 0;
    for (; i < sizeof(uart_solinst_received_string); i++) {
        t = uart_solinst_received_string[i];
        
        if ((t >= '0' && t <= '9') || t == '.') {
            depth[index] = t;
            index++;
        }
        else if (t == '+')
            continue;
        else if (t == '-')
            continue;        
        else if (t == 'm')
            break;
           
    }    

    (*reading).temp = (float)atof(temp);
    (*reading).depth = (float)atof(depth);
    
    if ( (*reading).temp != -9999.99 && (*reading).depth != -9999.99) {
        (*reading).valid = 1u;
    }
    
    return (*reading).valid;
}  

// Provide power to Solinst sensor
uint8 solinst_power_on(){
    solinst_power_pin_Write(0u);
    return 1u;
}

// Cut power to the Solinst sensor
uint8 solinst_power_off(){
    solinst_power_pin_Write(0u);
    return 0u;
}

CY_ISR(isr_solinst_byte_rx){
    // hold the next char in the rx register as a temporary variable
    uint8 rx_char_hold = uart_solinst_GetChar();
    
    // store the char in uart_received_string
    if(rx_char_hold){
        uart_solinst_received_string[uart_solinst_string_index] = rx_char_hold;
        uart_solinst_string_index++;
    }    
}


void uart_solinst_string_reset(){
    // reset uart_received_string to zero
    uint8 i = 0;
    
    for(i = 0; i < 128; i++){
        uart_solinst_received_string[i] = 0;
    }
    uart_solinst_string_index = 0;
    uart_solinst_ClearRxBuffer();
}
/* [] END OF FILE */
