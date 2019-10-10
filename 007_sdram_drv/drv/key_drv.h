#ifndef _KEY_DRV_H_
#define _KEY_DRV_H_

enum key_user{
S2=0,
S3,
S4,
};
struct key_flag{
	int flag;//按键状态  
	//int event;//事件状态 1 为按下事件
	int count; //按下时长
	unsigned int GPFXDAT;
	int pin;
};
extern struct key_flag key[];
#define KEY_S2 (0x1)
#define KEY_S3 (0x2)
#define KEY_S4 (0x4)

extern int key_config(void);
extern int key_read(int EvenFlag);



#endif
