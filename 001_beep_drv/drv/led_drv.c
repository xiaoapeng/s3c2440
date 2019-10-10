#include "led_drv.h"


//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6

void led_config(void)
{
	gpio_set(GPFCON,(3<<8)|(3<<10)|(3<<12),(1<<8)|(1<<10)|(1<<12));
	gpio_set(GPFDAT,(1<<4)|(1<<5)|(1<<6),(1<<4)|(1<<5)|(1<<6));
}


