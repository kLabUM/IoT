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
#include <string.h>
#include "maxbotix.h"
#define RAW_SERIAL_DATA_LENGTH_m 30
#define VALUES_ARRAY_LENGTH 5
uint8 raw_serial_data_m[RAW_SERIAL_DATA_LENGTH_m];
uint8 raw_serial_data_count_m;

CY_ISR_PROTO(IntUartRx_M);


CY_ISR(IntUartRx_M)
{
   uint8 getchar;
   getchar  = UART_Maxbotix_GetChar();
        
   if(getchar > 0u && raw_serial_data_count_m < RAW_SERIAL_DATA_LENGTH_m){
        raw_serial_data_m[raw_serial_data_count_m] = getchar;
        raw_serial_data_count_m++;
        }   
    
}

Maxbotix Maxbotix_Convert_Raw_Reading(uint8* raw_M){
    uint32 values[VALUES_ARRAY_LENGTH];
    char* token;
    uint8 value_count = 0u;
    token = strtok(raw_M,"\r");
	Maxbotix final_value;
	final_value.valid = 0u; 
    while(token != NULL){
        uint32 value;
        uint32 scan_valid;
        scan_valid = sscanf(token,"R%d",&value);
        if (scan_valid != 0){
            values[value_count] = value;
            value_count++;
            if (value_count == VALUES_ARRAY_LENGTH){
				final_value.valid = 1u;  
                break;
				
            }
        
        }
        token = strtok(NULL,"\r");
        
    }
    

  
    
    
    uint8 i = 0;
	final_value.depth = 0;
    for(i = 0; i < VALUES_ARRAY_LENGTH; i++){
        final_value.depth = final_value.depth + values[i];
    }
    final_value.depth = final_value.depth/VALUES_ARRAY_LENGTH;

    return final_value;
    
}

Maxbotix Maxbotix_Take_Reading(){

	
	Maxbotix_Power_Write(0u);
	CyDelay(1000u);
	UART_Maxbotix_Start();
    raw_serial_data_count_m = 0u;
    isr_Maxbotix_StartEx(IntUartRx_M);
    CyDelay(1000u);
	
    isr_Maxbotix_Stop();
	UART_Maxbotix_Stop();
	Maxbotix_Power_Write(1u);
	
    Maxbotix depth;
    depth = Maxbotix_Convert_Raw_Reading(raw_serial_data_m);

    return depth;
}

