# 1 "../lib/gpio.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "../lib/gpio.h"


# 1 "../lib/s3c2440_soc.h" 1
# 4 "../lib/gpio.h" 2





extern int gpio_set(unsigned int gpio_addr,unsigned int mask,unsigned int val);

static inline int get_gpio(unsigned int gpio_addr,int bit_count)
{
 return ((*((volatile unsigned int *)(gpio_addr)))>>bit_count)&(1U);
}
