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

#include <stdio.h>
#include <string.h>
#include <device.h>
#include "slre.h"
#include "modem.h"
#include "ultrasonic.h"

// define global variables
#define     MAX_PACKET_SIZE 128
uint8       packet_ready;
uint8       data_packet[MAX_PACKET_SIZE];
uint8       data_packet_size;

// prototype functions
void clear_packet();
void write_packet(uint8* packet, uint8 size);

// prototype interrupt
CY_ISR_PROTO(isr_timer);

void main(){
    // intialize modem
    modem_start();
    // intialize ultrasonic sensor
    ultrasonic_start();
    // intialize timer
    timer_Start();
    isr_timer_StartEx(isr_timer);
    clear_packet();
    packet_ready = 1u;
    // enable global interrupt
    CyGlobalIntEnable;
    
    // ====
    //ultrasonic_read();
    // ====
    
    for(;;){
        if(packet_ready){
            modem_state = modem_get_state();
            if(modem_state == MODEM_STATE_OFF){
                modem_power_on();
            }
            else if(modem_state == MODEM_STATE_IDLE){
                if(!modem_join_network()){  // if modem failed to connect
                    modem_reset();
                    modem_power_off();
                }
            }
            else if(modem_state == MODEM_STATE_READY){
                if(!modem_send_packet(data_packet, data_packet_size)){  // if packet failed to send
                    modem_reset();
                    modem_power_off();
                }
                else{  // if packet successfully sent
                    modem_power_off();
                    clear_packet();
                }
            }
        }
    }
}

CY_ISR(isr_timer){
    write_packet("PSoC\032", 5u);
    timer_ReadStatusRegister();
}

void clear_packet(){
    uint8 i;
    for(i = 0u; i < MAX_PACKET_SIZE; i++){
        data_packet[i] = 0;
    }
    packet_ready = 0u;
    data_packet_size = 0u;
}

void write_packet(uint8* packet, uint8 size){
    uint8 i;
    for(i = 0u; i < size; i++){
        data_packet[i] = packet[i];
    }
    packet_ready = 1u; 
    data_packet_size = size;
}

/* [] END OF FILE */
