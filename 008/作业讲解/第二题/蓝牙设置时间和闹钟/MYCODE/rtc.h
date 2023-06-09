#ifndef __RTC_H
#define __RTC_H

#include "stm32f4xx.h"
#include "led.h"


void Rtc_Init(void);
void Rtcc_Init(int h1, int m1, int s1);
void Rtc_SetAlarm_A(int data,int h2, int m2, int s2);
void Rtc_SetAlarm_B(void);

#endif