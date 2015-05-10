#include "stm32f10x.h"
#include "systick_delay.h"

#include "bsp_usart1.h"
#include "anbt_dmp_fun.h"
#include "anbt_i2c.h"
#include "anbt_dmp_mpu6050.h"
#include "anbt_dmp_driver.h"
#include "pwm_output.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define q30  1073741824.0f

int main(void)
{
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
	unsigned char more;
	long quat[4];
	float Yaw=0.00,Roll,Pitch;
	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
	
	USART1_Config();
	TIM3_PWM_Init();
	ANBT_I2C_Configuration();		//IIC初始化
	Delay_ms(5); 
	AnBT_DMP_MPU6050_Init();			//6050DMP初始化
	;
	
	while(1)
	{
		 dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);	
		

			 q0=quat[0] / q30;
			 q1=quat[1] / q30;
			 q2=quat[2] / q30;
			 q3=quat[3] / q30;
			 Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
			 Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
			 Yaw = 	-atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	
			 
			 printf("%.2f , %.2f , %.2f \n",Pitch,Roll,Yaw);
			                                 
	Delay_ms(20);   
	}
}

