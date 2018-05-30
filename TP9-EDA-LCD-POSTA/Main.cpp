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
	LCDHitachi LCDHit;					//Simplemente se crea un lcd especifico y luego las funciones se llaman
	FuncionesGenerales Func(LCDHit);	//a partir del basicLCD

	if (Func.LCD->lcdInitOk())
	{
		string str = "hola";

		Func.LCD->lcdClear();
		Func.imprimirPorcentaje(35);
		Func.marquesina(str, 0);


		return 0;
	}
}
