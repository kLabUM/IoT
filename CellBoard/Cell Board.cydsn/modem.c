///* ========================================
// *
// * Copyright YOUR COMPANY, THE YEAR
// * All Rights Reserved
// * UNPUBLISHED, LICENSED SOFTWARE.
// *
// * CONFIDENTIAL AND PROPRIETARY INFORMATION
// * WHICH IS THE PROPERTY OF your company.
// *
// * ========================================
//*/
//

#include <device.h>
#include <stdio.h>
#include <string.h>
#include "modem.h"
#include "packet.h"
//#include "debug.h" TODO: ACCOUNT FOR THIS

// declare varaiables
int	   iter = 0;
uint8  modem_state, lock_acquired = 0u, ready = 0u;
uint16 uart_string_index = 0u;
uint32 feed_id;
char   uart_received_string[1000] = {0}, *api_key;
char*  modem_apn = "epc.tmobile.com";



// prototype modem interrupt
CY_ISR_PROTO(Telit_isr_rx);
void uart_string_reset();

uint8 modem_set_api_feed(uint32 id, char* key){
    feed_id = id;
    api_key = key;
    return 1u;
}

// startup sequence to power on the modem, start modem
// components and prepare for sending/receiving messages
// over the network
uint8	modem_startup() {
	iter = 0, ready = 0u;

	modem_start();
	
	while( iter < MAX_CONN_ATTEMPTS) {
		iter++;

		/* Set up the modem */
		//LED_Write(!LED_Read());
		ready = modem_power_on();
		//LED_Write(!LED_Read());
		//ready = at_write_command("AT\r","OK",1000u);      
		modem_set_flow_control(0u);	
		modem_setup();
		
		if ( ready == 1u ) {
			// Connect modem to network
			// (modem_connect already accounts for retries)
			//LED_Write(!LED_Read());
			ready = modem_connect();
			
			if( ready == 3u ) {
								
				iter = MAX_CONN_ATTEMPTS;//break;	
				return 1u;
			}
		}
		else {
			modem_reset();
		}
	}
	
	// Timed out -- Failed to connect
	return 0u;
}

// shutdown sequence to stop modem components
// and power down the modem
uint8 	modem_shutdown() {
	if (modem_power_off()){
		return 1u;	
	}
	
	return 0u;
}

// initialize modem
void modem_start(){
    Telit_UART_Start();
    Telit_ControlReg_Write(0u);
    //Telit_PWR_Write(0u);        // 0u Enables power to cell module
	Telit_ON_Write(1u);			// Prep modem for "push button"
	Telit_RST_Write(1u);		// Prep modem for "push button"
    Telit_isr_rx_StartEx(Telit_isr_rx);
    modem_state = MODEM_STATE_OFF;
}

// deinitialize modem
void modem_stop(){
    Telit_UART_Stop();
    Telit_ControlReg_Write(0u);
    //Telit_PWR_Write(0u);        // 0u Enables power to cell module
	Telit_ON_Write(0u);			// Save energy by pulling down "push button"
	Telit_RST_Write(0u);		// Save energy by pulling down "push button"
    Telit_isr_rx_Stop();
    modem_state = MODEM_STATE_OFF;
}

// send at-command to modem
uint8 at_write_command(char* uart_string, char* expected_response, uint32 uart_timeout){
    uint8 response = 0u;
    uint32 i = 0u, delay = 100u, interval = uart_timeout/delay;
    
    uart_string_reset();
    Telit_UART_PutString(uart_string);//Telit_UART_PutString("AT\r");
    
    if( strcmp(expected_response, "") != 0){
        for(i=0;i<interval;i++){
            char* valid = strstr(uart_received_string, expected_response);
            if(valid != NULL){
                response = 1u;
                break;
            }
            CyDelay(delay);
        }
    }
    
    return response;
}

