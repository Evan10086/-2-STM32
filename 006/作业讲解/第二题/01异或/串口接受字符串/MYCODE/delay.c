#include "delay.h"


u32  my_us = 21;	//��21MHZ�£���21��������ʱ1us
u32  my_ms = 21000;	//��21MHZ�£���21000��������ʱ1ms
void Delay_Init(void)
{
	//ѡ��Systick��ʱ��ʱ�� HCLK/8 = 168MHZ/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

}

//nus���ֵΪ798915
void delay_us(u32 nus)
{
	u32 temp = 0x00;
	
	//��������ֵ�Ĵ���
	SysTick->LOAD = my_us*nus - 1;

	//���ü�����Ϊ0
	SysTick->VAL = 0x00;
	
	//ʹ�ܶ�ʱ������������ʼ����
	SysTick->CTRL |= (0x01<<0);
	
	do
	{
	
		temp = SysTick->CTRL;
			//�ж϶�ʱ���Ƿ���	�ж�16λ�Ƿ�Ϊ1��Ϊ1���˳�
	}while( (temp & (0x01<<0))  &&  !(temp & (0x01<<16)) );
	
	
	
	//��ʹ�ܶ�ʱ��
	SysTick->CTRL &= ~(0x01<<0);	

}

//nms���ֵΪ798
void delay_ms(u32 nms)
{
	u32 temp = 0x00;
	
	//��������ֵ�Ĵ���
	SysTick->LOAD = my_ms*nms - 1;

	//���ü�����Ϊ0
	SysTick->VAL = 0x00;
	
	//ʹ�ܶ�ʱ������������ʼ����
	SysTick->CTRL |= (0x01<<0);
	
	do
	{
	
		temp = SysTick->CTRL;
			//�ж϶�ʱ���Ƿ���	�ж�16λ�Ƿ�Ϊ1��Ϊ1���˳�
	}while( (temp & (0x01<<0))  &&  !(temp & (0x01<<16)) );
	
	
	
	//��ʹ�ܶ�ʱ��
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
