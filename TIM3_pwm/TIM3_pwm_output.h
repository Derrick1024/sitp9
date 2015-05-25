#ifndef __PWM3_OUTPUT_H
#define	__PWM3_OUTPUT_H

#include "stm32f10x.h"

void TIM3_PWM_Init(void);
void TIM3_Mode_Config(void);
void TIM3_CH1_Mode_Config(u16 CCR1_Val);
void TIM3_CH2_Mode_Config(u16 CCR2_Val);
void TIM3_direction_gpio_config(void);
void TIM3_direction_action(int pwm_left,int pwm_right);

#endif /* __PWM3_OUTPUT_H */

