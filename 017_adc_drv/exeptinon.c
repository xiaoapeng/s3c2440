#include "led_drv.h"
extern int printf(const char *fmt, ...);
void printException(unsigned int cpsr,char *str)
{
	printf("cpsr=0x%08x\r\n%s\r\n",cpsr,str);
}

void printSWIVal(int *val_p)
{
	unsigned int val;
	val=(*val_p )& ~0xff000000;
	printf("swival_addr=0x%x\r\n",(int)val_p,(int)val_p);
	printf("val=0x%08x\r\n",val);
	
}



