#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
#include "uart_drv.h"
#include "bank_drv.h"
#include "sdram_drv.h"

#ifdef CONFIG_DEBUG
#include "my_printf.h"
#endif
//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6

void delayed(volatile int us)
{
	while(us--);
}
//跑马灯
void horse_race_lamp(int us)
{
	while(1)
	{
		led1(0);
		delayed(us);
		led1(1);
		led2(0);
		delayed(us);
		led2(1);
		led3(0);
		delayed(us);
		led3(1);
	}
}
int main(void)
{

	volatile int Key,i;
	int c,v=1;
	char led[3];
	for(i=0;i<3;i++) led[i]=0;
	led_config();
	key_config();
	uart0_config();
	sdram_config();
#ifdef CONFIG_DEBUG
	printf("%d-----%c------%s\r\n",1,'5',"dddddddddd");
#endif
	
	puts("set nor v!!\n\r");
	if(sdram_text()==-1)
		return -1;
	while(1)
	{
		//c=getchar();
		if(c=='\n'||c=='\r')
		{
			puts("\r\n");
			continue;
		}
		//putchar(c);
		horse_race_lamp(100000);
	}
//	return 0;
}
