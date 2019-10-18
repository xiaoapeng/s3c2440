#include "start.h"
.text
#pragma pack(4)
.global _start

//NAND Flash地址线和数据线在一起，需要用程序来控制，才能出数据。要先把程序装载在内存 再从内存启动 
//NOR FLASH地址线和数据线分开，来了地址和控制信号，数据就出来。 直接将代码映射到内存中使用 但是这块映射的内存不可以直接写 

//所以通过向NOR FLASH映射的内存区写，然后再读，比较写成功没有，如果成功就是NAND FLASH 启动 不成功就是NOR启动，这是利用了NOR
//FLASH 的特性来判断的！



_start:
	b reset			 //
	ldr pc,=do_und	 //未定义指令
	ldr pc,=do_swi   //swi异常
	b halt			 /* vector 0x0c : prefetch aboot */
	b halt			 /* vector 0x10 : data abort */
	b halt			 /* vector 0x14 : reserved */
	ldr pc,=do_irq	 /* vector 0x18 : irq */
	b halt			 /* vector 0x1c : fiq */

do_irq:
	//为定义指令模式下的栈
	ldr sp,= IRQ_SRACK_ADDR
	//先存后减 为啥要保存r0-r12参考手册
	sub lr,lr,#4
	stmdb sp!,{r0-r12,lr}
	//保存lr值  ://r4的值不会被c语言函数所改变,
	
	bl handle_irq
	
	//恢复现场
	ldmia sp!,{r0-r12,pc}^  //"^"会把spsr的值恢复到cpsr中

do_swi:
	//为定义指令模式下的栈
	ldr sp,= SVC_STACK_ADDR
	//先存后减 为啥要保存r0-r12参考手册
	stmdb sp!,{r0-r12,lr}
	//保存lr值  ://r4的值不会被c语言函数所改变,
	mov r4,lr
	//传递参数
	mrs r0,cpsr
	ldr r1,=swi_string
	bl printException
	sub r0,r4,#0x04
	bl printSWIVal
	
	//恢复现场
	ldmia sp!,{r0-r12,pc}^  //"^"会把spsr的值恢复到cpsr中
swi_string:
	.string "do_svc !!!!!!!!"
.align 4
do_und:
	//为定义指令模式下的栈
	ldr sp,= UND_STACK_ADDR
	//先存后减 为啥要保存r0-r12参考手册
	stmdb sp!,{r0-r12,lr}
	
	//传递参数
	mrs r0,cpsr
	ldr r1,=und_string
	bl printException
	//恢复现场
	ldmia sp!,{r0-r12,pc}^  //"^"会把spsr的值恢复到cpsr中

und_string:
	.string "do_und !!!!!!!!"
.align 4
reset:
	//关闭看门狗
	ldr r0,=0x53000000
	ldr r1,=0
	str r1,[r0]
	
	//####设置时钟频率####
	//1.时钟锁定时间 LOCKTIME(addr:0x4C000000) = 0xffff ffff 
	ldr r0,=0x4C000000
	ldr r1,=0xffffffff
	str r1,[r0]
	//2.设置    如果MPLL为12MHZ     FCLK:HCLK:PCLK = 400MHZ:100MHZ:50MHZ 
	//CLKDIVN(addr:0x4C000014) =0x5
	ldr r0,=0x4C000014
	ldr r1,=0x5
	str r1,[r0]
	//3.HDIVN不为0 此时设置CPU为异步工作模式 才能使cpu工作在FCLK的时钟频率下
	MRC  p15,0,r0,c1,c0,0 
	ORR  r0,r0,#0xc0000000 
	MCR  p15,0,r0,c1,c0,0 
	//设置MPLL MPLLCON(  0x4C000004) = (92<<12)|(1<<4)|(1<<0)
	ldr r0,=0x4C000004
	ldr r1,=(92<<12)|(1<<4)|(1<<0)
	str r1,[r0]
	//一但设置pll,就会锁定locktime 直到锁定完成pll稳定输出
	//cpu运行到新的fclk上
	
	
	//为不同的启动方式来设置栈
	mov r1, #0
	ldr r0, [r1] /* 读出原来的值备份 */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? 如果相等表示是NAND启动 */
	ldr sp, =0x40000000+4096 /* 先假设是nor启动 */
	moveq sp, #4096  /* nand启动 */
	streq r0, [r1]   /* 恢复原来的值 */
	
	//进行代码重定位
	bl relocation

	

	//进入usr模式
	mrs r0,cpsr		 	//cpsr
	bic	r0,r0,#0xf	 	//m4-m0为0b10000,进入usr模式
	bic	r0,r0,#(1<<7)	//使能中断 
	msr cpsr,r0
	
	//设置用户栈
	ldr sp,=USR_STACK_ADDR
	//跳转到重定位的地址
	ldr pc, =next
next:

	
	bl init


	bl led1on
	.word 0xdeadc0de  /* 未定义指令 */
	bl led1off
	swi 0x123
	
	


	
	bl main
halt:
	b halt
