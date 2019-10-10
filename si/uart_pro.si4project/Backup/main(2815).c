#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
#include "uart_drv.h"
//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6

void delayed(volatile int us)
{

	while(us--);
}
//跑马灯
void horse_race_lamp(void)
{
	while(1)
	{
		led1(0);
		delayed(100000);
		led1(1);
		led2(0);
		delayed(100000);
		led2(1);
		led3(0);
		delayed(100000);
		led3(1);		
	}
}
int main(void)
{

	volatile int Key,i;
	char c;
	char led[3];
	for(i=0;i<3;i++) led[i]=0;
	led_config();
	key_config();
	uart0_config();
	puts("helloc arm linux\r\n");
	while(1)
	{
		c=getchar();
		if(c=='\n'||c=='\r')
		{
			puts("\r\n");
			continue;
		}
		putchar(c);
	}
//	return 0;
}
