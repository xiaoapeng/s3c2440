//用于代码重定位等等一些初始化操作
#include "led_drv.h"
#include "sdram_drv.h"

#ifdef CONFIG_DEBUG

#include "my_printf.h"


#endif //CONFIG_DEBUG

extern unsigned int data_load_addr;
extern unsigned int data_start;
extern unsigned int data_end;
extern unsigned int bss_start;
extern unsigned int bss_end;


static void relocation(void)
{
	unsigned int *data_load_addr_p=&data_load_addr;//(unsigned char *)0x1000;
	unsigned int *data_start_p=&data_start;
	unsigned int *data_end_p=&data_end;

	unsigned int *bss_start_p=&bss_start;
	unsigned int *bss_end_p=&bss_end;
	
	int i,n;
	printf("data_load_addr=%d\r\n",(int)data_load_addr_p);
	printf("data_start=%d\r\n",(int)data_start_p);
	printf("data_end=%d\r\n",(int)data_end_p);
	printf("bss_start=%d\r\n",(int)bss_start_p);
	printf("bss_end=%d\r\n",(int)bss_end_p);
	while(data_start_p<bss_end_p)
	{
		*data_start_p=*data_load_addr_p;
		data_load_addr_p++;
		data_start_p++;
	}
	while(bss_start_p<bss_end_p)
	{
		*bss_start_p=0;
		bss_start_p++;
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





