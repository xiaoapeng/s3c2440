#include "gpio.h"
#include "led_drv.h"


#define FUN_SiZE (32)
typedef void (*handle_irq_fun_t)(void);




void int_ADC_handle_irq(void)
{
}
void int_rtc_handle_irq(void)
{
}
void int_spi1_handle_irq(void)
{
}
void int_uart0_handle_irq(void)
{
}
void int_iic_handle_irq(void)
{
}

void int_usbh_handle_irq(void)
{
}
void int_usbd_handle_irq(void)
{
}
void int_nfcon_handle_irq(void)
{
}
void int_uart1_handle_irq(void)
{
}
void int_spi0_handle_irq(void)
{
}
void int_sdi_handle_irq(void)
{
}
void int_dma3_handle_irq(void)
{
}
void int_dma2_handle_irq(void)
{
}
void int_dma1_handle_irq(void)
{
}
void int_dma0_handle_irq(void)
{
}
void int_lcd_handle_irq(void)
{
}
void int_uart2_handle_irq(void)
{
}
void int_timer4_handle_irq(void)
{
}
void int_timer3_handle_irq(void)
{
}
void int_timer2_handle_irq(void)
{
}
void int_timer1_handle_irq(void)
{
}
void int_timer0_handle_irq(void)
{
}
void int_wdt_ac97_handle_irq(void)
{
}
void int_tick_handle_irq(void)
{
}
void int_flt_handle_irq(void)
{
}
void int_cam_handle_irq(void)
{
}
void int_8_23_handle_irq(void)
{
	//s4 s5
	unsigned int val = dgpio(EINTPEND);
	unsigned int val2 =dgpio(GPGDAT);
	
	if (val & (1<<11)) /* eint11 */
	{
		if (val2 & (1<<3)) /* s4 --> gpf4 */
		{
			/* 松开 */
			led1(1);
		}
		else
		{
			/* 按下 */
			led1(0);
		}
	}
	else if (val & (1<<19)) /* eint19 */
	{
		if (val2 & (1<<11))
		{
			/* 松开 */
			/* 熄灭所有LED */
			dgpio(GPFDAT) |= ((1<<4) | (1<<5) | (1<<6));
		}
		else
		{
			/* 按下: 点亮所有LED */
			dgpio(GPFDAT) &= ~((1<<4) | (1<<5) | (1<<6));
		}
	}


	
}
void int_4_7_handle_irq(void)
{
}
void int_3_handle_irq(void)
{
}
void int_2_handle_irq(void)
{
	unsigned int val1 = dgpio(GPFDAT);

	//s3
	if (val1 & (1<<2)) /* s3 --> gpf5 */
	{
		/* 松开 */
		led2(1);
	}
	else
	{
		/* 按下 */
		led2(0);
	}

}
void int_1_handle_irq(void)
{
}
void int_0_handle_irq(void)
{
	//s2
	unsigned int val1 = dgpio(GPFDAT);
	if (val1 & (1<<0)) /* s2 --> gpf6 */
	{
		/* 松开 */
		led3(1);
	}
	else
	{
		/* 按下 */
		led3(0);
	}
}
handle_irq_fun_t irq_fun[FUN_SiZE]={
int_0_handle_irq,int_1_handle_irq,int_2_handle_irq,int_3_handle_irq\
,int_4_7_handle_irq,int_8_23_handle_irq,int_cam_handle_irq\
,int_flt_handle_irq,int_tick_handle_irq,int_wdt_ac97_handle_irq\
,int_timer0_handle_irq,int_timer1_handle_irq,int_timer2_handle_irq\
,int_timer3_handle_irq,int_timer4_handle_irq,int_uart2_handle_irq\
,int_lcd_handle_irq,int_dma0_handle_irq,int_dma1_handle_irq\
,int_dma2_handle_irq,int_dma3_handle_irq,int_sdi_handle_irq\
,int_spi0_handle_irq,int_uart1_handle_irq,int_nfcon_handle_irq\
,int_usbd_handle_irq,int_usbh_handle_irq,int_iic_handle_irq\
,int_uart0_handle_irq,int_spi1_handle_irq,int_rtc_handle_irq\
,int_ADC_handle_irq
};







void handle_irq(void)
{
	int val=dgpio(EINTPEND);
	int bit =dgpio(INTOFFSET);
	//处理中断
	irq_fun[bit]();
	dgpio(EINTPEND)=val;
	gpio_set(SRCPND,(1<<bit),(1<<bit));
	gpio_set(INTPND,(1<<bit),(1<<bit));

}

