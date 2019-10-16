#include "printfhex.h"

int puts(const char *s);
int putchar(int c);

static const char hex_tab[16]={'0','1','2','3','4','5','6','7','8','9','A'\
,'B','C','D','E','F'};

void printfhex(int vla)
{
	int i;
	unsigned char arr[8];
	for(i=0;i<8;i++)
	{
		arr[i]=vla&0xf;
		vla>>=4;
	}
	puts("0x");
	for(i=7;i>=0;i--)
	{
		putchar(hex_tab[arr[i]]);
	}
}

