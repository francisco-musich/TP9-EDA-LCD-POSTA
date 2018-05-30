#include "LCDHitachi.h"
#include<ostream>
using namespace std;

/* FUNCION getADD*/
/*
	Funcion que transforma el cadd a un hexa para sobreescribir el adress counter
*/
unsigned char getADD(int cadd)
{
	unsigned char respuesta = 0x00;
	if (cadd >= COLUMNA)	//me fijo en que fila estoy
	{
		respuesta = (respuesta | OFFSET_ROW_DRAM);	//fila 2 entonces meto el 0x40 necesario
		respuesta = (respuesta | (cadd - COLUMNA)); //restando por 16 obteno el numero de columna le hago un or asi me queda en esa posicion
	}
	else
	{
		respuesta = respuesta | cadd;	//fila 1 entonces lo unico que hago es un or con el cadd y me deja el adress
	}
	return respuesta;
	
}


LCDHitachi::LCDHitachi()
{
	this->cadd = 1;	//inicializo counter en 1, por consigna, lel nose
	lcdUpdateCursor(); //Fuerzo al lcd a tener ese address counter
	cout << "Se ha creado el objeto LCD Hitachi" << endl;
}


LCDHitachi::~LCDHitachi()
{
}
/*Funcion lcdinitOK*/
/*
	Se fija en un dato miembro del padre ldc_low si se inicializo bien el lcd
*/
bool LCDHitachi::lcdInitOk()
{
	bool aux;
	if (status == FT_OK)	//AGREGAR INIT STATUS EN EL PADRE
	{
		aux = true;
		cout << "El lcd Inicializo correctamente" << endl;
	}
	else
	{
		aux = false;
		cout << "El lcd Inicializo correctamente" << endl;
	}
	return aux;
}
/*Funcion lcdGetErroe*/
/*
Se fija en un dato miembro del padre cual es el error de inicialiacion
*/
FT_STATUS LCDHitachi::lcdGetError()
{
	return status;
}

/*Funcion lcdClear*/
/*
Envia la instruccion para limpiar la pantalla inherente al lcd hitachi

*/
bool LCDHitachi::lcdClear()	//Limpia todo el display
{
	bool validacion;
	validacion = sendData(LCD_CLEAR, IR);	//envio la info
	cadd = 1;	//APunta siempre al siguiente no idea
	lcdUpdateCursor();	//Atucalio el cursor
	if (validacion)
	{
		cout << "Se ha limpiado la pantalla correctamente" << endl;
	}
	else
	{
		cout << "Problema al limpiar la pantalla" << endl;
	}
	return validacion;
}
/*Funcion lcdCleartoEOL*/
/*
Chequea que no se este en la ultima posicion. Envia un caracter vacio al lcd en la posicion actual hasta que se llegue al final de la linea
Luego setteo el address counter del lcd a el que originalmente tenia
*/
bool LCDHitachi::lcdClearToEOL()
{
	if (cadd < ELEMENTOS_TOTALES_AJUSTADO)	//Si el address es menor a 32 va borrando
	{
		bool validation= true;
		for (int i = cadd; (i%17!=0) && (validation); i++)	//For desde el address actual hasta la ultima posicion
		{
			validation = sendData(CLEAR_CHAR, DR); 
		}
		if (validation) //Solo vuelvo al address counter original si se enviaron todos los chars correctamente
		{
			cout << " CleartoEOL exitoso" << endl;
			lcdUpdateCursor();
		}
		else {
			cout << "CleartoEOL fallido" << endl;
		}


		return validation;
	}
	else 
	{
		cout << "CleartoEOL fallido, cursor fuera de rango" << endl;
		return false;
	}
}
/*Sobrecarga operador <<(para un char)*/
/*
Chequea que no se este en la ultima posicion. Envia el caracter deseado al lcd, incrementa el contador interno, devuelve una referencia a si mismo
*/
basicLCD& LCDHitachi::operator<<(const unsigned char c)	//Nose que tendria que ir devolviendo
{
	if ((cadd-1) <= ELEMENTOS_TOTALES/*_AJUSTADO*/)	//si estoy en los parametros imprimo
	{
		sendData(c, DR);
		cadd++;	//el address counter se actualiza solo
		lcdUpdateCursor();
	}
	else {
		cout << "Cursor fuera de rango" << endl;
	}
	return *this;
}
/*Sobrecarga operador <<(para un string)*/
/*
Chequea que el string no sea mayor a 32 caracteres, si lo es se adapta. Luego imprime hasta que se acabe el display o hasta que se acabe el string
*/
basicLCD& LCDHitachi::operator<<(const unsigned char* c)	//Aca asumo groseramente que lo unico que me pueden mandar son asciis
{
	if (cadd <= ELEMENTOS_TOTALES_AJUSTADO)
	{
		string recieved = (const char *)c;	//Lo hago un string por que los arreglos me ponen triste :(
		int stringIndicator = 0;	//NOse si poner size_t me resuelve algo
		int stringSize = (int)recieved.size();
		if (stringSize > ELEMENTOS_TOTALES)	//Chequeo si el string tiene mas de 32 caracteres
		{
			stringIndicator = stringSize - ELEMENTOS_TOTALES + cadd;	//Si tiene mas de 32 utilizo un indice corrido, sera el tamano del string menos 32(ultimos 32 caracteres)	
		}
		for (; cadd < ELEMENTOS_TOTALES && (stringIndicator <= stringSize - 1); stringIndicator++)	//Imprimo los caracteres hasta que se acabe el string o el lugar en el lcd, no hay problema en modificar directamente el cadd
		{
			unsigned char infotoSend = c[stringIndicator];
			sendData(infotoSend, DR);
			cadd++;
			lcdUpdateCursor();
		}
	}
	else
	{
		cout << "Cursor fuera de rango (<<string)" << endl;
	}
	return *this;
}



