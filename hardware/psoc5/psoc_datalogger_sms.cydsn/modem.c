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
#include "debug.h"

// declare varaiables
uint8 modem_state, lock_acquired = 0;
uint16 uart_string_index = 0;
uint32 feed_id;
char uart_received_string[700] = {0}, *api_key;



// prototype modem interrupt
CY_ISR_PROTO(isr_byte_rx);
void uart_string_reset();

uint8 modem_set_api_feed(uint32 id, char* key){
    feed_id = id;
    api_key = key;
    return 1u;
}

// initialize modem
void modem_start(){
    uart_Start();
    ControlReg_Modem_Write(0u);
    modem_power_pin_Write(0u);
    isr_byte_rx_StartEx(isr_byte_rx);
    modem_state = MODEM_STATE_OFF;
}

// send at-command to modem
uint8 at_write_command(char* uart_string, char* expected_response, uint32 uart_timeout){
    uint8 response = 0u;
    uint32 i = 0u, delay = 100u, interval = uart_timeout/delay;
    
    uart_string_reset();
    uart_PutString(uart_string);
    
    if( strcmp(expected_response, "") != 0){
        for(i=0;i<interval;i++){
            char* valid = strstr(uart_received_string, expected_response);
            if(valid != NULL){
                response = 1u;
                break;
            }
            CyDelay(delay);
        }
    }
    
    return response;
}

uint8 modem_power_on(){
    modem_power_pin_Write(1u);
    modem_reset_pin_Write(1u);
    modem_voltage_pin_Write(0u); //provide power to modem
    ControlReg_Modem_Write(1u);
    modem_power_pin_Write(0u);
    CyDelay(2000u);  // the pad ON# must be tied low for at least 1 second and then released.
    modem_power_pin_Write(1u);
    CyDelay(10000u);  
    /* changed from CyDelay(5000u);?
        "To get the desirable stability, 
        CC864-DUAL needs at least 10 seconds 
        after the PWRMON goes HIGH.*/
    modem_state = MODEM_STATE_IDLE;
    return modem_state;
}

uint8 modem_power_off(){
    modem_power_pin_Write(0u);
    CyDelay(2500u);  // To turn the CC864-DUAL off, the ON/OFF Pin must be tied low for 2 second and then released.
    modem_power_pin_Write(1u);
    CyDelay(5000u); 
    /* CyDelay(5000u); // wait for module to turn off
        "Normally it will be above 10 seconds later from releasing
        ON/OFF# and DTE should monitor the status of PWRMON to see the
        actual power off."  */
    ControlReg_Modem_Write(0u);
    modem_voltage_pin_Write(1u); // cut power to modem
    modem_power_pin_Write(0u); //kill modem power pin as well
    modem_reset_pin_Write(0u);
    modem_state = MODEM_STATE_OFF;
    return modem_state;
}

uint8 modem_reset(){
    if (modem_state != MODEM_STATE_OFF) { // The modem is idle/ready (powered on)
        //modem_reset_pin_Write(0u); //provide power to modem
        modem_reset_pin_Write(0u);
        CyDelay(500u);  // To reset and to reboot the module, 
                         // the RESET pin must be tied low for at least 200 milliseconds and then released.
        modem_reset_pin_Write(1u);
        //CyDelay(5000u);
        CyDelay(10000u);
        modem_state = MODEM_STATE_IDLE;
    }
    return modem_state;
}

