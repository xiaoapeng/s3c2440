#include "gpio.h"



typedef unsigned int gpiocon_t;
int gpio_set(unsigned int gpio_addr,unsigned int mask,unsigned int val)
{
	unsigned int gpiocon = dgpio(gpio_addr);
	//如果超出要操作的范围 说明该调用不合法
	if((~mask)&val)
		return -1;
	//先清除要操作的位 在对该位赋值 
	RESER_GPIO_VAL(&gpiocon, mask);
	SET_GPIO_VAL(&gpiocon, val);
	dgpio(gpio_addr)=gpiocon;
	return 0;
}


