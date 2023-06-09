#include "rtc.h"


#define BKR		0x54102


void Rtc_Init(void)
{

	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	//1��ʹ��PWRʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//2��ʹ�ܺ󱸼Ĵ���(�ϵ���Ȼ��������)����:  
	PWR_BackupAccessCmd(ENABLE);
	
	//�жϺ󱸼Ĵ��������ֵ
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKR )
	{
	
		//3������RTCʱ��Դ��ʹ��RTCʱ�ӣ�
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//���ʹ��LSE��Ҫ��LSE��
		RCC_LSEConfig(RCC_LSE_ON);
		
		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //24Сʱ��
		RTC_InitStruct.RTC_AsynchPrediv	= 0x7F;		//�첽ͨ����Ƶ 128
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;		//ͬ��ͨ����Ƶ 256
		//4�� ��ʼ��RTC(ͬ��/�첽��Ƶϵ����ʱ�Ӹ�ʽ)��
		RTC_Init(&RTC_InitStruct);
		
		
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM;	//����
		RTC_TimeStruct.RTC_Hours	= 11;//ʱ
		RTC_TimeStruct.RTC_Minutes	= 29;//��
		RTC_TimeStruct.RTC_Seconds	= 10;//��
		
		//5�� ����ʱ�䣺
		RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 23; //��
		RTC_DateStruct.RTC_Month	= 3;	//��
		RTC_DateStruct.RTC_Date		= 8;	//��
		RTC_DateStruct.RTC_WeekDay	= 3;	//����
		//6���������ڣ�
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
		
		
		//д�󱸼Ĵ���
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKR);
	}

}
//����ʱ��
void Rtcc_Init(int h1, int m1, int s1)
{

	RTC_TimeTypeDef		RTC_TimeStruct;

	RTC_TimeStruct.RTC_Hours	= h1;//ʱ
	RTC_TimeStruct.RTC_Minutes	= m1;//��
	RTC_TimeStruct.RTC_Seconds	= s1;//��
	
	//5�� ����ʱ�䣺
	RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
	

}

//����A����
void Rtc_SetAlarm_A(int data,int h2, int m2, int s2)
{
	RTC_TimeTypeDef 	RTC_AlarmTime;
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	//2���ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;	//����
	RTC_AlarmTime.RTC_Hours		= h2;//ʱ
	RTC_AlarmTime.RTC_Minutes	= m2;//��
	RTC_AlarmTime.RTC_Seconds	= s2;//��
	
	RTC_AlarmStruct.RTC_AlarmTime		= RTC_AlarmTime;  //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask		= RTC_AlarmMask_None;//������λ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date; //���Ӱ�������Ӧ
	RTC_AlarmStruct.RTC_AlarmDateWeekDay 	= data;
	
	//3���������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
	//4���������ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
	//5���������������жϣ�
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//�ж���17
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�жϼ�ʹ��
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = RTC_Alarm_IRQn;				//�ж�ͨ����ֻ����stm32f4xx.h�в���
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//��Ӧ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //ͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);
	 
	 
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
}




//����B����
void Rtc_SetAlarm_B(void)
{
	RTC_TimeTypeDef 	RTC_AlarmTime;
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	//2���ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;	//����
	RTC_AlarmTime.RTC_Hours		= 15;//ʱ
	RTC_AlarmTime.RTC_Minutes	= 12;//��
	RTC_AlarmTime.RTC_Seconds	= 10;//��
	
	RTC_AlarmStruct.RTC_AlarmTime		= RTC_AlarmTime;  //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask		= RTC_AlarmMask_None;//������λ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date; //���Ӱ�������Ӧ
	RTC_AlarmStruct.RTC_AlarmDateWeekDay 	= 8;
	
	//3���������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);
	//4���������ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);
	//5���������������жϣ�
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//�ж���17
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�жϼ�ʹ��
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = RTC_Alarm_IRQn;				//�ж�ͨ����ֻ����stm32f4xx.h�в���
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//��Ӧ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //ͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);
	 
	 
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);
}



//��д�жϷ�������
void RTC_Alarm_IRQHandler(void)
{

	//�жϱ�־�Ƿ���λ
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//�жϱ�־�Ƿ�Ϊ����A
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) ==  SET)
		{
			
			LED1(1);
			
			//�������A��־λ
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}
		
		//�жϱ�־�Ƿ�Ϊ����B
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) ==  SET)
		{
			
			LED2(1);
			
			//�������B��־λ
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line17);	
	}



}


