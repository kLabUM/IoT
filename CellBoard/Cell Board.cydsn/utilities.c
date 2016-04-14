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
#include "utilities.h"


uint32 interval_counter;
uint32 num_of_intervals;
uint8  ready;


void blink_LED(uint8 n_blinks) {
	uint8 k;
	for (k = 0; k < n_blinks; k++) {
		LED_Write(1u);
		CyDelay(200u);
		LED_Write(0u);
		CyDelay(200u);
	}	
}

void ScheduleSimpleTask(uint32 num_int){
	num_of_intervals = num_int;
	interval_counter = 0;
}

uint8 SimpleSchedulerTaskReady(){
	
	if(interval_counter > num_of_intervals){
		interval_counter = 0u;
		return 1u;
	}
	return 0u;	
	
}


void SleepCounterUpdate(){
	interval_counter++;
}

/* [] END OF FILE */
