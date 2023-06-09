#include "rtc.h"


#define BKR		0x54102


void Rtc_Init(void)
{

	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	//1、使能PWR时钟：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//2、使能后备寄存器(断电依然保存数据)访问:  
	PWR_BackupAccessCmd(ENABLE);
	
	//判断后备寄存器里面的值
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKR )
	{
	
		//3、配置RTC时钟源，使能RTC时钟：
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//如果使用LSE，要打开LSE：
		RCC_LSEConfig(RCC_LSE_ON);
		
		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //24小时制
		RTC_InitStruct.RTC_AsynchPrediv	= 0x7F;		//异步通道分频 128
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;		//同步通道分频 256
		//4、 初始化RTC(同步/异步分频系数和时钟格式)：
		RTC_Init(&RTC_InitStruct);
		
		
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM;	//下午
		RTC_TimeStruct.RTC_Hours	= 11;//时
		RTC_TimeStruct.RTC_Minutes	= 29;//分
		RTC_TimeStruct.RTC_Seconds	= 10;//秒
		
		//5、 设置时间：
		RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 23; //年
		RTC_DateStruct.RTC_Month	= 3;	//月
		RTC_DateStruct.RTC_Date		= 8;	//日
		RTC_DateStruct.RTC_WeekDay	= 3;	//星期
		//6、设置日期：
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
		
		
		//写后备寄存器
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKR);
	}

}
//设置时间
void Rtcc_Init(int h1, int m1, int s1)
{

	RTC_TimeTypeDef		RTC_TimeStruct;

	RTC_TimeStruct.RTC_Hours	= h1;//时
	RTC_TimeStruct.RTC_Minutes	= m1;//分
	RTC_TimeStruct.RTC_Seconds	= s1;//秒
	
	//5、 设置时间：
	RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
	

}

//闹钟A配置
void Rtc_SetAlarm_A(int data,int h2, int m2, int s2)
{
	RTC_TimeTypeDef 	RTC_AlarmTime;
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	//2、关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;	//下午
	RTC_AlarmTime.RTC_Hours		= h2;//时
	RTC_AlarmTime.RTC_Minutes	= m2;//分
	RTC_AlarmTime.RTC_Seconds	= s2;//秒
	
	RTC_AlarmStruct.RTC_AlarmTime		= RTC_AlarmTime;  //时间设置
	RTC_AlarmStruct.RTC_AlarmMask		= RTC_AlarmMask_None;//无掩码位
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date; //闹钟按日期响应
	RTC_AlarmStruct.RTC_AlarmDateWeekDay 	= data;
	
	//3、配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
	//4、开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
	//5、开启配置闹钟中断：
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//中断线17
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断级使能
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = RTC_Alarm_IRQn;				//中断通道，只能在stm32f4xx.h中查找
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//响应优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //通道使能
	 NVIC_Init(&NVIC_InitStructure);
	 
	 
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
}




//闹钟B配置
void Rtc_SetAlarm_B(void)
{
	RTC_TimeTypeDef 	RTC_AlarmTime;
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	//2、关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;	//下午
	RTC_AlarmTime.RTC_Hours		= 15;//时
	RTC_AlarmTime.RTC_Minutes	= 12;//分
	RTC_AlarmTime.RTC_Seconds	= 10;//秒
	
	RTC_AlarmStruct.RTC_AlarmTime		= RTC_AlarmTime;  //时间设置
	RTC_AlarmStruct.RTC_AlarmMask		= RTC_AlarmMask_None;//无掩码位
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date; //闹钟按日期响应
	RTC_AlarmStruct.RTC_AlarmDateWeekDay 	= 8;
	
	//3、配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);
	//4、开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);
	//5、开启配置闹钟中断：
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//中断线17
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断级使能
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = RTC_Alarm_IRQn;				//中断通道，只能在stm32f4xx.h中查找
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//响应优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //通道使能
	 NVIC_Init(&NVIC_InitStructure);
	 
	 
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);
}



//编写中断服务函数：
void RTC_Alarm_IRQHandler(void)
{

	//判断标志是否置位
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//判断标志是否为闹钟A
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) ==  SET)
		{
			
			LED1(1);
			
			//清空闹钟A标志位
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}
		
		//判断标志是否为闹钟B
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) ==  SET)
		{
			
			LED2(1);
			
			//清空闹钟B标志位
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}
		//清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line17);	
	}



}


