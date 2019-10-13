#include "interrupt_drv.h"
#include "gpio.h"



/* SRCPND 用来显示哪个中断产生了, 需要清除对应位
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8_23
 */

/* INTMSK 用来屏蔽中断, 1-masked
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8_23
 */

/* INTPND 用来显示当前优先级最高的、正在发生的中断, 需要清除对应位
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8_23
 */

/* INTOFFSET : 用来显示INTPND中哪一位被设置为1
 */

//初始化中断控制器
int inierript_config(void)
{
	
}

