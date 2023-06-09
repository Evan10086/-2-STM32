#include "rtc.h"

#define BKP   0x2281A1


void Rtc_My_Init(void)
{
	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	//1��ʹ��PWRʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//2��ʹ�ܺ󱸼Ĵ�������,���Ƕϵ�ɱ������� 
	PWR_BackupAccessCmd(ENABLE);
	
	
	//�жϺ󱸼Ĵ���ֵ
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP)
	{
		//3������RTCʱ��Դ��ʹ��RTCʱ�ӣ�
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//���ʹ��LSE��Ҫ��LSE��
		RCC_LSEConfig(RCC_LSE_ON);
		
		
		
		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //24Сʱ��
		RTC_InitStruct.RTC_AsynchPrediv = 0x7F; 			//�첽��Ƶ 128��Ƶ
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;				//ͬ����Ƶ 256��Ƶ
		//4�� ��ʼ��RTC(ͬ��/�첽��Ƶϵ����ʱ�Ӹ�ʽ)��
		RTC_Init(&RTC_InitStruct);
		
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM;  //����
		RTC_TimeStruct.RTC_Hours	= 15; //ʱ
		RTC_TimeStruct.RTC_Minutes	= 40; //��
		RTC_TimeStruct.RTC_Seconds	= 20; //��
		
		//5�� ����ʱ�䣺
		RTC_SetTime (RTC_Format_BIN,&RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 23;//��
		RTC_DateStruct.RTC_Month	= 6; //��
		RTC_DateStruct.RTC_Date		= 7; //��
	//	RTC_DateStruct.RTC_WeekDay	= 3; //����
		RTC_DateStruct.RTC_WeekDay	=RTC_Weekday_Wednesday;//����
		//6���������ڣ�
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);	
		
		//������д��󱸼Ĵ���
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKP);
		
	}

}


void RTC_Alarm_AInit(void)
{
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	
	//2���ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//����ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;  //����
	RTC_AlarmTime.RTC_Hours		= 15; //ʱ
	RTC_AlarmTime.RTC_Minutes	= 41; //��
	RTC_AlarmTime.RTC_Seconds	= 30; //��	
	
	
	
	RTC_AlarmStruct.RTC_AlarmTime = RTC_AlarmTime; //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_None;//������λ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;//��������Ӧ����
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 7; //7��
	
	//3���������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
	//4���������ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
	//5���������������жϣ�
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);



	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//�ж���
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = RTC_Alarm_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	


}



void RTC_Alarm_BInit(void)
{
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	
	//2���ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//����ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;  //����
	RTC_AlarmTime.RTC_Hours		= 15; //ʱ
	RTC_AlarmTime.RTC_Minutes	= 42; //��
	RTC_AlarmTime.RTC_Seconds	= 30; //��	
	
	
	
	RTC_AlarmStruct.RTC_AlarmTime = RTC_AlarmTime; //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_None;//������λ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;//��������Ӧ����
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 7; //7��
	
	//3���������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);
	//4���������ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);
	//5���������������жϣ�
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);



	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//�ж���
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = RTC_Alarm_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	


}


//6����д�жϷ�������

void RTC_Alarm_IRQHandler(void)
{

	//�ж��жϱ�־λ�Ƿ���1
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//�ж��Ƿ�������A�жϱ�־
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)
		{
		
			LED0(1);
			
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}

		//�ж��Ƿ�������B�жϱ�־
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) == SET)
		{
		
			LED3(1);
			
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}		
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line17);	
	}

}