uint8 modem_power_on(){

    if (modem_state != MODEM_STATE_OFF) {
        // Modem is already on
        return 1u;
    }
    
    // Set ON, PWR pins low
    Telit_ON_Write(0u); 
    Telit_RST_Write(0u);
    
    // Provide power to Telit module
    //Telit_PWR_Write(0u); //provide power to modem
    Telit_ControlReg_Write(1u);
    
    // "Push" the ON button for 2 seconds
    Telit_ON_Write(1u); 
    CyDelay(2000u);     // the pad ON# must be tied low for at least 1 second and then released.
    //CyDelay(1500u);     // At least 3 seconds if VBAT < 3.4 for GC 864
    Telit_ON_Write(0u); 
    
    CyDelay(5000u);  
    /* NOTE:
        "To get the desirable stability, 
        CC864-DUAL needs at least 10 seconds 
        after the PWRMON goes HIGH.*/
	
	if(at_write_command("AT\r","OK",1000u) == 1){    
        modem_state = MODEM_STATE_IDLE;
        return modem_state;
    }	
	
	// Failed to turn on
    return 0u;
}

uint8 modem_power_off(){
	
    if (modem_state == MODEM_STATE_OFF) {
        // Modem is already off
        return 1u;
    }
	
    // Try to disconnect the modem.  
    // Continue whether or not disconnect is successful
    modem_disconnect();
    
    // "Push" the ON button for 
    Telit_ON_Write(1u);
    CyDelay(2500u);  // To turn the CC864-DUAL off, the ON/OFF Pin must be tied low for 2 second and then released.
    Telit_ON_Write(0u);
    
    CyDelay(5000u); 
    /* CyDelay(5000u); // wait for module to turn off
        "Normally it will be above 10 seconds later from releasing
        ON/OFF# and DTE should monitor the status of PWRMON to see the
        actual power off."  */
    
    // Book keeping
    Telit_ControlReg_Write(0u);    
    //Telit_PWR_Write(1u); // Cut power to modem; 1u Disables power to the modem
    Telit_RST_Write(0u); // Make sure the RESET "button" is not pressed
    
    modem_state = MODEM_STATE_OFF;
    return 1u;
}

uint8 modem_reset(){
    if (modem_state != MODEM_STATE_OFF) { // The modem is idle/ready (powered on)
        
        Telit_RST_Write(1u);
        CyDelay(500u);  //   To reset and to reboot the module, 
                        // the RESET pin must be tied low for at least 200 milliseconds and then released.
        Telit_RST_Write(0u);
        
        CyDelay(5000u); //CyDelay(5000u);
        modem_state = MODEM_STATE_IDLE;
    }
    return modem_state;
}

uint8 modem_setup() {
/* Initialize configurations for the modem */
	// Set Error Reports to verbose mode
	if (modem_set_error_reports(2u) != 1u) {
		return 0u;
	}
	
	/* UNCOMMENT when using GC864 instead of CC864
	// Set the APN for GC864-Dual-V2
	if (modem_set_apn() != 1u) {
		return 0u;
	}
		
	// Select the band for GC864-Dual-V2
	if (modem_set_band(1u) != 1u) {
		return 0u;
	}
	*/
	
	return 1u;
}

uint8 modem_connect(){
/* Establish modem connection with the network */	
	uint8 count = 0u, network_status = 0u;
	
	// Check if modem is registered on home network
	// Buffer should return +CREG: 0,1
	// modem_check_network returns 1u if buffer contains ",1"
	network_status = modem_check_network();
	while(network_status == 0u && count < MAX_CONN_ATTEMPTS) {

		network_status = modem_check_network();
		CyDelay(3000u);
		count++;
	}
	
	if (network_status == 1u) {		
		// Try to activate network context
		// #SGACT1,<0,1> is for multisocket
		// For now, use #GPRS, which is from Enhanced Easy IP commands
	    if(at_write_command("AT#SGACT=1,1\r","OK",5000u) == 1){    
		//if(at_write_command("AT#GPRS=1\r","OK",5000u) == 1){    // Used for GSM (ATT, TMobile)
	        modem_state = MODEM_STATE_READY;
	        return modem_state;
	    }		
	}
	
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return modem_state;
    
/*
    if(at_write_command("AT+CREG=1\r","OK",5000u)){
        if(at_write_command("AT+CREG?\r","OK",5000u)){
        //if(!at_write_command("AT#CGPADDR=1\r","\"",5000u)){
            if(at_write_command("AT#SGACT=1,1\r","OK",30000u)){
                modem_state = MODEM_STATE_READY;
                //return 1u; // connected to network
            }
            else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
        }
       else debug_write("(AT#CGPADDR=1) No IP Address Exists.");   Returns IP address.. should be called after SGACT=1,1
    }
    else debug_write("(AT+CREG=1) Could not register to network."); CREG reports registration status of the device, does not set it
    
    return 0u;
*/
/*
    at_write_command("AT+CSQ\r","OK",5000u); // get signal strength
    
    if (!at_write_command("AT+CREG=1\r","OK",5000u)) { // look for network
        debug_write("(AT+CREG=1) Could not register to network.");
    }
    
    at_write_command("AT#SCFG=1,1,0,0,1200,0\r","OK",5000u); // config parameter
    
    if (at_write_command("AT#CGPADDR=1\r","OK",5000u)) {// check if ip address exists
        debug_write("(AT#CGPADDR=1) No IP Address Exists.");    
    }
    
    at_write_command("AT#SGACT?","OK",30000u);
    
    uint8 success  = at_write_command("AT#SGACT=1,1\r","OK",30000u); // This command should return an ip address but the modem seem to freeze after this
    //success = at_write_command("AT#SD=1,0,50000,\"141.212.136.222\",0,0,1\r","OK",5000u); // connect to server
    
    if (!success) {
        debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    }
    
    return success;
    */
    
}

