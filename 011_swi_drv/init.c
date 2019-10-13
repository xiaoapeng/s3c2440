//用于代码重定位等等一些初始化操作
#include "led_drv.h"
#include "sdram_drv.h"
#include "interrupt_drv.h"
#include "key_drv.h"
#ifdef CONFIG_DEBUG

#include "my_printf.h"


#endif //CONFIG_DEBUG

extern unsigned int code_start;
extern unsigned int bss_start;
extern unsigned int end;

extern void relocation(void);

void relocation(void)
{
	unsigned int* lma_start_p=(unsigned int* )0;
	unsigned int* code_start_p=&code_start;
	unsigned int* bss_start_p=&bss_start;
	unsigned int* end_p=&end;
	//初始化sdram
	sdram_config();
	while(code_start_p<bss_start_p)
	{
		*code_start_p=*lma_start_p;
		code_start_p++;
		lma_start_p++;
	}
	while(bss_start_p<end_p)
	{
		*bss_start_p=0;
		bss_start_p++;
	}
}
int init(void)
{
	inierript_config();
	uart0_config();
	led_config();
	key_config();
	
#ifdef CONFIG_DEBUG
	//printf("data_load_addr=%d   \r\n",6);
	//printf("data_start=%d    \r\n",data_start);
	//printf("data_end=%d\r    \n",data_end);
#endif //CONFIG_DEBUG
}





