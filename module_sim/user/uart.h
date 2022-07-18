#ifndef __UART_H
#define __UART_H

#include "main.h"
#include "stm32l4xx_hal_uart.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

void getStringToString( void *data, const char source[], const char startString[], const char finalString[]);
void getStringToStringAndMinLength( void *data, const char source[], const char startString[], const char finalString[],const int MIN_LENGTH);
void cutString( void *data, const char source[],const int start, const int final );
#endif

