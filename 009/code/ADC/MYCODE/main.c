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
#include "rtc.h"
#include "adc.h"



u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;

RTC_TimeTypeDef		RTC_TimeStruct;
RTC_DateTypeDef		RTC_DateStruct;


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
	u16 adc_value;
	float V_value;
	
	

	//����NVIC���� һ������,NVICֻ�ܷ���һ��
	//NVIC��Ϊ�ڶ��� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ:0~3 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();	
	Led_Init();
	Usart1_Init(115200);
	Adc_PA5_Init();
	
	while(1)
	{

		adc_value = Get_Adc_Value();
		V_value = (adc_value/4095.0)*3.3;
		
		
		printf("adc_value:%d\r\n", adc_value);
		printf("V_value:%f\r\n", V_value);
		delaly_s(1);
		
		
	
		
	}
	
	return 0;
}




