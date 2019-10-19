#include "adc_drv.h"
#include "gpio.h"

void adc_config(unsigned char pipeline)
{
	//初始化adc
	gpio_set(ADCCON,0xffff,(1<<14)|(49<<6)|(pipeline<<3));
	dgpio(ADCDLY)=0xff;
}

int adc_read(void)
{
	dgpio(ADCCON) |= (1<<0);
	while (!(dgpio(ADCCON) & (1<<15)));  /* 等待ADC结束 */
	return dgpio(ADCDAT0) & 0x3ff;
}

