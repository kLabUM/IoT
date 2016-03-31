
#include "sensirion_temprh.h"

#define SENSIRION_ADDR 0b1000000
#define SENSIRION_RH_COMMAND 0b11100101
#define SENSIRION_TEMP_COMMAND 0b11100011


uint16 Get_SensironValue(uint8 sensorCommand){

    //send command to sensor to take reading
    Sensirion_I2C_MasterClearStatus();
    Sensirion_I2C_MasterWriteBuf(SENSIRION_ADDR, &sensorCommand,1,
    Sensirion_I2C_MODE_COMPLETE_XFER);
    
    //wait until sensor responds
	//while(0u == (Sensirion_I2C_MasterStatus() &  Sensirion_I2C_MSTAT_WR_CMPLT));
	uint8 i;
	for(i=0;i<10;i++){
		if(Sensirion_I2C_MasterStatus() &  Sensirion_I2C_MSTAT_WR_CMPLT)
			break;
		else
			CyDelay(10u);
	}
    
    
    //read value from sensor
    uint8 i2cBufferRead[2];
    Sensirion_I2C_MasterClearStatus();
    Sensirion_I2C_MasterReadBuf(SENSIRION_ADDR, i2cBufferRead, 2,
    Sensirion_I2C_MODE_COMPLETE_XFER);
    
    //wait until sensor responds
	//while(0u == (Sensirion_I2C_MasterStatus() &  Sensirion_I2C_MSTAT_RD_CMPLT));
	for(i=0;i<10;i++){
		if(Sensirion_I2C_MasterStatus() &  Sensirion_I2C_MSTAT_RD_CMPLT){
			uint16 returnValue = (i2cBufferRead[0] <<8) + i2cBufferRead[1];
			return returnValue;
		}
		else
			CyDelay(10u);
	}
    //convert two bytes into 16-bit integer
    return 999;//non valid value if sensor does not respond (above)
}
Sensirion Take_TempRH_Reading(){
    
	//turn power on to sensor
	Sensirion_I2C_Start();
    Sensirion_Power_Write(1u);
	
    //delay 15ms based on data sheet
    CyDelay(200u);
    
    Sensirion returnValue;
	returnValue.valid = 1;
    
    float RH = (float) Get_SensironValue(SENSIRION_RH_COMMAND);
	if(RH == 999)
		returnValue.valid = 1;
    returnValue.rh = -6 + 125*(RH/65532);
    
    float TEMP = (float) Get_SensironValue(SENSIRION_TEMP_COMMAND);
	if(TEMP == 999)
		returnValue.valid = 1;
    returnValue.temp = -46.85 + 175.72*(TEMP/65532);
    
    //turn sensor off
	Sensirion_I2C_Stop();
    Sensirion_Power_Write(0u);
    return returnValue;


}


