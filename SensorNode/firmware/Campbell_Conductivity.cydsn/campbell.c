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
#include "campbell.h"

uint8 Timeout       = 5u;       // Number of iterations to read valid voltage differentials
uint16 R_Campbell   = 1000;     // Ohms, Resistance that V_differential is measured across
float R_Cable       = 25.0;     // Footage of cable of Campbell A547 sensor
float Kc            = 1.427;    // Capacitance Constant
float TempCoef      = 2.0;       // Temperature Compensation Coefficient (typ. between 0 and 5) 
float C0            = -53.4601; // Thermistor Constants
float C1            =  9.08067;
float C2            = -0.832569;
float C3            =  0.0522829;
float C4            = -0.00167234;
float C5            =  0.0000221098;

/* Declaration of all required variables */
float vpp1, vpp2, dvpp, Vs, Vx;
uint16 result1 = 0u, flag = 0u, result2 = 0u;
uint16 res1 = 0u, res2 = 0u;

uint8 campbell_temp_start(){
    /* Start of all components */
    AMux_1_Start();
    ADC_DelSig_1_Start();
    Temp_Vout_Write(0u);
    
    ADC_DelSig_1_SelectConfiguration(1u, 1u);
    
    return 1u;
}


uint8 campbell_cond_start(){
    /* Start of all components */
    ADC_DelSig_1_Start();
    
    ADC_DelSig_1_SelectConfiguration(1u, 1u);
   
    Comp_1_Start();
    Comp_2_Start();
    Comp_3_Start();
    //Comp_4_Start();
    
    AMux_1_Start();   
    //AMuxSeq_1_Next();  // Connect Mux to first 
    
    Sample_Hold_1_Start();
    Sample_Hold_2_Start();
    Sample_Hold_3_Start();
    //Sample_Hold_4_Start();
    
    PWM_1_Start();
    PWM_2_Start();
    
    Cond_Vout_Write(0u);
    
    return 1u;
}

uint8 campbell_start(){
    /* Start of all components */
    if(! campbell_temp_start()) {
        return 0u;
    }
    if(! campbell_cond_start()) {
        return 0u;
    }
    
    return 1u;
}

uint8 campbell_temp_stop() {

    Temp_Vout_Write(1u);
    ADC_DelSig_1_Stop();
    AMux_1_Stop();    
    
    return 1u;
}

uint8 campbell_cond_stop() {
    /* Stop of all components */
    ADC_DelSig_1_Stop();
   
    Comp_1_Stop();
    Comp_2_Stop();
    Comp_3_Stop();
    //Comp_4_Stop();
    
    AMux_1_Stop();  
    
    Sample_Hold_1_Stop();
    Sample_Hold_2_Stop();
    Sample_Hold_3_Stop();
    //Sample_Hold_4_Stop();
    
    PWM_1_Stop();
    PWM_2_Stop();
    
    Cond_Vout_Write(1u);
    
    return 1u;
}

uint8 campbell_stop(){
    /* Start of all components */
    if(! campbell_temp_stop()) {
        return 0u;
    }
    if(! campbell_cond_stop()) {
        return 0u;
    }
    
    return 1u;
}

uint8 campbell_temp_br_read(float* VsVx){
    
    uint8 i, chan = 2u;
    float mult = 1.0, ratio = 0.0, R = 0.0;
    
    if (! campbell_temp_start()) {
        return 0u;
    }
    
    AMux_1_Select(chan);
    ADC_DelSig_1_StartConvert();    
    CyDelay(100u);     
    
    for (i = 0u; i < 100; i++) {
        
        if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS)){
            
            if (chan == 2)
            {                
            
                ADC_DelSig_1_StopConvert(); // Stop the conversion so signals don't 
                                        // get mixed when switching the mux
                
                
                res1 = ADC_DelSig_1_GetResult16();
    			Vx = ADC_DelSig_1_CountsTo_Volts(res1) ;
                mult = 8/Vx;                // See Sec 12 http://s.campbellsci.com/documents/au/manuals/cs547a.pdf
                                            // Multiplier scales Vx to 8000 mV
                chan = 3u;
                AMux_1_Select(chan);  
                //ADC_DelSig_1_SelectConfiguration(2u, 1u);
                CyDelay(1u);
                ADC_DelSig_1_StartConvert(); 
                CyDelay(99u);                 
            }
            else {            
                ADC_DelSig_1_StopConvert(); // Stop the conversion so signals don't 
                                        // get mixed when switching the mux
                AMux_1_DisconnectAll();
                
                res2 = ADC_DelSig_1_GetResult16();
        		Vs = ADC_DelSig_1_CountsTo_Volts(res2) ;                
                break;
            }                    
        }
        CyDelay(1u); 
    }
        
    if (! campbell_temp_stop()) {
        return 0u;
    }     
    
    //*VsVx = mult * VsVx * 8000;   
    
    ratio = Vs/Vx;                          // Added to adjust for using 100 kOhm instead of 1 kOhm
    R = (100000 - (ratio*349000)) / ratio;  // Added to adjust for using 100 kOhm instead of 1 kOhm  
    *VsVx = 1000 / (R + 250000) * 8000;     // Now that Rs is known, use original equation
                                            // note: Datasheet says 800, but 8000 yields correct results

        // According to Therm107 Datasheet, http://s.campbellsci.com/documents/au/manuals/107.pdf
    // VsVx*8000 should range between 0 and 30
    if (*VsVx > 0 && *VsVx < 30) {                                            
        return 1u;      // Result is valid
    } else {
        return 0u;
    }
}