uint8 modem_disconnect(){
/* Close modem connection to network */
	
    // Proceed if modem is not connected to network.  Otherwise, try to disconnect from the network and proceed.
    if(modem_state != MODEM_STATE_READY) {
        /* Can use this statement instead for GSM (ATT, TMobile)
		return (at_write_command("AT#GPRS=0\r","OK",5000u) == 1u);
		*/
		return (at_write_command("AT#SGACT=1,0\r","OK",5000u) == 1u);
			
		/*
		if(at_write_command("AT#SH=1","OK",10000u) == 1){
            if(at_write_command("AT#SGACT=1,0","OK",10000u) == 1){
                modem_state = MODEM_STATE_IDLE;
                return 1u;
            }
            // Write to SD Card debugger
            else {
                debug_write("(AT#SGACT=1,0) Could not disconnect.");
            }
            
        }
        Write to SD Card debugger
        else {
            debug_write("(AT#SH=1) Could not close socket.");
        }
        */
    }
    /* Write to SD Card debugger
    else {
        if (modem_state == MODEM_STATE_OFF) {
            debug_write( "(modem_state != MODEM_STATE_READY) modem_state = MODEM_STATE_OFF" );
        }
        else if (modem_state == MODEM_STATE_IDLE) {
            debug_write( "(modem_state != MODEM_STATE_READY) modem_state = MODEM_STATE_IDLE" );
        }
    }
    */
    return 0u; // failed to disconnect
}

