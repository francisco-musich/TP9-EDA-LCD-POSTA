#include "FuncionesGenerales.h"



void marquesina(string str, LCDHitachi& lcd, int row)
{
	string blankSpace("                ");   //Espacio LCD sin nada bien tumbero!!!
	str = blankSpace + str + blankSpace;
	int sizeStr = str.size();

	unsigned char * pdm = (unsigned char *)str.c_str();

	for (int j = 0; j <= (sizeStr-16); j++)
	{
		if(!row)
			lcd.lcdSetCursorPosition(pos1);
		else
			lcd.lcdSetCursorPosition(pos2);

		for (int i = j; i < (16+j); i++)
		{
			lcd << str[i];
		}
		Sleep(100);
	}
}

void imprimirPorcentaje(char porcentaje, LCDHitachi& lcd)
{
	string blankSpace = "      ";
	string simpleBlank = " ";
	string simbPorcentaje = "%";
	std::string str = blankSpace + to_string(porcentaje) + simpleBlank + simbPorcentaje + blankSpace;

	unsigned char * pdm = (unsigned char *)str.c_str();

	if (lcd.lcdSetCursorPosition(pos2))
	{
		lcd << pdm;
	}
}

void imprimirFecha(string str, LCDHitachi& lcd)
{
	unsigned char * pdm = (unsigned char *)str.c_str();

	if (lcd.lcdSetCursorPosition(pos1))
	{
		lcd << pdm;
	}
}