#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void Delay_Init(void);

void delay_us(int nus);
void delay_ms(int nms);
void delaly_s(int ns);


#endif