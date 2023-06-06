#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"


u16 time_count = 0;


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

	//SysTickʱ������ SystemCoreClock = 168000 000
	SysTick_Config(SystemCoreClock/1000);

	GPIO_ResetBits(GPIOE, GPIO_Pin_14);	
	
	while(1)
	{
		
	}
	
	return 0;
}


void  SysTick_Handler(void)
{
	time_count++;
	
	if(time_count%1000 == 0)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
	}
	

}


