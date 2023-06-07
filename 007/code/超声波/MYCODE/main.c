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
#include "sys.h"

GPIO_InitTypeDef   GPIO_InitStructure;

u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART1_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//接受数据
		buffer[count++] = USART_ReceiveData(USART1);
		//判断接受的字符是否为结束符
		if(buffer[count-1] == ':')
		{
			//过滤结束符
			for(rx_i=0; rx_i<(count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i]; 
			}
			
			memset(buffer, 0, sizeof(buffer));
			
			//下一帧数据从buffer[0]开始存储
			count = 0;
			rx_flag = 1; //一帧数据接受完成
		}	
	}
}





int main(void)
{
	
	uint32_t distance=0;
	uint32_t duty=10;
	uint32_t distance_safe=1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);

	/* Configure PF9 PF10 in output pushpull mode，配置PF9 PF10引脚为输出模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;		//第9根和10根引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//设置输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽模式，增加驱动电流
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//设置IO的速度为100MHz，频率越高性能越好，频率越低，功耗越低
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//不需要上拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	
	/* Configure PE13 PE14 in output pushpull mode，配置PE13 PE14引脚为输出模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;		//第13根和14根引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//设置输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽模式，增加驱动电流
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//设置IO的速度为100MHz，频率越高性能越好，频率越低，功耗越低
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//不需要上拉电阻
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	


	//配置中断优先级的分组
	//配置支持4个抢占优先级，支持4个响应优先级
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	PFout(9)=1;
	PFout(10)=1;	
	PEout(13)=1;
	PEout(14)=1;
	
	//串口1初始化，波特率115200bps
	usart1_init(115200);

	//超声波模块初始化
	sr04_init();
	
	//添加蜂鸣器初始化
	beep_init();
	
	
	//按键的初始化
	key_init();
	
	while(1)
	{
		distance=sr04_get_distance();
		
		if(distance==0xFFFFFFFF)
		{
			//模块有可能没有连接好，连接错引脚或杜邦线松动
			printf("sr04 is error\r\n");
		}
		else if(distance>=20 && distance<=4000)
		{
			//数据是正确的
			printf("distance=%dmm\r\n",distance);		
		
			if(distance>=200)
			{
				PFout(9)=1;
				PFout(10)=1;
				PEout(13)=1;
				PEout(14)=1;	
				
				distance_safe=1;
			}
			else if(distance>=150 && distance<200)
			{
				PFout(9)=0;
				PFout(10)=1;
				PEout(13)=1;
				PEout(14)=1;	

				
				distance_safe=1;
			}	
			else if(distance>=100 && distance<150)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=1;
				PEout(14)=1;	
				
				distance_safe=0;
				
				tim13_set_freq(2);

			}				
			else if(distance>=50 && distance<100)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=0;
				PEout(14)=1;	
				
				distance_safe=0;
				
				tim13_set_freq(4);

			}	

			else if(distance<50)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=0;
				PEout(14)=0;	
				
				tim13_set_freq(10);
				
				distance_safe=0;
			}	

			//若是安全距离，则蜂鸣器禁鸣
			if(distance_safe)
				tim13_set_duty(0);
			//若不是安全距离，则蜂鸣器根据对应的占空比进行鸣响
			else
				tim13_set_duty(duty);
				
		}
		else
		{
			//数据是异常的
			printf("sr04 get distance is error\r\n");			
		
		}
		
		//添加按键检测代码
		if(PAin(0)==0)
		{
			//占空比减1，声音变小
			if(duty>0)
			{
				duty-=1;
				
				tim13_set_duty(duty);
			
			}
				
		
		}
		
		if(PEin(2)==0)
		{
			//占空比加1，声音变大
			if(duty<30)
			{
				duty+=1;
				
				tim13_set_duty(duty);
			
			}		
		}
		
		//延时500ms
		delay_ms(500);
	}
	
	return 0;
}




