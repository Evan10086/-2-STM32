#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "sr04.h"
#include "dht11.h"
#include "iwdg.h"
#include "stdio.h"


u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART1_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//��������
		buffer[count++] = USART_ReceiveData(USART1);
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
	
	int ret = 0;
	u8 data[5] = {0};
	
	
	//����NVIC���� һ������,NVICֻ�ܷ���һ��
	//NVIC��Ϊ�ڶ��� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();
	Exti_PA0_Init();
	Usart1_Init(115200);
	Dht11_Init();
	Iwdg_Init();
	Tim7_Init();
    printf("iwdg test\r\n");
	
	while(1)
	{
		ret = Dht11_Start();
		if(ret == 0)
		{

			ret = Dht11_Data(data);
			if(ret == 0)
			{
				printf("ʪ�ȣ�%d.%d\r\n", data[0],data[1]);
				printf("�¶ȣ�%d.%d\r\n", data[2],data[3]);
			}
			
		}
		
		delaly_s(2);
		
	}
	
	return 0;
}




