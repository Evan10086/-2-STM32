#include "pwm.h"


/****************************************
����˵��

LED0������PF9,�͵�ƽ�������ߵ�ƽ������
TIM14_CH1(TIM14 -- APB1 16λ  84MHZ)

*****************************************/

void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef			TIM_OCInitStruct;
	
	
	
	/* TIM10 clock enable */
	//ʹ�ܶ�ʱ��14ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	/* GPIOF clock enable */
	//ʹ��GPIOFʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	/* GPIOF Configuration: TIM10 CH1 (PF6) */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9 ;		//����9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;	//��������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;	//����
	GPIO_Init(GPIOF, &GPIO_InitStructure); 

	/* Connect TIM pins to AF3 */
	//��ʱ��ӳ�䵽PF9  ѡ������
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
	
	
	//����PWM����
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1);  //84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//��1000���� ����1MHZ, ��ʱ1ms PWM����1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStruct.TIM_OCMode 		= TIM_OCMode_PWM1;		//PWM1ģʽ
	TIM_OCInitStruct.TIM_OCPolarity 	= TIM_OCPolarity_Low;	//������Ե�ƽ������ѡ��͵�ƽ
	TIM_OCInitStruct.TIM_OutputState 	= TIM_OutputState_Enable;//���ʹ��
	TIM_OCInitStruct.TIM_Pulse 			= 0x00;	//���ñȽϼĴ���CCR1ֵ
	
	//OC1��ʼ��  OC1��ʾͨ��1
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);


	//ʹ��ͨ��1���ؼĴ�����
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);

	//ʹ�����ؼĴ���ARR
	TIM_ARRPreloadConfig(TIM14, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM14, ENABLE);


}