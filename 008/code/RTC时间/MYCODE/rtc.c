#include "rtc.h"

#define BKP   0x22819


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