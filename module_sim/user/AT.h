#ifndef __AT_H
#define __AT_H

#include "main.h"

typedef enum {
    AT_CheckModule,
    AT_CheckSim,
    AT_CheckSignal,
    AT_CheckSubscribe,
    AT_CheckGPRS,
    AT_SetTimeout,
    AT_SetTransmit,
    AT_SetNetOpen,
    AT_CheckIP,
    AT_SetReceive,
    AT_SetConnectTCP,
    AT_CheckConnectTCP,
    AT_CloseConnectTCP,
    AT_SetNetClose,
    AT_SendData,
    AT_GetTime
}AT_ListTypeCommand;

typedef struct{
    char *data;
    int length_Data;
}structString;

typedef struct __AT_CommandTypeDef
{              
    AT_ListTypeCommand idName;
    structString send;
    structString compare;
    structString final;
    int timeout;
}AT_CommandTypeDef;

typedef struct __AT_TimeTypeDef
{              
    char hours[2];
    char minuste[2];
    char second[2];
}AT_TimeTypeDef;

extern AT_TimeTypeDef AT_Time;
extern const AT_CommandTypeDef AT_CheckList[];

void checkConnectTCP(void);


#endif
