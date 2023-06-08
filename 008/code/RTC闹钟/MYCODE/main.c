#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "sr04.h"
#include "dht11.h"
#include "iwdg.h"
#include "rtc.h"


u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART1_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//接受数据
		buffer[count++] = USART_ReceiveData(USART1);
		//判断接受的字符是否为结束符
		if(buffer[count-1] == ':')
		{
			//过滤结束符
			for(rx_i=0; rx_i<(count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i]; 
			}
			
			memset(buffer, 0, sizeof(buffer));
			
			//下一帧数据从buffer[0]开始存储
			count = 0;
			rx_flag = 1; //一帧数据接受完成
		}	
	}
}





int main(void)
{
	
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	u8 year,month,date,hour,min,sec,weekday;
	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();
	Usart1_Init(115200);

	Rtc_My_Init();
	RTC_Alarm_AInit();
	RTC_Alarm_BInit();
	
	
	
	
	while(1)
	{
		
		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
		RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
		
		hour= RTC_TimeStruct.RTC_Hours;	 	//?
		min = RTC_TimeStruct.RTC_Minutes;	//??
		sec	= RTC_TimeStruct.RTC_Seconds; 	//??
		
		year = RTC_DateStruct.RTC_Year;//??
		month= RTC_DateStruct.RTC_Month; //??
		date = RTC_DateStruct.RTC_Date; //??
	//	RTC_DateStruct.RTC_WeekDay	= 3; //????
		weekday = RTC_DateStruct.RTC_WeekDay;//????
		
		printf("日期：20%d-%d-%d: 星期：%d\r\n", year,month,date,weekday);
		printf("时间：%d:%d:%d\r\n", hour,min,sec);
		
	
		delaly_s(1);
		
		
	
		
	}
	
	return 0;
}




