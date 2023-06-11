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
#include "adc.h"
#include "flash.h"
#include "iic.h"

u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;

RTC_TimeTypeDef		RTC_TimeStruct;
RTC_DateTypeDef		RTC_DateStruct;


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
//	u8 write_buff[6] = "HELLO";
//	u8 read_buff[6] = {0};

	u8 write_buf[27] = "adcdefghijklmnopqrstuvwxyz";
	u8 read_buf[27] = {0};	
	
	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();
	Usart1_Init(115200);

	Iic_Init();
//	AT24c02_Write_Byte(0x00, write_buff, 5);	
//	delay_ms(10);
//	AT24c02_Read_Byte(0x00, read_buff, 5);
//	
//	printf("read_buff:%s\r\n", read_buff);
	
	
	AT24c02_Write_Data(0x08, write_buf, 26);	
	delay_ms(10);
	AT24c02_Read_Byte(0x08, read_buf, 26);
	
	printf("read_buf:%s\r\n", read_buf);	
	
	while(1)
	{

		
		

		
	}
	
	return 0;
}




