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
#include "ADC_SAR_1.h"
#include "BatteryVoltage.h"


uint8 ReadBatteryVoltage(float* voltage){
    float tmp = 0.0;
    
    //Enable battery volatge input
    VBAT_EN_Write(1u);
    //let it settle 50us
    CyDelay(10u);
    ADC_SAR_1_StartConvert();
    CyDelay(10u);
    //ADC_SAR_1_IsEndConversion(ADC_SAR_1_RETURN_STATUS);
    tmp =  ADC_SAR_1_CountsTo_Volts(ADC_SAR_1_GetResult16());
    ADC_SAR_1_StopConvert();
    //Disable battery volatge input
    VBAT_EN_Write(0u);
    *voltage = tmp*(11);//convert based on voltage divider (1KOhm and 10 KOhm)
    return 1u;
}