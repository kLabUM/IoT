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

#define MODEM_STATE_OFF         0
#define MODEM_STATE_IDLE        1
#define MODEM_STATE_SEARCHING   2
#define MODEM_STATE_READY       3

uint8   modem_state;

void    modem_start();
uint8   modem_join_network();
uint8   modem_send_packet(uint8* packet);
uint8   modem_get_state();
uint8   modem_reset();
uint8   modem_power_on();
uint8   modem_power_off();

//[] END OF FILE
