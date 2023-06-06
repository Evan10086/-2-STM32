#include "delay.h"


u32 my_us = 21; 	//在21MHZ下，1us计21个数
u32 my_ms = 21000; 	//在21MHZ下，1ms计21000个数

void Delay_Init(void)
{
	//时钟源选择  HCLK/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}


//nus取值范围：1~798915
void delay_us(int nus)  
{
	u32 temp = 0x00;
	
	
	//设置重载值寄存器的值
	SysTick->LOAD = my_us*nus - 1;
	
	//设置计数的值为0
	SysTick->VAL = 0x00;
	
	//使能定时器
	SysTick->CTRL |= (0x01<<0);

	do
	{
		temp = SysTick->CTRL;
	// 判断定时器是否使能   判断第16位是否为1，为1则退出
	}while( (temp&(1<<0)) && !(temp&(1<<16)));


	//不使能定时器
	SysTick->CTRL &= ~(0x01<<0);	
}


//nms取值范围：1~798
void delay_ms(int nms)  
{
	u32 temp = 0x00;
	
	
	//设置重载值寄存器的值
	SysTick->LOAD = my_ms*nms - 1;
	
	//设置计数的值为0
	SysTick->VAL = 0x00;
	
	//使能定时器
	SysTick->CTRL |= (0x01<<0);

	do
	{
		temp = SysTick->CTRL;
	// 判断定时器是否使能   判断第16位是否为1，为1则退出
	}while( (temp&(1<<0)) && !(temp&(1<<16)));


	//不使能定时器
	SysTick->CTRL &= ~(0x01<<0);	
}

void delaly_s(int ns)
{
	int i;
	
	for(i=0; i<ns; i++)
	{
		delay_ms(500);
		delay_ms(500);
	}

}

