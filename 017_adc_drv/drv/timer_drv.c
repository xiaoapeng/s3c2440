#include "gpio.h"
#include "timer_drv.h"
//PCLK 50MHZ 
extern unsigned int ms_time;
static int init_clk=0;
static inline clk_init(void)
{
	//时钟频率=50M/(99+1)/分频值
	dgpio(TCFG0)=99;
	//输入时钟 500 000= 50 000 000 /100
}


#define if_init_clk()\
do{\
	if(init_clk==0)\
	{\
		clk_init();\
	}\
}while(0)\

//#define if_init_clk() 
void timer0_config(void)
{
	if_init_clk();
	
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
void timer1_config(void)
{
	if_init_clk();
	//设置为8分频
	//12000hz=12khz=100khz/8
	gpio_set(TCFG1,(0xf<4),(0x0<<4));
	
	
	//timer0的初值 250 为一毫秒
	dgpio(TCNTB1) =250; 

	//加载初值
	gpio_set(TCON,(1<<9),(1<<9));

	//设置开始且打开定时器
	gpio_set(TCON,(0xf<<8),(1<<8)|(1<<11));
	gpio_set(INTMSK,(1<<11),0<<0);
}
void delay(int ms)
{
	unsigned int ms_end=ms_time+ms;
	while(ms_time<ms_end) { }
}


