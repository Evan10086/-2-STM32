#include "sr04.h"

/**********************************

1��PA2 �C TRIG�������źţ�  PA3 �C ECHO�������źţ�
PA2��Ϊ��ͨ���
PA3��Ϊ��ͨ����

**********************************/
void Sr04_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	
	
	//GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	//1���ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;		//����2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	//���ģʽ
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;  //�������
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_25MHz;//�ٶ�25MHZ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3;		//����3
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;   //����
	GPIO_Init(GPIOA, &GPIO_InitStruct);		
	
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 84-1;  				// 84��Ƶ 84MHZ/84 = 1MHZ ��һ������1us
	TIM_TimeBaseInitStruct.TIM_Period		= 50000-1;					
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;			// ��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
			
	//5,��ʹ�ܶ�ʱ��
	 TIM_Cmd(TIM3, DISABLE);
}

u16 Get_sr04_value(void)
{
	u16 dis = 0, temp = 0, t = 0;
	
	//�����ź�
	PAout(2) = 0;
	delay_us(8);
	PAout(2) = 1;
	delay_us(20);
	PAout(2) = 0;
		
	//���ö�ʱ����CNTΪ0  
	TIM3->CNT = 0;

	//PA3�ȴ��ߵ�ƽ�������ο������ɿ����� 
	while( PAin(3) ==  0)
	{
		delay_us(5);
		t++;
		
		if(t >= 500) //�ȴ��ߵ�ƽʱ��2500us��2500us���޸ߵ�ƽ�����˳�
			return 0;
		
	}

	//ʹ�ܶ�ʱ����ʼ����
	 TIM_Cmd(TIM3, ENABLE);
	
	t = 0;
	//PA3�ȴ��͵�ƽ������
	while(  PAin(3) ==  1 )
	{
		delay_us(5);
		t++;
		
		if(t >= 4000) //�ȴ��ߵ�ƽʱ��20000us��20000us���޵͵�ƽ�����˳�
			return 0;		
	}


	//��ȡ��ʱ��CNTֵ���Ӷ��õ��ߵ�ƽ����ʱ��    
	temp = TIM3->CNT;

	//�رն�ʱ��
	TIM_Cmd(TIM3, DISABLE);
	
	//ͨ����ʽ�������������������
	dis = temp/58;

	return dis;
}

