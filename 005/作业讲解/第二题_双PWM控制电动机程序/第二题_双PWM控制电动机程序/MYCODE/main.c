#include "stm32f4xx.h"
#include "exti.h"
#include "delay.h"
#include "pwm.h"

/*************************************
S1----正转/反转
S2----暂停/继续（暂停后其他按键失能）
S3----速度+
S4----速度-
开机初始状态为暂停，需要按S2运行，其他按键才能起作用
****************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	Exti_Init();
	PWM_TIM9_CH1_PA2_Init();
	PWM_TIM9_CH2_PA3_Init();
	while(1)
	{
		delay_s(1);
	}
}
