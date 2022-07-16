#include "AT.h"


/**
  * @brief
  * @param 
  * @retval 
  */
const AT_CommandTypeDef AT_CheckList[]=
{
     // list enum                       send string                                                         compare string                      final string
    {AT_CheckModule,        {(uint8_t*) "AT\r\n",                                             4},      {(uint8_t*) "OK",                2},     {(uint8_t*) "\r\n",     2},  1000 },// \r\nOK\r\n
    {AT_CheckSim,           {(uint8_t*) "AT+CPIN?\r\n",                                      10},      {(uint8_t*) "+CPIN",             5},     {(uint8_t*) "OK",       2},  1000 },// \r\n+CPIN: READY\r\n\r\nOK\r\n
    {AT_CheckSignal,        {(uint8_t*) "AT+CSQ\r\n",                                         8},      {(uint8_t*) "+CSQ",              3},     {(uint8_t*) "OK",       2},  1000 },// \r\n+CSQ: 12,99\r\n\r\nOK\r\n
    {AT_CheckSubscribe,     {(uint8_t*) "AT+CREG?\r\n",                                      10},      {(uint8_t*) "+CREG",             5},     {(uint8_t*) "OK",       2},  1000 },// \r\n+CREG: 0,1\r\n\r\nOK\r\n
    {AT_CheckGPRS,          {(uint8_t*) "AT+CGATT?\r\n",                                     11},      {(uint8_t*) "+CGATT",            6},     {(uint8_t*) "OK",       2},  1000 },// \r\n+CGATT: 1\r\n\r\nOK\r\n
    {AT_SetTimeout,         {(uint8_t*) "AT+CIPTIMEOUT=30000,20000,40000,50000\r\n",         39},      {(uint8_t*) "OK",                2},     {(uint8_t*) "\r\n",     2},  1000 },// \r\nOK\r\n
    {AT_SetTransmit,        {(uint8_t*) "AT+CIPMODE=0\r\n",                                  14},      {(uint8_t*) "OK",                2},     {(uint8_t*) "\r\n",     2},  1000 },// \r\nOK\r\n
    {AT_SetNetOpen,         {(uint8_t*) "AT+NETOPEN\r\n",                                    12},      {(uint8_t*) "+NETOPEN:SUCCESS", 16},     {(uint8_t*) "\r\n",     2},  10000 },// \r\nOK\r\n\r\n+NETOPEN:SUCCESS\r\n
    {AT_CheckIP,            {(uint8_t*) "AT+IPADDR\r\n",                                     11},      {(uint8_t*) "+IPADDR:SUCCESS",  15},     {(uint8_t*) "OK",       2},  5000 },// \r\n+IPADDR:SUCCESS,10.222.37.231\r\n\r\nOK\r\n
    {AT_SetReceive,         {(uint8_t*) "AT+CIPRXGET=0,1\r\n",                               17},      {(uint8_t*) "OK",                2},     {(uint8_t*) "\r\n",     2},  1000 },// \r\nOK\r\n
    {AT_SetConnectTCP,      {(uint8_t*) "AT+CIPOPEN=1,\"TCP\",\"117.6.163.177\",7577,0\r\n", 43},      {(uint8_t*) "+CIPOPEN:SUCCESS", 16},     {(uint8_t*) "OK",       2},  30000 },// \r\nOK\r\n\r\n+CIPOPEN:SUCCESS,1\r\n  || \r\nOK\r\n 
    {AT_CheckConnectTCP,    {(uint8_t*) "AT+CIPOPQUERY?\r\n",                                16},      {(uint8_t*) "+CIPOPQUERY",      11},     {(uint8_t*) "OK",       2},  5000 },// \r\n+CIPOPQUERY:0,1,0,0,0,0,0,0,0,0\r\n\r\nOK\r\n
    {AT_CloseConnectTCP,    {(uint8_t*) "AT+CIPCLOSE=1\r\n",                                 15},      {(uint8_t*) "+CIPCLOSE:SUCCESS",17},     {(uint8_t*) "\r\n",     2},  5000 },// \r\nOK\r\n\r\n+CIPCLOSE:SUCCESS,1\r\n
    {AT_SetNetClose,        {(uint8_t*) "AT+NETCLOSE\r\n",                                   13},      {(uint8_t*) "+NETCLOSE:SUCCESS",17},     {(uint8_t*) "\r\n",     2},  5000 },// \r\nOK\r\n\r\n+NETCLOSE:SUCCESS\r\n
    {AT_SendData,           {(uint8_t*) "AT+CIPSEND=1,,,,",                                  16},      {(uint8_t*) "+CIPSEND:SUCCESS", 16},     {(uint8_t*) "\r\n",     2},  1000 },// \r\nOK\r\n\r\n+CIPSEND:SUCCESS,1,4,4\r\n
    {AT_GetTime,            {(uint8_t*) "AT+CCLK?\r\n",                                      10},      {(uint8_t*) "+CCLK",             5},     {(uint8_t*) "OK",       2},  1000 } // \r\n+CCLK: "22/07/13,10:26:04+28"\r\n\r\nOK\r\n

    // received data from tcp : \r\n+CIPRXGET:SUCCESS,0,1,3,\r\n123\r\n

};  

extern const AT_CommandTypeDef AT_CheckList[];
