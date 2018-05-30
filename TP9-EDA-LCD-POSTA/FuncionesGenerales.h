#pragma once

#include "LCDHitachi.h"
#include <string>
#include <windows.h>

using namespace std;

const cursorPosition pos1 = { 0, 0 };
const cursorPosition pos2 = { 1, 0 };

void marquesina(string str, LCDHitachi& lcd, int row);
void imprimirPorcentaje(char porcentaje, LCDHitachi& lcd);
void imprimirFecha(string str, LCDHitachi& lcd);