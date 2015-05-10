#include "stm32f10x.h"
#include "systick_delay.h"

void Delay_us(uint32_t n) 
{
	SysTick->LOAD=72*n;      //装载计数值，因为时钟72M，72次在1μs???
	SysTick->CTRL=0x00000005;   //时钟来源设为为HCLK(72M)，打开定时器???
	while(!(SysTick->CTRL&0x00010000));   //等待计数到0???
	SysTick->CTRL=0x00000004;   //关闭定时器
	
}
void Delay_ms(uint32_t n)
{
	Delay_us(1000*n); 
	//return;
	
}
