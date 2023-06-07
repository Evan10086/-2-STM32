#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"


#define LED0(X)	(X)?GPIO_ResetBits(GPIOF, GPIO_Pin_9) :GPIO_SetBits(GPIOF, GPIO_Pin_9)
#define LED1(X)	(X)?GPIO_ResetBits(GPIOF, GPIO_Pin_10):GPIO_SetBits(GPIOF, GPIO_Pin_10)
#define LED2(X)	(X)?GPIO_ResetBits(GPIOE, GPIO_Pin_13):GPIO_SetBits(GPIOE, GPIO_Pin_13)
#define LED3(X)	(X)?GPIO_ResetBits(GPIOE, GPIO_Pin_14):GPIO_SetBits(GPIOE, GPIO_Pin_14)


void Led_Init(void);


#endif