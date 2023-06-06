#include "pwm.h"

/*************************************
����˵��
LED0������PF9,�͵�ƽ�������ߵ�ƽ������
TIM14_CH1(TIM14 -- APB1 16λ  84MHZ)

**************************************/
void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef  			GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 			TIM_OCInitStruct;
	
	//��2��ʹ�ܶ�ʱ��14�����IO��ʱ�ӡ�
	//ʹ�ܶ�ʱ��14ʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	//ʹ��GPIOFʱ�ӣ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	//��3����ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9; 		//����9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
	

	//��4��GPIOF9����ӳ�䵽��ʱ��14
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); 
	
	
	
	//��5����ʼ����ʱ����ARR,PSC�ȣ�
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);


	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;  //PWM1ģʽ
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//���ͨ��ʹ��
	TIM_OCInitStruct.TIM_Pulse		= 0; //����
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //���Ե�ƽ ����ѡ��͵�ƽ
	//��6����ʼ������Ƚϲ���:
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);
	
	
	
	//��7��ʹ��Ԥװ�ؼĴ����� 
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable); 
	//��8��ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM14,ENABLE);
	//��9��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM14, ENABLE);


}





/*************************************
����˵��
TX3������PB10,�ߵ�ƽ������  �͵�ƽ��ͣ
TIM2_CH3(TIM2 -- APB1 16λ  84MHZ)

**************************************/
void Pwm_PB10_Init(void)
{
	GPIO_InitTypeDef  			GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 			TIM_OCInitStruct;
	
	//��2��ʹ�ܶ�ʱ��2�����IO��ʱ�ӡ�
	//ʹ�ܶ�ʱ��2ʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//ʹ��GPIOAʱ�ӣ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	
	//��3����ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_10; 		//����10
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	

	//��4��GPIOE2����ӳ�䵽��ʱ��2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2); 
	
	
	
	//��5����ʼ����ʱ����ARR,PSC�ȣ�
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);


	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;  //PWM1ģʽ
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//���ͨ��ʹ��
	TIM_OCInitStruct.TIM_Pulse		= 0; 
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //���Ե�ƽ ����ѡ��ߵ�ƽ
	//��6����ʼ������Ƚϲ���:
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	

	
	//��7��ʹ��Ԥװ�ؼĴ����� 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	//��8��ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//��9��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM2, ENABLE);
}




/*************************************
����˵��
RX3������PB11,�ߵ�ƽ������  �͵�ƽ��ͣ
TIM2_CH4(TIM2 -- APB1 16λ  84MHZ)

**************************************/
void Pwm_PB11_Init(void)
{
	GPIO_InitTypeDef  			GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 			TIM_OCInitStruct;
	
	//��2��ʹ�ܶ�ʱ��2�����IO��ʱ�ӡ�
	//ʹ�ܶ�ʱ��2ʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//ʹ��GPIOAʱ�ӣ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	
	//��3����ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_11; 		//����10
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	

	//��4��GPIOE2����ӳ�䵽��ʱ��2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2); 
	
	
	
	//��5����ʼ����ʱ����ARR,PSC�ȣ�
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000��������1MHZ�£���ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//��Ƶ����
	
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);


	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;  //PWM1ģʽ
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//���ͨ��ʹ��
	TIM_OCInitStruct.TIM_Pulse		= 0; 
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //���Ե�ƽ ����ѡ��ߵ�ƽ
	//��6����ʼ������Ƚϲ���:
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	

	
	//��7��ʹ��Ԥװ�ؼĴ����� 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	//��8��ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//��9��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM2, ENABLE);
}
