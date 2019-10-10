.text
.global _start

//NAND Flash地址线和数据线在一起，需要用程序来控制，才能出数据。要先把程序装载在内存 再从内存启动 
//NOR FLASH地址线和数据线分开，来了地址和控制信号，数据就出来。 直接将代码映射到内存中使用 但是这块映射的内存不可以直接写 

//所以通过向NOR FLASH映射的内存区写，然后再读，比较写成功没有，如果成功就是NAND FLASH 启动 不成功就是NOR启动，这是利用了NOR
//FLASH 的特性来判断的！



_start:
	b reset		//
	
	b do_und	//未定义指令
do_und:
	//为定义指令模式下的栈
	ldr sp,=0x34000000
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

	//跳转到重定位的地址
	ldr pc, =next
next:



	bl init
error:
	bl led1on
	.word 0xdeadc0de  /* 未定义指令 */
	bl led1off
	
	bl main
halt:
	b halt
