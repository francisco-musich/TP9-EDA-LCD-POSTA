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
	LCD->lcdMoveCursorRight();
	LCD->lcdMoveCursorDown();
	LCD->lcdMoveCursorUp();
	LCD->lcdGetCursorPosition();
	getchar();
	return 0;
}