#include "tim.h"

GPIO_InitTypeDef   GPIO_InitStructure;

EXTI_InitTypeDef   EXTI_InitStructure;


/********************************
��ʱ��˵��

TIM3����APB1

TIM3 16λ��ʱ����1~65535��

TIM3 Ƶ�ʣ�84MHZ

*********************************/


void Tim3_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1���ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
//	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
//	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
//	
//	//2����ʼ����ʱ��������ARR,PSC��
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	

	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1); //84��Ƶ 84MHZ/8400 = 10000HZ
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//��10000��������10000HZ�£���ʱ1s
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
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

uint32_t tim13_cnt=0;

void tim13_init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* ��ʱ��13��ʱ��ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	

	/*��ʱ���Ļ������ã��������ö�ʱ������������Ƶ��Ϊ100Hz */
	TIM_TimeBaseStructure.TIM_Period = (40000/100)-1;					//���ö�ʱ�����Ƶ��
	TIM_TimeBaseStructure.TIM_Prescaler = 2100-1;						//��һ�η�Ƶ�����ΪԤ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//�ڶ��η�Ƶ,��ǰʵ��1��Ƶ��Ҳ���ǲ���Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	tim13_cnt=TIM_TimeBaseStructure.TIM_Period;
	
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);

	/* ����PF8 ����Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					//��8������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ø���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//����ģʽ��������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//����IO���ٶ�Ϊ100MHz��Ƶ��Խ������Խ�ã�Ƶ��Խ�ͣ�����Խ��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//����Ҫ��������
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
	
	
	/* �ö�ʱ��14 PWM ��ͨ�� 1 ������ģʽ 1*/
	 //PWM ģʽ 1�� �ڵ���ģʽ�£� ֻҪTIMx_CNT < TIMx_CCR1�� ͨ�� 1 ��Ϊ��Ч״̬���ߵ�ƽ���� ����Ϊ��Ч״̬���͵�ƽ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//��Ч��ʱ�� ����ߵ�ƽ
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);
	
	/*  ʹ�ܶ�ʱ�� 13 ���� */
	TIM_Cmd(TIM13, ENABLE);
}

//���ö�ʱ��13��PWMƵ��
void tim13_set_freq(uint32_t freq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/*��ʱ���Ļ������ã��������ö�ʱ������������Ƶ��Ϊfreq Hz */
	TIM_TimeBaseStructure.TIM_Period = (40000/freq)-1;					//���ö�ʱ�����Ƶ��
	TIM_TimeBaseStructure.TIM_Prescaler = 2100-1;						//��һ�η�Ƶ�����ΪԤ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//�ڶ��η�Ƶ,��ǰʵ��1��Ƶ��Ҳ���ǲ���Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	tim13_cnt= TIM_TimeBaseStructure.TIM_Period;
	
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);

}

//���ö�ʱ��13��PWMռ�ձ�0%~100%
void tim13_set_duty(uint32_t duty)
{
	uint32_t cmp=0;
	
	cmp = (tim13_cnt+1) * duty/100;

	TIM_SetCompare1(TIM13,cmp);
}



void  TIM3_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
		
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}

}



