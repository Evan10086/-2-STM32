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

u8 rx_flag = 0;  //接受完毕标志
u8 rx_i, count = 0;
u8 buffer[32] = {0};
u8 rx_buffer[32] = {0};


void USART2_IRQHandler(void)
{

	
	//判断标志是否置位
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);			
		
		//***串口1接收数据***							
		buffer[count++] = USART_ReceiveData(USART2);	

		if(buffer[count-1] == ':')
		{
			//过滤结尾符':'
			for(rx_i=0; rx_i< (count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i];
				
			}
			
			//下一帧数据从buffer[0]开始接受。
			count = 0;
			
			//清空数组
			memset(buffer, 0, sizeof(buffer));
			
			//表示数据接受完成
			rx_flag = 1;		
		
		}

		

	}

}




int main(void)
{	
	
	u8 h1 = 0 ,h2 = 0;
	u8 m1 = 0 ,m2 = 0;
	u8 s1 = 0 ,s2 = 0;
	u8 data = 0;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	
	
	//设置NVIC分组 第二组 抢占优先级范围：0~3 响应优先级范围：0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Init();
	
	
	Led_Init();


//	Usart1_Init(9600);
	Usart2_Init(9600);
	
	Rtc_Init();

	
//	Rtc_SetAlarm_B();
	
	
	while(1)
	{
		if(rx_flag == 1)  
		{
			printf("rx_buffer:%s\r\n", rx_buffer);
			
			if(strncmp(rx_buffer, "HCD1", 4) == 0) //时间HCD1XXYYDD:(XX时 YY分 DD秒)  
			{
				
				h1 = (rx_buffer[4]-'0')*10+(rx_buffer[5]-'0'); //XX 将字符串转换为整型数  "21"转换21
				m1 = (rx_buffer[6]-'0')*10+(rx_buffer[7]-'0');
				s1 = (rx_buffer[8]-'0')*10+(rx_buffer[9]-'0');
				Rtcc_Init(h1, m1 ,s1);
				
				
			}
			
			if(strncmp(rx_buffer, "HCD0", 4) == 0)//时间HCD0BBXXYYDD:(BB:日期 XX时 YY分 DD秒)  
			{
				data = (rx_buffer[4]-'0')*10+(rx_buffer[5]-'0');	
				h2 = (rx_buffer[6]-'0')*10+(rx_buffer[7]-'0');
				m2 = (rx_buffer[8]-'0')*10+(rx_buffer[9]-'0');
				s2 = (rx_buffer[10]-'0')*10+(rx_buffer[11]-'0');
				Rtc_SetAlarm_A(data, h2, m2, s2);
			}	
			
		
			
			memset(rx_buffer, 0, sizeof(rx_buffer));
			
			rx_flag = 0;
		}
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
		
		printf("time: %02d:%02d:%02d\r\n",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
	
		printf("data: 20%02d:%02d:%02d\r\n",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);


		printf("week: %02d\r\n",RTC_DateStruct.RTC_WeekDay);
	
		delay_s(1);


	}
	


	return 0;
}