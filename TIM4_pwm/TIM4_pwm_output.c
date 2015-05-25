
/***************************
	PB.06: (TIM4_CH1)  
  PB.07: (TIM4_CH2)  
  PB.08: (TIM4_CH3) 
  PB.09: (TIM4_CH4)  
***************************/
#include "TIM4_pwm_output.h"

/*
 * ��������TIM4_GPIO_Config
 * ����  ������TIM4�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void TIM4_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM4 clock enable */
	//PCLK1����2��Ƶ����ΪTIM4��ʱ��Դ����72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM4 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*
 * ��������TIM4_Mode_Config
 * ����  ������TIM4�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 5;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
}
void TIM4_CH3_Mode_Config(u16 CCR3_Val)
{
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	
	/* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	  //����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);	  //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	

  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM4���ؼĴ���ARR
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��4	
}
void TIM4_CH4_Mode_Config(u16 CCR4_Val)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	
	/* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  //����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

  TIM_OC4Init(TIM4, &TIM_OCInitStructure);	  //ʹ��ͨ��3
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM4���ؼĴ���ARR
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��4	
}


void TIM4_direction_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	
}

void TIM4_CH3_direction_action(float pwm_in)
{ 
	pwm_in*=10;
	if(pwm_in == 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	}
	if(pwm_in > 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
		TIM4_CH3_Mode_Config((int)pwm_in);
	}
	if(pwm_in<0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		GPIO_SetBits(GPIOC, GPIO_Pin_4);
		TIM4_CH3_Mode_Config(-(int)pwm_in);
	}
}
void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();
	TIM4_CH3_Mode_Config(0);
	TIM4_CH4_Mode_Config(0);
	TIM4_direction_gpio_config();
}

/******************* (C) COPYRIGHT 2012  *****END OF FILE************/
