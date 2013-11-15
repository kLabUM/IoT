///* ========================================
// *
// * Copyright YOUR COMPANY, THE YEAR
// * All Rights Reserved
// * UNPUBLISHED, LICENSED SOFTWARE.
// *
// * CONFIDENTIAL AND PROPRIETARY INFORMATION
// * WHICH IS THE PROPERTY OF your company.
// *
// * ========================================
//*/
//

#include <device.h>
#include <string.h>
#include "modem.h"

uint8 uart_received_string[128];
uint8 uart_string_index = 0;

CY_ISR_PROTO(isr_byte_rx);

void uart_string_reset();
void at_command_write(uint8 uart_string, uint8 uart_timeout);

uint8 modem_get_state(){
    return modem_state;
}

void modem_start(){
    uart_Start();
    isr_byte_rx_StartEx(isr_byte_rx);
    modem_state = MODEM_STATE_OFF;
}

uint8 at_write_command(uint8* uart_string, uint8* expected_response, uint32 uart_timeout){
    uint8 response = 0u;
    uint32 i = 0u;
    uint32 delay = 100u;
    uint32 interval = uart_timeout/delay;
    
    uart_string_reset();
    uart_PutString(uart_string);
    
    if(expected_response != ""){
        for(i=0;i<interval;i++){
            uint16 valid = strstr ( uart_received_string, expected_response );
            if(valid != NULL){
                response = 1u;
                break;
            }
        CyDelay(delay);
        }
    }
    return response;
}

uint8 modem_reset(){
    if(at_write_command("AT#MODE=RESET\r","OK",10000u)){
        return 1u;
    }
    return 0u;
}

uint8 modem_join_network(){
   uint8 isResgister, isConfigPar, isIP = 255;
   isResgister = at_write_command("AT+CREG=1\r","OK",5000u);
    if(isResgister != 0){
        isConfigPar = at_write_command("AT#SCFG=1,1,0,0,1200,0\r","OK",5000u);
        if(isConfigPar != 0){
            isIP = at_write_command("AT+CSQ\r","OK",20000u);
            isIP = at_write_command("AT#SGACT=1,1\r","OK",40000u);
            if(isIP != 0){
                modem_state = MODEM_STATE_READY;
                return 1u;   // return 1 if succesfully connected
            }
        }
    }
    return 0u;   // return 0 if failure to connect
}

uint8 modem_send_packet(uint8* packet, uint8 size){
    if(at_write_command("AT#SD=1,0,50321,\"50.19.242.87\",0,0,1\r","OK",15000u) != 0){
        if(at_write_command("AT#SSEND=1\r",">",5000u) != 0){
            if(at_write_command(packet,"OK",20000u) != 0){
                modem_state = MODEM_STATE_READY;
                return 1u;   // return 1 if succesfully sent packet
            }
        }
    }
    return 0u;   // return 0 if failure to send packet
}

uint8 modem_power_on(){
    modem_voltage_pin_Write(0u); //provide power to modem
    modem_power_pin_Write(0u);
    CyDelay(1500u);
    modem_power_pin_Write(1u);
    CyDelay(5000u); // wait for module to turn on
    modem_state = MODEM_STATE_IDLE;
}

uint8 modem_power_off(){
    modem_power_pin_Write(0u);
    CyDelay(1500u);
    modem_power_pin_Write(1u);
    CyDelay(5000u); // wait for module to turn off
    modem_voltage_pin_Write(1u); // cut power to modem
    modem_state = MODEM_STATE_OFF;
}

void uart_string_reset(){
    // reset uart_received_string to zero
    uint8 i = 0;
    
    for(i = 0; i < 128; i++){
        uart_received_string[i] = 0;
    }
    uart_string_index = 0;
    uart_ClearRxBuffer();
}

CY_ISR(isr_byte_rx){
    // hold the next char in the rx register as a temporary variable
    uint8 rx_char_hold = uart_GetChar();
    
    // store the char in uart_received_string
    if(rx_char_hold){
        uart_received_string[uart_string_index] = rx_char_hold;
        uart_string_index++;
    }
}

///* [] END OF FILE */
//