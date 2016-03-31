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
#include <project.h>

void TakeAnalogReadings();

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        TakeAnalogReadings();
		CyDelay(1000u);
    }
}

void TakeAnalogReadings(){
	
	ADC_DelSig_1_Start(); // Initialize and start the ADC.
 	ADC_DelSig_1_StartConvert();

	//pwoer on all the sensors
	Power_Reg_Write(0b00000000);
	//take readings from four sensors
	float voltReading[4];
	uint8 channel;
	for(channel=0;channel<4;channel++){
		AMux_FastSelect(channel);
		CyDelay(10u);
	 	if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) != 0){
	 		uint32 adcResult = ADC_DelSig_1_GetResult32();
	 		voltReading[channel] = ADC_DelSig_1_CountsTo_Volts(adcResult);
	 	}
	}
 	
	//turn off sensor
	ADC_DelSig_1_StopConvert();
	ADC_DelSig_1_Stop();
 	//pwoer off all the sensors
	Power_Reg_Write(0b11111111);

}

/* [] END OF FILE */
