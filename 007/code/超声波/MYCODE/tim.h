#ifndef __TIM_H
#define __TIM_H

#include "stm32f4xx.h"

void Tim3_Init(void);
void tim13_init(void);
void tim13_set_freq(uint32_t freq);
void tim13_set_duty(uint32_t duty);



#endif