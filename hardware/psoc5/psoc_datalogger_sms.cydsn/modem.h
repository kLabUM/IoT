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
#define MODEM_STATE_READY       3
#define MAX_GET_ATTEMPTS        2
#define MAX_SEND_ATTEMPTS       2
#define MAX_PACKET_LENGTH       1000

extern uint8    modem_state;
extern uint8    lock_acquired;
extern uint32   feed_id;
extern char*    api_key;


uint8   modem_set_api_feed(uint32 feed_id, char* api_key);
void    modem_start();
uint8   modem_connect();
uint8   modem_disconnect();
uint8   modem_send_packet(char* packet);
uint8   modem_get_packet(char* packet, char* csv);
uint8   modem_acquire_lock();
uint8   modem_release_lock();
uint8   modem_get_state();
uint8   modem_reset();
uint8   modem_power_on();
uint8   modem_power_off();

//[] END OF FILE
