#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"


#define 	RCC_AHB1ENR  	*((volatile unsigned int *)(0x40023800+0x30))	//值转为地址，通过解引用访问地址空间的值

#define		GPIOF_MODER   	*((volatile unsigned int *)(0x40021400+0X00))	//值转为地址，通过解引用访问地址空间的值
#define		GPIOF_OTYPER  	*((volatile unsigned int *)(0x40021400+0X04))	//值转为地址，通过解引用访问地址空间的值
#define		GPIOF_OSPEEDR 	*((volatile unsigned int *)(0x40021400+0X08))	//值转为地址，通过解引用访问地址空间的值
#define		GPIOF_PUPDR   	*((volatile unsigned int *)(0x40021400+0X0C))	//值转为地址，通过解引用访问地址空间的值
#define		GPIOF_IDR     	*((volatile unsigned int *)(0x40021400+0X10))	//值转为地址，通过解引用访问地址空间的值
#define		GPIOF_ODR     	*((volatile unsigned int *)(0x40021400+0X14))	//值转为地址，通过解引用访问地址空间的值

void Led_Init(void);


#endif