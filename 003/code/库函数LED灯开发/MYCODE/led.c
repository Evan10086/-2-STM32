#include "led.h"


/*************************************
引脚说明
LED0连接在PF9
PF9输出低电平（0），灯亮；PF9输出高电平（1），灯灭；

**************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//使能GPIOF组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9; 	//引脚9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	

	
}
