#include "delay.h"


u32 my_us = 21;  	//1us��21����
u32 my_ms = 21000;  	//1ms��21000����

void Delay_Init(void)
{
	//ѡ����ʱ��ʱ�� HCLK/8 = 21MHZ(1us��21����)
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

//nus���Χ��798915
void delay_us(int nus)
{
	u32 temp = 0x00;
	SysTick->LOAD = my_us*nus - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (0x01<<0);
	do
	{
		temp = SysTick->CTRL;
	}while((temp & (1<<0)) && (!(temp & (1<<16))) );
	SysTick->CTRL &= ~(0x01<<0);
}

//nms���Χ��798
void delay_ms(int nms)
{
	u32 temp = 0x00;
	SysTick->LOAD = my_ms*nms - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (0x01<<0);
	do
	{
		temp = SysTick->CTRL;
	}while((temp & (1<<0)) && (!(temp & (1<<16))) );
	SysTick->CTRL &= ~(0x01<<0);
}
void delay_s(int ns)
{
	int i;
	for(i=0; i<ns; i++)
	{
		delay_ms(500);
		delay_ms(500);
	}
}
