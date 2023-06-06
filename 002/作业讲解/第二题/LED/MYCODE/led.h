#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#define 	RCC_AHB1ENR  	*((volatile unsigned int *)(0x40023800+0x30))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_MODER   	*((volatile unsigned int *)(0x40021400+0X00))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_OTYPER  	*((volatile unsigned int *)(0x40021400+0X04))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_OSPEEDR 	*((volatile unsigned int *)(0x40021400+0X08))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_PUPDR   	*((volatile unsigned int *)(0x40021400+0X0C))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_IDR     	*((volatile unsigned int *)(0x40021400+0X10))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOF_ODR     	*((volatile unsigned int *)(0x40021400+0X14))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
	
#define		GPIOE_MODER   	*((volatile unsigned int *)(0x40021000+0X00))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOE_OTYPER  	*((volatile unsigned int *)(0x40021000+0X04))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOE_OSPEEDR 	*((volatile unsigned int *)(0x40021000+0X08))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOE_PUPDR   	*((volatile unsigned int *)(0x40021000+0X0C))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOE_IDR     	*((volatile unsigned int *)(0x40021000+0X10))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ
#define		GPIOE_ODR     	*((volatile unsigned int *)(0x40021000+0X14))	//ֵתΪ��ַ��ͨ�������÷��ʵ�ַ�ռ��ֵ

void Led_Init0(void);
void Led_Init1(void);
void Led_Init2(void);
void Led_Init3(void);

#endif