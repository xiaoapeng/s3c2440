#include "gpio.h"
#include "timer_drv.h"
void timer0_config(void)
{
	dgpio(TCFG0)=0x99;
	gpio_set(TCFG1,0xf,0x3);
	
	//timer0的初值
	dgpio(TCNTB0) =15625;

	//加载初值
	gpio_set(TCON,(1<<1),(1<<1));

	//设置开始且打开定时器自动重装载开关
	gpio_set(TCON,(0xf<<0)|(1<<4),(1<<0)|(1<<3));
	
	//设置中断控制器 使能中断
	gpio_set(INTMSK,(1<<10),0<<0);
	
	
}

