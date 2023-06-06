#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"


u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART3_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);	

		//接受数据
		buffer[count++] = USART_ReceiveData(USART3);
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
	
	int count = 0;

	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();
//	Pwm_PB10_Init();
//	Pwm_PB11_Init();

	Usart3_Init(9600);
	
	
	while(1)
	{
		if(rx_flag == 1)
		{
			//打印，实现通过 串口输出字符 ???????
			printf("rx_buffer:%s\r\n", rx_buffer);
			
			if(strcmp(rx_buffer, "HCL11") == 0)	//LED0开关
			{
				LED0(1);
			}

			if(strcmp(rx_buffer, "HCL10") == 0)	//LED0开关
			{
				LED0(0);	
			}
					
			
			memset(rx_buffer, 0, sizeof(rx_buffer));
			
			rx_flag = 0;
		}
	
	}
	return 0;
}




