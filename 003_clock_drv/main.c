#include "led_drv.h"
#include "key_drv.h"
#include "gpio.h"
//LED1 低电平触发       		引脚 GPF4
//LED2 低电平触发 			引脚 GPF5
//lED3 低电平触发 			引脚 GPF6

void delayed(volatile int us)
{

	while(us--);
}
void horse_race_lamp(void)
{
	while(1)
	{
		led1(0);
		delayed(100000);
		led1(1);
		led2(0);
		delayed(100000);
		led2(1);
		led3(0);
		delayed(100000);
		led3(1);		
	}
}
int main(void)
{

	volatile int Key,i;
	char led[3];
	for(i=0;i<3;i++) led[i]=0;
	led_config();
	
	key_config();

	horse_race_lamp();
	
	while(1)
	{	
		Key=key_read(0);
		switch (Key)
		{
			case S2:
				led3(led[2]);
				led[2]=!led[2];
			break;
			case S3:
				led2(led[1]);
				led[1]=!led[1];
			break;
			case S4:
				led1(led[0]);	
				led[0]=!led[0];
			break;
			case -1:
			break;
		}

	}
	return 0;
}
