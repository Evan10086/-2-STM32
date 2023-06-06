#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"

u32 time_count = 0;

//1、配置蜂鸣器为PWM输出，控制蜂鸣器声音大小。
//粗延时
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}

//   beep     PF8/TIM13_CH1/FSMC_NIOWR/ADC3_IN6 
int main(void)
{
	
	int count = 0;

	
	
	//设置NVIC分组 一个工程,NVIC只能分组一次
	//NVIC分为第二组 抢占优先级范围:0~3  响应优先级范围:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	Delay_Init();
    Pwm_PF8_Init();

	

	
	while(1)
	{
		
		//GPIO_ToggleBits(GPIOE, GPIO_Pin_14);	
		//for(int n=1000;n<=0;n-=500)//   beep     PF8/TIM13_CH1/FSMC_NIOWR/ADC3_IN6 )
		
		
		TIM_SetCompare1(TIM13,100);
		
		delay_s(2);  
		
		TIM_SetCompare1(TIM13,888);
		delay_s(2);  
		//不断改变比较值CCRx，达到不同的占空比效果：
	}
	
	return 0;
}