uint8 modem_connect(){
    if(at_write_command("AT#SGACT=1,1\r","OK",15000u) == 1){
        modem_state = MODEM_STATE_READY;
        //return 1u; // connected to network
    }
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");

    return modem_state;
    
/*
    if(at_write_command("AT+CREG=1\r","OK",5000u)){
        if(at_write_command("AT+CREG?\r","OK",5000u)){
        //if(!at_write_command("AT#CGPADDR=1\r","\"",5000u)){
            if(at_write_command("AT#SGACT=1,1\r","OK",30000u)){
                modem_state = MODEM_STATE_READY;
                //return 1u; // connected to network
            }
            else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
        }
       else debug_write("(AT#CGPADDR=1) No IP Address Exists.");   Returns IP address.. should be called after SGACT=1,1
    }
    else debug_write("(AT+CREG=1) Could not register to network."); CREG reports registration status of the device, does not set it
    
    return 0u;
*/
/*
    at_write_command("AT+CSQ\r","OK",5000u); // get signal strength
    
    if (!at_write_command("AT+CREG=1\r","OK",5000u)) { // look for network
        debug_write("(AT+CREG=1) Could not register to network.");
    }
    
    at_write_command("AT#SCFG=1,1,0,0,1200,0\r","OK",5000u); // config parameter
    
    if (at_write_command("AT#CGPADDR=1\r","OK",5000u)) {// check if ip address exists
        debug_write("(AT#CGPADDR=1) No IP Address Exists.");    
    }
    
    at_write_command("AT#SGACT?","OK",30000u);
    
    uint8 success  = at_write_command("AT#SGACT=1,1\r","OK",30000u); // This command should return an ip address but the modem seem to freeze after this
    //success = at_write_command("AT#SD=1,0,50000,\"141.212.136.222\",0,0,1\r","OK",5000u); // connect to server
    
    if (!success) {
        debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    }
    
    return success;
    */
    
}

uint8 modem_disconnect(){
    // Proceed if modem is not connected to network.  Otherwise, try to disconnect from the network and proceed.
    if(modem_state != MODEM_STATE_READY) {
        if(at_write_command("AT#SH=1","OK",10000u) == 1){
            if(at_write_command("AT#SGACT=1,0","OK",10000u) == 1){
                modem_state = MODEM_STATE_IDLE;
                //return 1u;
            }
            else {
                debug_write("(AT#SGACT=1,0) Could not disconnect.");
            }
        }
        else {
            debug_write("(AT#SH=1) Could not close socket.");
        }
    }
    else {
        if (modem_state == MODEM_STATE_OFF) {
            debug_write( "(modem_state != MODEM_STATE_READY) modem_state = MODEM_STATE_OFF" );
        }
        else if (modem_state == MODEM_STATE_IDLE) {
            debug_write( "(modem_state != MODEM_STATE_READY) modem_state = MODEM_STATE_IDLE" );
        }
    }
    return modem_state; 
    //return 0u; // failed to disconnect
}

// send packet to Xively server
uint8 modem_send_packet(char* packet){

    
    /*
    // provide power to rx and tx pins
    //uart_rx_voltage_pin_Write(0u);
    //uart_tx_voltage_pin_Write(0u);
    
    // join network
    uint8 connected = modem_connect();
    */
    uint8 attempts = 0;
    
    for(attempts = 0; attempts < MAX_SEND_ATTEMPTS; attempts++) {
        
        // Proceed if modem is already connected.  Otherwise, try to join the network and proceed
        if( modem_state == MODEM_STATE_READY || modem_connect() != 0){ 
            // write to AWS server  - 184.72.228.61\",0,0,1
            //if(at_write_command("AT#SD=1,0,50030,\"184.72.228.61\",0,0,1\r","OK",5000u) != 0){
            if(at_write_command("AT#SD=1,0,8081,\"api.xively.com\",0,0,1\r","OK",10000u) != 0){
                if(at_write_command("AT#SSEND=1\r",">",10000u) != 0){
                    //if(at_write_command(packet,"OK",20000u) != 0){
                    char sendBuffer[750];
                    sprintf(sendBuffer, "%s\032", packet);
                    if(at_write_command(sendBuffer,"OK",15000u) != 0){
                        modem_state = MODEM_STATE_IDLE;
                        CyDelay(1000u); //debug_write("Packet sent successfully.");
                        return 1u;   // return 1 if succesfully sent sms
                    }
                    else {
                        debug_write("(at_write_command(sendBuffer,\"OK\"...) Data sent unsuccessfully.");
                    }
                }
                else {
                    debug_write("(AT#SSEND=1) Could not send data through connected socket.");
                }
            }
            else {
                debug_write("(AT#SD=1,0,8081,\"api.xively.com\",0,0,1\r) Could not connect to server.");
            }
        }
    
        if (attempts < MAX_SEND_ATTEMPTS-1) { // Don't reset the modem on the last attempt since it will be getting disconnected
            modem_reset();
        }
        
    }    
    
    // cut power to rx and tx pins
    //uart_rx_voltage_pin_Write(1u);
    //uart_rx_voltage_pin_Write(1u);
    debug_write("MAX_SEND_ATTEMPTS Exceeded.");
    modem_disconnect();
    return 0u;   // return 0 if failure to send sms
}


