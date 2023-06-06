#include "tim.h"

/**************************************
��ʱ��Ƶ��

TIM3 -- APB1
TIM3Ƶ�ʣ�84MHZ
TIM3Ϊ16λ��ʱ��

**************************************/
void Tim3_Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,  ENABLE);
	
//	TIM_TimeBaseInitStruct.TIM_Prescaler	= 83;			//84��Ƶ 84MHZ/84 = 1MHZ ��һ������1us
//	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);		//��1MHZ�£���1000��������ʱ1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//���ϼ���
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;		 //��Ƶ����
//	//2����ʼ����ʱ��������ARR,PSC��
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	TIM_TimeBaseInitStruct.TIM_Prescaler	= 8399;			//8400��Ƶ 84MHZ/8400 = 10000HZ ÿ��ɼ�10000����
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);	//10000HZ����10000��������ʱ1s
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;		 //��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;  //�ж�ͨ��������stm32f4xx.h�ļ����в���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x02;		//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//ͨ��ʹ��
	//3������ʱ���жϣ�����NVIC��
	NVIC_Init(&NVIC_InitStructure);	
	

	//4������ TIM3_DIER  ��������ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	//5��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM3, ENABLE);
	
}





