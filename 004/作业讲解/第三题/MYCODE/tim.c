#include "tim.h"

int flag1 = 0;
int flag2 = 0;
int time = 0;
unsigned int temp = 1;

u16 count = -1;
int count1 = -1;
int count2 = -1;
int count3 = -1;

/********************************
��ʱ��˵��

TIM3����APB1

TIM3 16λ��ʱ��

TIM3 Ƶ�ʣ�84MHZ

*********************************/

void Tim3_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����

//	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1); //84��Ƶ 84MHZ/84 = 1MHZ
//	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//��1000��������1MHZ�£���ʱ1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	//3������ʱ���жϣ�����NVIC��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4������ TIM3_DIER  ��������ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	//5��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM3, ENABLE);

}



void Tim2_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	//3������ʱ���жϣ�����NVIC��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4������ TIM2_DIER  ��������ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	//5��ʹ�ܶ�ʱ����TIM2
	TIM_Cmd(TIM2, ENABLE);

}

void Tim1_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (168-1); //168��Ƶ 168MHZ/168 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
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
	
	
	//5��ʹ�ܶ�ʱ����TIM1
	TIM_Cmd(TIM1, ENABLE);

}

void Tim4_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM4_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	//3������ʱ���жϣ�����NVIC��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4������ TIM3_DIER  ��������ж�
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	//5��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM4, ENABLE);

}

char bug_count = 0;
char test = 0;

void  TIM3_IRQHandler(void)//��ʱ��Ч��
{
	//�ж��жϱ�־λ�Ƿ���1
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
//		if(++count%2 == 0) //��һ����һ
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//			
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//			
//		}
		
		if(++count%3 == 0) //��һ�����
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
			bug_count++;
			test = 0;
		}
		else
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
			bug_count++;
			test = 0;
			
		}
		
//		if(++count%5 == 0) //��һ������
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//		
//		}		
//		
//		
//		if(++count%9 == 0) //��һ�����
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//		
//		}		
//			

		
			
		
		
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}
}
	
	
	
		

void  TIM2_IRQHandler(void)
{
		
		//�ж��жϱ�־λ�Ƿ���1
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
		{
				
				
//	    if(++count1%2 == 0&&flag1 == 1) //��һ����һ
//		{
//			flag1 = 0;
//		}
		if(++count1%3 == 0&&flag1 == 1) //��һ�����
		{
			flag1 = 0;
		}
//		if(++count1%5 == 0&&flag1 == 1) //��һ������
//		{
//			flag1 = 0;
//		}
//		if(++count1%9 == 0&&flag1 == 1) //��һ�����
//		{
//			flag1 = 0;
//		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOF, GPIO_Pin_10);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_10);	
		}
			
				
			
			
			//����жϱ�־λ
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
		}
}

void  TIM1_UP_TIM10_IRQHandler(void)
{
		
		//�ж��жϱ�־λ�Ƿ���1
		if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
		{
				
				
//		if(++count2%2 == 0&&flag1 == 1) //��һ����һ
//		{
//			flag1 = 0;
//		}
//		if(++count2%3 == 0&&flag1 == 1) //��һ�����
//		{
//			flag1 = 0;
//		}
		if(++count2%5 == 0&&flag1 == 1) //��һ������
		{
			flag1 = 0;
		}
//		if(++count2%9 == 0&&flag1 == 1) //��һ�����
//		{
//			flag1 = 0;
//		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOE, GPIO_Pin_13);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_13);	
		}
			
				
			
			
			//����жϱ�־λ
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	
		}
}

void  TIM4_IRQHandler(void)
{
		
		//�ж��жϱ�־λ�Ƿ���1
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
		{
				
				
//	    if(++count3%2 == 0&&flag1 == 1) //��һ����һ
//		{
//			flag1 = 0;
//		}
//		if(++count3%3 == 0&&flag1 == 1) //��һ�����
//		{
//			flag1 = 0;
//		}
//		if(++count3%5 == 0&&flag1 == 1) //��һ������
//		{
//			flag1 = 0;
//		}
		if(++count3%9 == 0&&flag1 == 1) //��һ�����
		{
			flag1 = 0;
		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOE, GPIO_Pin_14);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_14);	
		}
			
				
			
			
			//����жϱ�־λ
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	
		}
}


