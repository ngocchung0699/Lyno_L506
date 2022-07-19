#include "AT.h"


/**
  * @brief
  * @param 
  * @retval 
  */
AT_CommandTypeDef AT_CheckList[]=
{
     // list enum             send string                                    compare string                 final string
    {AT_CheckModule,        "AT\r\n",                                             "OK",                       "\r\n",      1000 },// \r\nOK\r\n
    {AT_CheckSim,           "AT+CPIN?\r\n",                                       "+CPIN",                    "OK",        1000 },// \r\n+CPIN: READY\r\n\r\nOK\r\n
    {AT_CheckSignal,        "AT+CSQ\r\n",                                         "+CSQ",                     "OK",        1000 },// \r\n+CSQ: 12,99\r\n\r\nOK\r\n
    {AT_CheckSubscribe,     "AT+CREG?\r\n",                                       "+CREG",                    "OK",        1000 },// \r\n+CREG: 0,1\r\n\r\nOK\r\n
    {AT_CheckGPRS,          "AT+CGATT?\r\n",                                      "+CGATT",                   "OK",        1000 },// \r\n+CGATT: 1\r\n\r\nOK\r\n
    {AT_SetTimeout,         "AT+CIPTIMEOUT=30000,20000,40000,50000\r\n",          "OK",                       "\r\n",      1000 },// \r\nOK\r\n
    {AT_SetTransmit,        "AT+CIPMODE=0\r\n",                                   "OK",                       "\r\n",      1000 },// \r\nOK\r\n
    {AT_SetNetOpen,         "AT+NETOPEN\r\n",                                     "+NETOPEN:SUCCESS",         "\r\n",      10000 },// \r\nOK\r\n\r\n+NETOPEN:SUCCESS\r\n
    {AT_CheckIP,            "AT+IPADDR\r\n",                                      "+IPADDR:SUCCESS",          "OK",        5000 },// \r\n+IPADDR:SUCCESS,10.222.37.231\r\n\r\nOK\r\n
    {AT_SetReceive,         "AT+CIPRXGET=0,1\r\n",                                "OK",                       "\r\n",      1000 },// \r\nOK\r\n
    {AT_SetConnectTCP,      "AT+CIPOPEN=1,\"TCP\",\"117.6.163.177\",7577,0\r\n",  "+CIPOPEN:SUCCESS",         "OK",        30000 },// \r\nOK\r\n\r\n+CIPOPEN:SUCCESS,1\r\n  || \r\nOK\r\n 
    {AT_CheckConnectTCP,    "AT+CIPOPQUERY?\r\n",                                 "+CIPOPQUERY",              "OK",        5000 },// \r\n+CIPOPQUERY:0,1,0,0,0,0,0,0,0,0\r\n\r\nOK\r\n
    {AT_CloseConnectTCP,    "AT+CIPCLOSE=1\r\n",                                  "+CIPCLOSE:SUCCESS",        "\r\n",      5000 },// \r\nOK\r\n\r\n+CIPCLOSE:SUCCESS,1\r\n
    {AT_SetNetClose,        "AT+NETCLOSE\r\n",                                    "+NETCLOSE:SUCCESS",        "\r\n",      5000 },// \r\nOK\r\n\r\n+NETCLOSE:SUCCESS\r\n
    {AT_SendData,           "AT+CIPSEND=1,,,,",                                   "+CIPSEND:SUCCESS",         "\r\n",      1000 },// \r\nOK\r\n\r\n+CIPSEND:SUCCESS,1,4,4\r\n
    {AT_GetTime,            "AT+CCLK?\r\n",                                       "+CCLK",                    "OK",        1000 } // \r\n+CCLK: "22/07/13,10:26:04+28"\r\n\r\nOK\r\n

    // received data from tcp : \r\n+CIPRXGET:SUCCESS,0,1,3,\r\n123\r\n

};  

extern AT_CommandTypeDef AT_CheckList[];
