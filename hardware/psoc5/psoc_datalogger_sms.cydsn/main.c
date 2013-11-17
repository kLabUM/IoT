/* M2M SMS Datalogger */ 

#include <stdio.h>
#include <string.h>
#include <device.h>
#include "modem.h"
#include "ultrasonic.h"
#include "sleep.h"

// define global variables
#define MAX_PACKET_SIZE 128
uint8   sensor_ready;
uint8   packet_ready;
uint8   data_packet[MAX_PACKET_SIZE];

// prototype functions
void read_packet(uint8* packet, uint8 size);
void write_packet(uint8* dest, uint8* src_ultrasonic, uint8* src_pressure, uint8 size);
void clear_packet(uint8* packet, uint8 size);
CY_ISR_PROTO(isr_timer);

void main(){
   
    ultrasonic_start();
    timer_Start();
    isr_timer_StartEx(isr_timer);
    SleepTimer_Start();
    modem_start();
    CyGlobalIntEnable;
    
    packet_ready = 1u; // temporary hack
    
//    // get ultrasonic_packet
//    uint8 ultrasonic_packet[MAX_PACKET_SIZE];
//    ultrasonic_read(ultrasonic_packet, MAX_PACKET_SIZE);
//    // write packet
//    write_packet(data_packet, ultrasonic_packet, ultrasonic_packet, MAX_PACKET_SIZE);
//    CyDelay(2000u);
//    CyDelay(2000u);
//    CyDelay(2000u);
//    
//    while(1){
//        CyDelay(2000u);
//    }
    
    int i;
    for(i = 0; i < 3; i++){
        if(packet_ready){
            if(modem_state == MODEM_STATE_OFF){
                modem_power_on();
            }
            else if(modem_state == MODEM_STATE_IDLE){
                //if(modem_send_packet(data_packet)){     // if packet sent
                if(modem_send_packet("This is sent from PSoC!")){     // if packet sent
                    modem_power_off();
                    clear_packet(data_packet, MAX_PACKET_SIZE);
                }
                else{                                   // if packet not sent
                    modem_reset();
                    modem_power_off();
                }
            }
        }
        else{
            if(sensor_ready){
                // get ultrasonic_packet
                uint8 ultrasonic_packet[MAX_PACKET_SIZE];
                ultrasonic_read(ultrasonic_packet, MAX_PACKET_SIZE);
                
                // write packet
                write_packet(data_packet, ultrasonic_packet, ultrasonic_packet, MAX_PACKET_SIZE);
                
                // set packet to ready
                packet_ready = 1u; 
                
                CyDelay(5000u);
            }
            else{
                // go to sleep
            }
        }
    }
}

CY_ISR(isr_timer){
    sensor_ready = 1u;
    timer_ReadStatusRegister();
}

//void read_packet(){
//}

void write_packet(uint8* dest, uint8* src_ultrasonic, uint8* src_pressure, uint8 size){
    uint8 i, j;
    char delimiter[] = ";";
    char term_seq[] = "\032";
    
    strncat(data_packet, src_ultrasonic, 20);
    
//    // add delimiter to packet
//    strncat(data_packet, delimiter, 1);
//    
//    // add terminal sequence to packet
//    strncat(data_packet, term_seq, 1);
    
    packet_ready = 1u; 
}

void clear_packet(uint8* packet, uint8 packet_size){
    uint8 i;
    for(i = 0u; i < packet_size; i++){
        packet[i] = 0u;
    }
    
    packet_ready = 0u;
}

/* [] END OF FILE */
