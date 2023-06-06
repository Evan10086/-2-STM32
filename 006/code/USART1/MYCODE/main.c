#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"


u32 time_count = 0;

u8 data = 0x00;
u8 flag = 0;  //flag = 1,表示接受数据完成
//粗延时
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}



void USART1_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//接受数据
		data = USART_ReceiveData(USART1);
		flag = 1;
		
		
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

	Usart1_Init(115200);
	
	while(1)
	{
		if(flag == 1)
		{
			if(data == '1')
			{
				LED0(1);
			}
			
			if(data == '0')
			{
				LED0(0);
			}		
			flag = 0;
		}
	
	}
	
	return 0;
}




