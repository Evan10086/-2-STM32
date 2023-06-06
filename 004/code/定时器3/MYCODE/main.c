#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"


u32 time_count = 0;


//粗延时
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{
	
	int count = 0;

	
	
	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Led_Init();
	Tim3_Init();

	Delay_Init();

	
	while(1)
	{
		
		GPIO_ToggleBits(GPIOE, GPIO_Pin_14);	
		delaly_s(1);
	}
	
	return 0;
}




