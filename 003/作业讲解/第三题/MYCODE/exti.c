#include "exti.h"

/********************************

KEY0 ����PA0��ѡ���½��ش���
KEY1 ����PE2��ѡ���½��ش���
KEY2 ����PE3��ѡ���½��ش���
KEY3 ����PE4��ѡ���½��ش���
*********************************/

//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}

void Exti_PA0_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIOA clock */
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* Enable SYSCFG clock */
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;    //����0
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	//ӳ��PA0��EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;			//�ж���0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI0_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);


}

void Exti_PE2_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* Enable GPIOE clock */
	//ʹ��GPIOE��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Enable SYSCFG clock */
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PE2 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;    //����2
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect EXTI Line1 to PE2 pin */
	//ӳ��PE2��EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);

	/* Configure EXTI Line1 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line2;			//�ж���2
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line1 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI2_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);

}	


void Exti_PE3_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* Enable GPIOE clock */
	//ʹ��GPIOE��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Enable SYSCFG clock */
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PE2 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;    //����2
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect EXTI Line1 to PE2 pin */
	//ӳ��PE2��EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);

	/* Configure EXTI Line1 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line3;			//�ж���2
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line1 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI3_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);

}	


void Exti_PE4_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* Enable GPIOE clock */
	//ʹ��GPIOE��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Enable SYSCFG clock */
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PE2 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;    //����4
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect EXTI Line1 to PE2 pin */
	//ӳ��PE2��EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);

	/* Configure EXTI Line1 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line4;			//�ж���2
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line1 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI4_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);

}	

/**************************************************
STM32�жϷ�����ע��Ҫ��
a.�жϷ��������ܴ���ʱ�������
b.�жϷ��������ǲ�������д�ģ�ֻ����startup_stm32f40_41xxx.s
�в���
c.STM32�жϷ������̶���ʽvoid �жϷ�������(void)
d.�жϷ������ǲ���Ҫ�ڳ����е��õģ����ж��������㣬CPU�Զ�
ִ�еĺ�����


***************************************************/

void EXTI0_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		delay(15); //��ʱ15ms
		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		{
			GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
			

		}
	
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line0);			
	}

}

void EXTI2_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		delay(15);
		
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == Bit_RESET)
		{
			GPIO_ToggleBits(GPIOF, GPIO_Pin_10);	
			

		}
			//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line2);		
	}

}

void EXTI3_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(EXTI_GetITStatus(EXTI_Line3) == SET)
	{
		delay(15);
		
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == Bit_RESET)
		{
			GPIO_ToggleBits(GPIOE, GPIO_Pin_13);	
			

		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line3);			
	}

}

void EXTI4_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(EXTI_GetITStatus(EXTI_Line4) == SET)
	{
		delay(15);
		
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_RESET)
		{
			GPIO_ToggleBits(GPIOE, GPIO_Pin_14);	
			

		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line4);			
		
	}

}

