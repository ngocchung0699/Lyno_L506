#ifndef __ATCOMMAND_H
#define __ATCOMMAND_H

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct __AT_HandleTypeDef
// {                           //                                                       to connect TCP server, install in order number
//     char AT[4];             // check module                                                             1
//     char CPIN[10];          // check sim                                                                2
//     char CSQ[8];            // check signal                                                             3
//     char CREG[10];          // check network registration module                                        4
//     char CGATT[11];         // Read command returns the current GPRS service state                      5
//     char CIPTIMEOUT[39];    // set timeout value                                                        6
//     char CIPMODE[14];       // set transmit mode                                                        7
//     char NETOPEN[12];       // open packet network                                                      8
//     char IPADDR[11];        // get the IP address of current active socket PDP                          9
//     char CIPRXGET[17];      // Get the Network Data Manually                                            10
//     char CIPSEND_DATA[100]; // Send data through TCP                               *                    
//     char CCLK[10];          // get time value
//     char CIPOPEN[50];       // connection with TCP server and UDP server           *                    11
//     char CIPOPQUERY[16];    // determine the connection port and connection status                      12
//     char CIPCLOSE[13];      // close connect TCP or UDP
//     char NETCLOSE[11];      // close packet network
// }AT_HandleTypeDef;

typedef enum __check_List{
    Command_0,      // Waitting
    Command_1,      // check module
    Command_2,      // check sim
    Command_3,      // check signal
    Command_4,      // check network registration module
    Command_5,      // Read command returns the current GPRS service state
    Command_6,      // set timeout value
    Command_7,      // set transmit mode
    Command_8,      // open packet network
    Command_9,      // get the IP address of current active socket PDP
    Command_10,     // Get the Network Data Manually
    Command_11,     // connection with TCP server and UDP server
    Command_12      // determine the connection port and connection status
}check_List;

typedef struct __AT_Command_HandleTypeDef
{              
    char Send[50];
    char Checking[50];
    char Error[50];
    char Ready[50];
    int Number_Get_Data;
}AT_Command_HandleTypeDef;

// function call necessary AT commands
void AT_Init(char IP_Address[], char Port[]);


#endif
