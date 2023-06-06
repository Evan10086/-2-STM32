#include "key.h"


/********************************
KEY0连接在PA0
按键未按下，PA0为高电平(1)
按键 按下，PA0为低电平(0)

KEY1连接在PE2
按键未按下，PE2为高电平(1)
按键 按下，PE2为低电平(0)

KEY2连接在PE3
按键未按下，PE3为高电平(1)
按键 按下，PE3为低电平(0)

KEY3接在PE4
按键未按下，PE4为高电平(1)
按键 按下，PE4为低电平(0)
*********************************/
void Key_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能GPIOE组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_0; 	//引脚0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//输出模式
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2; 	//引脚2
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//输出模式
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_3; 	//引脚3
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//输出模式
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOE, &GPIO_InitStruct);	

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_4; 	//引脚4
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//输出模式
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}