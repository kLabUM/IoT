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
#include <string.h>
#include "autosampler.h"
//#include debug.h

// prototype bottle_count interrupt
CY_ISR_PROTO(isr_SampleCounter);

// Declare variables
uint8 autosampler_state, i = 0;
uint8 SampleCount = 0, SampleCount1 = 0;

uint8 autosampler_start(){
    isr_SampleCounter_StartEx(isr_SampleCounter);
    autosampler_state = AUTOSAMPLER_STATE_OFF;
}

uint8 autosampler_stop() {
    
}

/*
Start the autosampler.  Then power it on.
*/
uint8 autosampler_power_on() {
    Pin_Sampler_Power_Write(0u);
    CyDelay(1000u);//give the sampler time to boot
    
    autosampler_state = AUTOSAMPLER_STATE_IDLE;
    
    return 1u;
}

uint8 autosampler_power_off() {
    Pin_Sampler_Power_Write(1u);
    autosampler_state = AUTOSAMPLER_STATE_OFF;
    
    return 1u;
}

uint8 autosampler_take_sampler(uint8* count){
    
    if (SampleCount >= MAX_BOTTLE_COUNT) {        
        //debug_write("(autosampler(): MAX_BOTTLE_COUNT met");
        return 0;
    }
    
    autosampler_state = AUTOSAMPLER_STATE_BUSY;
    
    // Initially set trigger high
    Pin_Sampler_Trigger_Write(1u);
        
    // Send PULSE_COUNT pulses @ 10Hz to trigger sampler
    for(i=0; i<PULSE_COUNT; i++){
        Pin_Sampler_Trigger_Write(0u);
        CyDelay(100u);
        Pin_Sampler_Trigger_Write(1u);
        CyDelay(100u);
    }
    
    //while(Pin_Sampler_Completed_Sample_Read()==0);
    for (i = 0; i < 2*60*10 ; i++) {  // Wait Max of 2 Minutes for distributor arm to move
        CyDelay(100u);
        if (Pin_Sampler_Completed_Sample_Read()!=0) {
            break;
        }
    }
    
    //while(Pin_Sampler_Completed_Sample_Read()!=0);
    if (Pin_Sampler_Completed_Sample_Read() != 0) {
        //count = BottleCount_Read();
        SampleCount = BottleCount_Read();
        
        for (i = 0; i < 4*60*10 ; i++) { // Wait Max of 4 Minutes for pumping to complete
            CyDelay(100u);
            if (Pin_Sampler_Completed_Sample_Read()==0) {
                break;
            }
        }
    }
    *count = BottleCount_Read();
    return 1u;
}

CY_ISR(isr_SampleCounter){
    SampleCount1++;
}

/* [] END OF FILE */
