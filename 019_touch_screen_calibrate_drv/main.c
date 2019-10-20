#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
#include "uart_drv.h"
#include "bank_drv.h"
#include "sdram_drv.h"
#include "printfhex.h"
#ifdef CONFIG_DEBUG
#include "my_printf.h"
#include "nor_drv.h"
#include "nand_drv.h"
#include "adc_drv.h"
#include "timer_drv.h"
#include "lcd_map.h"
#include "framebuffer.h"


extern int ms_time;
#else
	int printf(const char *fmt, ...)
	{
	
	}
#endif

void printf1(void)
{
	printf("哈哈哈 不乱码！！\r\n");
}
void printf2(void)
{
	printf("哈哈哈\r\n");
}

int main(void)
{
	
	volatile int Key,i;
	int c,v=1,x,y,xx,yy,xxbak=0,yybak=0;
	lcd_test();
	lcd_map_init();
	while(1)
	{
		get_xy(&x,&y);
		map_xy(x,y,&xx,&yy);
		if(yybak==0)
			fb_put_pixel(xx,yy,0xffffff);
		else
		{
			draw_line(xxbak,yybak,xx,yy,0xffffff);
		}
		xxbak=xx;
		yybak=yy;
		printf("<<<x:%08d  y:%08d>>>",xx,yy);
		delay(10);
	}
	//add_list(1000,printf1);
//	return 0;
}

