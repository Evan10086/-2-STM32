#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"


u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART3_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);	

		//��������
		buffer[count++] = USART_ReceiveData(USART3);
		//�жϽ��ܵ��ַ��Ƿ�Ϊ������
		if(buffer[count-1] == ':')
		{
			//���˽�����
			for(rx_i=0; rx_i<(count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i]; 
			}
			
			memset(buffer, 0, sizeof(buffer));
			
			//��һ֡���ݴ�buffer[0]��ʼ�洢
			count = 0;
			rx_flag = 1; //һ֡���ݽ������
		}	
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
//	Pwm_PB10_Init();
//	Pwm_PB11_Init();

	Usart3_Init(9600);
	
	
	while(1)
	{
		if(rx_flag == 1)
		{
			//��ӡ��ʵ��ͨ�� ��������ַ� ???????
			printf("rx_buffer:%s\r\n", rx_buffer);
			
			if(strcmp(rx_buffer, "HCL11") == 0)	//LED0����
			{
				LED0(1);
			}

			if(strcmp(rx_buffer, "HCL10") == 0)	//LED0����
			{
				LED0(0);	
			}
					
			
			memset(rx_buffer, 0, sizeof(rx_buffer));
			
			rx_flag = 0;
		}
	
	}
	return 0;
}




