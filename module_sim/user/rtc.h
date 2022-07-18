#ifndef __RTC_H
#define __RTC_H

#include "main.h"
// #include "stm32l4xx_hal_rtc.h"

extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

void MX_RTC_Init(void);
void get_RTC(void);     

#endif

