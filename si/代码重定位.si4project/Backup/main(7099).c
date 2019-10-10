#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
#include "uart_drv.h"
#include "bank_drv.h"
#include "sdram_drv.h"

#ifdef CONFIG_DEBUG
#include "my_printf.h"
#endif
extern unsigned char data_load_addr;
extern unsigned char data_start;
extern unsigned char data_end;

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
char g_a='a';
char g_A='A';
int main(void)
{
	volatile int Key,i;
	int c,v=1;
	led1(0);
	//*((char*)(0x30000000))=*((char*)(0x1000));
	//*((char*)(0x30000001))=*((char*)(0x1001));


	for(i='z'-'a';i;i--)
	{
		putchar(g_a);
		putchar(g_A);
		g_a++;
		g_A++;
	}
	//while(1) putchar('a');
//	return 0;
}
