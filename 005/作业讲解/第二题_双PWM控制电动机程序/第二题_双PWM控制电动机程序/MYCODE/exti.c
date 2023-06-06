#include "exti.h"

/********************************************
引脚说明
KEY0-------PA0
KEY1-------PE2
KEY2-------PE3
KEY3-------PE4
按键未按下为1
按键按下为低0
*******************************************/
int Flag = 1;  //1 正转  0 反转
int speed = 700;
int FlagContinue = 0;// 1--运行   0---暂停


void Exti_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//使能 GPIOA时钟 GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
	//使能 SYSCFG时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;		//引脚0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//EXTI0连到GPIOA

	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;//使用中断线0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI0_IRQn;  //中断通道，可在stm32f4xx.h文件当中查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x00;		//响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//通道使能
	NVIC_Init(&NVIC_InitStructure);
/*****************************************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;		//引脚2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//EXTI2连到GPIOE
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line2;//使用中断线2
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI2_IRQn;  //中断通道，可在stm32f4xx.h文件当中查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;		//响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//通道使能
	NVIC_Init(&NVIC_InitStructure);
/***********************************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;		//引脚3 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//EXTI3连到GPIOE
	
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line3;//使用中断线3
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI3_IRQn;  //中断通道，可在stm32f4xx.h文件当中查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x02;		//响应优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//通道使能
	NVIC_Init(&NVIC_InitStructure);	
/*********************************************************************************/	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;		//引脚4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//EXTI4连到GPIOE
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line4;//使用中断线4
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI4_IRQn;  //中断通道，可在stm32f4xx.h文件当中查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x03;		//响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//通道使能
	NVIC_Init(&NVIC_InitStructure);
}
/*
正转-----
TIM_SetCompare2(TIM9, 0);    //通道二占空比为0  		PA3接GND
TIM_SetCompare1(TIM9, speed);//speed越大转的越快	    PA2输出PWM
反转----
TIM_SetCompare1(TIM9, 0);//通道一占空比为0          PA2接GND
TIM_SetCompare2(TIM9, speed);//speed越大转的越快	PA3输出PWM
*/
void EXTI0_IRQHandler(void)//S1正转/反转---切换
{
	static unsigned int cnt = 1;//开机时，第一次按下，按键起作用
	if(EXTI_GetITStatus(EXTI_Line0) == SET)//判断标志位是否为1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  == Bit_RESET)
		{
			if(FlagContinue)  //1--运行   0---暂停
			{
				if(++cnt % 2 == 1)//正转
				{
					TIM_SetCompare2(TIM9, 0);  //GND PA3接GND
					//
					TIM_SetCompare1(TIM9, speed);
					Flag = 1;   //正转标志
				}
				else//反转
				{
					TIM_SetCompare1(TIM9, 0); //GND  PA2接GND
					//
					TIM_SetCompare2(TIM9, speed);
					Flag = 0;  //反转标志
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);//清空中断标志位
	}
}
void EXTI2_IRQHandler(void)//S2暂停/继续
{
	static unsigned int sus = 1;//开机时，按一下为运行
	if(EXTI_GetITStatus(EXTI_Line2) == SET)//判断标志位是否为1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)  == Bit_RESET)
		{
			if(++sus % 2 == 1)//暂停
			{
				FlagContinue = 0;//暂停标志
				if(Flag == 1)//正转
				{
					TIM_SetCompare2(TIM9, 0);//通道二占空比为0
					TIM_SetCompare1(TIM9, 0);//通道一占空比为0
				}
				else//反转
				{
					TIM_SetCompare1(TIM9, 0);//通道一占空比为0
					TIM_SetCompare2(TIM9, 0);//通道二占空比为0
				}
			}
			else//继续
			{
				FlagContinue = 1;//继续标志
				if(Flag == 1)//正转
				{
					TIM_SetCompare2(TIM9, 0);//通道二占空比为0
					TIM_SetCompare1(TIM9, speed);
				}
				else//反转
				{
					TIM_SetCompare1(TIM9, 0);//通道一占空比为0
					TIM_SetCompare2(TIM9, speed);
				}

			}
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//清空中断标志位
}
void EXTI3_IRQHandler(void)//S3速度++
{
	if(EXTI_GetITStatus(EXTI_Line3) == SET)//判断标志位是否为1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)  == Bit_RESET)
		{
			if(FlagContinue)	//在运行态才能加速
			{
				if(Flag == 1)//正转
				{
					
					speed = speed + 50; //加速
			
					if(speed >= 999){speed = 999;}//速度最大为999
					
					TIM_SetCompare1(TIM9, speed);
					TIM_SetCompare2(TIM9, 0); //PA3--GND
				}
				else//反转
				{
				
					speed = speed + 50;
					if(speed >= 999){speed = 999;}//速度最大为999
					TIM_SetCompare2(TIM9, speed);
					TIM_SetCompare1(TIM9, 0);  //PA2--GND
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line3);//清空中断标志位
	}
}
void EXTI4_IRQHandler(void)//S4速度--
{
	if(EXTI_GetITStatus(EXTI_Line4) == SET)//判断标志位是否为1
	{
		delay(20);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)  == Bit_RESET)
		{
			if(FlagContinue)
			{
				if(Flag == 0)//反转
				{
					speed = speed - 50;
					if(speed < 200){speed = 200;} //	L298N接12V，这行代码改为speed < 0  	speed = 0
					TIM_SetCompare2(TIM9, speed);
					TIM_SetCompare1(TIM9, 0);
				}
				else//正转
				{
					speed = speed - 50;
					if(speed < 200){speed = 200;}	//	L298N接12V，这行代码改为speed < 0	speed = 0
					TIM_SetCompare1(TIM9, speed);
					TIM_SetCompare2(TIM9, 0);
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line4);//清空中断标志位
	}
}
//粗延时
void delay(int n)
{
	int i, j;

	for(i=0; i<n; i++)
		for(j=0; j<40000; j++);
}
