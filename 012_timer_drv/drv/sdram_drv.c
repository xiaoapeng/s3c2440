#include "sdram_drv.h"
#include "gpio.h"

void sdram_config(void)
{
	dgpio(BWSCON)=0x22000000;
	dgpio(BANKCON6)=0x18001;
	dgpio(BANKCON7)=0x18001;

	dgpio(REFRESH)=0x8404f5;

	dgpio(BANKSIZE)=0xb1;

	dgpio(MRSRB6)=0x20;
	dgpio(MRSRB7)=0x20;
}
int sdram_text(void)
{
	char *str=(char*)0x30000000;
	int i=0;
	for(i=0;i<10;i++)
	{
		str[i]=0x88;
	}
	for(i=0;i<10;i++)
	{
		if(str[i]!=0x88)
			return -1;
	}
}