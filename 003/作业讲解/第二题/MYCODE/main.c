#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)
{
	
	int count = 0;

	
	
	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Led_Init();

	Exti_PA0_Init();
	Exti_PE2_Init();
	Exti_PE3_Init();	
	Exti_PE4_Init();
	while(1)
	{
		delay(1000);
	
	}
	
	return 0;
}
