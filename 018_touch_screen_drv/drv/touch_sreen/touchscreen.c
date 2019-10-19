#include	"gpio.h"
#include "touchscreen.h"
#include "int.h"

#define ADC_INT_BIT (10)
#define TC_INT_BIT  (9)

#define INT_ADC_TC   (31)


/* ADCTSC's bits */
#define WAIT_PEN_DOWN    (0<<8)
#define WAIT_PEN_UP      (1<<8)

#define YM_ENABLE        (1<<7)
#define YM_DISABLE       (0<<7)

#define YP_ENABLE        (0<<6)
#define YP_DISABLE       (1<<6)

#define XM_ENABLE        (1<<5)
#define XM_DISABLE       (0<<5)

#define XP_ENABLE        (0<<4)
#define XP_DISABLE       (1<<4)

#define PULLUP_ENABLE    (0<<3)
#define PULLUP_DISABLE   (1<<3)

#define AUTO_PST         (1<<2)

#define WAIT_INT_MODE    (3)
#define NO_OPR_MODE      (0)

static volatile int g_ts_timer_enable = 0;


void enter_wait_pen_down_mode(void)
{
	dgpio(ADCTSC) = WAIT_PEN_DOWN | PULLUP_ENABLE | YM_ENABLE | YP_DISABLE | XP_DISABLE | XM_DISABLE | WAIT_INT_MODE;
}

void enter_wait_pen_up_mode(void)
{
	dgpio(ADCTSC) = WAIT_PEN_UP | PULLUP_ENABLE | YM_ENABLE | YP_DISABLE | XP_DISABLE | XM_DISABLE | WAIT_INT_MODE;
}
void enter_auto_measure_mode(void)
{
	dgpio(ADCTSC) = AUTO_PST | NO_OPR_MODE;
}
static void ts_timer_enable(void)
{
	g_ts_timer_enable = 1;
}


static void ts_timer_disable(void)
{
	g_ts_timer_enable = 0;
}

static int get_status_of_ts_timer(void)
{
	return g_ts_timer_enable;
}

void Isr_Tc(void)
{
	//printf("ADCUPDN = 0x%x, ADCDAT0 = 0x%x, ADCDAT1 = 0x%x, ADCTSC = 0x%x\n\r", ADCUPDN, ADCDAT0, ADCDAT1, ADCTSC);
	
	if (dgpio(ADCDAT0) & (1<<15))
	{
		printf("pen up\n\r");
		//等待按下中断
		enter_wait_pen_down_mode();
	}
	else	
	{
		printf("pen down\n\r");

		/* 进入"等待触摸笔松开的模式" */
		enter_wait_pen_up_mode();
		dgpio(ADCCON) |= (1<<0);
	}
}
void Isr_Adc(void)
{
	int x = dgpio(ADCDAT0);
	int y = dgpio(ADCDAT1);
	//printf("进入ADC\r\n");
	if (!(x & (1<<15))) /* 如果仍然按下才打印 */
	{
		x &= 0x3ff;
		y &= 0x3ff;
		
		printf("x = %08d, y = %08d\n\r", x, y);

		/* 启动定时器以再次读取数据 */
		ts_timer_enable();
		enter_wait_pen_up_mode();
	}
	else
	{
		//不再adc不在读取
		ts_timer_disable();
		//进入等待按下模式
		enter_wait_pen_down_mode();
	}
}

//中断处理函数
void AdcTsIntHandle(void)
{
	if (dgpio(SUBSRCPND) & (1<<TC_INT_BIT))  /* 如果是触摸屏中断 */
		Isr_Tc();

	if (dgpio(SUBSRCPND) & (1<<ADC_INT_BIT))  /* ADC中断 */
		Isr_Adc();


	//清中断
	dgpio(SUBSRCPND) = (1<<TC_INT_BIT) | (1<<ADC_INT_BIT);
}

void adc_ts_int_init(void)
{
	//清次级源挂起寄存器
	dgpio(SUBSRCPND) = (1<<TC_INT_BIT) | (1<<ADC_INT_BIT);

	/* 注册中断处理函数 */
	register_irq(INT_ADC, AdcTsIntHandle);	

	/* 使能中断 */
	dgpio(INTSUBMSK) &= ~((1<<ADC_INT_BIT) | (1<<TC_INT_BIT));
	//INTMSK    &= ~(1<<INT_ADC_TC);
}


//该函数会在定时器中断中每10毫秒被调用一次
void touchscreen_timer_irq(void)
{
	/* 如果触摸屏仍被按下, 进入"自动测量模式", 启动ADC */
	if (get_status_of_ts_timer() == 0)
		return;

	if (dgpio(ADCDAT0) & (1<<15)) /* 如果松开 */
	{
		ts_timer_disable();
		enter_wait_pen_down_mode();
		return;
	}
	else  /* 按下状态 */
	{
		/* 进入"自动测量"模式 */
		enter_auto_measure_mode();

		/* 启动ADC */
		dgpio(ADCCON) |= (1<<0);
	}
}

void adc_ts_reg_init(void)
{
	/* [15] : ECFLG,  1 = End of A/D conversion
	 * [14] : PRSCEN, 1 = A/D converter prescaler enable
	 * [13:6]: PRSCVL, adc clk = PCLK / (PRSCVL + 1)
	 * [5:3] : SEL_MUX, 000 = AIN 0
	 * [2]   : STDBM
	 * [0]   : 1 = A/D conversion starts and this bit is cleared after the startup.
	 */
	dgpio(ADCCON) = (1<<14) | (49<<6) | (0<<3);
	dgpio(ADCDLY) = 60000;	
}


void touchscreen_init(void)
{
	/* 设置触摸屏接口:寄存器 */
	adc_ts_reg_init();

	//printf("ADCUPDN = 0x%x, SUBSRCPND = 0x%x, SRCPND = 0x%x\n\r", ADCUPDN, SUBSRCPND, SRCPND);

	/* 设置中断 */
	adc_ts_int_init();
	/*添加至定时器执行函数的列表，且设置为10毫秒执行一次*/
	add_list(10,touchscreen_timer_irq);
	/* 让触摸屏控制器进入"等待中断模式" */
	enter_wait_pen_down_mode();
}





