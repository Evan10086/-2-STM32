#include "tim.h"


/********************************
��ʱ��˵��

TIM1����APB2

TIM1 16λ��ʱ��

TIM1 Ƶ�ʣ�168MHZ

*********************************/


void Tim1_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (16800-1); //168��Ƶ 168MHZ/16800 = 0.01MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//��10000��������0.01MHZ�£���ʱ1s
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM1_UP_TIM10_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	//3������ʱ���жϣ�����NVIC��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4������ TIM1_DIER  ��������ж�
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	
	//5��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM1, ENABLE);

}


void  TIM1_UP_TIM10_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
		
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	
	}

}



