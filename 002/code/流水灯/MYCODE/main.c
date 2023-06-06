#include "stm32f4xx.h"
#include "led.h"



//¥÷—” ±
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
		//µ∆¡¡
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		delay(1000);
		//µ∆√
		GPIO_SetBits(GPIOF, GPIO_Pin_9);  
		delay(1000);
		//µ∆¡¡
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		delay(1000);
		//µ∆√
		GPIO_SetBits(GPIOF, GPIO_Pin_10);  
		delay(1000);
		//µ∆¡¡
		GPIO_ResetBits(GPIOE, GPIO_Pin_13);
		delay(1000);
		//µ∆√
		GPIO_SetBits(GPIOE, GPIO_Pin_13);  
		delay(1000);
		//µ∆¡¡
		GPIO_ResetBits(GPIOE, GPIO_Pin_14);
		delay(1000);
		//µ∆√
		GPIO_SetBits(GPIOE, GPIO_Pin_14);  
		delay(1000);
		
	}
	
	return 0;
}
