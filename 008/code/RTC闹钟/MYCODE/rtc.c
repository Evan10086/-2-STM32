#include "rtc.h"

#define BKP   0x2281A1


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


void RTC_Alarm_AInit(void)
{
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	
	//2、关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//闹钟时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;  //下午
	RTC_AlarmTime.RTC_Hours		= 15; //时
	RTC_AlarmTime.RTC_Minutes	= 41; //分
	RTC_AlarmTime.RTC_Seconds	= 30; //秒	
	
	
	
	RTC_AlarmStruct.RTC_AlarmTime = RTC_AlarmTime; //时间设置
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_None;//无掩码位
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;//按日期响应闹钟
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 7; //7号
	
	//3、配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
	//4、开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
	//5、开启配置闹钟中断：
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);



	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//中断线
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//中断线使能
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = RTC_Alarm_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	NVIC_Init(&NVIC_InitStructure);
	


}



void RTC_Alarm_BInit(void)
{
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	
	
	//2、关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//闹钟时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_PM;  //下午
	RTC_AlarmTime.RTC_Hours		= 15; //时
	RTC_AlarmTime.RTC_Minutes	= 42; //分
	RTC_AlarmTime.RTC_Seconds	= 30; //秒	
	
	
	
	RTC_AlarmStruct.RTC_AlarmTime = RTC_AlarmTime; //时间设置
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_None;//无掩码位
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;//按日期响应闹钟
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 7; //7号
	
	//3、配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);
	//4、开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);
	//5、开启配置闹钟中断：
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);



	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;			//中断线
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//中断线使能
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = RTC_Alarm_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	NVIC_Init(&NVIC_InitStructure);
	


}


//6、编写中断服务函数：

void RTC_Alarm_IRQHandler(void)
{

	//判断中断标志位是否置1
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//判断是否是闹钟A中断标志
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)
		{
		
			LED0(1);
			
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}

		//判断是否是闹钟B中断标志
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) == SET)
		{
		
			LED3(1);
			
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}		
		//清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line17);	
	}

}



