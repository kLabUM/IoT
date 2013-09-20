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
#include "ultrasonic.h"

CY_ISR_PROTO(isr_byte_ultrasonic_rx);

void ultrasonic_start(){
    ultrasonic_uart_Start();
    //isr_byte_ultrasonic_rx_StartEx(isr_byte_ultrasonic_rx);
}

uint8 ultrasonic_read(){
    uint8 ultrasonic_uart_received_string[128];
    uint8 ultrasonic_uart_return_string[16];
    uint8 i, j, r_count, rx_char;
    
    // provide power to start the sensing
    ultrasonic_voltage_pin_Write(0u); 
    CyDelay(250u);
    
    // store stream of characters in ultrasonic_uart_received_string
    for(i = 0;i < 128;){
        rx_char = ultrasonic_uart_GetChar();
        
        if(rx_char){
            ultrasonic_uart_received_string[i] = rx_char;
            i++;
        }
    }
    
    // initialize ultrasonic_uart_return_string to zero
    for(i = 0;i < sizeof(ultrasonic_uart_return_string);i++){
        ultrasonic_uart_return_string[i] = 0u;
    }
    
    // get reading from stream and store in ultrasonic_uart_return_string
    for(r_count = 0, i = 0, j = 0;r_count < 2;i++){
        rx_char = ultrasonic_uart_received_string[i];
        if(rx_char == 82u){
            r_count++;      // increment everytime an "R" ascii character is encountered
        }
        if(r_count > 0){    // 
            ultrasonic_uart_return_string[j] = ultrasonic_uart_received_string[i];
            j++;
        }
        if(i > 126 || j > 14){
            return 0u; 
        }
    }
    
    ultrasonic_voltage_pin_Write(0u); // cut power to stop the sensing
    return ultrasonic_uart_return_string;
}

CY_ISR(isr_byte_ultrasonic_rx){
    // hold the next char in the rx register as a temporary variable
    uint8 rx_char_hold = ultrasonic_uart_GetChar();
    uint8 rx_char_hold2 = ultrasonic_uart_GetByte();
    uint8 rx_char_hold3 = ultrasonic_uart_ReadRxData();
    ultrasonic_uart_ClearRxBuffer();
}

/* [] END OF FILE */
