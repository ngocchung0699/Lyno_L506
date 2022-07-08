#ifndef __ATCOMMAND_H
#define __ATCOMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __AT_TypeDef
{
    char AT[4];             // check module
    char CPIN[10];          // check sim
    char CSQ[8];            // check signal
    char CREG[10];          // check network registration module
    char CGATT[11];         // Read command returns the current GPRS service state
    char CIPTIMEOUT[39];    // set timeout value
    char CIPMODE[14];       // set transmit mode
    char NETOPEN[12];       // open packet network
    char IPADDR[11];        // get the IP address of current active socket PDP
    char CIPRXGET[17];      // Get the Network Data Manually
    char CIPSEND_DATA[100]; // Send data through TCP                               //
    char CCLK[10];          // get time value
    char CIPOPEN[50];       // connection with TCP server and UDP server           //
    char CIPOPQUERY[16];    // determine the connection port and connection status 
    char CIPCLOSE[13];      // close connect TCP or UDP
    char NETCLOSE[11];      // close packet network
}AT_TypeDef;

// function call necessary AT commands
void AT_init(char IP_Address[], char Port[]);

#endif
