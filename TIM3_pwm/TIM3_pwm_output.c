
/***************************
	PA.06: (TIM3_CH1)  
  PA.07: (TIM3_CH2)  
  PB.00: (TIM3_CH3) 
  PB.01: (TIM3_CH4)  
***************************/
#include "TIM3_pwm_output.h"

/*
 * 函数名：TIM3_GPIO_Config
 * 描述  ：配置TIM3复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM3 clock enable */
	//PCLK1经过2倍频后作为TIM3的时钟源等于72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * 函数名：TIM3_Mode_Config
 * 描述  ：配置TIM3输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */

void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 5;	    //设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

void TIM3_CH1_Mode_Config(u16 CCR1_Val)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}
void TIM3_CH2_Mode_Config(u16 CCR2_Val)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR2_Val时为高电平

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 //使能通道2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}

/*
 * 函数名：TIM3_PWM_Init
 * 描述  ：TIM3 输出PWM信号初始化，只要调用这个函数
 *         TIM3的四个通道就会有PWM信号输出
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();
	TIM3_CH1_Mode_Config(0);
	TIM3_CH2_Mode_Config(0);
	TIM3_direction_gpio_config();
}

void TIM3_direction_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  /* GPIOC clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	
}

void TIM3_direction_action(int pwm_left,int pwm_right)
{
	pwm_left*=10;
	pwm_right*=10;
	
	if(pwm_left == 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	}
	if(pwm_right == 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	}
	if(pwm_left > 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		TIM3_CH1_Mode_Config(pwm_left);
	}
	if(pwm_right > 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		TIM3_CH2_Mode_Config(pwm_right);
	}
	if(pwm_left < 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		TIM3_CH1_Mode_Config(-pwm_left);
	}
	if(pwm_right < 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		TIM3_CH2_Mode_Config(-pwm_right);
	}
}



/******************* (C) COPYRIGHT 2012  *****END OF FILE************/
