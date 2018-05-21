#pragma once
#include"basicLCD.h"
#include "HitachiLow.h"

class LCDHitachi: public basicLCD, public HitachiLow
{
public:
	LCDHitachi();

	~LCDHitachi();

	bool lcdInitOk();

	FT_STATUS lcdGetError();
	bool lcdClear();
	bool lcdClearToEOL();
	basicLCD& operator<<(const unsigned char c);
	basicLCD& operator<<(const unsigned char * c);
	bool lcdMoveCursorUp();
	bool lcdMoveCursorDown();
	bool lcdMoveCursorRight();
	bool lcdMoveCursorLeft();
	bool lcdSetCursorPosition(const cursorPosition pos);
	cursorPosition lcdGetCursorPosition();


};

unsigned char getADD(int cadd);

