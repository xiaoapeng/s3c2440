#ifndef  _LED_DRV_H_
#define  _LED_DRV_H_
#include "gpio.h"

//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6




extern void led_config();
#define led1(val) gpio_set(GPFDAT,(1<<4),(val<<4))
#define led2(val) gpio_set(GPFDAT,(1<<5),(val<<5))
#define led3(val) gpio_set(GPFDAT,(1<<6),(val<<6))






#endif

