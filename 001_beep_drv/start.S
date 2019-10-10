.text
.global _start

//NAND Flash地址线和数据线在一起，需要用程序来控制，才能出数据。要先把程序装载在内存 再从内存启动 
//NOR FLASH地址线和数据线分开，来了地址和控制信号，数据就出来。 直接将代码映射到内存中使用 但是这块映射的内存不可以直接写 

//所以通过向NOR FLASH映射的内存区写，然后再读，比较写成功没有，如果成功就是NAND FLASH 启动 不成功就是NOR启动，这是利用了NOR
//FLASH 的特性来判断的！



_start:
	//关闭看门狗
	ldr r0,=0x53000000
	ldr r1,=0
	str r1,[r0]

	mov r1,#0
	ldr r0,[r1]  				//去除0地址的值
	add r0,r0,#1				//将其+1
	str r0,[r1]					//写回去
	ldr r2,[r1]					//读到r2
	ldr sp,=0x40000000+4096 	//nor 启动
	cmp r0,r2					//如果值还和写入前相等 那么就是nand启动 
	ldr sp, =4096  				//nand 启动    0地址对应
	sub r0,r0,#1				//将值减一
	str r0,[r1]					//恢复写的地址

	
	
	//ldr sp,=0x40000000+4096 	//nor 启动
	bl main
halt:
	b halt
