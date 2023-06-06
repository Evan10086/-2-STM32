#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"

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
	Delay_Init();	
	Led_Init();

	Pwm_PF9_Init();
	


	//不断改变比较值CCRx，达到不同的占空比效果：
	TIM_SetCompare1(TIM14, 900);
	
	while(1)
	{
		for(count=0; count <= 999; count++)
		{
			TIM_SetCompare1(TIM14, count);
			delay_ms(5);
		}
		
		for(count=999; count >=0 ; count--)
		{
			TIM_SetCompare1(TIM14, count);
			delay_ms(5);
		}		
	
	}
	
	return 0;
}




