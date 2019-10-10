#include "led_drv.h"
extern int printf(const char *fmt, ...);
void printException(unsigned int cpsr,char *str)
{
	led1(1);
	printf("cpsr=0x%08x\r\n%s",cpsr,str);
}





