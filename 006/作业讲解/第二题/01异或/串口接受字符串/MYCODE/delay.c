#include "delay.h"


u32  my_us = 21;	//在21MHZ下，计21个数，用时1us
u32  my_ms = 21000;	//在21MHZ下，计21000个数，用时1ms
void Delay_Init(void)
{
	//选择Systick定时器时钟 HCLK/8 = 168MHZ/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

}

//nus最大值为798915
void delay_us(u32 nus)
{
	u32 temp = 0x00;
	
	//设置重载值寄存器
	SysTick->LOAD = my_us*nus - 1;

	//设置计数量为0
	SysTick->VAL = 0x00;
	
	//使能定时器，计数器开始倒数
	SysTick->CTRL |= (0x01<<0);
	
	do
	{
	
		temp = SysTick->CTRL;
			//判断定时器是否开启	判断16位是否为1，为1则退出
	}while( (temp & (0x01<<0))  &&  !(temp & (0x01<<16)) );
	
	
	
	//不使能定时器
	SysTick->CTRL &= ~(0x01<<0);	

}

//nms最大值为798
void delay_ms(u32 nms)
{
	u32 temp = 0x00;
	
	//设置重载值寄存器
	SysTick->LOAD = my_ms*nms - 1;

	//设置计数量为0
	SysTick->VAL = 0x00;
	
	//使能定时器，计数器开始倒数
	SysTick->CTRL |= (0x01<<0);
	
	do
	{
	
		temp = SysTick->CTRL;
			//判断定时器是否开启	判断16位是否为1，为1则退出
	}while( (temp & (0x01<<0))  &&  !(temp & (0x01<<16)) );
	
	
	
	//不使能定时器
	SysTick->CTRL &= ~(0x01<<0);	

}


void delay_s(u32 ns)
{
	int i;
	
	for(i=0; i<ns; i++)
	{
		delay_ms(500);
		delay_ms(500);
	}

}
