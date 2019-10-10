#include "gpio.h"



typedef unsigned int gpiocon_t;
int gpio_set(unsigned int gpio_addr,unsigned int mask,unsigned int val)
{
	gpiocon_t* gpiocon = (gpiocon_t *)gpio_addr;

	if((~mask)&val)
		return -1;
	*gpiocon &=(~mask);	
	*gpiocon |=val;
}


