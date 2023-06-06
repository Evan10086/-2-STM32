#include "stm32f4xx.h"
#include "led.h"



//粗延时
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
		//第9位清0 灯亮
		GPIOF_ODR &= ~(0x01<<9);
		delay(1000);
		//第9位置1 灯灭
		GPIOF_ODR |= (0x01<<9);
		delay(1000);
	}
	
	return 0;
}
