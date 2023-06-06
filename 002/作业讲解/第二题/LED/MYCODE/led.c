#include"led.h"
/*************************************
引脚说明
LED0连接在PF9
PF9输出低电平（0），灯亮；PF9输出高电平（1），灯灭；

**************************************/
void Led_Init0(void)
{
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

void Led_Init1(void)
{
	RCC_AHB1ENR |= (0x01<<5);
	//输出模式
	GPIOF_MODER &= ~(0x01<<21);//21位清0
	GPIOF_MODER |= (0x01<<20); //20位置1
	
	GPIOF_OTYPER &= ~(0x01<<10);//10位清0
	
	GPIOF_OSPEEDR &= ~(0x01<<21); //21位清0
	GPIOF_OSPEEDR |= (0x01<<20);//20位置1
	
	GPIOF_PUPDR &= ~(0x01<<21); //21位清0
	GPIOF_PUPDR |= (0x01<<20);  //20位置1
}
void Led_Init2(void)
{
	RCC_AHB1ENR |= (0x01<<4);
	//输出模式
	GPIOE_MODER &= ~(0x01<<27);//27位清0
	GPIOE_MODER |= (0x01<<26); //26位置1
	
	GPIOE_OTYPER &= ~(0x01<<13);//13位清0
	
	GPIOE_OSPEEDR &= ~(0x01<<27); //27位清0
	GPIOE_OSPEEDR |= (0x01<<26); //26位置1
	
	GPIOE_PUPDR &= ~(0x01<<27); //27位清0
	GPIOE_PUPDR |= (0x01<<26);  //26位置1
}
void Led_Init3(void)
{
	RCC_AHB1ENR |= (0x01<<4);
	//输出模式
	GPIOE_MODER &= ~(0x01<<29);//29位清0
	GPIOE_MODER |= (0x01<<28); //28位置1
	
	GPIOE_OTYPER &= ~(0x01<<14);//14位清0
	
	GPIOE_OSPEEDR &= ~(0x01<<29); //29位清0
	GPIOE_OSPEEDR |= (0x01<<28);  //28位置1
	
	GPIOE_PUPDR &= ~(0x01<<29); //29位清0
	GPIOE_PUPDR |= (0x01<<28); //28位置1
}  