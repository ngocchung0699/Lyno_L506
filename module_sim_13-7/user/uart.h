#ifndef __UART_H
#define __UART_H

#include "main.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);



#endif

