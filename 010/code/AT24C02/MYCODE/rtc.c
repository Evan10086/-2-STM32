#include "rtc.h"

#define BKP   0x22819


void Rtc_My_Init(void)
{
	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	//1、使能PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//2、使能后备寄存器访问,它是断电可保存数据 
	PWR_BackupAccessCmd(ENABLE);
	
	
	//判断后备寄存器值
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP)
	{
		//3、配置RTC时钟源，使能RTC时钟：
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//如果使用LSE，要打开LSE：
		RCC_LSEConfig(RCC_LSE_ON);
		
		
		
		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //24小时制
		RTC_InitStruct.RTC_AsynchPrediv = 0x7F; 			//异步分频 128分频
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;				//同步分频 256分频
		//4、 初始化RTC(同步/异步分频系数和时钟格式)：
		RTC_Init(&RTC_InitStruct);
		
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM;  //下午
		RTC_TimeStruct.RTC_Hours	= 15; //时
		RTC_TimeStruct.RTC_Minutes	= 40; //分
		RTC_TimeStruct.RTC_Seconds	= 20; //秒
		
		//5、 设置时间：
		RTC_SetTime (RTC_Format_BIN,&RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 23;//年
		RTC_DateStruct.RTC_Month	= 6; //月
		RTC_DateStruct.RTC_Date		= 7; //日
	//	RTC_DateStruct.RTC_WeekDay	= 3; //星期
		RTC_DateStruct.RTC_WeekDay	=RTC_Weekday_Wednesday;//星期
		//6、设置日期：
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);	
		
		//将数据写入后备寄存器
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKP);
		
	}
	
	
	


}