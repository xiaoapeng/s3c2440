//用于代码重定位等等一些初始化操作
#include "led_drv.h"
#include "sdram_drv.h"

#ifdef CONFIG_DEBUG

#include "my_printf.h"


#endif //CONFIG_DEBUG

extern unsigned char data_load_addr;
extern unsigned char data_start;
extern unsigned char data_end;

static void relocation(void)
{
	unsigned char *data_load_addr_p=&data_load_addr;//(unsigned char *)0x1000;
	unsigned char *data_start_p=&data_start;
	unsigned char *data_end_p=&data_end;
	int i,n;
	volatile unsigned char *p=&data_load_addr;
	for(i=0,n=data_end_p-data_start_p;i<n;i++)
	{
		data_start_p[i]=data_load_addr_p[i];
	}
}
int init(void)
{
	//初始化sdram 将sdram映射到内存
	sdram_config();
	uart0_config();
	led_config();
	key_config();
	//进行data重定向
	relocation();
#ifdef CONFIG_DEBUG
	//printf("data_load_addr=%d   \r\n",6);
	//printf("data_start=%d    \r\n",data_start);
	//printf("data_end=%d\r    \n",data_end);
#endif //CONFIG_DEBUG
}





