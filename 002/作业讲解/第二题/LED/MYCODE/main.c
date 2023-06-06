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
    //初始化四个Led灯
	Led_Init0();
	Led_Init1();
	Led_Init2();
	Led_Init3();
	
	
	while(1)
	{
		GPIOF_ODR &= ~(0x01<<9);//开灯
		delay(1000);
		GPIOF_ODR |= (0x01<<9);//关灯
		delay(1000);//设置延时
		GPIOF_ODR &= ~(0x01<<10);
		delay(1000);
		GPIOF_ODR |= (0x01<<10);
		delay(1000);
		GPIOE_ODR &= ~(0x01<<13);
		delay(1000);
		GPIOE_ODR |= (0x01<<13);
		delay(1000);
		GPIOE_ODR &= ~(0x01<<14);
		delay(1000);
		GPIOE_ODR |= (0x01<<14);
		delay(1000);
	}
	
	return 0;
}

	