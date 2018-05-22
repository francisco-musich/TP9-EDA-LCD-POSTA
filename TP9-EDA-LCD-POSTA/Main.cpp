#include"LCDHitachi.h"
#include <cstdio>

int main()
{
	basicLCD* LCD;
	LCDHitachi LCDH;
	LCD = &LCDH;
	LCD->lcdClear();
	*LCD<<'A';
	getchar();
	return 0;
}