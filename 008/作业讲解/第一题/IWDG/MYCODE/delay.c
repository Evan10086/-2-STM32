#include "delay.h"


u32 my_us = 21; 	//��21MHZ�£�1us��21����
u32 my_ms = 21000; 	//��21MHZ�£�1ms��21000����

void Delay_Init(void)
{
	//ʱ��Դѡ��  HCLK/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}


//nusȡֵ��Χ��1~798915
void delay_us(int nus)  
{
	u32 temp = 0x00;
	
	
	//��������ֵ�Ĵ�����ֵ
	SysTick->LOAD = my_us*nus - 1;
	
	//���ü�����ֵΪ0
	SysTick->VAL = 0x00;
	
	//ʹ�ܶ�ʱ��
	SysTick->CTRL |= (0x01<<0);

	do
	{
		temp = SysTick->CTRL;
	// �ж϶�ʱ���Ƿ�ʹ��   �жϵ�16λ�Ƿ�Ϊ1��Ϊ1���˳�
	}while( (temp&(1<<0)) && !(temp&(1<<16)));


	//��ʹ�ܶ�ʱ��
	SysTick->CTRL &= ~(0x01<<0);	
}


//nmsȡֵ��Χ��1~798
void delay_ms(int nms)  
{
	u32 temp = 0x00;
	
	
	//��������ֵ�Ĵ�����ֵ
	SysTick->LOAD = my_ms*nms - 1;
	
	//���ü�����ֵΪ0
	SysTick->VAL = 0x00;
	
	//ʹ�ܶ�ʱ��
	SysTick->CTRL |= (0x01<<0);

	do
	{
		temp = SysTick->CTRL;
	// �ж϶�ʱ���Ƿ�ʹ��   �жϵ�16λ�Ƿ�Ϊ1��Ϊ1���˳�
	}while( (temp&(1<<0)) && !(temp&(1<<16)));


	//��ʹ�ܶ�ʱ��
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

