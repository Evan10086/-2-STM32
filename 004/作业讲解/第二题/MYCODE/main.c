#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"


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
	Led_Init();
	Tim1_Init();
	//Exti_PA0_Init();
	//delay_s (2);
	//GPIO_ResetBits(GPIOF, GPIO_Pin_9);
	//GPIO_ResetBits(GPIOF, GPIO_Pin_10);
	
	while(1)
	{
		//delay_s(1);
		
		//GPIO_ToggleBits(GPIOF, GPIO_Pin_10);
	}
	
	return 0;
}




