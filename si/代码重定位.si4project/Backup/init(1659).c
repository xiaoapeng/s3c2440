//用于代码重定位等等一些初始化操作

#include "sdram_drv.h"

#ifdef CONFIG_DEBUG

#include "my_printf.h"
extern unsigned long data_load_addr;
extern unsigned long data_start;
extern unsigned long data_end;

#endif //CONFIG_DEBUG


int init(void)
{
	//初始化sdram 将sdram映射到内存
	sdram_config();
	uart0_config();
	led_config();
	key_config();
	//进行date重定向
#ifdef CONFIG_DEBUG
	printf("data_load_addr=%d\r\n",data_load_addr);
	printf("data_start=%d\r\n",data_start);
	printf("data_end=%d\r\n",data_end);
#endif //CONFIG_DEBUG

}





