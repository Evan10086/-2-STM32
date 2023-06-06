#include "led.h"

/********************************************
引脚说明

LED0连接在PF9
LED1连接在PF10
LED2连接在PE13
LED3连接在PE14
PF9输出低电平（0），灯亮；PF9输出高电平（1），灯灭；
PF10输出低电平（0），灯亮；PF10输出高电平（1），灯灭；
PE13输出低电平（0），灯亮；PE13输出高电平（1），灯灭；
PE14输出低电平（0），灯亮；PE14输出高电平（1），灯灭；

*******************************************/
void Led_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;//引脚配置结构体
	
	//1.打开GPIOF的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	//1.打开GPIOE的时钟RCC_AHB1Periph_GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//1.打开GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_10;//引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//输出推挽
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ中速
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF,&GPIO_InitStruct);//初始化引脚配置
	
	
	//2.配置引脚13和14
	//GPIO_InitTypeDef GPIO_InitStruct;//引脚配置结构体
	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14;//引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//输出推挽
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ中速
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;//上拉

	GPIO_Init(GPIOE,&GPIO_InitStruct);//初始化引脚配置	
	
	//2.配置引脚PA2
	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_3;//引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//输出推挽
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ中速

	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化引脚配置		
	//先把全部灯灭了
	GPIO_SetBits(GPIOF,GPIO_Pin_9);
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	GPIO_SetBits(GPIOE,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2 | GPIO_Pin_3);//电动机开机停止
	

	
}
