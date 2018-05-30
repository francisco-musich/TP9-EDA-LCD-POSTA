#include"LCDHitachi.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#include "FuncionesGenerales.h"

using namespace std;

int main()
{
	LCDHitachi LCDHitachi;
	basicLCD * LCD = &LCDHitachi;
	if (LCD->lcdInitOk())
	{
		LCD->lcdClear();


		return 0;
	}
}
