#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"



//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{

	Beep_Init();
	
	//��8λ��1 ��
	GPIOF_ODR |= (0x01<<8);
	delay(1000);	
	//��8λ��0  ����
	GPIOF_ODR &= ~(0x01<<8);
	delay(1000);
	
	while(1)
	{

	}
	
	return 0;
}
