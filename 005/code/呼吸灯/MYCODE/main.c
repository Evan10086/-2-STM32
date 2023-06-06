#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"

u32 time_count = 0;


//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{
	
	int count = 0;

	
	
	//����NVIC���� һ������,NVICֻ�ܷ���һ��
	//NVIC��Ϊ�ڶ��� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();

	Pwm_PF9_Init();
	


	//���ϸı�Ƚ�ֵCCRx���ﵽ��ͬ��ռ�ձ�Ч����
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




