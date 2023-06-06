#include "beep.h"

/*
引脚说明
蜂鸣器连接在PF8
PF8输出低电平（0），蜂鸣器不响；PF8输出高电平（1），蜂鸣器响；
*/

void Beep_Init()
{
	//打开GPIOF组时钟(PF8属于GPIOF组时钟)
	RCC_AHB1ENR |= (0x01<<5);
	
	//配置为通用输出模式 
	GPIOF_MODER &= ~(0x01<<17);  	//17位清0
	GPIOF_MODER |= (0x01<<16);  	//16位置1
	
	//输出推挽
	GPIOF_OTYPER &= ~(0x01<<8);
	
	//速度 25MHZ
	GPIOF_OSPEEDR &= ~(0x01<<17);  	//17位清0
	GPIOF_OSPEEDR |= (0x01<<16);  	//16位置1
	
	
	//上拉
	GPIOF_PUPDR &= ~(0x01<<17);  	//17位清0
	GPIOF_PUPDR |= (0x01<<16);  	//16位置1		

}