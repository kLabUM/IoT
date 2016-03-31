#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    float rh;
    float temp;
	uint8 valid;
}typedef Sensirion;

uint16 Get_SensironValue(uint8 sensorCommand);
Sensirion Take_TempRH_Reading();


/* [] END OF FILE */
