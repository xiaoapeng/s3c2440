#include "lcd_map.h"
#include "touchscreen.h"

static int swap=0;
double kx,ky;
int base_x,base_y,lcd_x,lcd_y;
void x_y_swap(int *x,int *y,int n)
{
	int i=0;
	int dswap;
	for(i=0;i<n;i++)
	{
		dswap=*x;
		*x=*y;
		*y=dswap;
		x++;
		y++;
	}
}
void get_touchscreen_xy(int a,int b,int *x,int *y)
{
	fb_disp_cross(a,b, 0xffffff);
	get_first_contact_xy(x,y);
	//printf("*****************x:0x%08x  y:0x%08x\r\n",*x,*y);
	
}
void lcd_map_init(void)
{
	unsigned int fb_base;
	int xres, yres, bpp;
	int x[5],y[5],sx,sy,ssx,ssy;
	
	get_lcd_params(&fb_base, &xres, &yres, &bpp);
	//使用五点校准法
	get_touchscreen_xy(50,50,&x[0],&y[0]);
	get_touchscreen_xy(xres-50,50,&x[1],&y[1]);
	get_touchscreen_xy(xres-50,yres-50,&x[2],&y[2]);
	get_touchscreen_xy(50,yres-50,&x[3],&y[3]);
	get_touchscreen_xy(xres/2,yres/2,&x[4],&y[4]);
	
	//测试xy轴的是否为置换
	if((x[1]-x[0])<(y[1]-y[0]))
	{
		swap=1;
		printf("000");
		x_y_swap(x,y,5);
	}
	sx=(x[1]-x[0])+(x[2]-x[3]);
	sy=(y[3]-y[0])+(y[2]-y[1]);
	ssx=(xres-50-50)*2;
	ssy=(yres-50-50)*2;
	base_x=x[4];
	base_y=y[4];
	lcd_x=xres/2;
	lcd_y=yres/2;
	kx=((double)ssx)/((double)sx);
	ky=((double)ssy)/((double)sy);
}

/*
@x 传入原始x
@y 传入原始y
@xx 传出映射值
@yy 传出映射值
*/
void map_xy(int x,int y,int *xx,int *yy)
{
	int swap_x;
	int sx,sy;
	if(swap)
	{
		swap_x=x;
		x=y;
		y=swap_x;
	}
	sx=x-base_x;
	sy=y-base_y;
	//映射
	sx=sx*kx;
	sy=sy*ky;
	*xx=sx+lcd_x;
	*yy=sy+lcd_y;
}



