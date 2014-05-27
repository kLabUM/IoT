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
#include "debug.h"

// Declare variables
uint8 uart_solinst_received_string[MAX_STRING_LENGTH];
uint8 uart_solinst_string_index = 0;

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

// Provide power to Solinst sensor
uint8 solinst_power_on(){
    ControlReg_Solinst_Write(1u);
    solinst_power_pin_Write(0u);
    return 1u;
}

// Cut power to the Solinst sensor
uint8 solinst_power_off(){
    solinst_power_pin_Write(1u);
    ControlReg_Solinst_Write(0u);
    return 0u;
}

// Start ISR, Fill array, Return array, Stop ISR
uint8 solinst_get_reading(SolinstReading *reading){

    int i, index;
    int temp_sign = 1, depth_sign = 1;
    uint8 temp[TEMP_STRING_LENGTH], depth[DEPTH_STRING_LENGTH], t;
    uint8 valid = 0;
    uint8 command[6] = {0x00, 0x61, 0xff, 0x18, 0x24, 0x10};
    
    // Reset variables
    (*reading).valid = 0u;
    (*reading).temp = -9999;    // Do not use -9999.99.. (inaccurate double representation)
    (*reading).depth = -9999;
    uart_solinst_string_reset();
    
    // Start the ISR to read the uart
    isr_solinst_byte_rx_StartEx(isr_solinst_byte_rx);
    solinst_power_on();
    CyDelay(100u);
    
    // Write the command to the sensor
    uart_solinst_PutArray(command,6);
    CyDelay(1000);
    
    // Stop the ISR
    isr_solinst_byte_rx_Stop();
    solinst_power_off();
    
    // Process the data
    index = 0;
    for (i = 0; i < sizeof(uart_solinst_received_string); i++) {
        t = uart_solinst_received_string[i];
        
        if ((t >= '0' && t <= '9') || t == '.') {
            temp[index] = t;
            index++;
        }
        else if (t == '+')
            continue;
        else if (t == '-') {
            temp_sign = -1;
        }
        else if (t == 'C') {
            valid = 1u;
            break;
        }
    }
    /*
    if (!valid) {
        debug_write("Solinst Invalid Temperature Reading.");
    }
    */
    index = 0;
    for (; i < strlen(uart_solinst_received_string); i++) {
        t = uart_solinst_received_string[i];
        
        if ((t >= '0' && t <= '9') || t == '.') {
            depth[index] = t;
            index++;
        }
        else if (t == '+')
            continue;
        else if (t == '-') {
            depth_sign = -1;  
        }
        else if (t == 'm') {
            (*reading).valid = 1u & valid;
            break;
        }
           
    }    
    /*
    (*reading).temp = (float)temp_sign * (float)atof(temp);
    (*reading).depth = (float)depth_sign * (float)atof(depth);
    
    
    if ( (*reading).temp != -9999 && (*reading).depth != -9999) {
        (*reading).valid = 1u;
    }
    */
    
    if ((*reading).valid) {
        (*reading).temp = (float)temp_sign * (float)atof(temp);
        (*reading).depth = (float)depth_sign * (float)atof(depth);
    }    
    else{
        debug_write("Solinst Invalid Temperature and/or Depth Reading.");
        debug_write(uart_solinst_received_string);
    }
    
    return (*reading).valid;
}  


CY_ISR(isr_solinst_byte_rx){
    // hold the next char in the rx register as a temporary variable
    uint8 rx_char_hold = uart_solinst_GetChar();
    
    // store the char in uart_received_string
    if(rx_char_hold && uart_solinst_string_index < MAX_STRING_LENGTH){
        uart_solinst_received_string[uart_solinst_string_index] = rx_char_hold;
        uart_solinst_string_index++;
    }    
}


void uart_solinst_string_reset(){
    // reset uart_received_string to zero
    uint8 i = 0;
    
    for(i = 0; i < MAX_STRING_LENGTH; i++){
        uart_solinst_received_string[i] = 0;
    }
    uart_solinst_string_index = 0;
    uart_solinst_ClearRxBuffer();
}
/* [] END OF FILE */
