#include "stm32f4xx.h"
#include "beep.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "sr04.h"
#include "dht11.h"
#include "iwdg.h"
#include "exti.h"
#include "rtc.h"
#include "adc.h"
#include "iic.h"
#include "flash.h"

u8 rx_flag = 0;  //rx_flag = 1��ʾ�����������
u8 rx_data = 0;
u8 buffer[32] = {0}, rx_buffer[32] = {0};
u8 count = 0, rx_i = 0;



void USART1_IRQHandler(void)
{
	
	//�жϽ����жϱ�־�Ƿ�Ϊ1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//��ձ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		//�������� �ȸ�ֵ�ټ�
		buffer[count++] = USART_ReceiveData(USART1);
		
		//�жϽ��ܵ��ַ��Ƿ�Ϊ ':'
		if(buffer[count-1] == ':')
		{
			//bufferѭ����ֵ��rx_buffer, ������Ҫ��ֵ':'  ���˽�����־
			for(rx_i=0; rx_i<(count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i];
			}
			
			memset(buffer, 0, sizeof(buffer));
			
			//ȷ����һ֡���λ�ô�buffer[0]��ʼ
			count = 0;
			
			rx_flag = 1;
		}
		
	}

}







int main(void)
{
	u8 write_buff[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 read_buff[27] = {0};
	//NVIC����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	Delay_Init();
	Led_Init();

	Usart1_Init(115200);
	Iic_Init();
	
//��������
	//Flash_write(0x08020000, write_buff, 26);
	
	delay_ms(10);
	
	Flash_Read(0x08020000, read_buff, 26);
	
	printf("read_buff:%s\r\n", read_buff);
	
	while(1)
	{
	
		delay_s(1);
	
	}

}
