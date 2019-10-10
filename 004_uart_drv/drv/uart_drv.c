#include "uart_drv.h"
#include "gpio.h"
void uart0_config(void)
{
	//配置引脚用于串口 
	//GPH2 TXD0
	//GPH3 RXD0
	gpio_set(GPHCON,(3<<4)|(3<<6),(2<<4)|(2<<6)); 	//配置引脚属性
	gpio_set(GPHUP,(1<<2)|(1<<3),(0<<2)|(0<<3)); 	//配置tx引脚默认上拉 
	//配置波特率
	// UCON0 设置为pclk为波特率发生时钟   
	//UBRDIV0 =(int)(50000000/(115200*16))-1
	dgpio(UCON0)=0x00000005;
	dgpio(UBRDIV0)=26;
	//设置数据格式
	dgpio(ULCON0)=0x00000003;
}
int putchar(int c)
{
	while(!get_gpio(UTRSTAT0,2));
	dgpio(UTXH0)=(unsigned int)c;
}
int getchar(void)
{
	while(!get_gpio(UTRSTAT0,0));
	return dgpio(URXH0);
}

int puts(const char *s)
{
	int ret=0;
	while(*s)
	{
		putchar(*s);
		s++;
		ret++;
	}
	return ret;
}




