#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"


#define LED1(x) (x)?(GPIO_ResetBits(GPIOF, GPIO_Pin_9)):(GPIO_SetBits(GPIOF, GPIO_Pin_9))
#define LED2(x) (x)?(GPIO_ResetBits(GPIOF, GPIO_Pin_10)):(GPIO_SetBits(GPIOF, GPIO_Pin_10))
#define LED3(x) (x)?(GPIO_ResetBits(GPIOE, GPIO_Pin_13)):(GPIO_SetBits(GPIOE, GPIO_Pin_13))
#define LED4(x) (x)?(GPIO_ResetBits(GPIOE, GPIO_Pin_14)):(GPIO_SetBits(GPIOE, GPIO_Pin_14))



void Led_Init(void);


#endif