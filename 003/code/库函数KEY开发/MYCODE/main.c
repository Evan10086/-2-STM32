#include "stm32f4xx.h"
#include "led.h"
#include "key.h"



//粗延时
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{
	
	int count = 0;

	Led_Init();
	Key_Init();
	
	
	while(1)
	{
		/*
		//运用场景1 通过长按时长，处理不同事件
		//判断按键是否按下
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		{
			delay(20); //15ms延时消抖作用
			//判断按键是否按下
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
			{
				//按键按下
				
				//变更灯状态
				//GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
				count++;
			
			}			
			
		}
		//4s处理事件1
		if(count == 200)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
		}
		
		//8s处理事件2
		if(count == 400)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_13);	
		}		
		*/
		
		//判断按键是否按下
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		{
			delay(15); //15ms延时消抖作用
			//判断按键是否按下
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
			{
				//等待按键松开
				while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET);
				
				//变更灯状态
				GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
			
				
			
			}			
			
		}		
	
	}
	
	return 0;
}