uint8 campbell_cond_br_read(float* Rs){
    
    uint8 i, chan = 0u;
    
    AMux_1_Select(chan);
    // if i == 5, Mux could not be reset to 0

    ADC_DelSig_1_StartConvert();    
    CyDelay(1u);     
    
    for (i = 0u; i < 100; i++) {
        
        if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS)){
            
            if (chan == 0)
            {                
            
                ADC_DelSig_1_StopConvert(); // Stop the conversion so signals don't 
                                        // get mixed when switching the mux
                chan = 1u;
                AMux_1_Select(chan);
                res1 = ADC_DelSig_1_GetResult16();
    			dvpp = ADC_DelSig_1_CountsTo_Volts(res1) ;

                CyDelay(1u);
                ADC_DelSig_1_StartConvert();  
                CyDelay(49u);
            }
            else {            
                ADC_DelSig_1_StopConvert(); // Stop the conversion so signals don't 
                                        // get mixed when switching the mux
                AMux_1_DisconnectAll();
                
                res2 = ADC_DelSig_1_GetResult16();
        		vpp1 = (ADC_DelSig_1_CountsTo_Volts(res2)/2);
                vpp2 = vpp1 - dvpp;
                
                break;
            }                                                       
        }
        CyDelay(1u); 
    }
    
    
    //*Rs_half = 2*(vpp2-(vpp1)/2)/(vpp1);    // BR_HALF: Voltage divider between Cond LO and GND
    //*Rs_full = 2*(vpp2-(vpp1)/2)/(vpp1);    // BR_FULL: Reversed Differential measurement bewteen Cond HI and cond LO
    
    //*Rs_half = vpp2/vpp1;    // BR_HALF: Voltage divider between Cond LO and GND
    *Rs = vpp2/vpp1;    // BR_FULL: Reversed Differential measurement bewteen Cond HI and cond LO
    
    // ADC range is configured as min(v1) +/- 6.114
    // Readings are expected to be between min(v1) to +6.114
    // and misreading min(v1) as max(v1) results in overflow (eg values like 7.8 and 11)
    if (vpp1 > 6.114 || vpp2 > 6.114) {                                            
        return 0u;
    // Range of excitation signal is 2-2.5 VAC        
    } else if (vpp1 > 2.6) {
        return 0u;
    // vpp2 should always be less than vpp1        
    } else if (*Rs > 1) {
        return 0u;        
    } else if (*Rs < 0) {
        return 0u;
    } else {
        return 1u;
    }
}

uint8 campbell_get_Celsius(float* T) {
    uint8 i;
    float VsVx, temp;
    
    for(i = 0u; i < Timeout; i++)
    {
        if (campbell_temp_br_read(&VsVx)) {
            temp = C0 + C1*VsVx + C2*pow(VsVx,2) + C3*pow(VsVx,3) + C4*pow(VsVx,4) + C5*pow(VsVx,5);
            *T = temp; //*T = TempCoef*temp;
            return 1u;
        }
    }
    
    return 0u;
}

uint8 campbell_get_mSiemens(float* S){
/*
Returns the capacitance according to the formulation
found in the Campbell Scientific manual for A547 (p6):
http://s.campbellsci.com/documents/us/manuals/cs547a.pdf

Note: C currently does not take R_cable, R_capacitors 
into account
*/
    uint8 i;
    float Rs, Rp, T, Ct, Ct_min = -1.0;
    
    campbell_cond_start();
    CyDelay(100u);
    
    for(i = 0u; i < Timeout; i++)
    {   
        if (campbell_cond_br_read(&Rs)) {
        
            Rs = (Rs/(1-Rs));
            
            // Subtract resistance errors (Rp) caused by the blocking capacitors 
            //(0.005Kohm and the cable length (0.000032Kohm/ft) 
            Rp = (0.000032 * R_Cable) + 0.005;
            
            if (Rp < Rs) {
                Rs = Rs - Rp;
            }    
            
            Ct = (1/Rs) * Kc;           // Siemens; C = 1/R
                        
            if (Ct < 0.474) {
                Ct = (Ct * 0.95031) - 0.00378;
            }
            else {
                Ct = -0.02889 + 0.98614 * Ct + 0.02846 * Ct*Ct;
            }                   
                        
            // Check if result is a positive value (valid)
            if (Ct >= 0) {
                // Check if result is the lowest reading (to guard for improper sampling)
                if (Ct_min < 0) {  // First time Ct is successfully calculated, Ct_min should be -1.0
                    Ct_min = Ct;
                } else if (Ct < Ct_min) {
                    Ct_min = Ct;
                }
            }
        } else {
            // Error reading signal.  Restart PWM, comparators, ADC
            campbell_cond_stop();
            CyDelay(1u);
            campbell_cond_start();
            CyDelay(100u);
        }
        
        
        CyDelay(1u);  
        
    }
    campbell_cond_stop();

    // Normalize to Conductivity at 25 degrees C
    if (campbell_get_Celsius(&T)) {
        Ct_min = (Ct_min * 100)/(((T-25) * TempCoef) + 100);
    }    
    
    if (Ct_min >= 0) {
        *S = Ct_min;
        return 1u;
    } else {
        return 0u;
    }
}

uint8 campbell_get_uSiemens(float* S){
    float Ct;
    if (campbell_get_mSiemens(&Ct)) {
        *S = Ct*1000;    // Siemens to milliSiemens
        return 1u;
    }
    return 0u;
}
    
/* [] END OF FILE */