/*Funcion lcdMoveCursorUp*/
/*
Chequea que el cursor este en la segunda fila. Le resta el tamano de la fila y settea el nuevo address counter en el lcd
*/
bool LCDHitachi::lcdMoveCursorUp()
{
	if (cadd >= COLUMNA)
	{
		cadd -= COLUMNA;	//muevo el counter una fila arriba
		lcdUpdateCursor();
		return true;
	}
	else
	{
		cout << "No se puede mover el cursor para arriba, se esta en la primera fila" << endl;
		return false;
	}

}
/*Funcion lcdMoveCursorDown*/
/*
Idem a metodo anterior. La diferencia es que se fija que este en la fila superior y luego incrementa en el tamano de fila
*/
bool LCDHitachi::lcdMoveCursorDown()
{
	if (cadd < COLUMNA)
	{
		cadd += COLUMNA;	//muevo el counter una fila arriba
		lcdUpdateCursor();
		return true;
	}
	else
	{
		cout << "No se puede mover el cursor para abajo, se esta en la ultima fila" << endl;
		return false;
	}

}
/*Funcion lcdMOveCursorRight*/
/*
Similar a lo anterior, solo que ahora chequeo no estar en la ultima posicion
*/
bool LCDHitachi::lcdMoveCursorRight()
{
	if (cadd < ELEMENTOS_TOTALES)
	{
		cadd++;	//incremento en una posicion el counter
		lcdUpdateCursor();
		return true;
	}
	else
	{
		cout << "No se puede mover el cursor para la derecha, se esta en la ultima posicion" << endl;
		return false;
	}
}
/*Funcion lcdMoveCursorLeft*/
/*
Ahora chequeo no estar en la primera posicion
*/
bool LCDHitachi::lcdMoveCursorLeft()
{
	if (cadd > 1)
	{
		cadd--;
		lcdUpdateCursor();
		return true;
	}
	else
	{
		cout << "No se puede mover el cursor para la izquierda, se esta en la primera posicion" << endl;
		return false;
	}
}
/*Funcion lcdSetCursorPosition*/
/*
recibo una estructura cursorPosition. valido que la fila y columna enviadas sean correctas.
Luego creo el cadd con esa informacion, lo transformo a hexa y lo envio al lcd
*/

bool LCDHitachi::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.row < FILAS && pos.column < COLUMNA)	//validacion
	{
		cadd = ((pos.row) * COLUMNA + pos.column)+1;	//creacion de cadd con pos
		lcdUpdateCursor();
		return true;
	}
	else
	{
		cout << "Parametros enviados a lcdSetCursorPosition incorrectos. Row tiene que ser<2 y Column < 16 " << endl;
		return false;
	}
}
/*Funcion lcdGetCursorPosition*/
/*
Devuelvo a partir del cadd una estructura con la posicion y filas correctas
*/
cursorPosition LCDHitachi::lcdGetCursorPosition()
{
	cursorPosition respuesta;
	respuesta.row = cadd / COLUMNA;	//me fijo en que fila estoy
	respuesta.column = cadd % COLUMNA;	//en que columna
	return respuesta;
}

void LCDHitachi::lcdUpdateCursor()
{
	if ((cadd-1) <= ELEMENTOS_TOTALES)
	{
		unsigned char newAddCount = (getADD(cadd - 1)) | ADDRESS_COUNT_SET_MASK; //transformacion hexa de cadd
		sendData(newAddCount, IR);	//setteo nuevo address counter
	}
}



