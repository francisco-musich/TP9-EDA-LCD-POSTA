#include"LCDHitachi.h"
#include <cstdio>

int main()
{
	basicLCD* LCD = new LCDHitachi;
	cursorPosition carlos =  LCD->lcdGetCursorPosition();

	LCD->lcdClear();
	/**LCD<<'A';
	
	*LCD << 'b';
	*LCD << 'C';*/
	unsigned char hola[156] = { "Ingresar String!" };
	*LCD << hola;
	
	LCD->lcdMoveCursorLeft();
	LCD->lcdMoveCursorLeft();
	LCD->lcdMoveCursorLeft();
	LCD->lcdMoveCursorLeft();
	LCD->lcdMoveCursorLeft();
	unsigned char hola2[156] = { "string 2" };
	*LCD << hola2;
	LCD->lcdMoveCursorLeft();
	LCD->lcdClearToEOL();
	LCD->lcdClear();
	LCD->lcdMoveCursorRight();
	LCD->lcdMoveCursorDown();
	LCD->lcdMoveCursorDown();
	LCD->lcdMoveCursorUp();
	LCD->lcdGetCursorPosition();
	getchar();
	return 0;
}