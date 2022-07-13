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
    uint8_t *data;
    uint16_t length_Data;
}structString;

typedef struct __AT_CommandTypeDef
{              
    AT_ListTypeCommand idName;
    structString send;
    structString receive;
    structString returnStatus;
}AT_CommandTypeDef;

extern const AT_CommandTypeDef AT_CheckList[];

void checkConnectTCP(void);


#endif
