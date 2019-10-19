#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
#include "uart_drv.h"
#include "bank_drv.h"
#include "sdram_drv.h"
#include "printfhex.h"
#ifdef CONFIG_DEBUG
#include "my_printf.h"
#include "nor_drv.h"
#include "nand_drv.h"
#include "adc_drv.h"
#include "timer_drv.h"


extern int ms_time;
#else
	int printf(const char *fmt, ...)
	{
	
	}
#endif

void printf1(void)
{
	printf("哈哈哈 不乱码！！\r\n");
}
void printf2(void)
{
	printf("哈哈哈\r\n");
}

int main(void)
{
	
	volatile int Key,i;
	int c,v=1;
	lcd_test();
	//add_list(1000,printf1);
//	return 0;
}

