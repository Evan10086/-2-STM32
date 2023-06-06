#include "led.h"


/*************************************
引脚说明
LED0连接在PF9
PF9输出低电平（0），灯亮；PF9输出高电平（1），灯灭；

**************************************/
void Led_Init(void)
{
	//打开GPIOF组时钟
	RCC_AHB1ENR |= (0x01<<5);
	
	//输出模式
	GPIOF_MODER &= ~(0x01<<19); //19位清0
	GPIOF_MODER |= (0x01<<18);  //18位置1
	
	//输出推挽
	GPIOF_OTYPER &= ~(0x01<<9); //9位清0
	
	// 速度（25MHZ）
	GPIOF_OSPEEDR &= ~(0x01<<19); //19位清0
	GPIOF_OSPEEDR |= (0x01<<18);  //18位置1
	
	
	//上拉
	GPIOF_PUPDR &= ~(0x01<<19); //19位清0
	GPIOF_PUPDR |= (0x01<<18);  //18位置1
	
	
}
