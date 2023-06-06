#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"



u8 rx_flag = 0;  //接受完毕标志
u8 rx_i, count = 0;
u8 buffer[32] = {0};
u8 rx_buffer[32] = {0};

void USART1_IRQHandler(void)
{
	//判断标志是否置位
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
		//串口1接收数据							
		buffer[count++] = USART_ReceiveData(USART1);	

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
//		printf("rx_buffer:%s\r\n", rx_buffer);
		

	}

}

//int check_fun(unsigned char *buf, int len)
//{
//    int i = 0;

//    unsigned char temp = 0;

//    for (i = 0; i < len; i++)
//    {
//        temp += buf[i];
//    }

//		if(buf[i] == temp)
//		{
//			return 0;
//		}
//		else
//		{
//			return -1;
//		}
//}

int check_fun(unsigned char *buf, int len)
{
    int i = 0;

    unsigned char temp = buf[0];

    for (i = 1; i < len; i++)
    {
        temp ^= buf[i];
    }

	if(buf[i] == temp)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


int main(void)
{	
	
	
	//设置NVIC分组 第二组 抢占优先级范围：0~3 响应优先级范围：0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Init();
	
	
	Led_Init();


	Usart1_Init(115200);
	
	while(1)
	{
		if(rx_flag == 1)
		{
			printf("rx_buffer:%s\r\n", rx_buffer);
			
			if(check_fun(rx_buffer, 5) == 0)
			{
				if(strncmp(rx_buffer, "HCL11", 5) == 0)
			  {
					LED1(1);//亮灯
				}
				if(strncmp(rx_buffer, "HCL10", 5) == 0)
				{
					LED1(0);//灭灯
				}	
			
				if(strncmp(rx_buffer, "HCL21", 5) == 0)
				{
					LED2(1);
				}	
				if(strncmp(rx_buffer, "HCL20", 5) == 0)
				{
					LED2(0);
				}	
			
				if(strncmp(rx_buffer, "HCL31", 5) == 0)
				{
					LED3(1);
				}		
				if(strncmp(rx_buffer, "HCL30", 5) == 0)
				{
					LED3(0);
				}	
			
				if(strncmp(rx_buffer, "HCL41", 5) == 0)
				{
					LED4(1);
				}	
				if(strncmp(rx_buffer, "HCL40", 5) == 0)
				{
					LED4(0);
				}	
			}
			
			memset(rx_buffer, 0, sizeof(rx_buffer));
			
			rx_flag = 0;
		}
		
		
		//delay_s(1);
	}
	


	return 0;
}