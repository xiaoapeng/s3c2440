#include "gpio.h"
#include "key_drv.h"
#include "led_drv.h"

#define DE 10







//一共三个按键
#define KEY_NU 3
struct key_flag key[KEY_NU];

void init_key_st(int i,unsigned int GPXCON,int pinX)
{
	key[i].GPFXDAT=GPXCON;
	key[i].pin=pinX;
	key[i].flag=0;
}
int key_config(void)
{
	//初始化按键为输入引脚 读到低电平为按下
	//S2	GPF0
	//S3	GPF2
	//S4	GPG3
	//S5	GPG11
	init_key_st(0,GPFDAT,0);
	init_key_st(1,GPFDAT,2);
	init_key_st(2,GPGDAT,3);
	//将各个引脚配置为中断
	if(gpio_set(GPFCON,(3<<0)|(3<<4),(2<<0)|(2<<4))==-1)
		return -1;
	if(gpio_set(GPGCON,(3<<6)|(3<<22),(2<<6)|(2<<22))==-1) //66
		return -1;
	//配置中断触发方式 双边缘
	if(gpio_set(EXTINT0,(7<<0)|(7<<8),(7<<0)|(7<<8))==-1) //66
		return -1;
	if(gpio_set(EXTINT1,(7<<12),(7<<12))==-1) //66
		return -1;
	if(gpio_set(EXTINT2,(7<<12),(7<<12))==-1) //66
		return -1;
	//使能EINT11,19
	if(gpio_set(EINTMASK,(1<<11)|(1<<19),(0<<11)|(0<<19))==-1) //66
		return -1;
	//初始化中断控制器
	if(gpio_set(INTMSK,(1<<0)|(1<<2)|(1<<5),(0<<0)|(0<<2)|(0<<5))==-1)
		return -1;
	return 0;
}
//不忽略抖动 返回按下事件或者抬起事件


//规定返回0时没有事件产生 
//返回正数为按下
//负数为抬起
int get_event(void)
{
	int i=0;
	for(i=0;i<KEY_NU;i++)
	{
		if(key[i].flag==get_gpio(key[i].GPFXDAT,key[i].pin))
		{
			key[i].flag=!key[i].flag;
			//led1(key[i].flag);
			return (key[i].flag)? i+1 : -(i+1);
		}
	}
	return 0;
}
int key_read(int EvenFlag)
{ 
	
	int event,i;
	event=get_event();
	if(event==0) 
	{
		goto add_tiem;
	}
	
	if(event>0)
	{
		//按下事件
		//led1(0);
		key[event-1].count=0; //开始计数
	}else if(event<0)
	{
		//抬起事件 
		//单按
		//led1(1);	
		if(!EvenFlag&&(key[((-event)-1)].count)>=DE)
		{
			return ((-event)-1);
		}
	}

	add_tiem:
	for(i=0;i<KEY_NU;i++)
	{
		if (key[i].flag) 
		{
			key[i].count++;
			if(EvenFlag&&key[i].count>=DE)
			{
				key[i].count=0;
				return i;
			}
		}
	}

}



