#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"

u32 time_count = 0;

//1�����÷�����ΪPWM��������Ʒ�����������С��
//����ʱ
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

	
	
	//����NVIC���� һ������,NVICֻ�ܷ���һ��
	//NVIC��Ϊ�ڶ��� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ:0~3 
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
		//���ϸı�Ƚ�ֵCCRx���ﵽ��ͬ��ռ�ձ�Ч����
	}
	
	return 0;
}




