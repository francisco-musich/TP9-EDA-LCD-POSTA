#include "LCDHitachi.h"

char getADD(int cadd)
{
	unsigned char respuesta = 0x00;
	if (cadd > 16)
	{
		respuesta = (respuesta | 0x40);
		respuesta = (respuesta | (cadd - 16));
	}
	else
	{
		respuesta = respuesta | cadd;
	}
	return respuesta;
	
}


LCDHitachi::LCDHitachi()
{
	this->cadd = 1;
}


LCDHitachi::~LCDHitachi()
{
}

bool LCDHitachi::lcdInitOk()
{
	return this->initstatus;	//AGREGAR INIT STATUS EN EL PADRE
}

FT_STATUS LCDHitachi::lcdGetError()
{
	return this->errorInit;		//Agregar error en el padre
}

bool LCDHitachi::lcdClear()	//Limpia todo el display, AGREGAR VALIDACION
{
	this->sendData(LCD_CLEAR, RS_WRITE);
	this->cadd = 1;
}

bool LCDHitachi::lcdClearToEOL()
{
	if (cadd < 16)	//Si el address es menor a 16 va borrando
	{
		for (int i = cadd; i <= 16; i++)
		{
			sendData(CLEAR_CHAR, RS_WRITE);
		}
		unsigned char addsetter = (getADD(cadd))|0x80;
		sendData(addsetter, RS_WRITE);
		return true;
	}
	else 
	{
		return false;
	}
}

basicLCD& LCDHitachi::operator<<(const unsigned char c)	//Nose que tendria que ir devolviendo
{
	if (cadd < 16)
	{
		sendData(c, RS_WRITE);
		cadd++;
	}
}

//FALTA EL OTRO OPERADOR DE INSERCION

bool LCDHitachi::lcdMoveCursorUp()
{
	if (cadd > 8)
	{
		cadd -= 8;	//muevo el counter una fila arriba
		unsigned char newAddCount = (getADD(cadd)) | 0x80;
		sendData(newAddCount, RS_WRITE);
		return true;
	}
	else
	{
		return false;
	}

}

bool LCDHitachi::lcdMoveCursorDown()
{
	if (cadd < 8)
	{
		cadd += 8;	//muevo el counter una fila arriba
		unsigned char newAddCount = (getADD(cadd)) | 0x80;
		sendData(newAddCount, RS_WRITE);
		return true;
	}
	else
	{
		return false;
	}

}

bool LCDHitachi::lcdMoveCursorRight()
{
	if (cadd < 16)
	{
		cadd++;
		unsigned char newAddCount = (getADD(cadd)) | 0x80;
		sendData(newAddCount, RS_WRITE);
		return true;
	}
	else
	{
		return false;
	}
}

bool LCDHitachi::lcdMoveCursorLeft()
{
	if (cadd > 1)
	{
		cadd--;
		unsigned char newAddCount = (getADD(cadd)) | 0x80;
		sendData(newAddCount, RS_WRITE);
		return true;
	}
	else
	{
		return false;
	}
}

bool LCDHitachi::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.row <= 3 && pos.column < 32)
	{
		cadd = (pos.row) * 16 + pos.column;
		unsigned char newAddCount = (getADD(cadd)) | 0x80;
		sendData(newAddCount, RS_WRITE);
		return true;
	}
	else
	{
		return false;
	}
}

cursorPosition LCDHitachi::lcdGetCursorPosition()
{
	cursorPosition respuesta;
	respuesta.row = cadd / 16;
	respuesta.column = cadd % 16;
	return respuesta;
}



