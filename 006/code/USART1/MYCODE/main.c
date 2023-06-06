#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"


u32 time_count = 0;

u8 data = 0x00;
u8 flag = 0;  //flag = 1,��ʾ�����������
//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}



void USART1_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//��������
		data = USART_ReceiveData(USART1);
		flag = 1;
		
		
	}



}





int main(void)
{
	
	int count = 0;

	
	
	//����NVIC���� һ������,NVICֻ�ܷ���һ��
	//NVIC��Ϊ�ڶ��� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();

	Usart1_Init(115200);
	
	while(1)
	{
		if(flag == 1)
		{
			if(data == '1')
			{
				LED0(1);
			}
			
			if(data == '0')
			{
				LED0(0);
			}		
			flag = 0;
		}
	
	}
	
	return 0;
}




