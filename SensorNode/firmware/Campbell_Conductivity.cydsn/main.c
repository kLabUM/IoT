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
#include <stdio.h>
#include <string.h>
#include "campbell.h"

void main()
{

    //CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    float Ct, T, output1, output2;
    uint16 res1, res2, iter;
    
    
    for(;;)
    {   
        if(! campbell_get_uSiemens(&Ct) ){
            iter++;        
        } else {
            campbell_get_Celsius(&T);
                iter = 0;
        }

        /*
        if(flag == 0u)
        {
            ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);
            result1 = ADC_SAR_Seq_1_GetResult16(0u);
            
            res1 = ADC_SAR_Seq_1_CountsTo_Volts(result1);
            
            CyDelay(2500u);
            flag = 1u;
        }    
        
        
        result1 = ADC_SAR_Seq_1_finalArray[0u];
        res1 = ADC_SAR_Seq_1_CountsTo_Volts(result1);
        sprintf((char *)str,"%+1.2f",res1);
        CyDelay(200u); 
        
        
        if(AMuxSeq_1_GetChannel() != 0){
            AMuxSeq_1_Next();
        }
        
        for (i = 0u; i<1000; i++){
            ADC_DelSig_1_StartConvert();
            CyDelay(100u);
            if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS))
            {
                if (AMuxSeq_1_GetChannel() == 0)
                {
                    res1 = ADC_DelSig_1_GetResult16();
        			output1 = ADC_DelSig_1_CountsTo_Volts(res1) ;
                }
                else {
                    res2 = ADC_DelSig_1_GetResult16();
            		output2 = ADC_DelSig_1_CountsTo_Volts(res2) ;
                    break;
                }
                ADC_DelSig_1_StopConvert();
                AMuxSeq_1_Next();         
                CyDelay(100u);            
            }
        }
        */
    }
    
  
    
}

/* [] END OF FILE */
