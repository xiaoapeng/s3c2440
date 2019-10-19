#include "gpio.h"
#include "led_drv.h"
#include "my_printf.h"
#include "int.h"

handle_irq_fun_t irq_fun[FUN_SiZE]={0};
#define  NULL ((void *)0)

void handle_irq(void)
{
	int val=dgpio(EINTPEND);
	int bit =dgpio(INTOFFSET);
	//处理中断
	if(bit==EINT2)
	{
		printf("irq_fun[bit]=0x%08x",(int)irq_fun[bit]);
	}
	if(irq_fun[bit]!=NULL)
		irq_fun[bit]();
	else	
		printf("nudefine handle num:%d\r\n",bit);
	dgpio(EINTPEND)=val;
	gpio_set(SRCPND,(1<<bit),(1<<bit));
	gpio_set(INTPND,(1<<bit),(1<<bit));

}
void register_irq(int irq,handle_irq_fun_t fun)
{
	irq_fun[irq]=fun;
	gpio_set(INTMSK,1<<irq,0);
}

