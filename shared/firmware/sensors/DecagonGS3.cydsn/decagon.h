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


#include "cytypes.h"


struct {
    float dielectric;
    float temp;
    uint16 conductivity;
    uint8 valid;
}typedef DecagonGS3;


DecagonGS3 Decagon_Take_Reading();
DecagonGS3 Decagon_Convert_Raw_Reading(uint8* raw_D);


/* [] END OF FILE */
