#include "exti.h"

/********************************************
����˵��
KEY0-------PA0
KEY1-------PE2
KEY2-------PE3
KEY3-------PE4
����δ����Ϊ1
��������Ϊ��0
*******************************************/
int Flag = 1;  //1 ��ת  0 ��ת
int speed = 700;
int FlagContinue = 0;// 1--����   0---��ͣ


void Exti_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//ʹ�� GPIOAʱ�� GPIOEʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
	//ʹ�� SYSCFGʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;		//����0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//EXTI0����GPIOA

	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;//ʹ���ж���0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI0_IRQn;  //�ж�ͨ��������stm32f4xx.h�ļ����в���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x00;		//��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
/*****************************************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;		//����2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//EXTI2����GPIOE
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line2;//ʹ���ж���2
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI2_IRQn;  //�ж�ͨ��������stm32f4xx.h�ļ����в���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;		//��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
/***********************************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;		//����3 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//EXTI3����GPIOE
	
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line3;//ʹ���ж���3
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI3_IRQn;  //�ж�ͨ��������stm32f4xx.h�ļ����в���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x02;		//��Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
/*********************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;		//����4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//EXTI4����GPIOE
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line4;//ʹ���ж���4
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI4_IRQn;  //�ж�ͨ��������stm32f4xx.h�ļ����в���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x03;		//��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
}
/*
��ת-----
TIM_SetCompare2(TIM9, 0);    //ͨ����ռ�ձ�Ϊ0  		PA3��GND
TIM_SetCompare1(TIM9, speed);//speedԽ��ת��Խ��	    PA2���PWM
��ת----
TIM_SetCompare1(TIM9, 0);//ͨ��һռ�ձ�Ϊ0          PA2��GND
TIM_SetCompare2(TIM9, speed);//speedԽ��ת��Խ��	PA3���PWM
*/
void EXTI0_IRQHandler(void)//S1��ת/��ת---�л�
{
	static unsigned int cnt = 1;//����ʱ����һ�ΰ��£�����������
	if(EXTI_GetITStatus(EXTI_Line0) == SET)//�жϱ�־λ�Ƿ�Ϊ1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  == Bit_RESET)
		{
			if(FlagContinue)  //1--����   0---��ͣ
			{
				if(++cnt % 2 == 1)//��ת
				{
					TIM_SetCompare2(TIM9, 0);  //GND PA3��GND
					//
					TIM_SetCompare1(TIM9, speed);
					Flag = 1;   //��ת��־
				}
				else//��ת
				{
					TIM_SetCompare1(TIM9, 0); //GND  PA2��GND
					//
					TIM_SetCompare2(TIM9, speed);
					Flag = 0;  //��ת��־
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);//����жϱ�־λ
	}
}
void EXTI2_IRQHandler(void)//S2��ͣ/����
{
	static unsigned int sus = 1;//����ʱ����һ��Ϊ����
	if(EXTI_GetITStatus(EXTI_Line2) == SET)//�жϱ�־λ�Ƿ�Ϊ1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)  == Bit_RESET)
		{
			if(++sus % 2 == 1)//��ͣ
			{
				FlagContinue = 0;//��ͣ��־
				if(Flag == 1)//��ת
				{
					TIM_SetCompare2(TIM9, 0);//ͨ����ռ�ձ�Ϊ0
					TIM_SetCompare1(TIM9, 0);//ͨ��һռ�ձ�Ϊ0
				}
				else//��ת
				{
					TIM_SetCompare1(TIM9, 0);//ͨ��һռ�ձ�Ϊ0
					TIM_SetCompare2(TIM9, 0);//ͨ����ռ�ձ�Ϊ0
				}
			}
			else//����
			{
				FlagContinue = 1;//������־
				if(Flag == 1)//��ת
				{
					TIM_SetCompare2(TIM9, 0);//ͨ����ռ�ձ�Ϊ0
					TIM_SetCompare1(TIM9, speed);
				}
				else//��ת
				{
					TIM_SetCompare1(TIM9, 0);//ͨ��һռ�ձ�Ϊ0
					TIM_SetCompare2(TIM9, speed);
				}

			}
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//����жϱ�־λ
}
void EXTI3_IRQHandler(void)//S3�ٶ�++
{
	if(EXTI_GetITStatus(EXTI_Line3) == SET)//�жϱ�־λ�Ƿ�Ϊ1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)  == Bit_RESET)
		{
			if(FlagContinue)	//������̬���ܼ���
			{
				if(Flag == 1)//��ת
				{
					
					speed = speed + 50; //����
			
					if(speed >= 999){speed = 999;}//�ٶ����Ϊ999
					
					TIM_SetCompare1(TIM9, speed);
					TIM_SetCompare2(TIM9, 0); //PA3--GND
				}
				else//��ת
				{
				
					speed = speed + 50;
					if(speed >= 999){speed = 999;}//�ٶ����Ϊ999
					TIM_SetCompare2(TIM9, speed);
					TIM_SetCompare1(TIM9, 0);  //PA2--GND
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line3);//����жϱ�־λ
	}
}
void EXTI4_IRQHandler(void)//S4�ٶ�--
{
	if(EXTI_GetITStatus(EXTI_Line4) == SET)//�жϱ�־λ�Ƿ�Ϊ1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)  == Bit_RESET)
		{
			if(FlagContinue)
			{
				if(Flag == 0)//��ת
				{
					speed = speed - 50;
					if(speed < 200){speed = 200;} //	L298N��12V�����д����Ϊspeed < 0  	speed = 0
					TIM_SetCompare2(TIM9, speed);
					TIM_SetCompare1(TIM9, 0);
				}
				else//��ת
				{
					speed = speed - 50;
					if(speed < 200){speed = 200;}	//	L298N��12V�����д����Ϊspeed < 0	speed = 0
					TIM_SetCompare1(TIM9, speed);
					TIM_SetCompare2(TIM9, 0);
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־λ
	}
}
//����ʱ
void delay(int n)
{
	int i, j;

	for(i=0; i<n; i++)
		for(j=0; j<40000; j++);
}