uint8 modem_set_apn() {
/* 
	Set the access point that the modem connects to.
	The APN is defined in "modem_apn" at the
	top of this file 
*/
    char cmd[100];
    sprintf(cmd,"AT+CGDCONT=1,\"IP\",\"%s\"\r",modem_apn);
    if(at_write_command(cmd,"OK",2000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u; 
}

uint8 modem_set_band(uint8 band) {
/* 
	Set the band on which the modem should communicate on
	Band ranges from <0,3>
	"epc.tmobile.com" uses band 1
*/
    char cmd[100];
    sprintf(cmd,"AT#BND=%d\r",band);
    if(at_write_command(cmd,"OK",2000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u; 
}

uint8 modem_get_time(){
    if(at_write_command("AT+CCLK?\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */
    
    /* Parse Time from data packet */

    return 0u;  
}

uint8 modem_check_network() {
    if(at_write_command("AT+CREG?\r",",1",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */
    
    /* Parse Time from data packet */

    return 0u;      
}
uint8 modem_get_signal_quality(){
    if(at_write_command("AT+CSQ\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */
    
    /* Parse Time from data packet */

    return 0u;  
}

uint8 modem_get_serial_number(){
    if(at_write_command("AT+CGSN\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}


uint8 modem_get_profile(){
    if(at_write_command("AT&V\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}

uint8 modem_set_flow_control(uint8 param){
    char cmd[100];
    sprintf(cmd,"AT&K%u\r",param);
    if(at_write_command(cmd,"OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}

uint8 modem_set_error_reports(uint8 param){
	/*
	2.4. Enable Extended Error Result codes
	Disable the Error Report in numerical and verbose format:
	AT+CMEE=0
	OK
	Enable the Error Report in numerical format:
	AT+CMEE=1
	OK
	Enable the Error Report in verbose format:
	AT+CMEE=2
	OK
	*/
	
    char cmd[100];
    sprintf(cmd,"AT+CMEE=%u\r",param);
    if(at_write_command(cmd,"OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}

uint8 modem_get_sw_version(){
    if(at_write_command("AT+CGMR\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}

uint8 modem_enable_CDMA_data(uint8 param){
	/*
	4.2.12 CDMA Data Connection
	0 - CDMA Data connection deactivation request
	1 - CDMA Data connection activation request
	*/
	
    char cmd[100];
    sprintf(cmd,"AT#CDMADC=%u\r",param);
    if(at_write_command(cmd,"OK",5000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;  
}

uint8 modem_test_CDMA_data(){
	
    if(at_write_command("AT#CDMADC?\r","OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */

    return 0u;	
}

uint8 modem_set_user(char* user) {
	
    char cmd[100];
    sprintf(cmd,"AT#USERID=\"%s\"\r",user);		
	
    if(at_write_command(cmd,"OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */
	
	return 0u;	
}

uint8 modem_set_password(char* pass) {
	
    char cmd[100];
    sprintf(cmd,"AT#PASSW=\"%s\"\r",pass);		
	
    if(at_write_command(cmd,"OK",1000u) == 1u){      
        return 1u;
    }
    /* Write to SD Card debugger
    else debug_write("(AT#SGACT=1,1) No IP Address Assigned.");
    */
	
	return 0u;	
}
uint8 modem_get_google(){

    // Proceed if modem is already connected.  Otherwise, try to join the network and proceed
    if( modem_state == MODEM_STATE_READY || modem_connect() != 0 ){ 
        
        if(at_write_command("AT#SKTD=0,80,\"www.google.com\"\r\n","CONNECT",10000u) != 0){
            
            char get_str[MAX_PACKET_LENGTH], key_str[100];
            
            //sprintf(get_str,"GET / HTTP/1.0\r\n");
            //sprintf(key_str,"Host: www.google.com\r\n");
            //sprintf(get_str,"GET /\r\n");
            //sprintf(get_str,"%s%s",
            //    get_str,
            //    "\r\n");
            
            uart_string_reset();
            
            //at_write_command(get_str,"",15000u);
			
			at_write_command("GET /get_status/ HTTP/1.0\r\n","",15000u);
			//CyDelay(1000u);
			//at_write_command("Host: www.google.com\r\n","",15000u);
			CyDelay(1000u);
			at_write_command("\r\n","",15000u);
			CyDelay(1000u);
			at_write_command("\r\n","",15000u);
			
			CyDelay(15000u);
            
			// Just return regardless
			return 1u;
            /*
            if(at_write_command(get_str,"SRING: 1",15000u) != 0){
                // Read GET response from the buffer
                uart_string_reset();
                //CyDelay(5000u);
                at_write_command("AT#SRECV=1,700\r","OK",15000u);
                //strcpy(packet, uart_received_string);
                strcpy(packet, strstr(uart_received_string, "\r\n\r\n")+strlen("\r\n\r\n"));
                
                CyDelay(1000u); //debug_write("Packet received successfully.");
                return 1u;   // return 1 if succesfully sent sms

            }
            */
        }
        
    }
    
    //debug_write("MAX_GET_ATTEMPTS Exceeded.");
    modem_disconnect();
    return 0u;   // return 0 if failure to send sms
}

// send packet to Xively server
uint8 modem_send_packet(char* body){

	// Handle retries in main()
    //uint8 attempts = 0;
    //for(attempts = 0; attempts < MAX_SEND_ATTEMPTS; attempts++) {
        
    // Proceed if modem is already connected.
    if( modem_state == MODEM_STATE_READY ){ 
		// Reset uart for incoming data from modem
        uart_string_reset();
			
		// Connect to web server
        //if(at_write_command("AT#SKTD=1,80,\"api.xively.com\",0,0\r","CONNECT",5000u) != 0){
		if(at_write_command("AT#SD=1,0,8086,\"ec2-54-148-229-234.us-west-2.compute.amazonaws.com\",0,0,1\r","OK",15000u) != 0){
		//if(at_write_command("AT#SD=1,0,80,\"www.google.com\",0,0\r\n","CONNECT",15000u) != 0){
			
			if(at_write_command("AT#SSEND=1\r",">",10000u) != 0){
			// Write packet information to serial and send
	            char put_str[MAX_PACKET_LENGTH], key_str[100];
	            
	            sprintf(put_str,"POST /write?db=cellBoard_test HTTP/1.0\r\n");
	            sprintf(put_str,"%s%s%s%d%s%s%s",
	                put_str,
	                "Host: ec2-54-148-229-234.us-west-2.compute.amazonaws.com:8086\r\n",
	                "Content-Length: ", strlen(body),
	                "\r\n\r\n", body, "\r\n\032");
	                // change second from last back to body
				// Reset uart for incoming data from modem
	            uart_string_reset();

				if(at_write_command(put_str,"SRING: 1",10000u) != 0){
                    // Read GET response from the buffer
                    uart_string_reset();
                    //CyDelay(5000u);
                    at_write_command("AT#SRECV=1,1000\r","200 OK",10000u);
					
                    return 1u;   // return 1 if succesfully sent sms

                }
				/* GC 864
	            if(at_write_command(put_str,"200 OK",15000u) != 0){
	                return 1u;   // return 1 if HTTP request was successful
	            }
				*/
            }
            /* Write to SD Card debugger
            else {
                debug_write("(AT#SSEND=1) Could not send data through connected socket.");
            }
            */
        }
        /* Write to SD Card debugger
        else {
            debug_write("(AT#SD=1,0,8081,\"api.xively.com\",0,0,1\r) Could not connect to server.");
        }
        */
    }        
    //}  
	//modem_reset();
    return 0u;   // return 0 if failure to send sms
}


// read packet from Xively server
uint8 modem_get_packet(char* packet, char* csv){    

	// Check if request is too long
    if (strlen(csv) > 125) {
        /* Write to SD Card debugger
        debug_write("modem_get_packet(): csv length > 100");
        */
        return 0u;
    }
	
	// Changed to handle looping in main()
    //uint8 attempts = 0;            
    //for(attempts = 0; attempts < MAX_GET_ATTEMPTS; attempts++) {
        // Proceed if modem is already connected.  Otherwise, try to join the network and proceed
    if( modem_state == MODEM_STATE_READY ){ 
		// Connect to server
        if(at_write_command("AT#SD=1,0,80,\"api.xively.com\",0,0,1\r\n","OK",20000u) != 0){
			
			if(at_write_command("AT#SSEND=1\r",">",10000u) != 0){
				// Write packet information to serial and send
	            char get_str[MAX_PACKET_LENGTH], key_str[100];
				
	            sprintf(get_str,"GET /v2/feeds/%lu.csv?datastreams=%s HTTP/1.0\r\n", feed_id, csv);
	            sprintf(key_str,"X-ApiKey: %s\r\n", api_key);
	            sprintf(get_str,"%s%s%s%s%s",
	                get_str,
	                key_str,
	                "Host: api.xively.com\r\n",
	                "Accept: text/csv\r\n",
	                "\r\n\032\r");
	            
				// Reset uart for incoming data from modem
	            uart_string_reset();
				
			    if(at_write_command(get_str,"SRING: 1",10000u) != 0){
                    // Read GET response from the buffer
                    uart_string_reset();
                    //CyDelay(5000u);
                    at_write_command("AT#SRECV=1,1000\r","OK",10000u);
                    //strcpy(packet, uart_received_string);
                    strcpy(packet, strstr(uart_received_string, "\r\n\r\n")+strlen("\r\n\r\n"));
                    
                    //debug_write("Packet received successfully.");
                    return 1u;   // return 1 if successful

                }
				
				/* GC864
	            if(at_write_command(get_str,"200 OK",15000u) != 0){
					strcpy(packet, strstr(uart_received_string, "\r\n\r\n")+strlen("\r\n\r\n"));
	                return 1u;   // return 1 if HTTP request was successful
	            }
				*/
            }
			/* OLD, method used AT#SD=1,0,80,\"api.xively.com\",0,0,1 combined with SSEND
            if(at_write_command(get_str,"SRING: 1",15000u) != 0){
                // Read GET response from the buffer
                uart_string_reset();
                //CyDelay(5000u);
                at_write_command("AT#SRECV=1,700\r","OK",15000u);
                //strcpy(packet, uart_received_string);
                strcpy(packet, strstr(uart_received_string, "\r\n\r\n")+strlen("\r\n\r\n"));
                
                CyDelay(1000u); //debug_write("Packet received successfully.");
                return 1u;   // return 1 if succesfully sent sms

            }
			*/
			
            /* Write to SD Card debugger
            else {
                debug_write("(at_write_command(sendBuffer,\"OK\"...) Data sent unsuccessfully.");
            }
            */

            //uint8 disconnected = modem_disconnect();
        }
            /* Write to SD Card debugger
            else {
                debug_write("(AT#SD=1,0,80,\"api.xively.com\",0,0,1) Could not connect to server.");
            }
            */
        /*}
        
        if (attempts < MAX_GET_ATTEMPTS-1) { // Don't reset the modem on the last attempt since it will be getting disconnected
            modem_reset();
        }
        */
    }
    //modem_disconnect();
    return 0u;   // return 0 if failure to send sms
}

uint8 modem_acquire_lock(){
    
    /*
    if (lock_acquired == 1u) {
        return 1u;
    }
    */
    
    uint8 lock = 0u;
    uint32 i = 0u, delay = 100u, lock_attempts = 2u;    
    char data_packet[300] = {0};
            
    for(i=0u; i < lock_attempts; i++) {
        if(modem_get_packet(data_packet,"lock")){
            if(packet_get_uint8(data_packet, "lock", &lock) && lock == 0u){
            
                memset(&data_packet[0],0,sizeof(data_packet));
                sprintf(data_packet, "{"
                      "\"method\":\"put\","
                      "\"resource\":\"/feeds/%lu\","
                      "\"headers\":{\"X-ApiKey\":\"%s\"},"
                      "\"body\":{\"version\":\"1.0.0\",\"datastreams\":["
                            "{ \"id\" : \"lock\", \"current_value\" : \"%u\"}"
                      "]}}",
                      feed_id,api_key,1u);
                      
                if(modem_send_packet(data_packet)) {
                    lock_acquired = 1u;
                    return 1u;
                }
            }  
        }
        CyDelay(delay);
    }
         
    return 0u;
}

uint8 modem_release_lock(){
    /*
    if (lock_acquired == 0u) {
        return 1u;
    }
    */
    
    uint32 i = 0u, delay = 100u, lock_attempts = 2u;    
    char data_packet[300] = {0};
    
    sprintf(data_packet, "{"
          "\"method\":\"put\","
          "\"resource\":\"/feeds/%lu\","
          "\"headers\":{\"X-ApiKey\":\"%s\"},"
          "\"body\":{\"version\":\"1.0.0\",\"datastreams\":["
                "{ \"id\" : \"lock\", \"current_value\" : \"%u\"}"
          "]}}",
          feed_id, api_key, 0u);
        
    for(i=0u; i < lock_attempts; i++) {

        if(modem_send_packet(data_packet)) {
            lock_acquired = 0u;
            return 1u;
        }
        
        CyDelay(delay);
    }
         
    return 0u;
}

void uart_string_reset(){
    // reset uart_received_string to zero
    /*
    uint16 i = 0;
    
    for(i = 0; i < 700; i++){
        uart_received_string[i] = 0;
    }
    */
    memset(&uart_received_string[0],0,sizeof(uart_received_string));
    uart_string_index = 0;
    Telit_UART_ClearRxBuffer();
//    uart_ClearTxBuffer();
}

// this function fires when uart rx receives bytes (when modem is sending bytes)
CY_ISR(Telit_isr_rx){
    while (Telit_UART_GetRxBufferSize()){
        // hold the next char in the rx register as a temporary variable
        char rx_char_hold = Telit_UART_GetChar();
        
        // store the char in uart_received_string
        if(rx_char_hold){
            uart_received_string[uart_string_index] = rx_char_hold;
            uart_string_index++;
        }
    }
}

///* [] END OF FILE */
//