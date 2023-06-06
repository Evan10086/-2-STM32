#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"



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
	Key_Init();
	Exti_PA0_Init();


	
	while(1)
	{
		delay(1000);
	
	}
	
	return 0;
}
