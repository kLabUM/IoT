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
#include "debug.h"

// prototype bottle_count interrupt
CY_ISR_PROTO(isr_SampleCounter);

// Declare variables
uint8 SampleCount = 0, SampleCount1 = 0, autosampler_state;;

uint8 autosampler_start(){
    isr_SampleCounter_StartEx(isr_SampleCounter);
    autosampler_state = AUTOSAMPLER_STATE_OFF;
    
    return 1u;
}

uint8 autosampler_stop() {
    return 1u;
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

uint8 autosampler_take_sample(uint8* count){
    
    if (*count >= MAX_BOTTLE_COUNT) {        
        debug_write("(autosampler(): MAX_BOTTLE_COUNT met");
        return 0;
    }
    
    uint32 i = 0u, delay = 100u, interval;
    
    autosampler_state = AUTOSAMPLER_STATE_BUSY;
    
    // Initially set trigger high
    Pin_Sampler_Trigger_Write(1u);
        
    // Send PULSE_COUNT pulses @ 10Hz to trigger sampler
    for(i=0; i < PULSE_COUNT; i++){
        Pin_Sampler_Trigger_Write(0u);
        CyDelay(100u);
        Pin_Sampler_Trigger_Write(1u);
        CyDelay(100u);
    }
    
    interval =  2u*60*1000/delay;           // Wait Max of 2 Minutes for distributor arm to move
    //while(Pin_Sampler_Completed_Sample_Read()==0);
    for (i = 0; i < interval ; i++) {  
        CyDelay(delay);
        if (Pin_Sampler_Completed_Sample_Read()!=0) { // Event pin on autosampler is HI
            break;
        }
    }
    
    //while(Pin_Sampler_Completed_Sample_Read()!=0);
    if (Pin_Sampler_Completed_Sample_Read() != 0) {
        //SampleCount = BottleCount_Read(); // Should be zero always
        
        interval =  4u*60*1000/delay;       // Wait Max of 4 Minutes for pumping to complete
        for (i = 0; i < interval ; i++) { 
            CyDelay(delay);
            if (Pin_Sampler_Completed_Sample_Read()==0) { // Event pin on autosampler is HI
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
