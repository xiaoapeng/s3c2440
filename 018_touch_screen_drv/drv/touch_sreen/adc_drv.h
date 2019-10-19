#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

extern void adc_config(unsigned char pipeline);
extern int adc_read(void);


enum pipeline_e{
	AIN_0=0,
	AIN_1,
	AIN_2,
	AIN_3,
	YM,
	YP,
	XM,
	XP
};



#endif
