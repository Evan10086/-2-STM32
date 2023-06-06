#include "pwm.h"

/********************************************
����˵��
�������������PA2
TIM9_CH1(TIM9 -- APB2 16λ  168MHZ)
*******************************************/
void PWM_TIM9_CH1_PA2_Init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	
	//ʹ�ܶ�ʱ��9
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	//��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_2;		//����
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; 	//���ù���
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;	//�������
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ����
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ����������	
	
	//ӳ��Ϊ��ʱ������  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler 	= 167;		//168��Ƶ  1MHZ
	TIM_TimeBaseStructure.TIM_Period 		= 999;		//PWM����Ϊ1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//��Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;			//PWM1ģ#ʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��ʹ��
	TIM_OCInitStructure.TIM_Pulse 		= 500;						//���ñȽϼĴ�����ֵΪ500
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;  		//���Ե�ƽΪ�ߵ�ƽ
	//OC1 -->ͨ��1
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);
	
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	//ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ
	TIM_ARRPreloadConfig(TIM9, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM9, ENABLE);
}
/********************************************
����˵��
�������������PA3
TIM9_CH2(TIM9 -- APB2 16λ  168MHZ)
*******************************************/
void PWM_TIM9_CH2_PA3_Init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;

	//ʹ�ܶ�ʱ��9
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	//��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_3;		//����3
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; 	//���ù���
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;	//�������
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ����
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ����������	
	
	//ӳ��Ϊ��ʱ������  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler 	= 167;		//168��Ƶ  1MHZ
	TIM_TimeBaseStructure.TIM_Period 		= 999;		//PWM����Ϊ1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//��Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;			//PWM1ģ#ʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��ʹ��
	TIM_OCInitStructure.TIM_Pulse 		= 500;						//���ñȽϼĴ�����ֵΪ500
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;  		//���Ե�ƽΪ�ߵ�ƽ
	//OC1 -->ͨ��1
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);
	
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	//ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ
	TIM_ARRPreloadConfig(TIM9, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM9, ENABLE);
}
