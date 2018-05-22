#include"LCDHitachi.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main()
{
	basicLCD* LCD = new LCDHitachi;
	if (LCD->lcdInitOk())
	{

		LCD->lcdClear();

		string input = "";
		bool run = true;

		// How to get a string/sentence with spaces
		cout << "Bienvenido al Controlador del LCD" << endl << "Introduzca el string deseado. Las acciones disponible son las siguientes" << endl;
		cout << "Seguido de un '`'" << endl << "L= mueve cursor izquierda" << endl << "D=Derecha " << endl << "U= Arriba " << endl << "D= Down " << endl << "Cl= CLear " << endl << " ClEOL = Clear to EOL " << endl;
		cout << "CurPos = imprime la fila y columna actual de cursor" << endl << "Exit = Termina el programa" << endl;
		while (run)
		{
			getline(cin, input);

			if (input == "`R"||input == "`r")
			{
				LCD->lcdMoveCursorRight();
			}
			else if (input == "`L"||input=="`l")
			{
				LCD->lcdMoveCursorLeft();
			}
			else if (input == "`D"||input == "`d")
			{
				LCD->lcdMoveCursorDown();
			}
			else if (input == "`U"||input == "`u")
			{
				LCD->lcdMoveCursorUp();
			}
			else if (input == "`Cl")
			{
				LCD->lcdClear();
			}
			else if (input == "`ClEOL")
			{
				LCD->lcdClearToEOL();
			}
			else if (input == "`CurPos")
			{
				cursorPosition carlos = LCD->lcdGetCursorPosition();
				cout << "Fila = " << carlos.row << endl;
				cout << "Columna = " << carlos.column << endl;
			}
			else if (input == "`Exit"||input =="`exit")
			{
				run = false;
			}
			else
			{
				const unsigned char* puntero_de_mierda = (const unsigned char*)input.c_str();
				*LCD << puntero_de_mierda;
			}
		}
		LCD->lcdClear();
	}

	else
	{
		cout << "El LCD no se ha cargado correctamtente" << endl;
		LCD->lcdGetError(); //NOSE
	}

cout << "EL programa ha finalizado, oprima enter para salir" << endl;

	getchar();
	delete LCD;
	return 0;
}
