#include "stm32f10x.h"
#include "systick_delay.h"

void Delay_us(uint32_t n) 
{
	SysTick->LOAD=72*n;      //װ�ؼ���ֵ����Ϊʱ��72M��72����1��s???
	SysTick->CTRL=0x00000005;   //ʱ����Դ��ΪΪHCLK(72M)���򿪶�ʱ��???
	while(!(SysTick->CTRL&0x00010000));   //�ȴ�������0???
	SysTick->CTRL=0x00000004;   //�رն�ʱ��
	
}
void Delay_ms(uint32_t n)
{
	Delay_us(1000*n); 
	//return;
	
}
