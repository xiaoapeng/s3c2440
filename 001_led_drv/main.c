#include "led_drv.h"


//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6

void delayed(volatile int us)
{
	volatile int i=4,n;
	while(i--)
		for(n=us;n;n--);
}



int main(void)
{
#if 0
	unsigned int *pGPFCON =(unsigned int *)GPFCON;
	unsigned int *pGPFDAT =(unsigned int *)GPFDAT;
	*pGPFCON =0x100;
	*pGPFDAT =0x0;
#endif
	led_config();
	while(1)
	{
		led1(0);
		delayed(10000);
		led1(1);
		led2(0);
		delayed(10000);
		led2(1);
		led3(0);
		delayed(10000);
		led3(1);
	}
	return 0;
}
