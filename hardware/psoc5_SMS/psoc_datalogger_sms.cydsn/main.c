/* M2M SMS Datalogger */ 

#include <stdio.h>
#include <string.h>
#include <device.h>
#include "slre.h"           /* simple regular expression library */ 
#include "modem.h"
#include "ultrasonic.h"
#include "sleep.h"

// define global variables
#define MAX_PACKET_SIZE 128
uint8   packet_ready;
uint8   data_packet[MAX_PACKET_SIZE];
uint8   data_packet_size;

// prototype functions
void clear_packet();
void write_packet(uint8* packet, uint8 size);
CY_ISR_PROTO(isr_timer);

void main(){
    // intialize modem
    modem_start();
    ultrasonic_start();
    timer_Start();
    isr_timer_StartEx(isr_timer);
    SleepTimer_Start();
    clear_packet();
    CyGlobalIntEnable;
    
    // =======
    modem_power_on();
    CyDelay(5000);
    modem_power_off();
    while(1){}
    // =======
    
    for(;;){
        if(packet_ready){
            if(modem_state == MODEM_STATE_OFF){
                modem_power_on();
            }
            else if(modem_state == MODEM_STATE_IDLE){
                // send packet
                if(!modem_send_packet(data_packet)){      // if packet failed to send
                    modem_reset();
                    modem_power_off();
                }
                else{                                     // if packet successfully sent
                    modem_power_off();
                    clear_packet();
                }
            }
        }
        else{
            //go to sleep
        }
    }
}

CY_ISR(isr_timer){
    uint8 i, j;
    uint8 ultrasonic_packet[16]; 
    ultrasonic_read(ultrasonic_packet, 16u);
    
    // add terminal sequence to packet
    char term_seq[] = "\032";
    for(i=0, j=0; j<sizeof(term_seq); i++){
        if(ultrasonic_packet[i] == 0u){
            ultrasonic_packet[i] = term_seq[j];
            j++;
        }
    }

    write_packet(ultrasonic_packet, 16u);
    timer_ReadStatusRegister();
}

void write_packet(uint8* packet, uint8 size){
    uint8 i;
    for(i = 0u; i < size; i++){
        data_packet[i] = packet[i];
    }
    packet_ready = 1u; 
    data_packet_size = size;
}

void clear_packet(){
    uint8 i;
    for(i = 0u; i < MAX_PACKET_SIZE; i++){
        data_packet[i] = 0;
    }
    packet_ready = 0u;
    data_packet_size = 0u;
}

/* [] END OF FILE */
