#ifndef __RTC_H
#define __RTC_H

#include "stm32f4xx.h"
#include "led.h"

void Rtc_My_Init(void);

void RTC_Alarm_AInit(void);

void RTC_Alarm_BInit(void);

void RTC_Alarm_B_IRQHandler(void);

#endif