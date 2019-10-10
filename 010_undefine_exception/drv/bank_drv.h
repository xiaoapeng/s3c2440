#ifndef _BANK_DRV_H_
#define _BANK_DRV_H_
#include "gpio.h"
#define TACS (13)
#define TCOS (11)
#define TACC (8)
#define TCOH (6)
#define TCAH (4)
#define TACP (2)
#define PMC	 (0)

#define TACS_MASK (3<<13)
#define TCOS_MASK (3<<11)
#define TACC_MASK (7<<8)
#define TCOH_MASK (3<<6)
#define TCAH_MASK (3<<4)
#define TACP_MASK (3<<2)
#define PMC_MASK  (3<<0)


#define BANKCONx_SET(BANKCONX,BIS_TYPE,VAL) gpio_set((BANKCONX),BIS_TYPE##_MASK,((VAL)<<BIS_TYPE))





#endif