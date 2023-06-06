#include "stm32f4xx.h"
#include "beep.h"

void delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<30000;j++);
}

int main(void)
{
	Beep_Init();
	
	//·äÃùÆ÷Ïì
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay(1000);
	//·äÃùÆ÷Í£
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
	delay(1000);	
	
	while(1)
	{

	}
	
	return 0;
}
