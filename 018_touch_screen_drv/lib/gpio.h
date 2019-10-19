#ifndef _GPIO_H_
#define _GPIO_H_
#include "s3c2440_soc.h"

#define dgpio_bety(u_i_gpio)	(*((volatile unsigned char *)(u_i_gpio)))
#define dgpio(u_i_gpio)	(*((volatile unsigned int *)(u_i_gpio)))
#define SET_GPIO_VAL(GpioReg,val) 		((dgpio((GpioReg))|=(val)))
#define RESER_GPIO_VAL(GpioReg,mask) 	((dgpio((GpioReg))&=(~(mask))))
extern int gpio_set(unsigned int gpio_addr,unsigned int mask,unsigned int val);

static inline int get_gpio(unsigned int gpio_addr,int bit_count)
{
	return (dgpio(gpio_addr)>>bit_count)&(1U);
}


#endif



