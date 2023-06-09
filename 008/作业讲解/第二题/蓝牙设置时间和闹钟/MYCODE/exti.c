#include "exti.h"

/**********************************

����˵��

KEY0 ����PA0��ѡ���½��ش���
**********************************/
void Exti_PA0_Init(void)
{

	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;		//����0
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	//�ж�ӳ�� PA0--EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	//�����жϿ�����
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;			//�ж���0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�жϼ�ʹ��
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = EXTI0_IRQn;				//�ж�ͨ����ֻ����stm32f4xx.h�в���
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//��Ӧ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //ͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);

}


//��д�жϷ�������
/*********************************************************
a.�жϷ��������ֲ�������ȡ��ֻ����startup_stm32f40_41xxx.s�в���
b.�жϺ����������� void �жϷ�������(void)
c.�жϷ������ǲ���Ҫ���е��ã������������CPU�Զ�ִ�еĺ���
d.�ж�һ�㲻��ִ�й���ʱ��

**********************************************************/


//����ʱ
void delay(int n)
{
	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


void   EXTI0_IRQHandler(void)
{
	//�жϱ�־�Ƿ���λ
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		
			//15ms ���ù����½���
			delay(15);
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
			{	
				*((unsigned int *)(0xC0000000)) = 0x88;
			}				
			
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}

}
