// read packet from Xively server
uint8 modem_get_packet(char* packet, char* csv){
    
    /*
    // provide power to rx and tx pins
    //uart_rx_voltage_pin_Write(0u);
    //uart_tx_voltage_pin_Write(0u);    
    
    // join network
    uint8 connected = modem_connect();
    */
    char get_str[200], key_str[100];
    uint8 attempts = 0;
    
    if (strlen(csv) > 125) {
        debug_write("modem_get_packet(): csv length > 100");
        return 0u;
    }
            
    for(attempts = 0; attempts < MAX_GET_ATTEMPTS; attempts++) {
        // Proceed if modem is already connected.  Otherwise, try to join the network and proceed
        if( modem_state == MODEM_STATE_READY || modem_connect() != 0 ){ 
            // write to AWS server  - 184.72.228.61\",0,0,1
            //if(at_write_command("AT#SD=1,0,50030,\"184.72.228.61\",0,0,1\r","OK",5000u) != 0){
            if(at_write_command("AT#SD=1,0,80,\"api.xively.com\",0,0,1\r","OK",10000u) != 0){
                if(at_write_command("AT#SSEND=1\r",">",10000u) != 0){
                    
                    sprintf(get_str,"GET /v2/feeds/%lu.csv?datastreams=%s HTTP/1.0\r\n", feed_id, csv);
                    sprintf(key_str,"X-ApiKey: %s\r\n\r\n", api_key);
                    
                    uart_string_reset();
                    at_write_command(get_str,">",10000u);// CyDelay(500u);
                    at_write_command("Host: api.xively.com\r\n",">",10000u);// CyDelay(500u);
                    at_write_command("Accept: text/csv\r\n",">",10000u);// CyDelay(500u);
                    at_write_command(key_str,">",10000u);// CyDelay(500u);
                    
                    // Successfully Sent AT-Commands for GET Request
                    if(at_write_command("\032\r","OK",15000u) != 0){
                    
                        // Read GET response from the buffer
                        uart_string_reset();
                        CyDelay(5000u);
                        at_write_command("AT#SRECV=1,700\r","OK",15000u);
                        //strcpy(packet, uart_received_string);
                        strcpy(packet, strstr(uart_received_string, "\r\n\r\n")+strlen("\r\n\r\n"));
                        
                        CyDelay(1000u); //debug_write("Packet received successfully.");
                        return 1u;   // return 1 if succesfully sent sms

                    }
                    else {
                        debug_write("(at_write_command(sendBuffer,\"OK\"...) Data sent unsuccessfully.");
                    }
                }
                else {
                    debug_write("(AT#SSEND=1) Could not send data through connected socket.");
                }
                //uint8 disconnected = modem_disconnect();
            }
            else {
                debug_write("(AT#SD=1,0,80,\"api.xively.com\",0,0,1) Could not connect to server.");
            }
        }
        
        if (attempts < MAX_GET_ATTEMPTS-1) { // Don't reset the modem on the last attempt since it will be getting disconnected
            modem_reset();
        }
        
    }
    // cut power to rx and tx pins
    //uart_rx_voltage_pin_Write(1u);
    //uart_rx_voltage_pin_Write(1u);
    debug_write("MAX_GET_ATTEMPTS Exceeded.");
    modem_disconnect();
    return 0u;   // return 0 if failure to send sms
}

uint8 modem_acquire_lock(){
    return 1u;
}

uint8 modem_release_lock(){
    return 1u;
}

void uart_string_reset(){
    // reset uart_received_string to zero
    /*
    uint16 i = 0;
    
    for(i = 0; i < 700; i++){
        uart_received_string[i] = 0;
    }
    */
    memset(&uart_received_string[0],0,sizeof(uart_received_string));
    uart_string_index = 0;
    uart_ClearRxBuffer();
//    uart_ClearTxBuffer();
}

// this function fires when uart rx receives bytes (when modem is sending bytes)
CY_ISR(isr_byte_rx){
    while (uart_GetRxBufferSize()){
        // hold the next char in the rx register as a temporary variable
        char rx_char_hold = uart_GetChar();
        
        // store the char in uart_received_string
        if(rx_char_hold){
            uart_received_string[uart_string_index] = rx_char_hold;
            uart_string_index++;
        }
    }
}

///* [] END OF FILE */
//