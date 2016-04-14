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

#define MODEM_STATE_OFF         0
#define MODEM_STATE_IDLE        1
#define MODEM_STATE_READY       3
#define MAX_CONN_ATTEMPTS		5
#define MAX_GET_ATTEMPTS        2
#define MAX_SEND_ATTEMPTS       1//2
#define MAX_PACKET_LENGTH       1000

extern uint8    modem_state;
extern uint8    lock_acquired;
extern uint32   feed_id;
extern char*    api_key;


uint8   modem_set_api_feed(uint32 feed_id, char* api_key);
uint8	modem_startup();
uint8 	modem_shutdown();
void    modem_start();
void	modem_stop();
uint8   modem_connect();
uint8   modem_connect_with_retries(uint8 retries);
uint8   modem_disconnect();
uint8 hardware_specific_modem_setup();
uint8 	modem_set_apn();
uint8 	modem_set_band(uint8 band);
uint8   modem_get_rtc_time();
uint8 modem_get_nertwork_time();
uint8   modem_check_network();
uint8   modem_get_signal_quality();
uint8   modem_get_serial_number();
uint8 	modem_enable_CDMA_data(uint8 param);
uint8	modem_test_CDMA_data();
uint8	modem_set_user(char* user);
uint8	modem_set_password(char* pass);
uint8   modem_get_google();
uint8   modem_get_profile();
uint8   modem_set_flow_control(uint8 param);
uint8 	modem_set_error_reports(uint8 param);
uint8   modem_get_sw_version();
uint8   modem_send_packet(char* packet);
uint8   modem_get_packet(char* packet, char* csv);
uint8   modem_acquire_lock();
uint8   modem_release_lock();
uint8   modem_get_state();
uint8   modem_reset();
uint8   modem_power_on();
uint8   modem_power_off();
void    modem_sleep();
void    modem_wakeup();

uint8	modem_setup();
uint8   modem_get_time();
uint8   modem_check_network();
uint8   modem_get_signal_quality();
uint8   modem_get_serial_number();
uint8   modem_get_google();
uint8   modem_get_profile();
uint8   modem_set_flow_control(uint8 param);
uint8 	modem_set_error_reports(uint8 param);
uint8   modem_get_sw_version();
uint8 	modem_enable_CDMA_data(uint8 param);
uint8	modem_test_CDMA_data();
uint8	modem_set_user(char* user);
uint8	modem_set_password(char* pass);
uint8 	at_write_command(char* uart_string, char* expected_response, uint32 uart_timeout);

//[] END OF FILE
