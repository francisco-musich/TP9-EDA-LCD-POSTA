#include"LCDHitachi.h"
#include <cstdio>

int main()
{
	basicLCD* LCD;
	LCDHitachi LCDH;
	LCD = &LCDH;
	LCD->lcdClear();
	*LCD<<'A';
	*LCD << 'b';
	*LCD << 'C';
	LCD->lcdClear();
	LCD->lcdMoveCursorDown();
	LCD->lcdGetCursorPosition();
	getchar();
	return 0;
}