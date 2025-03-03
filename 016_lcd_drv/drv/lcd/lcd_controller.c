
#include "lcd_controller.h"

#define LCD_CONTROLLER_NUM 10

//lcd控制器函数指针数组
static p_lcd_controller p_array_lcd_controller[LCD_CONTROLLER_NUM];
static p_lcd_controller g_p_lcd_controller_selected;

//向下提供注册接口
int register_lcd_controller(p_lcd_controller plcdcon)
{
	int i;
	for (i = 0; i < LCD_CONTROLLER_NUM; i++)
	{
		if (!p_array_lcd_controller[i])
		{
			p_array_lcd_controller[i] = plcdcon;
			return i;
		}
	}
	return -1;		
}
//选择led控制器
int select_lcd_controller(char *name)
{
	int i;
	for (i = 0; i < LCD_CONTROLLER_NUM; i++)
	{
		if (p_array_lcd_controller[i] && !strcmp(p_array_lcd_controller[i]->name, name))
		{
			g_p_lcd_controller_selected = p_array_lcd_controller[i];
			return i;
		}
	}
	return -1;		
}


//向上提供初始化接口
int lcd_controller_init(p_lcd_params plcdparams)
{
	/* 调用所选择的LCD控制器的初始化函数 */
	if (g_p_lcd_controller_selected)
	{
		g_p_lcd_controller_selected->init(plcdparams);
		return 0;
	}
	return -1;
}
//向上提供使能接口
void lcd_controller_enable(void)
{
	if (g_p_lcd_controller_selected)
	{
		g_p_lcd_controller_selected->enable();
	}
}
//向上提供失能接口
void lcd_controller_disable(void)
{
	if (g_p_lcd_controller_selected)
	{
		g_p_lcd_controller_selected->disable();
	}
}

//向上提供添加接口
void lcd_contoller_add(void)
{
	s3c2440_lcd_contoller_add();
}

