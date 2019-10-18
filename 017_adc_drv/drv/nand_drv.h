#ifndef __NAND_DRV_H_
#define __NAND_DRV_H_

extern void nand_init(void);
extern void nand_flash_test(void);
extern void nand_read(unsigned int addr, unsigned char *buf, unsigned int len);

#endif



