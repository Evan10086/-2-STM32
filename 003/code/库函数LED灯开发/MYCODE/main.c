#include "stm32f4xx.h"
#include "led.h"



//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{

	Led_Init();
	
	
	
	while(1)
	{
		//����
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		delay(1000);
		//����
		GPIO_SetBits(GPIOF, GPIO_Pin_9);  
		delay(1000);
	}
	
	return 0;
}
